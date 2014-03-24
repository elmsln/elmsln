<?php
/**
 * @file
 * How to work with the CIS automation scripts.
 */

/**
 * Implements hook_cis_service_instance_options_alter().
 *
 * This allows for the altering of options (drush calls)
 * just prior to creation of the service based on a course.
 * Course / service are also passed in for context
 *
 * @param $options
 *   array of drush commands
 * @param $course
 *   node object
 * @param $service
 *   node object
 */
function hook_cis_service_instance_options_alter(&$options, $course, $service) {
  // run drush dis pathauto as part of the install routine
  $options['dis'][] = 'pathauto';
  // run drush en devel as part of setup
  $options['en'][] = 'devel';
}

/**
 * Implements hook_cis_service_instance_TOOL_options_alter().
 *
 * This allows for the altering of options (drush calls)
 * just prior to creation of the service based on a course.
 * This hook is specific to the machine_name of the tool being produced.
 *
 * To integrate with home-grown distributions you can replace TOOL with the
 * machine_name of the service, such as courses, blog, interact, etc.
 *
 * @param $options
 *   array of drush commands
 * @param $course
 *   node object
 * @param $service
 *   node object
 */
function hook_cis_service_instance_TOOL_options_alter(&$options, $course, $service) {
  // run drush dis pathauto as part of the install routine
  $options['dis'][] = 'pathauto';
  // run drush en devel as part of setup
  $options['en'][] = 'devel';
}

/**
 * Implements hook_cis_instructional_outlines_alter().
 *
 * This allows for the altering of listed instructional outlines
 * Use this to add your own instructional outlines for selection
 * during section setup.
 * This simply adds the options for selecting it, you'll still need
 * a hook_entity_insert / update handler to correctly handle this.
 * A common use-case for this is overriding traditional remote
 * reference and setup of an outline to allow for creation of a new
 * one based on a pre-packaged XML outline of content.
 *
 * @param $outlines
 *   an array of possible outlines to select from.
 */
function hook_cis_instructional_outlines(&$outlines) {
  // allow for module based, paced instruction
  $outlines['module-based'] = t('Module based');
}
