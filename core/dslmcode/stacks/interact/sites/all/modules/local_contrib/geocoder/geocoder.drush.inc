<?php

/**
 * Implementation of hook_drush_command().
 */
function geocoder_drush_command() {
  $items = array();

  // the key in the $items array is the name of the command.
  $items['geocoder-backfill'] = array(
    'callback' => 'geocoder_drush_backfill',
    'description' => "Geocodes all nodes that have a geocoder widget but no geodata.",
    'options' => array(
      'force' => 'Force the geocode to run, even if there is already geodata',
    ),
  );

  return $items;
}

function geocoder_drush_backfill() {
  $force_reload = drush_get_option('force');
  $all_entity_info = entity_get_info();
  foreach ($all_entity_info as $entity_type => $entity_info) {
    if ($entity_type == 'node') { //TODO: FIX THE LOGIC BELOW and implement for all entities
      if ($entity_info['fieldable']) {
        foreach ($entity_info['bundles'] as $bundle_name => $bundle_info) {
          foreach (field_info_instances($entity_type, $bundle_name) as $field_name => $field_instance) {
            $field_info = field_info_field($field_name);
            if ($field_instance['widget']['type'] === 'geocoder') {
              $entity_load = $entity_info['load hook'];

              $query = db_select($entity_info['base table'])
                         ->fields($entity_info['base table'], array($entity_info['entity keys']['id']))
                         ->condition($entity_info['entity keys']['bundle'], $bundle_name);

              $results = $query->execute();
              while ($id = $results->fetchField()) {
                $entity = $entity_load($id);
                $langcode = field_language($entity_type, $entity, $field_name);
                $items = field_get_items($entity_type, $entity, $field_name, $langcode);

                if ($force_reload) {
                  $entity->original = array();
                }

                // Check for values and if there are no values, reload the entity
                if ($field_info['type'] == 'geofield') {
                  if ($force_reload || (empty($items['wkt']) && empty($items['geom']))) node_save($entity); //TODO: fix for all entities
                }
                if ($field_info['type'] == 'location') {
                  if ($force_reload || empty($items['latitude'])) node_save($entity); //TODO: fix for all entities
                }
                if ($field_info['type'] == 'geolocation') {
                  if ($force_reload || empty($items['lat'])) node_save($entity); //TODO: fix for all entities
                }
              }
            }
          }
        }
      }
    }
  }
}