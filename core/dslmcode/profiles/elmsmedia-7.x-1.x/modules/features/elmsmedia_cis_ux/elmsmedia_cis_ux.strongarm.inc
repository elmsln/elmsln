<?php
/**
 * @file
 * elmsmedia_cis_ux.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_cis_ux_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_author_options';
  $strongarm->value = array();
  $export['jammer_author_options'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_body_options';
  $strongarm->value = array();
  $export['jammer_body_options'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_comment_settings';
  $strongarm->value = array(
    'audio' => 'audio',
    'cis_course' => 'cis_course',
    'section' => 'section',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'video' => 'video',
  );
  $export['jammer_comment_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_delete_button_unset_node_types';
  $strongarm->value = array();
  $export['jammer_delete_button_unset_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_menu_options';
  $strongarm->value = array(
    'audio' => 'audio',
    'cis_course' => 'cis_course',
    'section' => 'section',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'video' => 'video',
  );
  $export['jammer_menu_options'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_node_promoted';
  $strongarm->value = 1;
  $export['jammer_node_promoted'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_node_sticky';
  $strongarm->value = 1;
  $export['jammer_node_sticky'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_path_options';
  $strongarm->value = array(
    'audio' => 'audio',
    'cis_course' => 'cis_course',
    'section' => 'section',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'video' => 'video',
  );
  $export['jammer_path_options'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_preview_button_unset_node_types';
  $strongarm->value = array(
    'audio' => 'audio',
    'cis_course' => 'cis_course',
    'section' => 'section',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'video' => 'video',
  );
  $export['jammer_preview_button_unset_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_revision_information';
  $strongarm->value = array(
    'audio' => 'audio',
    'cis_course' => 'cis_course',
    'section' => 'section',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'video' => 'video',
  );
  $export['jammer_revision_information'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_revision_log_textarea_unset_node_types';
  $strongarm->value = array(
    'audio' => 'audio',
    'cis_course' => 'cis_course',
    'section' => 'section',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'video' => 'video',
  );
  $export['jammer_revision_log_textarea_unset_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_submit_button_unset_node_types';
  $strongarm->value = array();
  $export['jammer_submit_button_unset_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_teaser_controls_unset_node_types';
  $strongarm->value = array(
    'audio' => 'audio',
    'cis_course' => 'cis_course',
    'section' => 'section',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'video' => 'video',
  );
  $export['jammer_teaser_controls_unset_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_user_delete_hide_button';
  $strongarm->value = 0;
  $export['jammer_user_delete_hide_button'] = $strongarm;

  return $export;
}
