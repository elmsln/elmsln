<?php
/**
 * @file
 * chamfer_defaults.box.inc
 */

/**
 * Implements hook_default_box().
 */
function chamfer_defaults_default_box() {
  $export = array();

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'site_footer';
  $box->plugin_key = 'simple';
  $box->title = '<none>';
  $box->description = 'Site Footer';
  $box->options = array(
    'body' => array(
      'value' => '',
      'format' => 'plain_text',
    ),
    'additional_classes' => '',
  );
  $export['site_footer'] = $box;

  return $export;
}
