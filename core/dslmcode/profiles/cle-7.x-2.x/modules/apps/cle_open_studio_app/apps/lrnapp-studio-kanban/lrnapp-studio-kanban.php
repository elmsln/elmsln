<?php
/**
 * Callback for apps/lrnapp-studio-kanban/project-data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_studio_kanban_project_data($machine_name, $app_route, $params, $args) {
  $return = array();
  $status = 200;
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
      $return = _cle_submission_submission_status($assignment);
    }
    else {
      $status = 403;
    }
  }
  else {
    // find all the projects for the current section
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    $field_conditions = array(
      'og_group_ref' => array('target_id', $section, '='),
    );
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    $data = _cis_connector_assemble_entity_list('node', 'cle_project', 'nid', '_entity', $field_conditions, $property_conditions);
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
  }
  return array(
    'status' => $status,
    'data' => $return
  );
}