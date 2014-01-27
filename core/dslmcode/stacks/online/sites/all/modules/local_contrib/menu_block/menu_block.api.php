<?php
/**
 * @file
 * Hooks provided by the Menu Block module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the menu tree and its configuration before the tree is rendered.
 *
 * @param $tree
 *   An array containing the unrendered menu tree.
 * @param $config
 *   An array containing the configuration of the tree.
 */
function hook_menu_block_tree_alter(&$tree, &$config) {
}

/**
 * Return a list of configurations for menu blocks.
 *
 * Modules that want to have menu block configurations exported to code should
 * provide them using this hook.
 *
 * @see menu_tree_build() for a description of the config array.
 */
function hook_menu_block_blocks() {
  return array(
    // The array key is the block id used by menu block.
    'custom-nav' => array(
      // Use the array keys/values described in menu_tree_build().
      'menu_name'   => 'primary-links',
      'parent_mlid' => 0,
      'title_link'  => FALSE,
      'admin_title' => 'Drop-down navigation',
      'level'       => 1,
      'follow'      => 0,
      'depth'       => 2,
      'expanded'    => TRUE,
      'sort'        => FALSE,
    ),
    // To prevent clobbering of the block id, it is recommended to prefix it
    // with the module name.
    'custom-active' => array(
      'menu_name'   => MENU_TREE__CURRENT_PAGE_MENU,
      'title_link'  => TRUE,
      'admin_title' => 'Secondary navigation',
      'level'       => 3,
      'depth'       => 3,
      // Any config options not specified will get the default value.
    ),
  );
}

/**
 * Return a list of menus to use with the menu_block module.
 *
 * @return
 *   An array containing the menus' machine names as keys with their menu titles
 *   as values.
 */
function hook_menu_block_get_menus() {
  $menus = array();
  // For each menu, add the following information:
  $menus['menu_name'] = 'menu title';

  return $menus;
}

/**
 * Return a list of menus to use on menu block's settings form.
 *
 * Menu block's settings page sorts menus for use with its "the menu selected by
 * the page" option.
 *
 * @return
 *   An array containing the menus' machine names as keys with their menu titles
 *   as values. The key may optionally be a regular expression to match several
 *   menus at a time; see book_menu_block_get_sort_menus() for an example.
 */
function hook_menu_block_get_sort_menus() {
  $menus = array();
  // For each menu, add the following information:
  $menus['menu_name'] = 'menu title';
  // Optionally, add a regular expression to match several menus at once.
  $menus['/^my\-menus\-.+/'] = t('My menus');

  return $menus;
}

/**
 * @} End of "addtogroup hooks".
 */
