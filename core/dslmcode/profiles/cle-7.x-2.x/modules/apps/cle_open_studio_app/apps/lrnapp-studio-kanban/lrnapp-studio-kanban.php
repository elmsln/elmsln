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
 * Callback for apps/lrnapp-studio-kanban/project-data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_studio_kanban_project_data($machine_name, $app_route, $params, $args) {
  $data = array();
  $status = 404;
  // see if we're doing updates from the app
  if (isset($params['submissionid'])) {
    // load the submission node, typecasting
    $submission = node_load($params['submissionid']);
    // ensure they have access to this
    if (entity_access('update', 'node', $submission)) {
      // simple toggle of true / false on submission state
      if ($params['status'] == 'true') {
        $submission->field_submission_state[LANGUAGE_NONE][0]['value'] = 'submission_ready';
      }
      else {
        $submission->field_submission_state[LANGUAGE_NONE][0]['value'] = 'submission_in_progress';
      }
      // save the node
      node_save($submission);
      // load the assignment this was related to
      $assignment = node_load($submission->field_assignment[LANGUAGE_NONE][0]['target_id']);
      // rebuild the part of the metadata array for the front-end and ship it off
      $data = _cle_submission_submission_status($assignment);
      $status = 200;
    }
    else {
      $status = 403;
    }
  }
  else {
    $data = array();
    $options = new stdClass();
    $options->order = array();
    $service = new CleOpenStudioAppProjectService();
    $data = $service->getProjects($options);
    if (!empty($data)) {
      $status = 200;
      foreach ($data as $key => &$project) {
        $project->relationships->assignments = array();
        // loop through the steps and pull in all the assignments
        foreach ($project->attributes->steps as $step) {
          $assignment = node_load($step->id);
          if (isset($assignment->nid)) {
            $project->relationships->assignments['assignment-' . $assignment->nid] = _cle_assignment_v1_assignment_output($assignment, $app_route);
          }
        }
      }
    }

  }
  return array(
    'status' => $status,
    'data' => $data
  );
}