<?php
/**
 * @file
 * icor_jmol.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function icor_jmol_defaultconfig_features() {
  return array(
    'icor_jmol' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function icor_jmol_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'node-jmol-field_cis_course_ref'.
  $fields['node-jmol-field_cis_course_ref'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_cis_course_ref',
      'foreign keys' => array(
        'node' => array(
          'columns' => array(
            'target_id' => 'nid',
          ),
          'table' => 'node',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => 0,
      'module' => 'entityreference',
      'settings' => array(
        'cis_connector_access' => FALSE,
        'cis_connector_disable' => FALSE,
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(
            'cis_course' => 'cis_course',
          ),
        ),
        'target_type' => 'node',
      ),
      'translatable' => 0,
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'jmol',
      'default_value' => NULL,
      'default_value_function' => '',
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 1,
        ),
        'entityreference_view_widget' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
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
      'field_name' => 'field_cis_course_ref',
      'label' => 'Course',
      'required' => 0,
      'settings' => array(
        'behaviors' => array(
          'prepopulate' => array(
            'status' => 0,
          ),
        ),
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'apply_chosen' => '',
        ),
        'type' => 'options_select',
        'weight' => 32,
      ),
    ),
  );

  // Exported field: 'node-jmol-field_jmol_file'.
  $fields['node-jmol-field_jmol_file'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_jmol_file',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'file',
      'settings' => array(
        'cis_connector_access' => FALSE,
        'cis_connector_disable' => FALSE,
        'display_default' => 1,
        'display_field' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'file',
    ),
    'field_instance' => array(
      'bundle' => 'jmol',
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'jmol',
          'settings' => array(
            'alignment' => 'center',
            'defaultstyle' => 'sticks',
            'filename' => 0,
            'script' => 0,
            'size' => 600,
            'units' => 'angstroms',
            'use' => 'html5',
            'viewstyle' => array(
              'backbone' => 'backbone',
              'balls' => 'balls',
              'ribbon' => 'ribbon',
              'sticks' => 'sticks',
              'trace' => 'trace',
              'wireframe' => 'wireframe',
            ),
          ),
          'type' => 'jmol',
          'weight' => 0,
        ),
        'entityreference_view_widget' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
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
      'field_name' => 'field_jmol_file',
      'label' => 'Jmol File',
      'required' => 0,
      'settings' => array(
        'description_field' => 0,
        'file_directory' => '',
        'file_extensions' => 'pdb',
        'max_filesize' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'file',
        'settings' => array(
          'progress_indicator' => 'throbber',
        ),
        'type' => 'file_generic',
        'weight' => 33,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Course');
  t('Jmol File');

  return $fields;
}
