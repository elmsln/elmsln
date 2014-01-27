<?php

/**
 * @file
 * Exposes reporting data to views.
 */

/**
 * Implements hook_views_data().
 */
function accessibility_reporting_views_data() {
  // Define the base group of this table.
  $data['accessibility_reporting']['table']['group']  = t('Accessibility reporting');

  $data['accessibility_reporting']['field'] = array(
    'title' => t('Responsible field'),
    'help'  => t('The field in the entity that had the error.'),
    'field' => array(
      'handler' => 'views_handler_accessibility_reporting_field',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['accessibility_reporting']['total'] = array(
    'title' => t('Total errors'),
    'help'  => t('Total number of errors in a field.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['accessibility_reporting']['accessibility_test'] = array(
    'title' => t('Accessibility test'),
    'help'  => t('The accessibility test that failed.'),
    'relationship' => array(
      'label' => t('Accessibility test'),
      'base' => 'accessibility_test',
      'base field' => 'test_id',
      'relationship field' => 'test_id',
    ),
  );
    
  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function accessibility_reporting_views_data_alter(&$data) {
  // Load information for entity types so we can find their base tables
  $entity_infos = entity_get_info();
  $entity_tables = array();
  foreach ($entity_infos as $entity_type => $entity_info) {
    if (isset($entity_info['base table'])) {
      $data[$entity_info['base table']]['accessibility_reporting_base_left_' . $entity_info['base table']] = array(
        'title' => t('Accessibility reporting results'),
        'help' => t('Provides a relationship from entities to the appropriate accessibility reporting'),
        'relationship' => array(
          'label' => t('Reporting'),
          'title' => t('Accessibility report results'),
          'base' => 'accessibility_reporting',
          'base field' => 'entity_id',
          'relationship field' => $entity_info['entity keys']['id'],
          'entity_type_left' => $entity_type,
          'handler' => 'views_handler_relationship',
        ),
      );
    }
  }
  
}