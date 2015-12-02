<?php

/**
 * @file
 * Contains the post from URL argument default plugin.
 */

/**
 * Default argument plugin to extract a post via menu_get_object
 *
 * This plugin actually has no options so it odes not need to do a great deal.
 */
class harmony_core_views_plugin_argument_default_post extends views_plugin_argument_default {
  function get_argument() {
    foreach (range(1, 3) as $i) {
      $post = menu_get_object('harmony_post', $i);
      if (!empty($post)) {
        return $post->post_id;
      }
    }

    if (arg(0) == 'post' && ctype_digit((string) arg(1))) {
      return arg(1);
    }
  }
}
