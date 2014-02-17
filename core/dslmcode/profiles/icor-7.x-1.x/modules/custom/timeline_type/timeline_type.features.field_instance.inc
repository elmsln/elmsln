<?php
/**
 * @file
 * timeline_type.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function timeline_type_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-timeline-field_time_points'
  $field_instances['node-timeline-field_time_points'] = array(
    'bundle' => 'timeline',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'iframe' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
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
    'field_name' => 'field_time_points',
    'label' => 'Time points',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference_dynamicselect_widget',
      'settings' => array(
        'filter' => 'Keyword',
        'filters' => array(
          'status' => 0,
          'title' => 'title',
          'type' => 0,
        ),
        'layout' => '',
        'select' => 'User',
        'submit' => 'Filter',
        'view' => 'timeline_content_type:dynamic_select_1',
      ),
      'type' => 'entityreference_dynamicselect_widget',
      'weight' => -3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Time points');

  return $field_instances;
}
