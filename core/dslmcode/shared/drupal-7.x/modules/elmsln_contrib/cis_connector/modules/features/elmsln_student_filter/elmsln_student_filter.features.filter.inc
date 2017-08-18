<?php
/**
 * @file
 * elmsln_student_filter.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function elmsln_student_filter_filter_default_formats() {
  $formats = array();

  // Exported format: Student format.
  $formats['student_format'] = array(
    'format' => 'student_format',
    'name' => 'Student format',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_url' => array(
        'weight' => -45,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -42,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_html' => array(
        'weight' => -41,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <h3> <iframe> <code> <ul> <ol> <li> <video> <source> <img>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
    ),
  );

  // Exported format: Student Markdown Format.
  $formats['student_markdown'] = array(
    'format' => 'student_markdown',
    'name' => 'Student Markdown Format',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <h3> <iframe> <code> <ul> <ol> <li> <video> <source> <img> <lrn-math>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
    ),
  );

  return $formats;
}
