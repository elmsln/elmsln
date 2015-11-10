<?php

/**
 * @file
 * Drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function filefield_paths_drush_command() {
  $items = array();

  $items['ffp-update'] = array(
    'description' => 'Retroactively updates all File (Field) Paths of a chosen field instance.',
    'arguments'   => array(
      'entity_type' => 'Entity type.',
      'bundle_name' => 'Bundle name.',
      'field_name'  => 'Field name.'
    ),
    'options'     => array(
      'all' => 'Retroactively update all File (Field) Paths.',
    ),
    'examples'    => array(
      'drush ffp-update'                          => 'Retroactively updates the File (Field) Paths of the instances choosen via an interactive menu.',
      'drush ffp-update node article field_image' => 'Retroactively updates the File (Field) Paths of all instances of the Article content types Image field.',
      'drush ffp-update --all'                    => 'Retroactively update all File (Field) Paths.',
    ),
    'aliases'     => array('ffpu'),
  );

  return $items;
}

/**
 * Retroactively updates all File (Field) Paths of a chosen field instance.
 *
 * @param null $entity_type
 * @param null $bundle_name
 * @param null $field_name
 *
 * @return string
 */
function drush_filefield_paths_ffp_update($entity_type = NULL, $bundle_name = NULL, $field_name = NULL) {
  // Build array of information of all entity types, bundle names and field
  // names.
  $field_types = array_keys(_filefield_paths_get_field_types());
  $info        = array();
  foreach (field_info_fields() as $field) {
    if (in_array($field['type'], $field_types)) {
      foreach ($field['bundles'] as $entity_type_name => $bundles) {
        if (!isset($info[$entity_type_name])) {
          $entity_type_info        = entity_get_info($entity_type_name);
          $info[$entity_type_name] = array(
            '#label' => "{$entity_type_info['label']} ({$entity_type_name})",
          );
        }
        $bundles_info = field_info_bundles($entity_type_name);
        foreach ($bundles as $bundle) {
          if (!isset($info[$entity_type_name][$bundle])) {
            $info[$entity_type_name][$bundle] = array(
              '#label' => "{$bundles_info[$bundle]['label']} ({$bundle})",
            );
          }
          $field = field_info_instance($entity_type_name, $field['field_name'], $bundle);

          $info[$entity_type_name][$bundle][$field['field_name']] = "{$field['label']} ({$field['field_name']})";
        }
      }
    }
  }

  if (drush_get_option('all')) {
    $instances = array();
    foreach ($info as $entity_type => $bundles) {
      foreach (element_children($bundles) as $bundle_name) {
        foreach (element_children($info[$entity_type][$bundle_name]) as $field_name) {
          $instances[] = field_info_instance($entity_type, $field_name, $bundle_name);
        }
      }
    }
    _filefield_paths_drush_ffp_update($instances);

    return '';
  }

  // Get entity type.
  if (empty($entity_type)) {
    $choices = array('all' => dt('All'));
    foreach ($info as $entity_type => $entity_type_info) {
      $choices[$entity_type] = $entity_type_info['#label'];
    }
    $entity_type = drush_choice($choices, dt("Choose an Entity type."));
  }
  if (empty($entity_type)) {
    return '';
  }
  if ($entity_type == 'all') {
    $instances = array();
    foreach ($info as $entity_type => $bundles) {
      foreach (element_children($bundles) as $bundle_name) {
        foreach (element_children($info[$entity_type][$bundle_name]) as $field_name) {
          $instances[] = field_info_instance($entity_type, $field_name, $bundle_name);
        }
      }
    }
    _filefield_paths_drush_ffp_update($instances);

    return '';
  }

  // Get bundle.
  if (empty($bundle_name)) {
    $choices = array('all' => dt('All'));
    foreach (element_children($info[$entity_type]) as $bundle_name) {
      $choices[$bundle_name] = $info[$entity_type][$bundle_name]['#label'];
    }
    $bundle_name = drush_choice($choices, dt("Choose a Bundle."));
  }
  if (empty($bundle_name)) {
    return '';
  }
  if ($bundle_name == 'all') {
    $instances = array();
    foreach (element_children($info[$entity_type]) as $bundle_name) {
      foreach (element_children($info[$entity_type][$bundle_name]) as $field_name) {
        $instances[] = field_info_instance($entity_type, $field_name, $bundle_name);
      }
    }
    _filefield_paths_drush_ffp_update($instances);

    return '';
  }

  // Get field.
  if (empty($field_name)) {
    $choices = array('all' => dt('All'));
    foreach (element_children($info[$entity_type][$bundle_name]) as $field_name) {
      $choices[$field_name] = $info[$entity_type][$bundle_name][$field_name];
    }
    $field_name = drush_choice($choices, dt("Choose a Field."));
  }
  if (empty($field_name)) {
    return '';
  }
  if ($field_name == 'all') {
    $instances = array();
    foreach (element_children($info[$entity_type][$bundle_name]) as $field_name) {
      $instances[] = field_info_instance($entity_type, $field_name, $bundle_name);
    }
    _filefield_paths_drush_ffp_update($instances);

    return '';
  }

  // Invoke Retroactive update.
  $instance = field_info_instance($entity_type, $field_name, $bundle_name);
  _filefield_paths_drush_ffp_update(array($instance));
}

/**
 * Helper function; Invokes File (Field) Paths Retroactive updates.
 *
 * @param $instances
 */
function _filefield_paths_drush_ffp_update($instances) {
  foreach ($instances as $instance) {
    if (filefield_paths_batch_update($instance)) {
      $batch                =& batch_get();
      $batch['progressive'] = FALSE;
      drush_backend_batch_process();
      drush_log(dt('!field_name File (Field) Paths updated.', array('!field_name' => "{$instance['label']} ({$instance['entity_type']}-{$instance['bundle']}-{$instance['field_name']})")), 'success');
    }
  }
}
