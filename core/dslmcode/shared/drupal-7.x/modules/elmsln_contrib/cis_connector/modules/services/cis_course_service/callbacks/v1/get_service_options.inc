<?php

/**
 * Callback to sync sections and roster of users with network.
 */
function cis_course_service_elmsln_api_callback_get_service_options() {
  global $_elmsln;
  // return an options request for the section if available
  if (isset($_elmsln['args']['section'])) {
    $options = _elmsln_core_get_service_settings($_elmsln['args']['section']);
  }
  else {
    $options = _elmsln_core_get_service_settings();
  }
  return array(
    'get_service_options' => TRUE,
    'options' => $options,
    'message' => "Course service options request successful.",
  );
}
