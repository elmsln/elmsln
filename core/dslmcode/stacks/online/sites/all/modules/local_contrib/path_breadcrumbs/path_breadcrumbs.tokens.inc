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

  // Support 'current-page:menu-link:*' tokens.
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
