<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(__FILE__)));
require_once(__ROOT__.'/services/CleOpenStudioAppSubmissionService.php');
require_once(__ROOT__.'/services/CleOpenStudioAppProjectService.php');
require_once(__ROOT__.'/services/CleOpenStudioAppFileService.php');
require_once(__ROOT__.'/services/CleOpenStudioAppCommentService.php');

/**
 * Callback for apps/open-studio/data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_app_data($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->state = array('submission_ready', '=');
  // @todo we need to pull only what we're asked for as a range
  // this way we don't destroy the UI in huge classes
  // invoke our submission service to get submissions
  $service = new CleOpenStudioAppSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new CleOpenStudioAppProjectService();
  $data['projects'] = $service->getProjects();
  return array(
    'status' => $status,
    'data' => $data
  );
}