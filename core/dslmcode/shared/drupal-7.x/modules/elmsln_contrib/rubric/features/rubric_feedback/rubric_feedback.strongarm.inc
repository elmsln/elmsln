<?php
/**
 * @file
 * rubric_feedback.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function rubric_feedback_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'audioconverter';
  $strongarm->value = '0';
  $export['audioconverter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'audioconverter_all';
  $strongarm->value = '0';
  $export['audioconverter_all'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'audioconverter_field_rubric_feedback_audio';
  $strongarm->value = 1;
  $export['audioconverter_field_rubric_feedback_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'audioconverter_on_save';
  $strongarm->value = '1';
  $export['audioconverter_on_save'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'audioconverter_wav_setting';
  $strongarm->value = '0';
  $export['audioconverter_wav_setting'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_rubric_submission_assessment';
  $strongarm->value = 0;
  $export['comment_anonymous_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_rubric_submission_assessment';
  $strongarm->value = 1;
  $export['comment_default_mode_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_rubric_submission_assessment';
  $strongarm->value = '50';
  $export['comment_default_per_page_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_rubric_submission_assessment';
  $strongarm->value = 1;
  $export['comment_form_location_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_rubric_submission_assessment';
  $strongarm->value = '1';
  $export['comment_preview_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_rubric_submission_assessment';
  $strongarm->value = '0';
  $export['comment_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_rubric_submission_assessment';
  $strongarm->value = 1;
  $export['comment_subject_field_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ffmpeg_executable_command';
  $strongarm->value = ' -i %audiofile %convertfile';
  $export['ffmpeg_executable_command'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ffmpeg_executable_path';
  $strongarm->value = '/usr/bin/avconv';
  $export['ffmpeg_executable_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__rubric_submission_assessment';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_rubric_submission_assessment';
  $strongarm->value = array();
  $export['menu_options_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_rubric_submission_assessment';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_rubric_submission_assessment';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_rubric_submission_assessment';
  $strongarm->value = '0';
  $export['node_preview_rubric_submission_assessment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_rubric_submission_assessment';
  $strongarm->value = 0;
  $export['node_submitted_rubric_submission_assessment'] = $strongarm;

  return $export;
}
