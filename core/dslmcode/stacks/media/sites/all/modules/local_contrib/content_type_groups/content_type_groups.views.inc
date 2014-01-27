<?php
/**
 * @file
 * Views integration of the Content type groups custom tables
 */

/**
 * Implements hook_views_data().
 */
function content_type_groups_views_data() {

  $data = array();

  $group = t('Content type groups');

  // ----------------------------------------------------------------------
  // content_type_groups_types table

  $data['content_type_groups_types']['table']['group'] = $group;

  // Advertise this table as a possible base table
  $data['content_type_groups_types']['table']['base'] = array(
    'field'    => 'content_type',
    'title'    => $group,
    'help'     => t('Foo'),
    'defaults' => array(
      'field' => 'title',
    ),
  );

  // Table - join info
  $data['content_type_groups_types']['table']['join'] = array(
    // links to node via content_type field
    'node' => array(
      'left_field' => 'type',
      'field'      => 'content_type',
    ),
  );

  // Field - group_type
  $data['content_type_groups_types']['group_type'] = array(
    'title' => t('Content type group'),
    'help'  => t('Get all content in the given content types.'),
    'field' => array(
      'field' => 'content_type', // The real field
      'handler' => 'views_handler_field_markup',
    ),
    'filter' => array(
      'handler' => 'content_type_groups_handler_filter_group',
    ),
  );

  return $data;

}


/**
 * Implements hook_views_handlers().
 */
function content_type_groups_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'content_type_groups'),
    ),
    'handlers' => array(

      // Filter - content groups
      'content_type_groups_handler_filter_group' => array(
        'parent' => 'views_handler_filter_in_operator', // Extends "IN" filter
      ),

    ),
  );
}