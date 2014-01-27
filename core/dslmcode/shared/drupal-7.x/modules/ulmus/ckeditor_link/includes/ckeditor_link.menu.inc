<?php
/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 */

/**
 * Implementation of hook_ckeditor_link_TYPE_autocomplete().
 */
function ckeditor_link_ckeditor_link_menu_autocomplete($string, $limit) {
  $matches = array();

  $menus = array_keys(array_filter(variable_get('ckeditor_link_autocomplete_menus', array())));
  if (count($menus)) {
    $query = db_select('menu_links')
      ->fields('menu_links', array('link_path', 'link_title'))
      ->condition('link_title', '%'. db_like($string) .'%', 'LIKE')
      ->condition('hidden', 0)
      ->condition('external', 0)
      ->orderBy('link_title')
      ->range(0, $limit);
    if (function_exists('ckeditor_link_ckeditor_link_i18n_menu_autocomplete')) {
      $query->fields('menu_links', array('language'));
    }
    if (!in_array('- any -', $menus)) {
      $query->condition('menu_name', $menus, 'IN');
    }
    $result = $query->execute();
    foreach ($result as $item) {
      if (_ckeditor_link_check_path($item->link_path)) {
        $router_item = menu_get_item($item->link_path);
        if ($router_item && $router_item['access']) {
          $langcode = (isset($item->language)) ? $item->language : LANGUAGE_NONE;
          $path = ckeditor_link_path_prefix_language($item->link_path, $langcode);
          $matches[$path] = $item->link_title;
        }
      }
    }
  }

  return $matches;
}

/**
 * Implementation of hook_ckeditor_link_TYPE_revert().
 */
function ckeditor_link_ckeditor_link_menu_revert($path, &$langcode) {
  if (function_exists('ckeditor_link_ckeditor_link_i18n_menu_revert')) {
    return;
  }

  $router_item = menu_get_item($path);
  if ($router_item) {
    if (!$router_item['access']) {
      return FALSE;
    }
    $link_title = db_query("SELECT link_title FROM {menu_links} WHERE link_path = :link_path AND hidden = 0 ORDER BY customized DESC", array(':link_path' => $path))->fetchField();
    return ($link_title) ? $link_title : NULL;
  }
}

/**
 * Implementation of hook_ckeditor_link_TYPE_settings().
 */
function ckeditor_link_ckeditor_link_menu_settings() {
  $form = array();

  if (module_exists('menu')) {
    $form['menu'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu items'),
    );
    $form['menu']['ckeditor_link_autocomplete_menus'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Menus'),
      '#options' => array('- any -' => t('<em>Any menu</em>')) + array_map('check_plain', menu_get_menus()),
      '#default_value' => variable_get('ckeditor_link_autocomplete_menus', array()),
      '#description' => t('Select the menus to be available as autocomplete suggestions.'),
    );
  }

  return $form;
}
