<?php
/**
 * @file
 * cis_data.data_default.inc
 */

/**
 * Implements hook_data_default().
 */
function cis_data_data_default() {
  $export = array();

  $data_table = new stdClass();
  $data_table->disabled = FALSE; /* Edit this to true to make a default data_table disabled initially */
  $data_table->api_version = 1;
  $data_table->title = 'Historical course data';
  $data_table->name = 'historical_course_data';
  $data_table->table_schema = array(
    'description' => '',
    'fields' => array(
      'schedule_id' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'course' => array(
        'type' => 'text',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'semester' => array(
        'type' => 'text',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'year' => array(
        'type' => 'text',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'location' => array(
        'type' => 'text',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'section' => array(
        'type' => 'text',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'enrolled' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'limit' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
    ),
    'name' => 'historical_course_data',
    'primary key' => array(
      0 => 'schedule_id',
    ),
  );
  $data_table->meta = array(
    'fields' => array(
      'schedule_id' => array(),
      'course' => array(),
      'semester' => array(),
      'year' => array(),
      'location' => array(),
      'section' => array(),
      'enrolled' => array(),
      'limit' => array(),
    ),
    'join' => array(
      'historical_name_to_data' => array(
        'left_field' => 'name',
        'field' => 'course',
        'inner_join' => '0',
      ),
    ),
  );
  $export['historical_course_data'] = $data_table;

  $data_table = new stdClass();
  $data_table->disabled = FALSE; /* Edit this to true to make a default data_table disabled initially */
  $data_table->api_version = 1;
  $data_table->title = 'Historical name to data';
  $data_table->name = 'historical_name_to_data';
  $data_table->table_schema = array(
    'description' => '',
    'fields' => array(
      'nid' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => FALSE,
        'description' => '',
      ),
      'name' => array(
        'type' => 'text',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
    ),
    'name' => 'historical_name_to_data',
  );
  $data_table->meta = array(
    'fields' => array(
      'nid' => array(),
      'name' => array(),
    ),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
        'inner_join' => '0',
      ),
    ),
    'data_node' => array(
      'content_type' => 'course',
      'id' => 'nid',
    ),
  );
  $export['historical_name_to_data'] = $data_table;

  return $export;
}
