<?php

/**
 * @file
 * Contains the thread from URL argument default plugin.
 */

/**
 * Default argument plugin to extract a thread via menu_get_object
 *
 * This plugin actually has no options so it odes not need to do a great deal.
 */
class harmony_core_views_plugin_argument_default_thread extends views_plugin_argument_default {
  function get_argument() {
    foreach (range(1, 3) as $i) {
      $thread = menu_get_object('harmony_thread', $i);
      if (!empty($thread)) {
        return $thread->thread_id;
      }
    }

    if (arg(0) == 'thread' && ctype_digit((string) arg(1))) {
      return arg(1);
    }
  }
}
