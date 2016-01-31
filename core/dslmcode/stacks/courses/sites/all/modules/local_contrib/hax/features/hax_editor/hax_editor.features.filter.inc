<?php
/**
 * @file
 * hax_editor.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function hax_editor_filter_default_formats() {
  $formats = array();

  // Exported format: Hax editor.
  $formats['hax_editor'] = array(
    'format' => 'hax_editor',
    'name' => 'Hax editor',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<figure> <figcaption> <details> <aside> <article> <div> <fn> <object> <embed> <param> <h2> <h3> <h4> <h5> <h6> <em> <iframe> <video> <strong> <img> <blockquote> <cite> <sup> <sub> <p> <ul> <ol> <li> <dl> <dt> <dd> <a> <table> <tr> <td> <th> <tbody> <thead> <tfoot> <colgroup> <caption> <hr>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
    ),
  );

  return $formats;
}
