<?php
/**
 * Callback for apps/lrnapp-cis/data.
 */
function _lrnapp_cis_app_data($machine_name, $app_route, $params, $args) {
  $return = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'course')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->propertyOrderBy('title', 'DESC')
  ->execute();
  // flip the results if it found them
  if (isset($result['node'])) {
    foreach ($result['node'] as $item) {
      $node = node_load($item->nid);
      $return[$node->nid]->id = $node->nid;
      $return[$node->nid]->data = new stdClass();
      $return[$node->nid]->data->machine_name = $node->field_machine_name['und'][0]['value'];
      $return[$node->nid]->data->name = $node->title;
      $return[$node->nid]->data->title = $node->field_course_title['und'][0]['value'];
      $return[$node->nid]->data->image = file_create_url($node->field_banner['und'][0]['uri']);
      $return[$node->nid]->data->color = 'red';
      $return[$node->nid]->data->uri = 'node/' . $node->nid;
      // build out the relationships
      $return[$node->nid]->relationships = new stdClass();
      $return[$node->nid]->program = new stdClass();
      $return[$node->nid]->program->data = new stdClass();
      $return[$node->nid]->academic = new stdClass();
      $return[$node->nid]->academic->data = new stdClass();
      // test and make sure program home exists
      if (isset($node->field_program_classification['und'][0]['target_id'])) {
        $program = node_load($node->field_program_classification['und'][0]['target_id']);
        $return[$node->nid]->program->id = $program->nid;
        $return[$node->nid]->program->data->name = $program->title;
      }
      // test and make sure academic home exists
      if (isset($node->field_academic_home['und'][0]['target_id'])) {
        $academic = node_load($node->field_academic_home['und'][0]['target_id']);
        $return[$node->nid]->academic->id = $academic->nid;
        $return[$node->nid]->academic->data->name = $academic->title;
      }
    }
  }
  return array(
    'status' => 200,
    'data' => $return
  );
}
