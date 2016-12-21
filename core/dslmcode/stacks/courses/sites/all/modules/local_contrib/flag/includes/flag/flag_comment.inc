<?php

/**
 * @file
 * Contains the flag_comment class.
 */

/**
 * Implements a comment flag.
 */
class flag_comment extends flag_entity {
  function options() {
    $options = parent::options();
    $options += array(
      'access_author' => '',
    );
    return $options;
  }

  /**
   * Options form extras for comment flags.
   */
  function options_form(&$form) {
    parent::options_form($form);

    $form['access']['access_author'] = array(
      '#type' => 'radios',
      '#title' => t('Flag access by content authorship'),
      '#options' => array(
        '' => t('No additional restrictions'),
        'comment_own' => t('Users may only flag own comments'),
        'comment_others' => t('Users may only flag comments by others'),
        'node_own' => t('Users may only flag comments of nodes they own'),
        'node_others' => t('Users may only flag comments of nodes by others'),
      ),
      '#default_value' => $this->access_author,
      '#description' => t("Restrict access to this flag based on the user's ownership of the content. Users must also have access to the flag through the role settings."),
    );
  }

  function type_access_multiple($entity_ids, $account) {
    $access = array();

    // If all subtypes are allowed, we have nothing to say here.
    if (empty($this->types)) {
      return $access;
    }

    // Ensure node types are granted access. This avoids a
    // node_load() on every type, usually done by applies_to_entity_id().
    $query = db_select('comment', 'c');
    $query->innerJoin('node', 'n', 'c.nid = n.nid');
    $result = $query
      ->fields('c', array('cid'))
      ->condition('c.cid', $entity_ids, 'IN')
      ->condition('n.type', $this->types, 'NOT IN')
      ->execute();
    foreach ($result as $row) {
      $access[$row->nid] = FALSE;
    }

    return $access;
  }

  function get_entity_id($comment) {
    // Store the comment object in the static cache, to avoid getting it
    // again unneedlessly.
    $this->remember_entity($comment->cid, $comment);
    return $comment->cid;
  }

  /**
   * Overrides flag_flag::get_flagging_record().
   *
   * This queries for flagging records for all comments on the node for the
   * current comment, and prefills the flag_get_user_flags() static cache with
   * the result for a performance gain.
   */
  function get_flagging_record($entity_id, $uid = NULL, $sid = NULL) {
    static $seen_comment_nids = array();

    $comment = $this->fetch_entity($entity_id);

    // Figure out if this is the first comment we've seen for its parent node.
    if (!isset($seen_comment_nids[$comment->nid])) {
      // Preload the flag_get_user_flags() static cache with flagging records
      // for all the comments on the node. This means that if multiple comments
      // on this node are being viewed, only one query is run for all their
      // flagging records, rather than one for each comment. This is because
      // flag_get_user_flags() can only optimized across flags on one entity.
      $flag_get_user_flags_cache = &drupal_static('flag_get_user_flags');

      // We need to get a row for each comment, including empty ones if there is
      // no flagging, so that the cache is warmed up for all comments. Therefore
      // the query has to have the {comment} table as its base, and include the
      // comment cid field.
      $query = db_select('comment', 'c');
      $query->leftJoin('flagging', 'f',
        "c.cid = f.entity_id AND f.entity_type = 'comment'");
      $query->fields('f')
        ->fields('c', array('cid'))
        ->condition('c.nid', $comment->nid)
        ->condition(db_or()
          // We want to include rows for comments which have no flaggings at all
          // for the current user.
          ->isNull('f.flagging_id')
          // The same conditions as flag_get_user_flags()'s query.
          ->condition(db_and()
            ->condition(db_or()
              ->condition('f.uid', $uid)
              ->condition('f.uid', 0)
            )
            ->condition('f.sid', $sid)
          )
        );

      // The result set can have multiple rows for a single comment, and rows
      // which have no flagging ID, so there's nothing useful to index it by.
      $result = $query->execute()->fetchAll();

      $flag_names = _flag_get_flag_names();
      foreach ($result as $flagging_data) {
        $cid = $flagging_data->cid;

        // At the very least, we need an empty array for the entity ID key in
        // the cache array, so it counts as present.
        if (!isset($flag_get_user_flags_cache[$uid][$sid]['comment'][$cid])) {
          $flag_get_user_flags_cache[$uid][$sid]['comment'][$cid] = array();
        }

        // If the flagging table gave us no data, we're done with this row.
        if (is_null($flagging_data->flagging_id)) {
          continue;
        }

        // Remove the comment ID field from the row, so it's just the flagging
        // table row.
        unset($flagging_data->cid);

        $flag_get_user_flags_cache[$uid][$sid]['comment'][$cid][$flag_names[$flagging_data->fid]] = $flagging_data;
      }

      // Mark that we've seen this node so we don't process it again.
      $seen_comment_nids[$comment->nid] = TRUE;
    }

    // Return data for the comment we were asked about.
    $user_flags = flag_get_user_flags($this->entity_type, $entity_id, $uid, $sid);
    return isset($user_flags[$this->name]) ? $user_flags[$this->name] : NULL;
  }

  function get_labels_token_types() {
    return array_merge(array('comment', 'node'), parent::get_labels_token_types());
  }

  function replace_tokens($label, $contexts, $options, $entity_id) {
    if ($entity_id) {
      if (($comment = $this->fetch_entity($entity_id)) && ($node = node_load($comment->nid))) {
        $contexts['node'] = $node;
        $contexts['comment'] = $comment;
      }
    }
    return parent::replace_tokens($label, $contexts, $options, $entity_id);
  }

  function get_flag_action($entity_id) {
    $flag_action = parent::get_flag_action($entity_id);
    $comment = $this->fetch_entity($entity_id);
    $flag_action->content_title = $comment->subject;
    $flag_action->content_url = $this->_flag_url("comment/$comment->cid", "comment-$comment->cid");
    return $flag_action;
  }

  function get_relevant_action_objects($entity_id) {
    $comment = $this->fetch_entity($entity_id);
    return array(
      'comment' => $comment,
      'node' => node_load($comment->nid),
    );
  }
}
