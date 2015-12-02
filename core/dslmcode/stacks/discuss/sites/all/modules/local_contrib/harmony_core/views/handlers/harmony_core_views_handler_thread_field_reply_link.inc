<?php

/**
 * @file
 * Definition of harmony_core_views_handler_thread_field_link.
 */

/**
 * Field handler to present a link to the thread's reply form.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_thread_field_reply_link extends harmony_core_views_handler_thread_field_link {
  function render_link($thread, $values) {
    // Bail out if the user can't even see the thread.
    if (!harmony_core_thread_access_callback('view', $thread)) {
      return;
    }

    // Check that the thread is open.
    $thread_properties = harmony_core_thread_get_properties(NULL, $thread);
    if (!empty($thread_properties['can_post_in']) && !$thread_properties['can_post_in']) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $return_link = FALSE;

    // Output the link if the user has access, otherwise provide a link
    // via the login page.
    if (harmony_core_thread_access_callback('create', $thread)) {
      $this->options['alter']['path'] = 'post/add';
      $this->options['alter']['query'] = array('field_harmony_thread' => $thread->thread_id);
      $this->options['alter']['link_class'] = 'reply-link';
      $return_link = TRUE;
    }
    // NEED AN ELSE IF HERE FOR "If the user doesn't have access to create within the thread and is anonymous, output the link anyway?"
    else {
      global $user;

      if (!$user->uid) {
        $this->options['alter']['path'] = 'user';
        $this->options['alter']['query'] = array(
          'destination' => url('post/add', array(
            'query' => array(
              'field_harmony_thread' => $thread->thread_id,
            ),
          )),
        );
        $this->options['alter']['link_class'] = 'login-link';
        $return_link = TRUE;
      }
    }

    if ($return_link) {
      return !empty($this->options['text']) ? $this->tokenize_value(check_plain($this->options['text'])) : t('reply');
    }
  }
}
