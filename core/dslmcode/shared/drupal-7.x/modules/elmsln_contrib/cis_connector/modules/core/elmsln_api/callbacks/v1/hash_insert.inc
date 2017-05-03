<?php

/**
 * Callback to insert a token / value at the prescribed hash'ed paragraph location
 * @return array of success status
 */
function elmsln_api_elmsln_api_callback_hash_insert() {
  global $_elmsln;
  // test we have an entity / etid / type
  if (isset($_elmsln['args']['hash']) && isset($_elmsln['args']['token']) && isset($_elmsln['args']['etid']) && isset($_elmsln['args']['type'])) {
    $changed = FALSE;
    // load the entity
    $entity = entity_load_single($_elmsln['args']['type'], $_elmsln['args']['etid']);
    $search = '/<p>(.*?)<\/p>/s';
    $hashed = preg_replace_callback($search, '_elmsln_api_paragraph_marker', $entity->body[LANGUAGE_NONE][0]['value']);
    // generate insert place holder
    $replaceit = '<insert' . $_elmsln['args']['hash'] . '/>';
    // replace the targetted item if found
    $hashed = str_replace($replaceit, $_elmsln['args']['token'], $hashed);
    // now remove the older ones
    $search = '/<insert(.*?)\/>/s';
    $hashed = preg_replace($search, '', $hashed);
    if ($entity->body[LANGUAGE_NONE][0]['value'] != $hashed) {
      $entity->body[LANGUAGE_NONE][0]['value'] = $hashed;
      $changed = TRUE;
    }
    else {
      $entity->body[LANGUAGE_NONE][0]['value'] .= $_elmsln['args']['token'];
      $changed = TRUE;
    }
    // only send back if we save the changes
    if ($changed) {
      entity_save($_elmsln['args']['type'], $entity);
      return array(
        'entity_update' => TRUE,
        'entity' => $entity,
        'message' => t('Entity id @etid updated successfully', array('@etid' => $_elmsln['args']['etid'])),
      );
    }
  }
  return FALSE;
}

/**
 * Callback to convert preg_replace into what we need it to be
 * since we have to process some of the elements based on position
 * in the HTML.
 */
function _elmsln_api_paragraph_marker($matches) {
  static $key;
  if (empty($key)) {
    $key = 0;
  }
  return '<insert' . hash('md5', 'p' . $key++) . '/><p>' . $matches[1] .'</p>';
}
