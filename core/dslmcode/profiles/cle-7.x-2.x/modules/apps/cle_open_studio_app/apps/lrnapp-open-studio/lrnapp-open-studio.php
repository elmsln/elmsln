<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(__FILE__)));
require_once(__ROOT__.'/services/CleOpenStudioAppSubmissionService.php');
require_once(__ROOT__.'/services/CleOpenStudioAppFileService.php');
require_once(__ROOT__.'/services/CleOpenStudioAppCommentService.php');

/**
 * Callback for apps/open-studio/data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_app_data($machine_name, $app_route, $params, $args) {
  $data = array();
  // @todo need a better render method then this as this is lazy for now
  if (isset($params['nid']) && is_numeric($params['nid'])) {
    $node = node_load($params['nid']);
    $node_view = node_view($node);
    $rendered_node = drupal_render($node_view);
    $data = $rendered_node;
  }
  else {
    // @todo need to pull just the most recent submissions, 1 per project
    // which might be too complex of logic for this efq to express
    // get all submissions
    // unique per project
    // sort by most recent
    // ... ugh... this is more complex then this
    // pull together all the submissions they should be seeing
    $options = new stdClass();
    // only show things marked ready for feedback
    $options->state = array('submission_ready', '=');
    // @todo we need to pull only what we're asked for as a range
    // this way we don't destroy the UI in huge classes
    // invoke our submission service to get submissions
    $service = new CleOpenStudioAppSubmissionService();
    $data = $service->getSubmissions($options);
    if (!empty($data)) {
      $status = 200;
    }
  }
  return array(
    'status' => 200,
    'data' => $data
  );
}