<?php

/**
 * Callback to propagate course network.
 * @return bool if it was successfully cleared
 */
function cis_helper_elmsln_api_callback_populate_course_network() {
  global $_elmsln;
  // see if course isset
  if (isset($_elmsln['args']['course'])) {
    $nid = _cis_connector_get_course_by_machine_name($_elmsln['args']['course']);
  }
  // see if this is a queue based job to process
  elseif (isset($_elmsln['args']['queue'])) {
    // weird, but we'll call ourselves again in the background if
    // we had an item in the queue
    $queue = DrupalQueue::get('cis_course_process');
    $item = $queue->claimItem();
    $nid = $item->data;
    $queue->deleteItem($item);
  }
  if (isset($nid)) {
    // load up the course node
    $course = node_load($nid);
    $course_data = array(
      'title' => $course->title,
      'machine_name' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
      'uuid' => $course->uuid,
    );
    // pull together sections for this course
    $sections = _cis_helper_course_access_strings($course);
    // pull together roster per section
    $roster = _cis_helper_assemble_roster($sections);
    // add in the users from CIS who are global users
    $staff = _cis_connector_assemble_entity_list('user', 'user', 'uid', 'name', array('__role' => _cis_connector_role_groups('staff')));
    $active = array();
    // simplify section data so we can send along if its active or not
    foreach ($sections as $section_id => $section) {
      // mix in the staff people from CIS
      // so they get section access
      foreach ($staff as $uname) {
        if (!isset($roster[$section_id][$uname]) && strpos($uname, 'SERVICE_') === FALSE) {
          $roster[$section_id][$uname] = 'staff';
        }
      }
      $active[$section_id] = $section->active;
    }
    // ship it around the network
    $requests = array(
      array(
        'method' => 'POST',
        'api' => 1,
        'data' => array(
          'elmsln_module' => 'cis_course_authority',
          'elmsln_callback' => 'sync_data_model',
          '__course_context' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
          'roster' => $roster,
          'course' => $course_data,
          'sections' => $active,
        ),
      )
    );
    _elmsln_api_authority_request($requests, TRUE, array('cis'), TRUE);
    // queue of the same call against the course service network
    $requests = array(
      array(
        'elmsln_module' => 'cis_course_service',
        'elmsln_callback' => 'sync_data_model',
        '__course_context' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
        'roster' => $roster,
        'course' => $course_data,
        'sections' => $active,
      )
    );
    // need to set context just before making this call
    $_SESSION['cis_course_context'] = $course->field_machine_name[LANGUAGE_NONE][0]['value'];
    $returned_data = _elmsln_api_network_request($requests, '1', TRUE, '/' . $course->field_machine_name[LANGUAGE_NONE][0]['value'] . '/', TRUE);
    // ensure we have stuff in the queue before trying this
    if (isset($_elmsln['args']['queue']) && $queue->numberOfItems() > 0) {
      // now kick off a call to do roster syncing that kicks the next item off the queue
      // at the end of it
      $nonblock = array(
        'method' => 'POST',
        'api' => '1',
        'bucket' => 'cis',
        'path' => '/',
        'data' => array(
          'elmsln_module' => 'cis_helper',
          'elmsln_callback' => 'populate_course_network',
          'queue' => TRUE,
        ),
      );
      _elmsln_api_nonblocking_requests(array($nonblock), TRUE);
    }
  }

  return array(
    'populate_course_network' => TRUE,
    'course' => $course,
    'message' => "Course network synced successfully",
  );
}
