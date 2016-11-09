<?php

/**
 * Callback to set a variable based on remote data coming in
 * @return bool if it was successfully cleared
 */
function elmsln_api_elmsln_api_callback_entity_update() {
  global $_elmsln;
  // test we have an entity / etid / type
  if (isset($_elmsln['args']['entity']) && isset($_elmsln['args']['etid']) && isset($_elmsln['args']['type'])) {
    $changed = FALSE;
    // load the entity
    $entity = entity_load_single($_elmsln['args']['type'], $_elmsln['args']['etid']);
    // loop through the properties of the remote entity, check against internal
    // this allows for partcial update
    foreach ($_elmsln['args']['entity'] as $key => $value) {
      if (isset($entity->{$key})) {
        $entity->{$key} = $value;
        $changed = TRUE;
      }
    }
    // only send back if we save the changes
    if ($changed) {
      entity_save($_elmsln['args']['type'], $entity);
      return array(
        'entity_update' => TRUE,
        'entity' => $entity,
        'type' => $_elmsln['args']['type'],
        'etid' => $_elmsln['args']['etid'],
        'message' => t('Entity id @etid updated successfully', array('@etid' => $_elmsln['args']['etid'])),
      );
    }
  }
  return FALSE;
}
