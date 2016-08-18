<?php

/**
 * @file
 *   drush integration for modernizr.
 */

/**
 * Implements hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * For a list of recognized keys,
 * @see drush_parse_command()
 *
 * @return
 *   An associative array describing your command(s).
 */
function modernizr_drush_command() {
  $items = array();

  $items['modernizr-dev'] = array(
    'callback'    => '_modernizr_drush_download_dev',
    'description' => dt('This command used to download a development copy of Modernizr but it is no longer offered on modernizr.com as of v3'),
    'aliases'     => array('mdl'),
  );
  $items['modernizr-build'] = array(
    'callback'    => '_modernizr_drush_custom_build',
    'description' => dt('Requests a custom build of Modernizr based on your Drupal module settings. Depends on node.js/npm.'),
    'aliases'     => array('mcb'),
    'arguments'   => array(),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function modernizr_drush_help($section) {
  switch ($section) {
    case 'error:modernizr-dev':
    case 'drush:modernizr-dev':
      return dt('This command used to download a development copy of Modernizr but it is no longer offered on modernizr.com as of v3');
    case 'drush:modernizr-build':
      return dt('Queries Drupal modules for any Modernizr tests they require, and creates a request for a node.js-powered CLI builder. You must install node.js, npm, and the CLI builder beforehand.');
  }
}

/**
 * Helper function downloads the uncompressed development copy of Modernizr.
 */
function _modernizr_drush_download_dev() {
  return drush_set_error('modernizr-dev');
}

/**
 * Helper function that generates a list of Modernizr tests
 * from other modules and sends them to the node.js CLI builder.
 */
function _modernizr_drush_custom_build() {
  $output_args = array();
  $args = modernizr_api_list();
  $output = '';

  // Get the map of Modernizr args.
  include_once(drupal_get_path('module', 'modernizr') . '/modernizr.args.inc');

  // Fetch all the tests, and record which modules supplied them.
  foreach ($args as $key => $test) {
    $meta = _modernizr_args_return($key);
    $type = $meta['type'];
    $output_args[$type][] = $key;
  }

  // Collapse tests into the format accepted by the node builder.
  $tests  = (isset($output_args['tests']))  ? ' -t ' . implode(' ', $output_args['tests'])  : '';
  $extras = (isset($output_args['extras'])) ? ' -e ' . implode(' ', $output_args['extras']) : '';
  $groups = (isset($output_args['groups'])) ? ' -g ' . implode(' ', $output_args['groups']) : '';
  $not    = (isset($output_args['not']))    ? ' -n ' . implode(' ', $output_args['not'])    : '';

  $output = $tests . $extras . $groups . $not;

  return $output;
}
