<?php
/**
 * @file
 * mooc_textbook.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_textbook_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function mooc_textbook_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['filters']['cis_filter'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -49,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['ckeditor_link_filter']['weight'] = -45; /* WAS: -47 */
    $data['textbook_editor']['filters']['filter_footnotes'] = array(
      'settings' => array(
        'footnotes_collapse' => 0,
      ),
      'status' => 1,
      'weight' => -39,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['filter_tokens'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -42,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['shortcode'] = array(
      'settings' => array(
        'box' => 1,
        'button' => 1,
        'col' => 1,
        'contact' => 1,
        'divider' => 1,
        'dropcap' => 1,
        'dropshadow' => 1,
        'highlight' => 1,
        'icon-list' => 0,
        'social' => 1,
        'teaser' => 0,
        'toggle' => 0,
      ),
      'status' => 1,
      'weight' => -46,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['shortcode_text_corrector'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -47,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['weight'] = -41; /* WAS: 0 */
  }
}

/**
 * Implements hook_wysiwyg_default_profiles_alter().
 */
function mooc_textbook_wysiwyg_default_profiles_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['settings']['buttons']['drupal'] = array(
      'rendered_entity' => 1,
      'shortcode_wysiwyg' => 1,
      'token_insert_wysiwyg' => 1,
    ); /* WAS: '' */
    $data['textbook_editor']['settings']['buttons']['footnotes'] = array(
      'footnotes' => 1,
    ); /* WAS: '' */
  }
}
