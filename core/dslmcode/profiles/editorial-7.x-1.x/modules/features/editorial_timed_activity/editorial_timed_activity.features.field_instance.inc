<?php
/**
 * @file
 * editorial_timed_activity.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function editorial_timed_activity_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'taxonomy_term-editorial_exercise-field_timed_exercise'
  $field_instances['taxonomy_term-editorial_exercise-field_timed_exercise'] = array(
    'bundle' => 'editorial_exercise',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optionally define a length of time for this activity. A timer will be displayed to help students have a timer to keep track of how long it has been.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_timed_exercise',
    'label' => 'Timed exercise',
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
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Optionally define a length of time for this activity. A timer will be displayed to help students have a timer to keep track of how long it has been.');
  t('Timed exercise');

  return $field_instances;
}
