<?php

/**
 * @file
 * Provides internal API for page cache flushes.
 */

class ExpireAPI {

  /**
   * Executes internal or external cache expiration.
   *
   * @param $urls
   *   List of internal or external urls that should be expired.
   *
   * @param $object_type
   *  Name of object type ('node', 'comment', 'user', etc).
   *
   * @param $object
   *   Object (node, comment, user, etc) for which expiration is executes.
   *
   * @param $absolute_urls_passed
   *   Indicates whether absolute URLs or internal paths were passed.
   */
  public static function executeExpiration($urls, $object_type = '', $object = NULL, $absolute_urls_passed = FALSE) {

    // Allow other modules to modify the list prior to expiring.
    drupal_alter('expire_cache', $urls, $object_type, $object, $absolute_urls_passed);

    // Nothing to expire, so exit.
    if (empty($urls)) {
      return;
    }

    // Check if base urls should be included.
    $include_base_url = variable_get('expire_include_base_url', EXPIRE_INCLUDE_BASE_URL);

    // Absolute urls may be passed from drush command or from rules action.
    if ($absolute_urls_passed) {

      // If was passed array with absolute URLs, we need to add to them
      // internal path first, because some external cache tools (like Varnish)
      // works only with internal paths.
      $urls = self::addInternalPaths($urls);

      // If base url should not be include (for example, for Varnish or Acquia Purge),
      // then remove it from values.
      if (!$include_base_url) {
        $urls = drupal_map_assoc(array_keys($urls));
      }

      // We not allow using wildcards for absolute urls.
      $wildcards = array_fill_keys(array_keys($urls), FALSE);
    }
    else {

      // Define a language code. It will be used to define path aliases.
      $langcode = NULL;
      if (!empty($object_type) && !empty($object)) {
        if(function_exists('entity_language')){
          $langcode = entity_language($object_type, $object);
        }
        else{
          $info = entity_get_info($object_type);
          if (isset($info['language callback']) && function_exists($info['language callback'])) {
            $langcode = $info['language callback']($object_type, $object);
          }
          elseif (!empty($info['entity keys']['language']) && isset($object->{$info['entity keys']['language']})) {
            $langcode = $object->{$info['entity keys']['language']};
          }
          else {
            $langcode = NULL;
          }
        }
      }

      // Get a language of current object (if exists). We need to respect cases
      // when entities having one site language has been expired from another
      // site locale. For this purpose we always have to pass a proper language
      // key/object to get a correct URL of entity's language.
      if ($langcode == LANGUAGE_NONE) {
        $language = language_default();
        $langcode = $language->language;
      }
      else {
        $languages = language_list();
        $language = isset($languages[$langcode]) ? $languages[$langcode] : NULL;
      }

      // Adds paths aliases, defines wildcards, etc.
      list($urls, $wildcards) = self::processInternalPaths($urls, $langcode);

      // If base site url should be included, then simply add it to the internal paths.
      if ($include_base_url) {
        foreach ($urls as $internal_path) {
          $urls[$internal_path] = url($internal_path, array('absolute' => TRUE, 'alias' => TRUE, 'language' => $language));
        }
      }
    }

    // Latest possibility to change urls that should be expired.
    drupal_alter('expire_urls', $urls, $object_type, $object);

    // Write some debug information.
    self::debugLog($urls, $wildcards, $object_type);

    // Execute internal or external expiration.
    $status = variable_get('expire_status', EXPIRE_STATUS_DISABLED);
    if ($status == EXPIRE_STATUS_ENABLED_INTERNAL) {
      self::executeInternalExpiration($urls, $wildcards);
    }
    elseif ($status == EXPIRE_STATUS_ENABLED_EXTERNAL) {
      self::executeExternalExpiration($urls, $wildcards, $object_type, $object);
    }
  }

  /**
   * Execute internal urls expiration.
   * Calls cache_clear_all().
   *
   * @param $urls
   *   List of absolute urls that should be flushed.
   *
   * @param $wildcards
   *   List of paths and its wildcard flushes.
   */
  protected static function executeInternalExpiration($urls, $wildcards) {
    foreach ($urls as $internal_path => $absolute_url) {

      // Check if wildcard is enabled for this URL.
      $wildcard = !empty($wildcards[$internal_path]);

      // Clear cached page data.
      cache_clear_all($absolute_url, 'cache_page', $wildcard);
    }
  }

  /**
   * Executes hook_cache_expire().
   *
   * It allows other modules to implement custom login for cache expiration.
   *
   * @param $urls
   *   List of absolute urls that should be flushed.
   *
   * @param $wildcards
   *   List of paths and its wildcard flushes.
   *
   * @param $object_type
   *  Name of object type ('node', 'comment', 'user', etc).
   *
   * @param $object
   *   Object (node, comment, user, etc) for which expiration is executes.
   */
  protected static function executeExternalExpiration($urls, $wildcards, $object_type, $object) {
    $modules = module_implements('expire_cache');
    foreach ($modules as $module) {
      module_invoke($module, 'expire_cache', $urls, $wildcards, $object_type, $object);
    }
  }

  /**
   * Find all taxonomy terms in the entity fields and build urls for them.
   *
   * @param $entity
   *   Entity object.
   *
   * @param $entity_type
   *   Type of entity.
   *
   * @return array
   *   Term urls that should be flushed.
   */
  public static function expireTermPages($entity, $entity_type) {

    $terms = array();
    list($id, $vid, $bundle_name) = entity_extract_ids($entity_type, $entity);
    $field_instances = field_info_instances($entity_type, $bundle_name);

    foreach ($field_instances as $field_name => $field_instance) {

      // Load information about field.
      $field_info = field_info_field($field_name);

      if ($field_info['type'] == 'taxonomy_term_reference') {
        $new_terms = field_get_items($entity_type, $entity, $field_name);
        if (is_array($new_terms) && !empty($new_terms)) {
          $terms = array_merge($new_terms, $terms);
        }
        $old_terms = !empty($entity->original) ? field_get_items($entity_type, $entity->original, $field_name) : array();
        if (is_array($old_terms) && !empty($old_terms)) {
          $terms = array_merge($old_terms, $terms);
        }
      }
    }

    $urls = array();
    foreach ($terms as $term) {
      $urls['term-' . $term['tid']] = 'taxonomy/term/' . $term['tid'];
    }

    return $urls;
  }

  /**
   * Find all entity references in fields and build urls for them.
   *
   * @param object $entity
   *   Entity object.
   * @param string $entity_type
   *   Type of entity.
   * @param bool $traverse_field_collection
   *   (optional) Whether or not to traverse references from field collections
   *   attached to this entity. Defaults to FALSE.
   *
   * @return array
   *   Entity references' urls that should be flushed.
   */
  public static function expireReferences($entity, $entity_type, $traverse_field_collection = FALSE) {

    $field_references = array();

    list($id, $vid, $bundle_name) = entity_extract_ids($entity_type, $entity);

    // Get all fields from current entity type.
    $field_instances = field_info_instances($entity_type, $bundle_name);

    // Gather references across field_collections.
    $field_collection_items = array();
    foreach ($field_instances as $field_name => $field_instance) {

      // Load information about field.
      $field_info = field_info_field($field_name);

      // Collect field collection items.
      if ($traverse_field_collection && $field_info['type'] == 'field_collection') {
        $items = field_get_items($entity_type, $entity, $field_name);
        if (!empty($items) && is_array($items)) {
          foreach ($items as $item) {
            $field_collection_items[] = $item['value'];
          }
        }
      }

      if (in_array($field_info['type'], array('node_reference', 'user_reference', 'entityreference'))) {

        if (in_array($field_info['type'], array('node_reference', 'user_reference'))) {
          $field_value_key = $field_info['type'] == 'node_reference' ? 'nid' : 'uid';
          $field_entity_type = $field_info['type'] == 'node_reference' ? 'node' : 'user';
        }
        else {
          $field_value_key = 'target_id';
          $field_entity_type = $field_info['settings']['target_type'];
        }

        // Get new values from reference field.
        $new_references = field_get_items($entity_type, $entity, $field_name);

        // Get old values from reference field.
        $old_references = !empty($entity->original) ? field_get_items($entity_type, $entity->original, $field_name) : array();

        $references = array();
        if (!empty($new_references) && is_array($new_references)) {
          $references = array_merge($references, $new_references);
        }
        if (!empty($old_references) && is_array($old_references)) {
          $references = array_merge($references, $old_references);
        }

        foreach ($references as $reference) {
          $field_entity_id = isset($reference[$field_value_key]) ? $reference[$field_value_key] : FALSE;
          $field_references[$field_entity_type . $field_entity_id] = array(
            'entity_type' => $field_entity_type,
            'entity_id' => $field_entity_id,
          );
        }

      }
    }

    // Collect urls of referenced entities.
    $urls = array();
    foreach ($field_references as $field_reference) {

      // Load entity.
      $field_entity = _expire_load_single_entity($field_reference['entity_type'], $field_reference['entity_id']);
      if (empty($field_entity)) {
        continue;
      }

      // Get entity uri;
      $field_entity_uri = entity_uri($field_reference['entity_type'], $field_entity);
      if (empty($field_entity_uri['path'])) {
        continue;
      }

      $urls['reference-' . $field_reference['entity_type'] . '-' . $field_reference['entity_id']] = $field_entity_uri['path'];
    }

    // Traverse gathered field collections.
    if ($field_collection_items) {
      foreach (field_collection_item_load_multiple($field_collection_items) as $field_collection_item) {
        $field_collection_urls = ExpireAPI::expireReferences($field_collection_item, 'field_collection_item');
        $urls = array_merge($urls, $field_collection_urls);
      }
    }

    return $urls;
  }

  /**
   * Create expiration urls for custom pages.
   *
   * @param $pages
   *   Unformated string from user input raw.
   *
   * @param $token_options
   *   Options for token replacements.
   *
   * @return array
   *   List of custom urls that should be flushed.
   */
  public static function expireCustomPages($pages, $token_options) {

    $urls = array();

    $pages = explode("\n", $pages);
    foreach ($pages as $index => $page) {
      $page = trim($page);
      if (!empty($page)) {

        // Replace only urls with tokens.
        if (token_scan($page)) {
          $page = token_replace($page, $token_options);
        }

        $urls['custom-' . $index] = $page;
      }
    }

    return $urls;
  }

  /**
   * Return urls for a front page.
   */
  public static function getFrontPageUrls() {
    $urls = array();
    $urls['front'] = '';
    $urls['front-path'] = variable_get('site_frontpage', 'node');
    return $urls;
  }

  /**
   * Add internal path as a keys to array with absolute urls.
   *
   * @param $absolute_urls
   *   Array with absolute urls.
   *
   * @return array
   *   Array, where key is internal path, and value - absolute url.
   */
  protected static function addInternalPaths($absolute_urls) {

    $urls = array();
    $base_path = url('<front>', array('absolute' => TRUE));
    foreach ($absolute_urls as $absolute_url) {
      if (strpos($absolute_url, $base_path) === 0) {
        $internal_path = substr($absolute_url, strlen($base_path));
        $urls[$internal_path] = $absolute_url;
      }
    }

    return $urls;
  }

  /**
   * Looks for aliases and wildcards in internal paths.
   * If finds some - add to an array with expiration paths.
   *
   * @param $internal_paths
   *   Array of internal paths.
   *
   * @param null $langcode
   *   Language code of object that is expiring.
   *
   * @return array
   */
  protected static function processInternalPaths($internal_paths, $langcode = NULL) {

    $urls = array();
    $wildcards = array();

    foreach ($internal_paths as $path) {
      $wildcard = FALSE;

      // Every URL may contain |wildcard suffix, so we should check this.
      $path_parts = explode('|', $path);
      if (sizeof($path_parts) > 1 && $path_parts[sizeof($path_parts) - 1] == 'wildcard') {
        $wildcard = TRUE;
        array_pop($path_parts); // Remove 'wildcard' from path.
        $path = implode('|', $path_parts);
      }

      // Collect array with information about expired URLs and its wildcards.
      $urls[$path] = $path;
      $wildcards[$path] = $wildcard;

      // Don't process empty pass, because otherwise drupal will return us
      // alias for the current page. And that is not what we actually want.
      if ($path == NULL) {
        continue;
      }

      // Get the path alias for this path, and add it to the array if one was
      // found.
      $alias = drupal_get_path_alias($path, $langcode);
      if ($alias != $path) {
        $urls[$alias] = $alias;
        $wildcards[$alias] = $wildcard;
      }
    }

    return array($urls, $wildcards);
  }

  /**
   * Log debug information.
   *
   * @param $absolute_urls
   * @param $wildcards
   * @param $object_type
   */
  protected static function debugLog($absolute_urls, $wildcards, $object_type) {

    $debug = variable_get('expire_debug', EXPIRE_DEBUG_DISABLED);
    if (empty($debug)) {
      return;
    }

    $output_urls = array();
    foreach ($absolute_urls as $internal_path => $url) {
      $wildcard = !empty($wildcards[$internal_path]) ? 'true' : 'false';
      $output_urls[] = t('URL: @url', array('@url' => check_url($url)));
      $output_urls[] = t('Wildcard: @wildcard', array('@wildcard' => $wildcard));
      $output_urls[] = t('Expired object: @type', array('@type' => $object_type ? $object_type : '(none)'));
      $output_urls[] = '--------';
    }

    // Log debug message in watchdog.
    $message = t('Expiration was executed for the next URLs: !urls', array('!urls' => theme('item_list', array('items' => $output_urls))));
    watchdog('expire', $message, array(), WATCHDOG_DEBUG);

    // For development might be useful to print info on screen.
    if ($debug == EXPIRE_DEBUG_FULL) {
      drupal_set_message($message);
    }
  }

}
