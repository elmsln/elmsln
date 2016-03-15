<?php
/**
 * @file
 * Include file for Views hooks
 */

/**
 * Implements hook_views_data().
 *
 * Provides the Hidden Node status as a Views field for Views 2+.
 */
function hidden_nodes_views_data() {
  $data = array();

  // Define the hidden_nodes table.
  $data['hidden_nodes']['table'] = array(
    'group' => t('Content'),
    'title' => t('Hidden status'),
    'help'  => t('Hidden/not hidden via the Hidden Nodes module'),
  );

  // Join to the node table.
  $data['hidden_nodes']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  // Define the field.
  $data['hidden_nodes']['hidden'] = array(
    'title' => t('Hidden'),
    'help' => t('Whether or not the content is hidden.'),
    'field' => array(
      'field' => 'hidden',
      'group' => t('Content'),
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Hidden'),
      'type' => 'yes-no',
    ),
  );
  return $data;
}
