<?php
// $Id: dhtml_menu.theme.inc,v 1.14 2009/11/12 21:47:59 arancaytar Exp $


/**
 * @file dhtml_menu.theme.inc
 * All functions related to generating the menu markup.
 */

/**
 * Preprocessor for menu_link.
 * Adds the required HTML attributes and loads subtrees if necessary.
 */
function dhtml_menu_preprocess_menu_link(&$variables) {
  $cookie = &drupal_static(__FUNCTION__);
  $settings = variable_get('dhtml_menu_settings');

  // Parse the cookie, if it is enabled.
  if (!isset($cookie)) {
    if ($settings['effects']['remember'] && $settings['nav'] != 'open' && $settings['effects']['siblings'] != 'close-all') {
      $cookie = explode(',', @$_COOKIE['dhtml_menu']);
    }
    else {
      $cookie = array();
    }
  }

  // Saves a lot of code.
  $l = &$variables['element']['#original_link'];

  // Determine if the menu is blacklisted or not whitelisted.
  $disabled = ($settings['filter']['type'] == 'blacklist') == !empty($settings['filter']['list'][$l['menu_name']]);
  if (empty($l['menu_name']) || empty($l['mlid']) || $disabled) {
    return;
  }

  // Add the ID and class attributes.

  $variables['element']['#attributes']['id'] = 'dhtml_menu-' . _dhtml_menu_unique_id($l['mlid']);
  $variables['element']['#attributes']['class'][] = 'dhtml-menu';

  // If there are children, but they were not loaded, load them.
  if ($l['has_children'] && !$variables['element']['#below']) {
    $variables['element']['#below'] = _dhtml_menu_subtree($l['menu_name'], $l['mlid']);
  }

  // If the current item can expand, and is neither saved as open nor in the active trail, close it.
  if ($l['has_children'] && !$l['in_active_trail'] && !in_array($variables['element']['#attributes']['id'], $cookie)) {
    $variables['element']['#attributes']['class'][] = 'collapsed';
    $variables['element']['#attributes']['class'][] = 'start-collapsed';
  }
}

/**
 * Traverses the menu tree and returns the sub-tree of the item
 * indicated by the parameter.
 *
 * @param $menu_name
 *   The internal name of the menu.
 * @param $mlid
 *   The menu link ID.
 *
 * @return
 *   The tree below the menu item, as a renderable array, or an empty array.
 */
function _dhtml_menu_subtree($menu_name, $mlid) {
  static $index = array();
  static $indexed = array();

  // This looks expensive, but menu_tree_all_data uses static caching.
  $tree = menu_tree_all_data($menu_name);

  // Index the menu tree to find ancestor paths for each item.
  if (!isset($indexed[$menu_name])) {
    $index += _dhtml_menu_index($tree);
    $indexed[$menu_name] = TRUE;
  }

  // If the menu tree does not contain this item, stop.
  if (!isset($index[$mlid])) {
    return array();
  }

  // Traverse the tree using the ancestor path.
  foreach ($index[$mlid]['parents'] as $id) {
    $key = $index[$id]['key'];
    if (isset($tree[$key])) {
      $tree = $tree[$key]['below'];
    }
    else {
      return array();
    }
  }

  // Go one level further to go below the current item.
  $key = $index[$mlid]['key'];
  return isset($tree[$key]) ? menu_tree_output($tree[$key]['below']) : array();
}

/**
 * Indexes the menu tree by mlid. This is needed to identify the items
 * without relying on titles or stacks. This function is recursive.
 *
 * @param $tree
 *   A tree of menu items such as the return value of menu_tree_all_data().
 * @param $ancestors
 *   Optional, used only by internal recursion.
 * @param $parent
 *   Optional, used only by internal recursion.
 *
 * @return
 *   An array associating mlid values with the internal keys of the menu tree,
 *   and all the mlids of the item's ancestors.
 */
function _dhtml_menu_index($tree, $ancestors = array(), $parent = NULL) {
  $index = array();
  if ($parent) {
    $ancestors[] = $parent;
  }

  foreach ($tree as $key => $item) {
    $index[$item['link']['mlid']] = array(
      'key' => $key,
      'parents' => $ancestors,
    );
    if (!empty($item['below'])) {
      $index += _dhtml_menu_index($item['below'], $ancestors, $item['link']['mlid']);
    }
  }
  return $index;
}

/**
 * Keeps track of ID attributes and adds a suffix to make it unique-when necessary.
 */
function _dhtml_menu_unique_id($id) {
  static $ids = array();
  if (!isset($ids[$id])) {
    $ids[$id] = 1;
    return $id;
  }
  else {
    return $id . '-' . $ids[$id]++;
  }
}

