<?php
/**
 * @file
 * editorial_story_seeds.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function editorial_story_seeds_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_story-seeds:node/add/editorial-story-seeds
  $menu_links['menu-elmsln-add_story-seeds:node/add/editorial-story-seeds'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/editorial-story-seeds',
    'router_path' => 'node/add/editorial-story-seeds',
    'link_title' => 'Story Seeds',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_story-seeds:node/add/editorial-story-seeds',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Story Seeds');


  return $menu_links;
}
