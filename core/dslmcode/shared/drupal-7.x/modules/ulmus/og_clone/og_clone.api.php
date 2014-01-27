<?php

/**
 * @file
 * Describe hooks provided by the OG Clone module.
 */

 /**
 * Allows overriding of the selected entity list for cloning.
 *
 * @param $ids
 *   An array of entity ids currently selected.
 * @return
 *   An array of entity ids after processing.
 */
function hook_get_group_content_ids_alter(&$ids) {
  // array of content types to remove from cloning
  $content_types = array('cle_submission');
  // pull out nodes for testing as this could have other entities
  foreach ($ids as $key => $id) {
    if ($id['entity_type'] == 'node') {
      $id_key[$key] = $id['etid'];
    }
  }
  // Don't allow submissions to be cloned
  $query = new EntityFieldQuery();
  // select all nodes
  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', $content_types, 'IN')
  // where the nid matches the 
  ->propertyCondition('nid', $id_key, 'IN')
  // run as user 1
  ->addMetaData('account', user_load(1));
  $result = $query->execute();
  // verify that we have results
  if (isset($result['node'])) {
    // test the node array against the nodes in the clone array
    foreach ($result['node'] as $node) {
      // if the node selected is in the array, remove it from the ids
      if (in_array($node->nid, $id_key)) {
        unset($ids[array_search($node->nid, $id_key)]);
      }
    }
  }
}