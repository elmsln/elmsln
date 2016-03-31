<?php

/**
 * Callback to create / update contextually assets that have
 * been submitted to comply.
 */
function ecd_helper_elmsln_api_callback_asset() {
  global $_elmsln;
  $value = $_elmsln['args'];
  // ensure we have all the values needed for this callback
  if (isset($value['title']) &&
      isset($value['course']) &&
      isset($value['url']) &&
      isset($value['uuid']) &&
      isset($value['type'])) {
    // see if we should create a new one
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', 'ecd_asset');
    $query->fieldCondition('field_resource_uuid_bind', 'value', $value['uuid'], '=');
    $result = $query->execute();
    // looks like we need to make a new one if this is empty
    if (empty($result)) {
      $node = new stdClass();
      $node->type = 'ecd_asset';
      node_object_prepare($node);
      $node->language = LANGUAGE_NONE;
      $node->uid = 1;
      $node->status = 1;
      $node->promote = 0;
      $node->revision = 0;
      // calculate the course uuid
      $query = new EntityFieldQuery;
      $query->entityCondition('entity_type', 'node');
      $query->entityCondition('bundle', 'cis_course');
      $query->fieldCondition('field_course_machine_name', 'value', $value['course'], '=');
      $result = $query->execute();
      $etids = array_keys($result['node']);
      $nid = array_pop($etids);
      // load all the entities in the array
      $course = node_load($nid);
      if (isset($course->uuid)) {
        $node->field_course['und'][0]['target_id'] = $course->nid;
      }
      // set title to match what came from the remote
      $node->title = $value['title'];
      // set the URL so we can send people to view it
      $node->field_source['und'][0]['url'] = $value['url'];
      // type of asset here
      $node->field_asset_type['und'][0]['value'] = $value['type'];
      // this is a hidden value, setting the uuid here
      $node->field_resource_uuid_bind['und'][0]['value'] = $value['uuid'];
      // unset content and media being updated, also do this on new items
      $node->field_accessibility_verified['und'][0]['value'] = 0;
      $node->field_quality_verified['und'][0]['value'] = 0;
      $node->field_copyright_verified['und'][0]['value'] = 0;
      // save this new item
      node_save($node);
      $message = t('Created new asset record');
    }
    else {
      // unset content and media being updated but NOT links
      // we assume that links state was validated on a different
      // timetable / process
      $etids = array_keys($result['node']);
      $nid = array_pop($etids);
      if ($value['type'] != 'link') {
        // our remote item got deleted; let's keep in sync
        if ($value['operation'] == 'delete') {
          node_delete($nid);
          $message = t('Deleted associated asset record');
        }
        else {
          // load all the entities in the array
          $node = node_load($nid);
          // update title incase it changed
          $node->title = $value['title'];
          // unset these because we need a human to verify it
          $node->field_accessibility_verified['und'][0]['value'] = 0;
          $node->field_quality_verified['und'][0]['value'] = 0;
          $node->field_copyright_verified['und'][0]['value'] = 0;
          // save node
          node_save($node);
          $message = t('Updated existing asset record');
        }
      }
      else {
        $node = node_load($nid);
        // update title incase it changed
        $node->title = $value['title'];
        node_save($node);
        $message = t('Link, no update.');
      }
    }
    return array(
      'asset' => TRUE,
      'node' => serialize($node),
      'message' => $message,
    );
  }
}
