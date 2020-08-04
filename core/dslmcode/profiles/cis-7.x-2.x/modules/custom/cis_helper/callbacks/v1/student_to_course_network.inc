<?php

/**
 * Callback to propagate course network with a premade roster;
 * a singular student if nessecary.
 * @see cis_helper.pages.inc for example implementation
 * @return bool if it was successfully cleared
 */
function cis_helper_elmsln_api_callback_student_to_course_network() {
  global $_elmsln;
  // see if course isset
  if (isset($_elmsln['args']['course'])) {
    $nid = _cis_connector_get_course_by_machine_name($_elmsln['args']['course']);
  }
  // ensure we have a course node id from some where
  if (isset($nid)) {
    // we MUST be fully bootstrapped for this to work
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
    // we MUST blow away the static cache on the registry otherwise it's possible that custom
    // callbacks that hook systems into scope won't be known about.
    // This took 2 hours to realize at the wrong time of year! :)
    drupal_static_reset('_cis_connector_build_registry');
    // load up the course node
    $course = node_load($nid);
    $course_data = array(
      'title' => $course->title,
      'machine_name' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
      'uuid' => $course->uuid,
    );
    $_elmsln['args']['__course_context'] = $course->field_machine_name[LANGUAGE_NONE][0]['value'];
    // pull together sections for this course
    // pull together roster per section
    $roster = json_decode($_elmsln['args']['roster']);
    $roster = __objectToArray($roster);
    // get section id from the arguments required for this to work
    $section_id = $_elmsln['args']['section'];
    // silly but this ensures we say "Yeah it's active" as we
    // are roping this functionality into the piece that syncs full
    // rosters across the network and are now using this for potential
    // rosters of one.
    $active = array(
      $section_id => TRUE,
    );
    // ship it around the network
    $requests = array(
      array(
        'method' => 'POST',
        'api' => 1,
        'data' => array(
          'elmsln_module' => 'cis_course_authority',
          'elmsln_callback' => 'sync_data_model',
          'defer' => FALSE,
          '__course_context' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
          'roster' => serialize($roster),
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
        'defer' => FALSE,
        '__course_context' => $course->field_machine_name[LANGUAGE_NONE][0]['value'],
        'roster' => serialize($roster),
        'course' => $course_data,
        'sections' => $active,
      )
    );
    // need to set context just before making this call
    $_SESSION['cis_course_context'] = $course->field_machine_name[LANGUAGE_NONE][0]['value'];
    $returned_data = _elmsln_api_network_request($requests, '1', FALSE, '/' . $course->field_machine_name[LANGUAGE_NONE][0]['value'] . '/', TRUE);
  }

  return array(
    'student_to_course_network' => TRUE,
    'course' => $course,
    'roster' => $roster,
    'active' => $active,
    'data_back' => $returned_data,
    'section_id' => $section_id,
    'message' => "Student added to course network",
  );
}

function __objectToArray($obj) {
  if (is_object($obj)) $obj = (array)$obj;
  if (is_array($obj)) {
      $new = array();
      foreach ($obj as $key => $val) {
          $new[$key] = __objectToArray($val);
      }
  } else {
      $new = $obj;
  }
  return $new;
}