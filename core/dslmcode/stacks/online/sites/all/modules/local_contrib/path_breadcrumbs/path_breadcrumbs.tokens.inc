<?php

/**
 * @file
 * Provides useful tokens for Path Breadcrumbs. Also see path_breadcrumbs.info.inc file.
 */

/**
 * Implements hook_tokens().
 */
function path_breadcrumbs_tokens($type, $tokens, array $data = array(), array $options = array()) {

  $replacements = array();

  if ($type == 'menu-link') {
    $replacements += _path_breadcrumbs_menu_token_generate($tokens, $data, $options);
  }

  // Fallback support for all 'menu-link' tokens if Token module disabled.
  if (!module_exists('token') && $type != 'site') {
    if ($menu_tokens = token_find_with_prefix($tokens, 'menu-link')) {
      if (empty($data['menu-link']) && isset($data['node'])) {
        $data['menu-link'] = menu_link_get_preferred('node/' . $data['node']->nid);
      }

      $replacements += _path_breadcrumbs_menu_token_generate($menu_tokens, $data, $options);
    }
  }

  // Support 'current-page:menu-link:*' and 'current-page:path-menu-trail:*'
  // tokens.
  if ($type == 'site') {
    // We have to unprefix 'current-page:*' tokens manually.
    if ($site_tokens = token_find_with_prefix($tokens, 'current-page')) {
      if ($menu_tokens = token_find_with_prefix($site_tokens, 'menu-link')) {
        $data['menu-link'] = menu_link_get_preferred();
        $replacements += _path_breadcrumbs_menu_token_generate($menu_tokens, $data, $options);

        // Also replace common menu-link tokens.
        foreach ($menu_tokens as $name => $original) {
          switch ($name) {
            case 'mlid':
              $replacements[$original] = $data['menu-link']['mlid'];
              break;

            case 'title':
              $replacements[$original] = check_plain($data['menu-link']['link_title']);
              break;

            case 'url':
              $replacements[$original] = $data['menu-link']['href'];
              break;
          }
        }
      }
      // Support 'current-page:path-menu-trail:*' tokens.
      elseif ($path_tokens = token_find_with_prefix($site_tokens, 'path-menu-trail')) {
        $replacements += _path_breadcrumbs_path_menu_trail_token_generate($path_tokens);
      }
    }
  }

  return $replacements;
}

/**
 * Helper function to replace 'menu-link:pb-join:*' tokens.
 */
function _path_breadcrumbs_menu_token_generate($tokens, $data, $options) {
  $static_cache = &drupal_static(__FUNCTION__);

  $replacements = array();

  // Menu link is required.
  if (empty($data['menu-link'])) {
    return $replacements;
  }
  // Find 'pb-join' tokens.
  $pb_join_tokens = token_find_with_prefix($tokens, 'pb-join');
  if (empty($pb_join_tokens)) {
    return $replacements;
  }

  if (!empty($static_cache[$data['menu-link']['mlid']])) {
    $pb_menu_data = $static_cache[$data['menu-link']['mlid']];
  }
  else {
    // Load menu hierarchy.
    $pb_menu_data = array('name' => array(), 'url' => array(), 'none' => array());

    for ($i = 1; $i < MENU_MAX_DEPTH; $i++) {
      if (!empty($data['menu-link']["p$i"])) {
        $parant_mlid = $data['menu-link']["p$i"];
        if ($parant_mlid != $data['menu-link']['mlid']) {
          $parent_menu_item = menu_link_load($parant_mlid);

          // i18n_menu support.
          if (module_exists('i18n_menu')) {
            $langcode = i18n_language_interface()->language;
            $i18n_mode = i18n_object('menu_link', $parent_menu_item)->get_translate_mode();
            if ($i18n_mode == I18N_MODE_TRANSLATE) {
              // Load translation from i18n_translation.
              if (($translation_object = i18n_translation_object('menu_link', $parent_menu_item)) &&
                ($translated_item = $translation_object->get_item($langcode))
              ) {
                $parent_menu_item = $translated_item;
              }

            }
            elseif ($i18n_mode == I18N_MODE_LOCALIZE) {
              // Load translation from i18n_string.
              if (_i18n_menu_link_is_localizable($parent_menu_item)) {
                $parent_menu_item['link_title'] = i18n_object('menu_link', $parent_menu_item)->get_title();
              }
            }
          }

          $pb_menu_data['name'][] = $parent_menu_item['link_title'];
          $pb_menu_data['url'][] = $parent_menu_item['link_path'];
          $pb_menu_data['none'][] = '<none>';
        }
      }

    }

    // Save in static cache.
    $static_cache[$data['menu-link']['mlid']] = $pb_menu_data;
  }

  foreach ($pb_join_tokens as $name => $original) {
    if ($name == 'name' || $name == 'url' || $name == 'none') {
      $replacements[$original] = implode("\n", $pb_menu_data[$name]);
    }
  }

  return $replacements;
}

/**
 * Helper function that generates tokens for menu trail by path.
 */
function _path_breadcrumbs_path_menu_trail_token_generate($tokens) {
  global $language;

  // Find 'pb-join' tokens.
  $pb_join_tokens = token_find_with_prefix($tokens, 'pb-join');
  if (empty($pb_join_tokens)) {
    return array();
  }

  // Get current path and explode it by path bits.
  $current_path_alias = drupal_get_path_alias();
  $path_bits = explode('/', $current_path_alias);

  // Add static cache to avoid performance issues.
  $pb_data = &drupal_static(__FUNCTION__);
  if (!isset($pb_data)) {

    // Check if each subpath has menu item. For example, if the current path is
    // "this/is/path/to/check", then we will build menu structure for:
    // * this
    // * this/is
    // * this/is/path
    // * this/is/path/to
    // * this/is/path/to/check
    $path_bits_checked = array();
    foreach ($path_bits as $bit) {
      $path_bits_checked[] = $bit;

      // Menu item can be added with aliased or not aliased path. We should
      // check both cases.
      $path = implode('/', $path_bits_checked);
      $path_normal = drupal_get_normal_path($path);
      $search_path = array($path);
      if ($path != $path_normal) {
        $search_path[] = $path_normal;
      }

      // Find menu item in menu by path.
      $query = db_select('menu_links', 'ml')
        ->fields('ml', array('mlid', 'link_path', 'link_title'))
        ->condition('ml.link_path', $search_path)
        ->range(0, 1);

      if (module_exists('i18n_menu')) {
        $query->condition('ml.language', array(LANGUAGE_NONE, $language->language));
      }

      $menu_link = $query->execute()->fetchObject();

      // If menu item was found, then we can add it as a replacements.
      if (!empty($menu_link)) {
        $pb_data['name'][] = $menu_link->link_title;
        $pb_data['url'][] = $menu_link->link_path;
        $pb_data['none'][] = '<none>';
      }
    }
  }

  $replacements = array();
  foreach ($pb_join_tokens as $name => $original) {
    if (!empty($pb_data[$name])) {
      $replacements[$original] = implode("\n", $pb_data[$name]);
    }
  }

  return $replacements;
}
