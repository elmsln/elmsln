<?php

/**
 * @file
 * Hooks provided by the Feedback module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Act on an array of feedback entry objects when loaded from the database.
 *
 * @param $entries
 *   An array of feedback entry objects, indexed by fid.
 */
function hook_feedback_load($entries) {
  $result = db_query('SELECT * FROM {my_table} WHERE fid IN (:fids)', array(':fids' => array_keys($entries)));
  foreach ($result as $record) {
    $entries[$record->fid]->foo = $result->foo;
  }
}

/**
 * Act on a feedback entry before it is saved.
 *
 * Modules implementing this hook can act on the feedback entry object before it
 * is inserted or updated.
 *
 * @param $entry
 *   The feedback entry object.
 */
function hook_feedback_presave($entry) {
  $entry->foo = 'bar';
}

/**
 * Respond to creation of a new feedback entry.
 *
 * @param $entry
 *   The feedback entry object.
 *
 * @see hook_feedback_update()
 */
function hook_feedback_insert($entry) {
  db_insert('mytable')
    ->fields(array(
      'fid' => $entry->fid,
      'extra' => $entry->extra,
    ))
    ->execute();
}

/**
 * Respond to updates to a feedback entry.
 *
 * @param $entry
 *   The feedback entry object.
 *
 * @see hook_feedback_insert()
 */
function hook_feedback_update($entry) {
  db_update('mytable')
    ->fields(array('extra' => $entry->extra))
    ->condition('fid', $entry->fid)
    ->execute();
}

/**
 * Respond to deletion of a feedback entry.
 *
 * @param $entry
 *   The feedback entry object.
 *
 * @see feedback_delete_multiple()
 */
function hook_feedback_delete($entry) {
  db_delete('mytable')
    ->condition('fid', $entry->fid)
    ->execute();
}

/**
 * The feedback entry is being displayed.
 *
 * The module should format its custom additions for display and add them to the
 * $entry->content array.
 *
 * @param $entry
 *   The feedback entry object.
 * @param $view_mode
 *   View mode, e.g. 'full'.
 * @param $langcode
 *   The language code used for rendering.
 *
 * @see hook_feedback_view_alter()
 * @see hook_entity_view()
 */
function hook_feedback_view($entry, $view_mode, $langcode) {
  $entry->content['foo'] = array(
    '#markup' => t('Bar'),
  );
}

/**
 * The feedback entry was built; the module may modify the structured content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * @param $build
 *   A renderable array representing the feedback entry.
 *
 * @see feedback_view()
 * @see hook_entity_view_alter()
 */
function hook_feedback_view_alter(&$build) {
  // Check for the existence of a field added by another module.
  if (isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;
  }

  // Add a #post_render callback to act on the rendered HTML of the entry.
  $build['#post_render'][] = 'my_module_feedback_post_render';
}

/**
 * @} End of "addtogroup hooks".
 */
