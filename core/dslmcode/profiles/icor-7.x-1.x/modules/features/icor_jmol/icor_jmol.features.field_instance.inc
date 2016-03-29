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
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
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
      'authcache' => array(
        'clients' => array(
          'authcache_ajax' => array(
            'status' => 1,
            'weight' => 0,
          ),
        ),
        'fallback' => 'cancel',
        'lifespan' => 3600,
        'perpage' => 0,
        'peruser' => 1,
        'status' => 0,
      ),
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'providers' => array(
            'og_context' => FALSE,
            'url' => 1,
          ),
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 0,
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
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Course');
  t('Jmol File');

  return $field_instances;
}
