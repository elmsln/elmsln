<?php
/**
 * @file
 * editorial_blog_post.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function editorial_blog_post_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_editorial_blog_body'
  $field_bases['field_editorial_blog_body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_editorial_blog_body',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
