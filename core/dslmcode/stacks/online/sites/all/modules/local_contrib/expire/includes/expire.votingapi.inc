<?php

/**
 * @file
 * Provides class that expires voted objects' pages.
 */

class ExpireVotingapi implements ExpireInterface {

  /**
   * Executes expiration actions for user.
   *
   * @param $votes
   *   Array of votes.
   *   See votingapi_set_votes() to get more info about array params.
   *
   * @param $action
   *   Action that has been executed.
   *
   * @param $skip_action_check
   *   Shows whether should we check executed action or just expire node.
   */
  public function expire($votes, $action, $skip_action_check = FALSE) {

    if (empty($votes)) {
      return;
    }

    // Some vote actions may be executed one after another. To avoid
    // duplicate flushes we should check whether cache was already flushed.
    static $cache_flushed = FALSE;
    if ($cache_flushed) {
      return;
    }

    $enabled_actions = variable_get('expire_votingapi_actions', array());
    $enabled_actions = array_filter($enabled_actions);

    // Stop further expiration if executed action is not selected by admin.
    if (!in_array($action, $enabled_actions) && !$skip_action_check) {
      return;
    }

    $expire_urls = array();

    foreach ($votes as $vote) {

      $entity_type = $vote['entity_type'];
      $entity_id = $vote['entity_id'];

      // Expire voted entity url.
      $expire_entity_page = variable_get('expire_votingapi_entity_page', EXPIRE_VOTINGAPI_ENTITY_PAGE);
      if ($expire_entity_page) {

        // Load entity.
        $entity = _expire_load_single_entity($entity_type, $entity_id);

        // Check whether entity is loaded.
        if (!empty($entity)) {

          // Check whether entity has uri.
          $uri = entity_uri($entity_type, $entity);
          if (!empty($uri['path'])) {
            $expire_urls['vote-' . $entity_type . '-' . $entity_id] = $uri['path'];
          }
        }
      }

      // Execute expiration for voted entity.
      $expire_entity = variable_get('expire_votingapi_entity', EXPIRE_VOTINGAPI_ENTITY_PAGE);
      if ($expire_entity) {

        // Load entity.
        $entity = _expire_load_single_entity($entity_type, $entity_id);
        $handler = _expire_get_expiration_handler($entity_type);
        if (is_object($handler) && !empty($entity)) {
          $handler->expire($entity, 0, $skip_action_check = TRUE);
        }
      }

      // Expire custom pages.
      $expire_custom = variable_get('expire_votingapi_custom', EXPIRE_VOTINGAPI_CUSTOM);
      if ($expire_custom) {
        $pages = variable_get('expire_votingapi_custom_pages');

        // Load voted entity.
        $entities = entity_load($entity_type, array($entity_id));

        // Check whether entity is loaded.
        if (isset($entities[$entity_id])) {
          $entity = $entities[$entity_id];

          $urls = ExpireAPI::expireCustomPages($pages, array($entity_type => $entity));
          $expire_urls = array_merge($expire_urls, $urls);
        }
      }

    }

    // Flush page cache for expired urls.
    ExpireAPI::executeExpiration($expire_urls, 'votingapi', $votes);

    $cache_flushed = TRUE;
  }

}
