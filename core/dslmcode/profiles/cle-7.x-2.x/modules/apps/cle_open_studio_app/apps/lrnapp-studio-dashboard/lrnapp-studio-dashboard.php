<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(__FILE__)));
require_once(__ROOT__.'/services/CleOpenStudioAppSubmissionService.php');
require_once(__ROOT__.'/services/CleOpenStudioAppFileService.php');
require_once(__ROOT__.'/services/CleOpenStudioAppCommentService.php');

/**
 * Callback for getting comment data out of Drupal
 */
function _lrnapp_studio_dashboard_recent_comments($machine_name, $app_route, $params, $args) {
  $data = array();
  $status = 404;
  $options = new stdClass();
  $options->order = array('property' => array(array('changed', 'DESC')));
  $options->limit = array(0, 3);
  // invoke our submission service to get submissions
  $service = new CleOpenStudioAppCommentService();
  $data = $service->getComments($options);
  if (!empty($data)) {
    $status = 200;
  }
  return array(
    'status' => $status,
    'data' => $data
  );
}
/**
 * Callback to get details of the recent project
 */
function _lrnapp_studio_dashboard_recent_project($machine_name, $app_route, $params, $args) {
  // get the user's last submitted submission, see what assignment it's for
  // then see what project it's for
  // then only pull that project's assignments for the response

  // find all the projects for the current section
  $orderby = array('property' => array(array('changed', 'DESC')));
  $limit = array(0, 3);
  $section_id = _cis_connector_section_context();
  $section = _cis_section_load_section_by_id($section_id);
  $field_conditions = array(
    'og_group_ref' => array('target_id', $section, '='),
  );
  $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
  $data = _cis_connector_assemble_entity_list('node', 'cle_project', 'nid', '_entity', $field_conditions, $property_conditions, $orderby, TRUE, $limit);
  foreach ($data as $project) {
    $return['project-' . $project->nid] = new stdClass();
    // calculate metadata to act on this
    $metadata = array(
      'canUpdate' => 0,
      'canDelete' => 0,
      'deleteLink' => base_path() . 'node/' . $project->nid . '/delete?destination=' . $app_route,
      'updateLink' => base_path() . 'node/' . $project->nid . '/edit?destination=' . $app_route,
    );
    // see the operations they can perform here
    if (entity_access('update', 'node', $project)) {
      $metadata['canUpdate'] = 1;
    }
    if (entity_access('delete', 'node', $project)) {
      $metadata['canDelete'] = 1;
    }
    $return['project-' . $project->nid]->metadata = $metadata;
    $return['project-' . $project->nid]->title = $project->title;
    $return['project-' . $project->nid]->id = $project->nid;
    $return['project-' . $project->nid]->assignments = array();
    // loop through the steps and pull in all the assignments
    foreach ($project->field_project_steps['und'] as $step) {
      $tmp = array();
      $assignment = node_load($step['target_id']);
      if (isset($assignment->nid)) {
        $return['project-' . $project->nid]->assignments['assignment-' . $assignment->nid] = _cle_assignment_v1_assignment_output($assignment, $app_route);
      }
    }
    $return['project-' . $project->nid]->body = $project->field_project_description['und'][0]['safe_value'];
  }
  return array(
    'status' => $status,
    'data' => $return
  );
}
/**
 * Get recent submission info
 */
function _lrnapp_studio_dashboard_recent_submissions($machine_name, $app_route, $params, $args) {
  $data = array();
  $status = 404;
  $options = new stdClass();
  $options->state = array('submission_ready', '=');
  $options->order = array('property' => array(array('changed', 'DESC')));
  $options->limit = array(0, 5);
  // invoke our submission service to get submissions
  $service = new CleOpenStudioAppSubmissionService();
  $data = $service->getSubmissions($options);
  if (!empty($data)) {
    $status = 200;
  }
  return array(
    'status' => $status,
    'data' => $data
  );
}