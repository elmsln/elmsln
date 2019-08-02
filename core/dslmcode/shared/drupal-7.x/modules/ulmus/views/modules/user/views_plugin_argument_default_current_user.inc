<?php

/**
 * @file
 * Definition of views_plugin_argument_default_current_user.
 */

/**
 * Default argument plugin to extract the global $user.
 *
 * This plugin actually has no options so it odes not need to do a great deal.
 */
class views_plugin_argument_default_current_user extends views_plugin_argument_default {

  /**
   * {@inheritdoc}
   */
  public function get_argument() {
    global $user;
    return $user->uid;
  }

}
