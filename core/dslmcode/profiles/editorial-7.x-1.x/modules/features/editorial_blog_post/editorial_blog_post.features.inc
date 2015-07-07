<?php
/**
 * @file
 * editorial_blog_post.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function editorial_blog_post_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function editorial_blog_post_node_info() {
  $items = array(
    'editorial_blog_post' => array(
      'name' => t('Blog post'),
      'base' => 'node_content',
      'description' => t('Create a public Blog Post the rest of your classmates can see.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
