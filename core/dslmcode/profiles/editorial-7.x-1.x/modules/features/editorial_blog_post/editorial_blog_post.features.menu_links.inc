<?php
/**
 * @file
 * editorial_blog_post.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function editorial_blog_post_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-add_public-blog-post:node/add/editorial-blog-post
  $menu_links['menu-cis-add_public-blog-post:node/add/editorial-blog-post'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/editorial-blog-post',
    'router_path' => 'node/add/editorial-blog-post',
    'link_title' => 'Public Blog post',
    'options' => array(
      'identifier' => 'menu-cis-add_public-blog-post:node/add/editorial-blog-post',
      'menu_token_link_path' => 'node/add/editorial-blog-post?og_group_ref=[current-user:og-user-node:0:nid]',
      'menu_token_data' => array(),
      'menu_token_options' => array(
        'clear' => 1,
      ),
      'alter' => TRUE,
      'query' => array(
        'og_group_ref' => 6,
      ),
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
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Public Blog post');


  return $menu_links;
}
