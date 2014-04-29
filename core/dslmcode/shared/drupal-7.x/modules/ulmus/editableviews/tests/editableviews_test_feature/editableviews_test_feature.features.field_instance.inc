<?php
/**
 * @file
 * editableviews_test_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function editableviews_test_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-editable_views_test_node-field_test_editable_options'
  $field_instances['node-editable_views_test_node-field_test_editable_options'] = array(
    'bundle' => 'editable_views_test_node',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_test_editable_options',
    'label' => 'Test editable options',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-editable_views_test_node-field_test_editable_text'
  $field_instances['node-editable_views_test_node-field_test_editable_text'] = array(
    'bundle' => 'editable_views_test_node',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_test_editable_text',
    'label' => 'Test editable text',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-editable_views_test_referencing-field_test_node_reference'
  $field_instances['node-editable_views_test_referencing-field_test_node_reference'] = array(
    'bundle' => 'editable_views_test_referencing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_test_node_reference',
    'label' => 'Test node reference',
    'options_limit' => 0,
    'options_limit_fields' => array(
      'body' => 0,
    ),
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => -3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Test editable options');
  t('Test editable text');
  t('Test node reference');

  return $field_instances;
}
