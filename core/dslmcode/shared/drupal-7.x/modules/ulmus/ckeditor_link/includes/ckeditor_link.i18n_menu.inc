<?php
/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 */

/**
 * Implementation of hook_ckeditor_link_TYPE_autocomplete().
 */
function ckeditor_link_ckeditor_link_i18n_menu_autocomplete($string, $limit) {
  // Currently, this function only supports MySQL.
  // TODO: Add support for pgsql.
  if (!in_array(db_driver(), array('mysql'))) {
    return array();
  }

  $matches = array();

  $menus = array_keys(array_filter(variable_get('ckeditor_link_autocomplete_menus', array())));
  if (count($menus)) {
    $query = db_select('menu_links', 'ml');
    $query->innerJoin('locales_source', 'ls', 'ls.context = CONCAT(:prefix, ml.mlid, :suffix)', array(':prefix' => 'item:', ':suffix' => ':title'));
    $query->innerJoin('locales_target', 'lt', 'lt.lid = ls.lid');
    $query->fields('ml', array('link_path'));
    $query->addExpression('CONVERT(lt.translation USING utf8)', 'link_title');
    $query->fields('lt', array('language'));
    $query->where('CONVERT(lt.translation USING utf8) LIKE :pattern', array(':pattern' => '%'. db_like($string) .'%'));
    $query->condition('ml.hidden', 0);
    $query->condition('ml.external', 0);
    $query->orderBy('link_title');
    $query->range(0, $limit);
    if (!in_array('- any -', $menus)) {
      $query->condition('ml.menu_name', $menus, 'IN');
    }
    $result = $query->execute();
    foreach ($result as $item) {
      if (_ckeditor_link_check_path($item->link_path)) {
        $router_item = menu_get_item($item->link_path);
        if ($router_item && $router_item['access']) {
          $path = ckeditor_link_path_prefix_language($item->link_path, $item->language);
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
function ckeditor_link_ckeditor_link_i18n_menu_revert($path, &$langcode) {
  $router_item = menu_get_item($path);
  if ($router_item) {
    if (!$router_item['access']) {
      return FALSE;
    }
    $result = db_query('SELECT mlid, link_title, language FROM {menu_links} WHERE link_path = :link_path AND hidden = 0 ORDER BY customized DESC', array(':link_path' => $path));
    $default_langcode = language_default('language');
    $link_title = NULL;
    foreach ($result as $item) {
      if ($item->language == $langcode) {
        $link_title = $item->link_title;
        break;
      }
      elseif (($item->language == $default_langcode) && ($langcode == LANGUAGE_NONE)) {
        $langcode = $default_langcode;
        $link_title = $item->link_title;
        break;
      }
      elseif (!$link_title && ($item->language == LANGUAGE_NONE)) {
        $link_title = i18n_string_translate(array('menu', 'item', $item->mlid, 'title'), $item->link_title, array('langcode' => $langcode));
      }
    }
    return ($link_title) ? $link_title : NULL;
  }
}
