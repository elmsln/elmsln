<?php

class CleOpenStudioAppCommentService {
  /**
   * Create Stub Comment based on assignment
   */
  public function createStubComment($comment_id) {
    global $user;
    $comment = new stdClass();
    $comment->subject = t('Feedback from @name', array('@name' => $user->name));
    $comment->type = 'comment';
    $comment->uid = $user->uid;
    $comment->name = $user->name;
    $comment->status = 1;
    $comment->language = LANGUAGE_NONE;
    $comment->pid = $comment_id;
     array(
      'name' => '',
      'mail' => '',
      'homepage' => '',
      'subject' => '',
      'comment' => '',
    );
    comment_save($comment);
    if (isset($comment->cid)) {
      return $this->encodeSubmission($comment);
    }
    else {
      return FALSE;
    }
  }
  /**
   * Get a list of comments
   * This will take into concideration what section the user is in and what section
   * they have access to.
   *
   * @param object $options
   *                - filter
   *                -- author
   *                -- submission
   */
  public function getComments($options) {
    $items = array();
    $field_conditions = array();
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    if (isset($options)) {
      if (isset($options->filter)) {
        if (isset($options->filter['author'])) {
          $property_conditions['uid'] = array($options->filter->author, '=');
        }
        if (isset($options->filter['submission'])) {
          $property_conditions['nid'] = array($options->filter['submission'], '=');
        }
      }
    }
    $orderby = array();
    $items = _cis_connector_assemble_entity_list('comment', 'comment', 'cid', '_entity', $field_conditions, $property_conditions, $orderby);
    // sort the comments into a thread
    usort($items, 'CleOpenStudioAppCommentService::sortComments');
    $items = $this->encodeComments($items);
    return $items;
  }

  private static function sortComments($a, $b) {
    return $a->thread - $b->thread;
  }

  /**
   * Get a single comments
   * This will take into concideration what section the user is in and what section
   * they have access to.
   *
   * @param string $id
   *    Nid of the comments
   *
   * @return object
   */
  public function getComment($id) {
    $item = array();
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    $field_conditions = array(
      'og_group_ref' => array('target_id', $section, '='),
    );
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    if (isset($id)) {
      $property_conditions['cid'] = array($id, '=');
    }
    $orderby = array();
    $items = _cis_connector_assemble_entity_list('node', 'cle_comments', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
    /**
     * @todo add better checks to return status codes based on if none were found or if more than
     *       one was found.
     */
    if (count($items) == 1) {
      $item = $this->encodeComment(array_shift($items));
    }
    return $item;
  }

  /**
   * Prepare a list of comments to be outputed in json
   *
   * @param array $comments
   *  An array of comments node objects
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
   *  A comments node object
   *
   * @return Object
   */
  protected function encodeComment($comment) {
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
      $encoded_comments->metadata->editing = false;
      $encoded_comments->metadata->disabled = false;
      // Relationships
      $encoded_comments->relationships = new stdClass();
      // Author
      $encoded_comments->relationships->author = new stdClass();
      $encoded_comments->relationships->author->data = new stdClass();
      $encoded_comments->relationships->author->data->type = 'user';
      $encoded_comments->relationships->author->data->id = $comment->uid;
      $encoded_comments->relationships->author->data->name = $comment->name;
      // Actions
      $encoded_comments->actions = new stdClass();
      $encoded_comments->actions->reply = entity_access('view', 'comment', $comment);
      $encoded_comments->actions->edit = entity_access('update', 'comment', $comment);
      $encoded_comments->actions->delete = entity_access('delete', 'comment', $comment);

      drupal_alter('cle_open_studio_app_encode_comments', $encoded_comments);
      return $encoded_comments;
    }
    return NULL;
  }
}
