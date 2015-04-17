<?php
/**
 * @file
 * Defines a personalization setting for retrieving the number of new comments
 * on a node.
 */

/**
 * Personalization setting for retrieving the number of new comments on a node.
 *
 * @see node.module
 */
class AuthcacheCommentNumNewSetting implements AuthcacheP13nSettingInterface {

  /**
   * Number of new comments for given nids.
   */
  public function get($params, $context) {
    include_once DRUPAL_ROOT . '/modules/node/node.module';
    include_once DRUPAL_ROOT . '/modules/comment/comment.module';

    $result = array();
    foreach ($params as $nid) {
      $result[$nid] = (int) comment_num_new($nid);
    }

    return array_filter($result);
  }

}
