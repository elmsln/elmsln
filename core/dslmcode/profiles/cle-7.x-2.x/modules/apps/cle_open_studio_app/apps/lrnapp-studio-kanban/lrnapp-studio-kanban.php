<?php
/**
 * Callback for apps/lrnapp-studio-kanban/project-data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_studio_kanban_project_data($machine_name, $app_route, $params, $args) {
  $return = array();
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
          $metadata = array(
            'canCritique' => 0,
            'canUpdate' => 0,
            'canDelete' => 0,
            'critiqueLink' => '',
            'deleteLink' => base_path() . 'node/' . $assignment->nid . '/delete?destination=' . $app_route,
            'updateLink' => base_path() . 'node/' . $assignment->nid . '/edit?destination=' . $app_route,
          );
          // see the operations they can perform here
          if (entity_access('update', 'node', $assignment)) {
            $metadata['canUpdate'] = 1;
          }
          if (entity_access('delete', 'node', $assignment)) {
            $metadata['canDelete'] = 1;
          }
          $tmp['title'] = $assignment->title;
          $tmp['icon'] = 'assignment';
          $tmp['id'] = $assignment->nid;
          $tmp['metadata'] = $metadata;
          $tmp['body'] = $assignment->field_assignment_description['und'][0]['safe_value'];
          $return['project-' . $project->nid]->assignments['assignment-' . $step['target_id']] = $tmp;
        }
      }
      $return['project-' . $project->nid]->body = $project->field_project_description['und'][0]['safe_value'];
  }
  return array(
    'status' => 200,
    'data' => $return
  );
}