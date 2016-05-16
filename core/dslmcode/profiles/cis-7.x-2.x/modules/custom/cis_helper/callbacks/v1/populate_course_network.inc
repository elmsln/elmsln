<?php

/**
 * Callback to propagate course network.
 * @return bool if it was successfully cleared
 */
function cis_helper_elmsln_api_callback_populate_course_network() {
  global $_elmsln;
  // see if course isset
  if (isset($_elmsln['args']['course'])) {

  }
  elseif (isset($_elmsln['args']['queue'])) {
    // weird, but we'll call ourselves again in the background if
    // we had an item in the queue
    $queue = DrupalQueue::get('cis_course_process');
    $item = $queue->claimItem();
    $nid = $item->data;
    $queue->deleteItem($item);
    // load up the course node
    $course = node_load($nid);
    // pull together sections for this course
    $sections = _cis_helper_course_access_strings($course);
    // pull together roster per section
    $roster = _cis_helper_assemble_roster($sections);
    // ship it around the network
    $requests = array(
      array(
        'method' => 'POST',
        'api' => 1,
        'data' => array(
          'elmsln_module' => 'cis_course_authority',
          'elmsln_callback' => 'sync_data',
          '__course_context' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
          'roster' => $roster,
        ),
      )
    );
    _elmsln_api_authority_request($requests, TRUE, array('cis', 'ecd'));
    // queue of the same call against the services
    $requests = array(
      array(
        'elmsln_module' => 'cis_section',
        'elmsln_callback' => 'sync_data',
        '__course_context' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
        'roster' => $roster,
      )
    );
    _elmsln_api_network_request($requests, '1', TRUE, '/' . $course->field_machine_name[LANGUAGE_NONE][0]['value'] . '/');
    // ensure we have stuff in the queue before trying this
    if ($queue->numberOfItems() > 0) {
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
    'message' => "Course network synced successfully",
  );
}
