<?php
/**
 * @file
 * mooc_cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mooc_cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_child-page:node/add/page.
  $menu_links['menu-elmsln-add_child-page:node/add/page'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/page',
    'router_path' => 'node/add/page',
    'link_title' => 'Child page',
    'options' => array(
      'menu_token_link_path' => 'node/add/page?parent=[node:book:mlid]',
      'menu_token_data' => array(
        'node' => array(
          'type' => 'node',
          'plugin' => 'node_context',
          'options' => array(),
        ),
      ),
      'menu_token_options' => array(
        'clear' => 1,
      ),
      'alter' => TRUE,
      'query' => array(
        'parent' => '',
      ),
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_child-page:node/add/page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_duplicate-outline:menutoken/57f673a80b41d.
  $menu_links['menu-elmsln-add_duplicate-outline:menutoken/57f673a80b41d'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'menutoken/57f673a80b41d',
    'router_path' => 'menutoken/%',
    'link_title' => 'Duplicate outline',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'menu_token_link_path' => 'node/[node:nid]/outline/copy',
      'menu_token_data' => array(
        'node' => array(
          'type' => 'node',
          'plugin' => 'node_context',
          'options' => array(),
        ),
      ),
      'menu_token_options' => array(
        'clear' => 1,
      ),
      'identifier' => 'menu-elmsln-add_duplicate-outline:menutoken/57f673a80b41d',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-settings_content-tools:<nolink>.
  $menu_links['menu-elmsln-settings_content-tools:<nolink>'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Content Tools',
    'options' => array(
      'identifier' => 'menu-elmsln-settings_content-tools:<nolink>',
      'fa_icon' => 'page',
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-settings_import-content-outline:import/feeds_node_helper_book_import.
  $menu_links['menu-elmsln-settings_import-content-outline:import/feeds_node_helper_book_import'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => 'import/feeds_node_helper_book_import',
    'router_path' => 'import/%',
    'link_title' => 'Import course outline',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_import-content-outline:import/feeds_node_helper_book_import',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-settings_content-tools:<nolink>',
  );
  // Exported menu link: menu-elmsln-settings_outline-designer:admin/content/book.
  $menu_links['menu-elmsln-settings_outline-designer:admin/content/book'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => 'admin/content/book',
    'router_path' => 'admin/content/book',
    'link_title' => 'Course outline designer',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_outline-designer:admin/content/book',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-settings_content-tools:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Child page');
  t('Content Tools');
  t('Duplicate outline');
  t('Import course outline');
  t('Course outline designer');

  return $menu_links;
}
