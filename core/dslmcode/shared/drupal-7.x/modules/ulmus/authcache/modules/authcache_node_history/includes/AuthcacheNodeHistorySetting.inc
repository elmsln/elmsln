<?php
/**
 * @file
 * Defines a personalized setting for retrieving the last time a node was seen.
 */

/**
 * Personalized setting for retrieving the last time a node was seen.
 *
 * @see
 * - node_last_viewed()
 * - node_tag_new()
 */
class AuthcacheNodeHistorySetting implements AuthcacheP13nSettingInterface {
  protected $limit;

  /**
   * Construct a new node history setting instance.
   */
  public function __construct($select_limit, $update_limit) {
    $this->selectLimit = $select_limit;
    $this->updateLimit = $update_limit;
  }

  /**
   * Determine which comments need to be marked.
   */
  public function get($params, $context) {
    global $user;

    $tsmap = array();
    if ($user->uid) {
      if (!empty($params['n']) && is_array($params['n'])) {
        $tsmap = db_query_range('SELECT nid, timestamp FROM {history} WHERE uid = :uid AND nid IN (:nids)', 0, $this->selectLimit, array(
          ':uid' => $user->uid,
          ':nids' => $params['n'],
        ))->fetchAllKeyed();

        if (!empty($_SESSION['authcache_node_history_last_viewed'])) {
          // After a page was cleared from the cache, the first user requesting
          // it will trigger a node_tag_new and update its last viewed
          // timestamp. Therefore it is necessary to preserve the original
          // last-viewed timestamp in the session, such that it can be retrieved
          // during the subsequent personalization phase.
          $history = &drupal_static('node_last_viewed', array());
          $history = $_SESSION['authcache_node_history_last_viewed'];

          foreach ($params['n'] as $nid) {
            if (isset($history[$nid])) {
              $tsmap[$nid] = $history[$nid]->timestamp;
            }
          }
        }
        unset($_SESSION['authcache_node_history_last_viewed']);
      }

      if (!empty($params['u']) && is_array($params['u'])) {
        $n = min(count($params['u']), $this->updateLimit);
        for ($i = 0; $i < $n; $i++) {
          // Update the 'last viewed' timestamp of the specified node for
          // current user. We do not want to use node_tag_new here because it
          // requires a node_load. The following code is directly copied from
          // node_tag_new.
          db_merge('history')
            ->key(array(
              'uid' => $user->uid,
              'nid' => intval($params['u'][$i]),
            ))
            ->fields(array('timestamp' => REQUEST_TIME))
            ->execute();
        }
      }
    }

    $result = array();
    foreach ($tsmap as $nid => $ts) {
      $result[] = array(
        'nid' => $nid,
        'ts' => $ts,
      );
    }

    return $result;
  }
}
