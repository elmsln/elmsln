<?php

$query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', 'ecd_asset');
    $query->fieldCondition('field_resource_uuid_bind', 'value', $value['uuid'], '=');
    $result = $query->execute();

/**
 * Callback to keep an entity in sync based on criteria
 * matching the remote uuid. If the EFQ comes up empty
 * then we know we need to create something that would
 * match on subsequent sync calls.
 */
function elmsln_api_elmsln_api_callback_entity_sync() {
  global $_elmsln;
  // test we have a query constructed and data to set in either case
  if (isset($_elmsln['args']['query']) && isset($_elmsln['args']['data'])) {
    $changed = FALSE;
    // try to load something that matches
    $query = new EntityFieldQuery;
    foreach ($_elmsln['args']['query'] as $condition => $criteria) {
      foreach ($criteria as $field => $target) {
        if (is_array($match)) {
          if (count($match) == 2) {
            $query->{$condition}($field, $target[0], $taget[1]);
          }
          else {
            $query->{$condition}($field, $target[0], $taget[1], $taget[1]);
          }
        }
        else {
          // skim off entity type
          if ($field == 'entity_type') {
            $etype = $target;
          }
          else if ($field == 'bundle') {
            $bundle = $target;
          }
          $query->{$condition}($field, $target);
        }
      }
    }
    $result = $query->execute();
    if (isset($result[$etype])) {
      $etids = array_keys($result[$etype]);
      foreach ($etids as $nid) {
        $entity = entity_load_single($etype, $etid);
      }
    }
    // we didn't find anything to load, make something new
    if (!isset($entity)) {
      // calculate the bundle property
      $info = entity_get_info($etype);
      $entity = entity_create($etype, array($info['entity keys']['bundle'] => $bundle));
      $message = t('Entity created successfully');
    }
    else {
      $message = t('Entity updated successfully');
    }
    // loop through the properties of the remote entity, check against internal
    // this allows for partcial update
    foreach ($_elmsln['args']['data'] as $key => $value) {
      $entity->{$key} = $value;
    }
    // only send back if we save the changes
    entity_save($_elmsln['args']['type'], $entity);
    return array(
      'entity_sync' => TRUE,
      'entity' => $entity,
      'message' => $message,
    );
  }
  return FALSE;
}
