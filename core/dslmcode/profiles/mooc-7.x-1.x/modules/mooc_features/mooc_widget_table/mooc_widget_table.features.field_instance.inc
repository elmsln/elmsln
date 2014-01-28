<?php
/**
 * @file
 * mooc_widget_table.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mooc_widget_table_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-mooc_table-field_table_data'
  $field_instances['node-mooc_table-field_table_data'] = array(
    'bundle' => 'mooc_table',
    'default_value' => array(
      0 => array(
        'tablefield' => array(
          'cell_0_0' => '',
          'cell_0_1' => '',
          'cell_1_0' => '',
          'cell_1_1' => '',
          'cell_2_0' => '',
          'cell_2_1' => '',
          'cell_3_0' => '',
          'cell_3_1' => '',
          'cell_4_0' => '',
          'cell_4_1' => '',
          'import' => array(
            'rebuild_field_table_data_0' => 'Upload CSV',
            'tablefield_csv_field_table_data_0' => '',
          ),
          'rebuild' => array(
            'count_cols' => 2,
            'count_rows' => 5,
            'rebuild' => 'Rebuild Table',
          ),
        ),
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'tablefield',
        'settings' => array(),
        'type' => 'default',
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
    'field_name' => 'field_table_data',
    'label' => 'Table data',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'tablefield',
      'settings' => array(),
      'type' => 'tablefield',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Table data');

  return $field_instances;
}
