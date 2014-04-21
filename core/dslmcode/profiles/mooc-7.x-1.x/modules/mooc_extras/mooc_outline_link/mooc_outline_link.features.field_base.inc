<?php
/**
 * @file
 * mooc_outline_link.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function mooc_outline_link_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ml_redirect'
  $field_bases['field_ml_redirect'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ml_redirect',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'link',
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'rel' => '',
        'target' => 'default',
      ),
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
    ),
    'translatable' => 0,
    'type' => 'link_field',
  );

  return $field_bases;
}
