<?php

/**
 * @file
 * Providing extra functionality for views.
 */
function accessibility_views_data() {
  // Define the base group of this table.
  $data['accessibility_test']['table']['group']  = t('Accessibility test');

  // Advertise this table as a possible base table
  $data['accessibility_test']['table']['base'] = array(
    'field' => 'test_id',
    'title' => t('Accessibility test'),
    'weight' => -10,
  );
  $data['accessibility_test']['table']['entity type'] = 'accessibility_test';
  $data['accessibility_test']['test_id'] = array(
    'title' => t('Test ID'),
    'help' => t('The test ID.'),
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

  $data['accessibility_test']['name'] = array(
    'title' => t('Name'),
    'help' => t('The test name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'relation_get_types_options',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['accessibility_test']['severity'] = array(
    'title' => t('Severity'),
    'help' => t('The severity level of the test.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'relation_get_types_options',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['accessibility_test']['quail_name'] = array(
    'title' => t('QUAIL Name'),
    'help' => t('The name of the QUAIL test to be called.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'relation_get_types_options',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['accessibility_test']['status'] = array(
    'field' => array(
      'title' => t('Test status'),
      'help' => t('Show the status of the test.'),
      'handler' => 'accessibility_handler_status',
    ),
  );

  $data['accessibility_test']['link_accessibility'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the test.'),
      'handler' => 'accessibility_handler_link_field',
    ),
  );
  
  $data['accessibility_test']['edit_accessibility'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the accessibility.'),
      'handler' => 'accessibility_handler_edit_link_field',
    ),
  );
  
  $data['accessibility_test']['delete_accessibility'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the accessibility.'),
      'handler' => 'accessibility_handler_delete_link_field',
    ),
  );
    
  return $data;
}
