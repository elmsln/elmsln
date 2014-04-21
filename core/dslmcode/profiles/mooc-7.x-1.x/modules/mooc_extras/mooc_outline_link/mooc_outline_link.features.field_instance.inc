<?php
/**
 * @file
 * mooc_outline_link.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mooc_outline_link_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-mooc_link-field_ml_redirect'
  $field_instances['node-mooc_link-field_ml_redirect'] = array(
    'bundle' => 'mooc_link',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Where to redirect users if they access this.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'field_redirection',
        'settings' => array(
          '404_if_empty' => 0,
          'code' => 301,
        ),
        'type' => 'field_redirection',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ml_redirect',
    'label' => 'Redirect',
    'required' => 1,
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 0,
      'rel_remove' => 'default',
      'title' => 'none',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Redirect');
  t('Where to redirect users if they access this.');

  return $field_instances;
}
