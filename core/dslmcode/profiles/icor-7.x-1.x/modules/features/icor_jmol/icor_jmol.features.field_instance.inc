<?php
/**
 * @file
 * icor_jmol.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function icor_jmol_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-jmol-field_cis_course_ref'
  $field_instances['node-jmol-field_cis_course_ref'] = array(
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
  );

  // Exported field_instance: 'node-jmol-field_jmol_file'
  $field_instances['node-jmol-field_jmol_file'] = array(
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
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Course');
  t('Jmol File');

  return $field_instances;
}
