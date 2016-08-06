<?php
/**
 * @file
 * mooc_content_theming.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function mooc_content_theming_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_fa_primary_color'.
  $field_bases['field_fa_primary_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_fa_primary_color',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'jquery_colorpicker',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'jquery_colorpicker',
  );

  // Exported field_base: 'field_fa_secondary_color'.
  $field_bases['field_fa_secondary_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_fa_secondary_color',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'jquery_colorpicker',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'jquery_colorpicker',
  );

  // Exported field_base: 'field_instructional_significance'.
  $field_bases['field_instructional_significance'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_instructional_significance',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'page' => 'Reading',
        'demonstration' => 'Demonstration',
        'interview' => 'Interview',
        'lecture' => 'Lecture',
        'exercise' => 'Exercise',
        'writing' => 'Writing',
        'assignment' => 'Assignment',
        'groupwork' => 'Group work',
        'finalproject' => 'Final project',
        'critique' => 'Critique',
        'speechballoons' => 'Discussion',
        'recitation' => 'Recitation',
        'seminar' => 'Seminar',
        'workshop' => 'Workshop',
        'quiz' => 'Quiz',
        'exam' => 'Exam / Mid-term',
        'final' => 'Final Exam',
      ),
      'allowed_values_function' => '',
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_mooc_image'.
  $field_bases['field_mooc_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mooc_image',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  return $field_bases;
}
