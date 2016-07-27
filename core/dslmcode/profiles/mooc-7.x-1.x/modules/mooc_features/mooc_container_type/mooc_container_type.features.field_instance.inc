<?php
/**
 * @file
 * mooc_container_type.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mooc_container_type_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-mooc_container-field_mooc_container_type'
  $field_instances['node-mooc_container-field_mooc_container_type'] = array(
    'bundle' => 'mooc_container',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'How this container should operate. Folders are purely for organizational purposes.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
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
    'field_name' => 'field_mooc_container_type',
    'label' => 'Type',
    'required' => 1,
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
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('How this container should operate. Folders are purely for organizational purposes.');
  t('Type');

  return $field_instances;
}
