<?php
/**
 * @file
 * cis_breakpoints.default_breakpoint_group.inc
 */

/**
 * Implements hook_default_breakpoint_group().
 */
function cis_breakpoints_default_breakpoint_group() {
  $export = array();

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'custom.user.cis_phone';
  $breakpoints[] = 'custom.user.cis_tablet';
  $breakpoints[] = 'custom.user.cis_lappy';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'cis_course';
  $breakpoint_group->name = 'CIS Course';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'custom';
  $breakpoint_group->overridden = 0;
  $export['cis_course'] = $breakpoint_group;

  return $export;
}
