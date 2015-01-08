<?php

/**
 * @file
 * Definition of harmony_core_views_handler_field_thread_read_history_timestamp.
 */

/**
 * Field handler to display the marker for new content.
 *
 * The handler is named such because of compability reasons, the table
 * is thread_read_history.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_field_thread_read_history_timestamp extends harmony_core_views_handler_thread_field {
  function init(&$view, &$options) {
    parent::init($view, $options);
    global $user;
    if ($user->uid) {
      $this->additional_fields['created'] = array('table' => 'harmony_thread', 'field' => 'created');
      $this->additional_fields['updated'] = array('table' => 'harmony_thread', 'field' => 'updated');
    }
  }

  function query() {
    // Only add ourselves to the query if logged in.
    global $user;
    if (!$user->uid) {
      return;
    }
    parent::query();
  }

  function render($values) {
    // Let's default to 'read' state.
    // This code shadows node_mark, but it reads from the db directly and
    // we already have that info.
    $mark = MARK_READ;
    global $user;
    if ($user->uid) {
      $last_read = $this->get_value($values);
      $updated = $this->get_value($values, 'updated');

      if (!$last_read && $updated > variable_get('harmony_core_thread_new_limit', 2592000)) {
        $mark = MARK_NEW;
      }
      elseif ($updated > $last_read && $updated > variable_get('harmony_core_thread_new_limit', 2592000)) {
        $mark = MARK_UPDATED;
      }
      return $this->render_link(theme('mark', array('type' => $mark)), $values);
    }
  }
}
