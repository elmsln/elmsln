<?php
/**
 * @file
 * discuss_thread.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function discuss_thread_field_default_field_instances_alter(&$data) {
  if (isset($data['harmony_post-harmony_post-field_harmony_text'])) {
    $data['harmony_post-harmony_post-field_harmony_text']['fences_wrapper'] = 'div'; /* WAS: '' */
    $data['harmony_post-harmony_post-field_harmony_text']['settings']['authcache'] = array(
      'clients' => array(
        'authcache_ajax' => array(
          'status' => 1,
          'weight' => 0,
        ),
      ),
      'fallback' => 'cancel',
      'lifespan' => 3600,
      'perpage' => 0,
      'peruser' => 1,
      'status' => 0,
    ); /* WAS: '' */
    $data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['allowed_formats']['harmony_filtered'] = 0; /* WAS: 'harmony_filtered' */
    $data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['allowed_formats']['student_format'] = 'student_format'; /* WAS: '' */
    $data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['allowed_formats']['textbook_editor'] = 0; /* WAS: '' */
    $data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['default_order_wrapper']['formats']['student_format'] = array(
      'weight' => 0,
    ); /* WAS: '' */
    $data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['default_order_wrapper']['formats']['textbook_editor'] = array(
      'weight' => -10,
    ); /* WAS: '' */
    unset($data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['allowed_formats']['filtered_html']);
    unset($data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['allowed_formats']['full_html']);
    unset($data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['default_order_wrapper']['formats']['filtered_html']);
    unset($data['harmony_post-harmony_post-field_harmony_text']['settings']['better_formats']['default_order_wrapper']['formats']['full_html']);
  }
}

/**
 * Implements hook_default_harmony_thread_type().
 */
function discuss_thread_default_harmony_thread_type() {
  $items = array();
  $items['harmony_thread'] = entity_import('harmony_thread_type', '{ "type" : "harmony_thread", "label" : "Thread" }');
  return $items;
}
