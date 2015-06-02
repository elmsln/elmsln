<?php
/**
 * @file
 * cis_ux.delta.inc
 */

/**
 * Implements hook_delta_default_templates().
 */
function cis_ux_delta_default_templates() {
  $export = array();

  $delta = new stdClass();
  $delta->disabled = FALSE; /* Edit this to true to make a default delta disabled initially */
  $delta->api_version = 3;
  $delta->machine_name = 'course_display';
  $delta->name = 'Course display';
  $delta->description = 'Delta to use for course displays';
  $delta->theme = 'chamfer';
  $delta->mode = 'preserve';
  $delta->parent = '';
  $delta->settings = array(
    'theme_chamfer_settings' => array(
      'toggle_main_menu' => 0,
      'toggle_secondary_menu' => 0,
      'alpha_toggle_feed_icons' => 1,
      'alpha_region_postscript_second_zone' => NULL,
      'alpha_region_postscript_second_equal_height_element' => FALSE,
      'alpha_region_sidebar_first_zone' => NULL,
      'alpha_region_sidebar_first_columns' => '12',
      'alpha_region_sidebar_first_weight' => '2',
      'alpha_region_sidebar_first_position' => '2',
      'alpha_region_sidebar_first_equal_height_element' => FALSE,
      'alpha_region_postscript_third_zone' => NULL,
      'alpha_region_postscript_third_equal_height_element' => FALSE,
      'alpha_region_postscript_fourth_zone' => NULL,
      'alpha_region_postscript_fourth_equal_height_element' => FALSE,
      'alpha_region_postscript_first_zone' => NULL,
      'alpha_region_postscript_first_columns' => '12',
      'alpha_region_postscript_first_weight' => '5',
      'alpha_region_postscript_first_position' => '6',
      'alpha_region_postscript_first_equal_height_element' => FALSE,
      'alpha_zone_postscript_order' => 1,
      'alpha_zone_postscript_weight' => '2',
      'alpha_zone_content_wrapper' => 0,
      'alpha_zone_content_weight' => '0',
      'alpha_region_sidebar_second_columns' => '4',
      'alpha_region_sidebar_second_weight' => '1',
      'alpha_region_sidebar_second_position' => '1',
      'alpha_region_content_columns' => '8',
      'alpha_region_content_weight' => '0',
    ),
  );
  $export['course_display'] = $delta;

  return $export;
}
