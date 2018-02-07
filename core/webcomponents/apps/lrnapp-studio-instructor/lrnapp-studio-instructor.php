<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(dirname(__FILE__))));
require_once(__ROOT__.'/services/LRNAppOpenStudioSubmissionService.php');
require_once(__ROOT__.'/services/LRNAppOpenStudioProjectService.php');
require_once(__ROOT__.'/services/LRNAppOpenStudioAssignmentService.php');
require_once(__ROOT__.'/services/LRNAppOpenStudioCommentService.php');

/**
 * Callback for apps/open-studio/data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _lrnapp_studio_instructor_data($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  $options = new stdClass();
  $submissionService = new LRNAppOpenStudioSubmissionService();
  $commentService = new LRNAppOpenStudioCommentService();
  $assignmentService = new LRNAppOpenStudioAssignmentService();

  // load section
  $section_id = _cis_connector_section_context();
  // try and load by id since og_context wants a node id not our primary key
  $nid = _cis_section_load_section_by_id($section_id);
  // roster of current section
  $role = user_role_load_by_name(CIS_SECTION_STUDENT);
  $roster = _cis_section_load_users_by_gid($nid, $role->rid);
  // snag assignments
  $assignments = $assignmentService->getAssignments($options);

  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $submissions = $submissionService->getSubmissions($options);
  // student centric data to return
  $students = Array();
  $options = new stdClass();
  // walk the roster and build from there
  foreach ($roster as $uid) {
    $students[$uid] = new stdClass();
    // establish 0 for all assignments
    foreach ($assignments as $assignment) {
      $students[$uid]->assignment_comments[$assignment->nid] = 0;
    }
    // change service to get things per user
    $options->filter['author'] = $uid;
    // load comments for this user
    $comments = $commentService->getComments($options);
    // regroup based on assignment, related to the submission
    foreach ($comments as $id => $comment) {
      $submission = node_load($comment->relationships->node->data->id);
      $students[$uid]->assignment_comments[$submission->field_assignment['und'][0]['target_id']]++;
      // set author data off of the submission
      $students[$uid]->author = $comment->relationships->author->data;
    }
  }
  $data['submissions'] = $submissions;
  $data['assignments'] = $assignments;
  $data['students'] = $students;
  return array(
    'status' => $status,
    'data' => $data
  );
}