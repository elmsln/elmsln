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

  // Exported menu link: menu-cis-add_blog-post:node/add/editorial-blog-post
  $menu_links['menu-cis-add_blog-post:node/add/editorial-blog-post'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/editorial-blog-post',
    'router_path' => 'node/add/editorial-blog-post',
    'link_title' => 'Blog post',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_blog-post:node/add/editorial-blog-post',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Blog post');


  return $menu_links;
}
