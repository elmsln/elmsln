<?php

class LRNAppOpenStudioCommentService {
  /**
   * Create Stub Comment based on assignment
   */
  public function createStubComment($data) {
    global $user;
    $comment = new stdClass();
    $comment->subject = t('Feedback from @name', array('@name' => $user->name));
    $comment->uid = $user->uid;
    $comment->name = $user->name;
    $comment->status = 0;
    $comment->language = LANGUAGE_NONE;
    $comment->nid = $data['nid'];
    $comment->pid = $data['pid'];
    if (user_access('post comments')) {
      try {
        comment_save($comment);
        if (isset($comment->cid)) {
          $comment->_stub = TRUE;
          return $this->encodeComment($comment, TRUE);
        }
      }
      catch (Exception $e) {
        throw new Exception($e->getMessage(), 1);
      }
    }
    return FALSE;
  }
  /**
   * Get a list of comments
   * This will take into consideration what section the user is in and what section
   * they have access to.
   * @param object $options
   *                - filter
   *                -- author
   *                -- submission
   */
  public function getComments($options) {
    $items = array();
    $field_conditions = array();
    $orderby = array();
    $limit = NULL;
    $property_conditions = array('status' => array(COMMENT_PUBLISHED, '='));
    if (isset($options)) {
      if (isset($options->filter)) {
        if (isset($options->filter['author'])) {
          // support modified operator
          if (is_array($options->filter['author'])) {
            $property_conditions['uid'] = array($options->filter['author'][0], $options->filter['author'][1]);
          }
          else {
            $property_conditions['uid'] = array($options->filter['author'], '=');
          }
        }
        if (isset($options->filter['submission'])) {
          $property_conditions['nid'] = array($options->filter['submission'], '=');
        }
      }
      if (isset($options->order)) {
        $orderby = $options->order;
      }
      if (isset($options->limit)) {
        $limit = $options->limit;
      }
    }
    $items = _cis_connector_assemble_entity_list('comment', 'comment', 'cid', '_entity', $field_conditions, $property_conditions, $orderby, TRUE, $limit, array('node_access'));
    // sort the comments into a thread
    usort($items, 'LRNAppOpenStudioCommentService::sortComments');
    $items = $this->encodeComments($items);
    return $items;
  }

  /**
   * Sort comment threads low to high.
   */
  private static function sortComments($a, $b) {
    return $a->thread - $b->thread;
  }

  /**
   * Get a single comments
   * This will take into consideration what section the user is in and what section
   * they have access to.
   *
   * @param string $id
   *    cid of the comment
   *
   * @return object
   */
  public function getComment($id) {
    $comment = comment_load($id);
    if ($comment && isset($comment->cid) && entity_access('view', 'comment', $comment)) {
      $comment = $this->encodeComment($comment);
      return $comment;
    }
    return NULL;
  }


  public function updateComment($payload, $id) {
    if ($payload) {
      // make sure we have an id to work with
      if ($id && is_numeric($id)) {
        // load the comment from drupal
        $comment = comment_load($id);
        // make sure the comment is allowed to be updated
        if ($comment && isset($comment->cid) && user_access('post comments') && ((user_access('edit own comments') && $comment->uid == $GLOBALS['user']->uid) || entity_access('update', 'comment', $comment))) {
          // decode the payload comment to the drupal comment
          $decoded_comment = $this->decodeComment($payload, $comment);
          // save the comment
          try {
            comment_save($decoded_comment);
            // encode the comment to send it back
            $encoded_comment = $this->encodeComment($decoded_comment);
            return $encoded_comment;
          }
          catch (Exception $e) {
            throw new Exception($e->getMessage());
            return;
          }
        }
      }
    }
  }

  public function likeComment($payload, $id) {
    if ($payload) {
      // make sure we have an id to work with
      if ($id && is_numeric($id)) {
        // load the comment from drupal
        $comment = comment_load($id);
        // make sure the comment is allowed to be updated / liked
        if ($comment && isset($comment->cid) && entity_access('update', 'comment', $comment)) {
          // @todo like the comment via rate / voting API
          // may be able to skip rate entirely via voting API directly
          return true;
        }
      }
    }
  }

  public function deleteComment($id) {
    if ($id && is_numeric($id)) {
      $comment = comment_load($id);
      if ($comment && isset($comment->cid) && entity_access('update', 'comment', $comment)) {
        $decoded_comment = $this->decodeComment($payload, $comment);
        // unpublish the comment
        $decoded_comment->status = 0;
        try {
          comment_save($decoded_comment);
          return true;
        }
        catch (Exception $e) {
          throw new Exception($e->getMessage());
          return;
        }
      }
    }
  }

  /**
   * Prepare a list of comments to be outputed in json
   *
   * @param array $comments
   *  An array of comment objects
   *
   * @return array
   */
  protected function encodeComments($comments) {
    if (is_array($comments)) {
      foreach ($comments as &$comment) {
        $comment = $this->encodeComment($comment);
      }
      return $comments;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single comments to be outputed in json
   *
   * @param object $comment
   *  A comment object
   *
   * @return Object
   */
  protected function encodeComment($comment, $editing = FALSE) {
    $encoded_comments = new stdClass();
    if (is_object($comment)) {
      $encoded_comments->type = 'comment';
      $encoded_comments->id = $comment->cid;
      // Attributes
      $encoded_comments->attributes = new stdClass();
      $encoded_comments->attributes->subject = $comment->subject;
      $encoded_comments->attributes->body = $comment->comment_body[LANGUAGE_NONE][0]['safe_value'];
      $encoded_comments->attributes->thread = $comment->thread;
      $tmp = explode(".", $comment->thread);
      $encoded_comments->attributes->threadDepth = count($tmp);
      $encoded_comments->attributes->parentComment = $comment->pid;
      $encoded_comments->attributes->created = Date('c', $comment->created);
      $encoded_comments->attributes->changed = Date('c', $comment->changed);
      // Metadata info
      $encoded_comments->metadata = new stdClass();
      $encoded_comments->metadata->editing = $editing;
      $encoded_comments->metadata->disabled = false;
      // Relationships
      $encoded_comments->relationships = new stdClass();
      // Author
      $encoded_comments->relationships->author = new stdClass();
      $encoded_comments->relationships->author->data = new stdClass();
      $encoded_comments->relationships->author->data->type = 'user';
      $encoded_comments->relationships->author->data->id = $comment->uid;
      $encoded_comments->relationships->author->data->name = $comment->name;
      $encoded_comments->relationships->author->data->display_name = _elmsln_core_get_user_name('full', $comment->uid);
      $encoded_comments->relationships->author->data->avatar = _elmsln_core_get_user_picture('avatar', $comment->uid);
      $encoded_comments->relationships->author->data->visual = _elmsln_core_get_user_extras($comment->uid);
      $encoded_comments->relationships->author->data->sis = _elmsln_core_get_sis_user_data($comment->uid);
      // Assignment
      $encoded_comments->relationships->node = new stdClass();
      $encoded_comments->relationships->node->data = new stdClass();
      $encoded_comments->relationships->node->data->type = 'node';
      $encoded_comments->relationships->node->data->id = $comment->nid;
      // Actions
      $encoded_comments->actions = new stdClass();
      $encoded_comments->actions->reply = entity_access('view', 'comment', $comment);
      // @todo this needs to hit the _rate_check_permissions stuff in rate module really work
      if ($editing || $comment->uid == $GLOBALS['user']->uid || !$encoded_comments->actions->reply) {
        $like = FALSE;
      }
      else {
        $like = TRUE;
      }
      // @todo actually implement this, disabled globally for now
      $encoded_comments->actions->like = FALSE;
      $edit_condition = FALSE;
      // account for lower permission accounts needing to have initially unpublished things
      if (entity_access('update', 'comment', $comment) || (isset($comment->_stub) && $comment->uid == $GLOBALS['user']->uid)) {
        $edit_condition = TRUE;
      }
      $encoded_comments->actions->edit = $edit_condition;
      // delete in our case is just unpublishing so we actually verify edit capabilities
      $encoded_comments->actions->delete = $edit_condition;

      drupal_alter('cle_open_studio_app_encode_comments', $encoded_comments);
      return $encoded_comments;
    }
    return NULL;
  }

  protected function decodeComment($payload, $comment) {
    if ($payload) {
      module_load_include('inc', 'transliteration');
      if ($payload->attributes) {
        if ($payload->attributes->subject) {
          $comment->subject = _transliteration_process(drupal_substr($payload->attributes->subject, 0, 255));
        }
        if ($payload->attributes->body) {
          $format = 'student_format';
          $comment->status = COMMENT_PUBLISHED;
          $payload->attributes->body = _transliteration_process($payload->attributes->body);
          $comment->comment_body[LANGUAGE_NONE][0] = array(
            'format' => $format,
            'value' => $payload->attributes->body,
            'safe_value' => check_markup($payload->attributes->body, $format),
          );
        }
      }
    }
    return $comment;
  }
}
