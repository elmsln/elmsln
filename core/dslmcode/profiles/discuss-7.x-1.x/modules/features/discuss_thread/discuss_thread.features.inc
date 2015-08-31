<?php
/**
 * @file
 * discuss_thread.features.inc
 */

/**
 * Implements hook_default_harmony_thread_type().
 */
function discuss_thread_default_harmony_thread_type() {
  $items = array();
  $items['harmony_thread'] = entity_import('harmony_thread_type', '{ "type" : "harmony_thread", "label" : "Thread" }');
  return $items;
}
