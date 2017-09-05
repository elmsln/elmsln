<?php
/**
 * @file
 * cle_assignment.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function cle_assignment_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cle_assignment|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_assignment';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'group_assignment_details',
        3 => 'field_assignment_description',
        5 => 'field_assignment_privacy_setting',
        7 => 'field_assignment_due_date',
        11 => 'field_assignment_late_submission',
        13 => 'field_assignment_color',
        14 => 'field_assignment_image',
        16 => 'field_assignment_feedback',
      ),
      'header' => array(
        1 => 'title',
      ),
      'right' => array(
        2 => 'group_assignment_evidence',
        4 => 'group_assignment_hierarchy',
        6 => 'field_assignment_dependencies',
        10 => 'field_assignment_project',
        19 => 'field_critique_method',
        20 => 'field_critique_outline',
        21 => 'field_critique_privacy',
        22 => 'field_elmsln_competencies',
        23 => 'field_assignment_evidence',
        24 => 'field_assignment_artifacts',
        25 => 'group_critique',
      ),
      'footer' => array(
        8 => 'og_group_ref',
      ),
      'hidden' => array(
        9 => 'options',
        12 => 'revision_information',
        15 => 'path',
        17 => 'author',
        18 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'group_assignment_details' => 'left',
      'title' => 'header',
      'group_assignment_evidence' => 'right',
      'field_assignment_description' => 'left',
      'group_assignment_hierarchy' => 'right',
      'field_assignment_privacy_setting' => 'left',
      'field_assignment_dependencies' => 'right',
      'field_assignment_due_date' => 'left',
      'og_group_ref' => 'footer',
      'options' => 'hidden',
      'field_assignment_project' => 'right',
      'field_assignment_late_submission' => 'left',
      'revision_information' => 'hidden',
      'field_assignment_color' => 'left',
      'field_assignment_image' => 'left',
      'path' => 'hidden',
      'field_assignment_feedback' => 'left',
      'author' => 'hidden',
      '_add_existing_field' => 'hidden',
      'field_critique_method' => 'right',
      'field_critique_outline' => 'right',
      'field_critique_privacy' => 'right',
      'field_elmsln_competencies' => 'right',
      'field_assignment_evidence' => 'right',
      'field_assignment_artifacts' => 'right',
      'group_critique' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => 0,
  );
  $export['node|cle_assignment|form'] = $ds_layout;

  return $export;
}
