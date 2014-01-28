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
      'weight' => -50,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['filter_footnotes'] = array(
      'settings' => array(
        'footnotes_collapse' => 0,
      ),
      'status' => 1,
      'weight' => -20,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['filter_html']['settings']['allowed_html'] = '<div> <legend> <fieldset> <h2> <h3> <h4> <h5> <h6> <em> <iframe> <video> <strong> <img> <br> <blockquote> <cite> <sup> <sub> <p> <ul> <ol> <li> <dl> <dt> <dd> <a> <table> <tr> <td> <th> <tbody> <thead> <tfoot> <colgroup> <caption> <hr> <fn>'; /* WAS: '<div> <h2> <object> <embed> <param> <h3> <h4> <h5> <h6> <em> <iframe> <video> <strong> <img> <blockquote> <cite> <sup> <sub> <p> <ul> <ol> <li> <dl> <dt> <dd> <a> <table> <tr> <td> <th> <tbody> <thead> <tfoot> <colgroup> <caption> <hr>' */
    $data['textbook_editor']['filters']['filter_html']['weight'] = -49; /* WAS: -50 */
    $data['textbook_editor']['filters']['filter_tokens'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -44,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['nrhi'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -42,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['weight'] = -43; /* WAS: 0 */
  }
}

/**
 * Implements hook_wysiwyg_default_profiles_alter().
 */
function mooc_textbook_wysiwyg_default_profiles_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['settings']['buttons']['drupal'] = array(
      'rendered_entity' => 1,
      'token_insert_wysiwyg' => 1,
    ); /* WAS: '' */
    $data['textbook_editor']['settings']['buttons']['footnotes'] = array(
      'footnotes' => 1,
    ); /* WAS: '' */
  }
}
