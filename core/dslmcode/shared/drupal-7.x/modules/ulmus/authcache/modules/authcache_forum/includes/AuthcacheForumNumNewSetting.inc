<?php
/**
 * @file
 * Defines a personalization setting for retrieving the number of new topics on
 * the forum list.
 */

/**
 * Setting for retrieving new-flags on a list of forum topics.
 */
class AuthcacheForumNumNewSetting implements AuthcacheP13nSettingInterface {

  /**
   * Number of new forum topics for user.
   *
   * @see forum.module
   */
  public function get($params, $context) {
    global $user;

    // Include node.module for NODE_NEW_LIMIT.
    include_once DRUPAL_ROOT . '/modules/node/node.module';
    include_once DRUPAL_ROOT . '/modules/forum/forum.module';

    $result = array();
    foreach ($params as $tid) {
      $result[$tid] = (int) _forum_topics_unread($tid, $user->uid);
    }

    return array_filter($result);
  }

}
