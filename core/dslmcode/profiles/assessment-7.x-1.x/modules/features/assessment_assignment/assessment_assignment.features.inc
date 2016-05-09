<?php
/**
 * @file
 * assessment_assignment.features.inc
 */

/**
 * Implements hook_default_cer().
 */
function assessment_assignment_default_cer() {
  $items = array();
  $items['node:assessment_assignment:field_cis_course_ref*node:cis_course:field_grades_assignments_ref'] = entity_import('cer', '{
    "cer_bidirectional" : { "und" : [ { "value" : "1" } ] },
    "cer_enabled" : { "und" : [ { "value" : "1" } ] },
    "cer_left" : { "und" : [ { "path" : "node:assessment_assignment:field_cis_course_ref" } ] },
    "cer_right" : { "und" : [ { "path" : "node:cis_course:field_grades_assignments_ref" } ] },
    "cer_weight" : { "und" : [ { "value" : "0" } ] },
    "identifier" : "node:assessment_assignment:field_cis_course_ref*node:cis_course:field_grades_assignments_ref"
  }');
  $items['node:assessment_assignment:og_group_ref*node:section:field_grades_assignments_ref'] = entity_import('cer', '{
    "cer_bidirectional" : { "und" : [ { "value" : "1" } ] },
    "cer_enabled" : { "und" : [ { "value" : "1" } ] },
    "cer_left" : { "und" : [ { "path" : "node:assessment_assignment:og_group_ref" } ] },
    "cer_right" : { "und" : [ { "path" : "node:section:field_grades_assignments_ref" } ] },
    "cer_weight" : { "und" : [ { "value" : "0" } ] },
    "identifier" : "node:assessment_assignment:og_group_ref*node:section:field_grades_assignments_ref"
  }');
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function assessment_assignment_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function assessment_assignment_node_info() {
  $items = array(
    'assessment_assignment' => array(
      'name' => t('Assignment'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
