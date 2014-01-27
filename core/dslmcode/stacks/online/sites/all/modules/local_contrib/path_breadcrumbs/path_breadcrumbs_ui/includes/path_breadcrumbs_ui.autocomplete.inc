<?php

/**
 * @file
 * Path breadcrumbs UI autocomplete.
 */

class PathBreadcrumbsUIAutocomplete {

  protected static $context_keywords = array();

  public static function processAutocomplete($string, $context_keywords, $raw_keywords = array()) {

    // Remove selector from search string.
    if (drupal_substr($string, 0, 1) == '%') {
      $string = drupal_substr($string, 1);
    }

    // Apply site information to contexts.
    self::$context_keywords = $context_keywords + array('site' => 'site');

    // Remove the last part as it might be unfinished.
    $parts = explode(':', $string);
    $last_part = array_pop($parts);
    $selector = implode(':', $parts);

    // Wrap entity in metadata wrapper.
    $wrapper = PathBreadcrumbsUIAutocomplete::applyDataSelector($selector, self::$context_keywords);

    $result = array();
    if ($selector && $wrapper) {
      $result = PathBreadcrumbsUIAutocomplete::matchDataSelector($wrapper, $selector . ':', 0);
    }
    elseif (!$selector) {
      $result = PathBreadcrumbsUIAutocomplete::matchDataSelector(PathBreadcrumbsUIAutocomplete::applyCurrentVariables(self::$context_keywords), '', 0);
      // Add custom keywords in first autocomplete level.
      $result += $raw_keywords;

    }

    return PathBreadcrumbsUIAutocomplete::processResultData($result, $last_part, $string);
  }


  public static function applyDataSelector($selector, $context_keywords) {
    $parts = explode(':', str_replace('-', '_', $selector), 2);

    if (isset($context_keywords[$parts[0]])) {

      // Wrap required entity with metadata wrapper.
      $context_type = $context_keywords[$parts[0]];
      $info = PathBreadcrumbsUIAutocomplete::getEntityInfo($context_type);
      $wrapper = entity_metadata_wrapper($context_type, NULL, $info);

      if (count($parts) > 1 && $wrapper instanceof EntityMetadataWrapper) {
        try {
          foreach (explode(':', $parts[1]) as $name) {
            if ($wrapper instanceof EntityListWrapper || $wrapper instanceof EntityStructureWrapper) {
              $wrapper = $wrapper->get($name);
            }
            else {
              return FALSE;
            }
          }
        }
          // In case of an exception or we were unable to get a wrapper, return FALSE.
        catch (EntityMetadataWrapperException $e) {
          return FALSE;
        }
      }
    }

    return isset($wrapper) ? $wrapper : FALSE;
  }

  /**
   * Returns matching data variables or properties for the given info and the to
   * be configured parameter.
   *
   * @param $source
   *   Either an array of info about available variables or a entity metadata
   *   wrapper.
   * @param $prefix
   *   An optional prefix for the data selectors.
   * @param $recursions
   *   The number of recursions used to go down the tree. Defaults to 2.
   * @param $suggestions
   *   Whether possibilities to recurse are suggested as soon as the deepest
   *   level of recursions is reached. Defaults to TRUE.
   *
   * @return array
   *  An array of info about matching variables or properties that match, keyed
   *  with the data selector.
   */
  public static function matchDataSelector($source, $prefix = '', $recursions = 2, $suggestions = TRUE) {

    $matches = array();

    // Convert "parent" token from list to single item.
    if (preg_match('@:parent:$@', $prefix) && $source instanceof EntityListWrapper) {
      $source = $source->get(0);
    }

    foreach ($source as $name => $wrapper) {
      $info = $wrapper->info();
      // Keep underscores unchanged in context keywords.
      if (!array_key_exists($name, self::$context_keywords)) {
        $name = str_replace('_', '-', $name);
      }

      // Convert "parent" token from list to single item.
      if ($name == 'parent' && $wrapper instanceof EntityListWrapper) {
        $wrapper = $wrapper->get(0);
      }

      $matches[$prefix . $name] = $info;
      if (!is_array($source) && $source instanceof EntityListWrapper) {
        // Add some more possible list items.
        for ($i = 1; $i < 4; $i++) {
          $matches[$prefix . $i] = $info;
        }
      }

      // Recurse later on to get an improved ordering of the results.
      if ($wrapper instanceof EntityStructureWrapper || $wrapper instanceof EntityListWrapper) {
        $recurse[$prefix . $name] = $wrapper;
        if ($recursions > 0) {
          $matches += PathBreadcrumbsUIAutocomplete::matchDataSelector($wrapper, $prefix . $name . ':', $recursions - 1, $suggestions);
        }
        elseif ($suggestions) {
          // We may not recurse any more, but indicate the possibility to recurse.
          $matches[$prefix . $name . ':'] = $wrapper->info();
          if (!is_array($source) && $source instanceof EntityListWrapper) {
            // Add some more possible list items.
            for ($i = 1; $i < 4; $i++) {
              $matches[$prefix . $i . ':'] = $wrapper->info();
            }
          }
        }
      }
    }

    return $matches;
  }

  public static function processResultData($result, $last_selector, $string) {
    $matches = array();

    foreach ($result as $selector => $info) {
      // If we have an uncomplete last part, take it into account now.
      $attributes = array();
      if (!$last_selector || strpos($selector, $string) === 0) {
        $attributes['class'][] = 'token-normal';
        $attributes['title'] = isset($info['description']) ? strip_tags($info['description']) : '';
        if ($selector[strlen($selector) - 1] == ':') {
          $attributes['class'][] = 'token-expandable';
          $text = check_plain($selector) . '... (' . check_plain($info['label']) . ')';
        }
        else {
          $text = check_plain($selector) . ' (' . check_plain($info['label']) . ')';
        }
        $selector_sign = isset($info['selector_sign']) ? $info['selector_sign'] : '%';
        $matches[$selector_sign . $selector] = "<div" . drupal_attributes($attributes) . ">$selector_sign$text</div";
      }
    }

    return $matches;
  }

  /**
   * Applies all bundles fields to property fields of entity.
   *
   * @param EntityMetadataWrapper $wrapper
   * @param $property_info
   * @return mixed
   */
  public static function processPropertyInfo(EntityMetadataWrapper $wrapper, $property_info) {

    $bundles_properties = array();
    if (!empty($property_info['bundles'])) {
      $bundles = $property_info['bundles'];
      foreach ($bundles as $bundle) {
        if (!empty($bundle['properties'])) {
          $bundles_properties += $bundle['properties'];
        }
      }
    }

    $property_info['properties'] += $bundles_properties;

    return $property_info;
  }

  /**
   * Wrap all available entities in entity metadata wrapper.
   *
   * @param $context_keywords
   * @return array
   */
  public static function applyCurrentVariables($context_keywords) {
    $sources = array();
    foreach ($context_keywords as $keyword => $context_type) {
      $info = PathBreadcrumbsUIAutocomplete::getEntityInfo($context_type);
      $sources[$keyword] = entity_metadata_wrapper($context_type, NULL, $info);
    }
    return $sources;
  }

  /**
   * Return information about entity.
   *
   * @param $context_type
   *   Entity type.
   *
   * @return array
   */
  protected static function getEntityInfo($context_type) {
    $entity_info = PathBreadcrumbsUIAutocomplete::defaultEntityInfo();

    if (isset($entity_info[$context_type])) {
      $info = $entity_info[$context_type];
    }
    else {
      $info = $entity_info['default'];
      if ($enity_info = entity_get_info($context_type)) {
        $info += $enity_info;
      }
    }

    return $info;
  }

  /**
   * Provides default information about entities.
   *
   * @return mixed
   */
  protected static function defaultEntityInfo() {

    // Add a variable for accessing site-wide data properties.
    $vars['site'] = array(
      'type' => 'site',
      'label' => t('Site information'),
      'description' => t('Site-wide settings and other global information.'),
      'property info alter' => array('PathBreadcrumbsUIAutocomplete', 'addSiteMetadata'),
      'property info' => array(),
      'optional' => TRUE,
    );

    // Add default property alter for other entities.
    $vars['default'] = array(
      'property info alter' => array('PathBreadcrumbsUIAutocomplete', 'processPropertyInfo'),
    );

    return $vars;
  }

  /**
   * Add metadata for 'site' entity type.
   *
   * @param EntityMetadataWrapper $wrapper
   * @param $property_info
   *
   * @return mixed
   */
  public static function addSiteMetadata(EntityMetadataWrapper $wrapper, $property_info) {
    $site_info = entity_get_property_info('site');
    $property_info['properties'] += $site_info['properties'];
    return $property_info;
  }

}
