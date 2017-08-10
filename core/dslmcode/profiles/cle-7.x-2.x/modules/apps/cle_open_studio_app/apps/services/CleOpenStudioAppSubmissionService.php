<?php

include_once 'CleOpenStudioAppCommentService.php';

class CleOpenStudioAppSubmissionService {

  /**
   * Create Stub Submission based on assignment
   */
  public function createStubSubmission($assignment_id) {
    global $user;
    $node = new stdClass();
    $node->title = t('Submission for assignment @id', array('@id' => $assignment_id));
    $node->type = 'cle_submission';
    $node->uid = $user->uid;
    $node->status = 1;
    $node->field_assignment[LANGUAGE_NONE][0]['target_id'] = $assignment_id;
    node_save($node);
    if (isset($node->nid)) {
      return $this->encodeSubmission($node);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Get a list of submissions
   * This will take into concideration what section the user is in and what section
   * they have access to.
   */
  public function getSubmissions($options) {
    $items = array();
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    $field_conditions = array(
      'og_group_ref' => array('target_id', $section, '='),
    );
    // things unpublished are considered "deleted"
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    $orderby = array('property' => array(array('changed', 'DESC')));
    $limit = NULL;
    $property_conditions = array('status' => array(COMMENT_PUBLISHED, '='));
    if (isset($options)) {
      if (isset($options->filter)) {
        if (isset($options->filter['author'])) {
          $property_conditions['uid'] = array($options->filter->author, '=');
        }
        if (isset($options->filter['submission'])) {
          $property_conditions['nid'] = array($options->filter['submission'], '=');
        }
        if (isset($options->filter['state'])) {
          $field_conditions['field_submission_state'] = array('value', $options->filter['state'][0], $options->filter['state'][1]);
        }
      }
      if (isset($options->order)) {
        $orderby = $options->order;
      }
      if (isset($options->limit)) {
        $limit = $options->limit;
      }
    }
    $items = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', '_entity', $field_conditions, $property_conditions, $orderby, TRUE, $limit);
    $items = $this->encodeSubmissions($items);
    return $items;
  }

  /**
   * Get a single submission
   * This will take into concideration what section the user is in and what section
   * they have access to.
   *
   * @param string $id
   *    Nid of the submission
   *
   * @return object
   */
  public function getSubmission($id) {
    $item = array();
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    $field_conditions = array(
      'og_group_ref' => array('target_id', $section, '='),
    );
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    if (isset($id)) {
      $property_conditions['nid'] = array($id, '=');
    }
    $orderby = array();
    $items = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
    /**
     * @todo add better checks to return status codes based on if none were found or if more than
     *       one was found.
     */
    if (count($items) == 1) {
      $item = $this->encodeSubmission(array_shift($items));
    }
    return $item;
  }
  
  public function updateSubmission($payload, $id) {
    if ($payload) {
      // make sure we have an id to work with
      if ($id && is_numeric($id)) {
        // load the submission from drupal
        $node = node_load($id);
        // make sure the node is actually a submission
        if ($node && isset($node->type) && $node->type == 'cle_submission') {
          // decode the payload submission to the drupal node
          $decoded_submission = $this->decodeSubmission($payload, $node);
          // save the node
          try {
            // $decoded_submission = new stdClass(); #fake error message
            node_save($decoded_submission);
            // encode the submission to send it back
            $encoded_submission = $this->encodeSubmission($decoded_submission);
            return $encoded_submission;
          }
          catch (Exception $e) {
            throw new Exception($e->getMessage());
            return;
          }
        }
      }
    }
  }

  public function deleteSubmission($id) {
    if ($id && is_numeric($id)) {
      $node = node_load($id);
      if ($node && isset($node->type) && $node->type == 'cle_submission') {
        $decoded_submission = $this->decodeSubmission($payload, $node);
        // unpublish the node
        $decoded_submission->status = 0;
        try {
          node_save($decoded_submission);
          return true;
        }
        catch (Exception $e) {
          throw new Exception($e->getMessage());
          return;
        }
      }
    }
  }

  public function videoGenerateSourceUrl($url) {
    return _elmsln_api_video_url($url);
  }

  /**
   * Prepare a list of submissions to be outputed in json
   *
   * @param array $submissions
   *  An array of submission node objects
   *
   * @return array
   */
  protected function encodeSubmissions($submissions) {
    if (is_array($submissions)) {
      foreach ($submissions as &$submission) {
        $submission = $this->encodeSubmission($submission);
      }
      return $submissions;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single submission to be outputed in json
   *
   * @param object $submission
   *  A submission node object
   *
   * @return Object
   */
  protected function encodeSubmission($submission) {
    global $user;
    $account = $user;
    $encoded_submission = new stdClass();
    if (is_object($submission)) {
      $encoded_submission->type = $submission->type;
      $encoded_submission->id = $submission->nid;
      $encoded_submission->display = new stdClass();
      $encoded_submission->display->image = NULL;
      $encoded_submission->display->icon = 'subject';
      // append specific data about each output type
      if (isset($submission->field_files['und'])) {
        $encoded_submission->display->icon = 'file-download';
      }
      if (isset($submission->field_links['und'])) {
        $encoded_submission->display->icon = 'link';
      }
      if (isset($submission->field_video['und'])) {
        $encoded_submission->display->icon = 'av:video-library';
      }
      // Attributes
      $encoded_submission->attributes = new stdClass();
      $encoded_submission->attributes->title = $submission->title;
      $encoded_submission->attributes->body = $submission->field_submission_text[LANGUAGE_NONE][0]['safe_value'];
      $encoded_submission->attributes->state = $submission->field_submission_state[LANGUAGE_NONE][0]['value'];
      // Files
      $encoded_submission->attributes->files = NULL;
      if (isset($submission->field_files[LANGUAGE_NONE])) {
        foreach ($submission->field_files[LANGUAGE_NONE] as $file) {
          $encoded_submission->attributes->files[] = _elmsln_api_v1_file_output($file);
        }
      }
      // Links
      $encoded_submission->attributes->links = NULL;
      $encoded_submission->attributes->links = $submission->field_links[LANGUAGE_NONE];
      // Video
      $encoded_submission->attributes->video = array();
      if (isset($submission->field_video[LANGUAGE_NONE])) {
        $videos = $submission->field_video[LANGUAGE_NONE];
        if ($videos) {
          foreach ($videos as $key => &$video) {
            // add a video_src property to give the correct embed src to an iframe
            $video['video_src'] = _elmsln_api_video_url($video['video_url']);
          }
        }
        $encoded_submission->attributes->video = $videos;
      }
      // Images
      $encoded_submission->attributes->images = NULL;
      if (isset($submission->field_images[LANGUAGE_NONE])) {
        foreach ($submission->field_images[LANGUAGE_NONE] as $file) {
          $encoded_submission->attributes->images[] = _elmsln_api_v1_file_output($file);
        }
        $images = $encoded_submission->attributes->images;
        $encoded_submission->display->image = array_pop($images);
        $encoded_submission->display->image = file_create_url($encoded_submission->display->image['uri']);
        $encoded_submission->display->icon = FALSE;
      }
      // Meta Info
      $encoded_submission->meta = new stdClass();
      $encoded_submission->meta->created = Date('c', $submission->created);
      $encoded_submission->meta->changed = Date('c', $submission->changed);
      $encoded_submission->meta->humandate = Date("F j, Y, g:i a", $submission->changed);
      $encoded_submission->meta->revision_timestamp = Date('c', $submission->revision_timestamp);
      $encoded_submission->meta->canUpdate = 0;
      $encoded_submission->meta->canDelete = 0;
      $encoded_submission->meta->canCritique = 0;
      $encoded_submission->meta->filefieldTypes = $this->fileFieldTypes('node', 'field_files', 'cle_submission');
        // see the operations they can perform here
      if (entity_access('update', 'node', $submission)) {
        $encoded_submission->meta->canUpdate = 1;
      }
      if (entity_access('delete', 'node', $submission)) {
        $encoded_submission->meta->canDelete = 1;
      }
      // @todo need more advanced check then just this based on
      // assignment methodology for critique
      if (entity_access('view', 'node', $submission) && $submission->uid != $account->uid) {
        $encoded_submission->meta->canCritique = 1;
      }
      switch ($submission->field_submission_state[LANGUAGE_NONE][0]['value']) {
        case 'submission_in_progress':
          $encoded_submission->meta->state_icon = 'assignment-late';
          $encoded_submission->meta->state_color = 'red lighten-3';
        break;
        case 'submission_ready':
          $encoded_submission->meta->state_icon = 'done';
          $encoded_submission->meta->state_color = 'green lighten-3';
        break;
        case 'submission_needs_work':
          $encoded_submission->meta->state_icon = 'assignment-returned';
          $encoded_submission->meta->state_color = 'yellow lighten-3';
        break;
        default:
          $encoded_submission->meta->state_icon = 'assignment';
          $encoded_submission->meta->state_color = 'grey lighten-3';
        break;
      }
      // Relationships
      $encoded_submission->relationships = new stdClass();
      // assignment
      $encoded_submission->relationships->assignment = new stdClass();
      $encoded_submission->relationships->assignment->data = new stdClass();
      $encoded_submission->relationships->assignment->data->id = $submission->field_assignment[LANGUAGE_NONE][0]['target_id'];
      // group
      $encoded_submission->relationships->group = new stdClass();
      $encoded_submission->relationships->group->data = new stdClass();
      $encoded_submission->relationships->group->data->id = $submission->og_group_ref[LANGUAGE_NONE][0]['target_id'];
      // author
      $encoded_submission->relationships->author = new stdClass();
      $encoded_submission->relationships->author->data = new stdClass();
      $encoded_submission->relationships->author->data->type = 'user';
      $encoded_submission->relationships->author->data->id = $submission->uid;
      $encoded_submission->relationships->author->data->name = $submission->name;
      $encoded_submission->relationships->author->data->display_name = _elmsln_core_get_user_name('full', $submission->uid);
      $encoded_submission->relationships->author->data->sis = _elmsln_core_get_sis_user_data($submission->uid);
      // comments
      $encoded_submission->relationships->comments = null;
      $encoded_submission->meta->comment_count = (!empty($submission->comment_count) ? $submission->comment_count : 0);
      $encoded_submission->meta->comment_new = comment_num_new($submission->nid);
      if ($submission->comment_count > 0) {
        $comments_service = new CleOpenStudioAppCommentService();
        $options = (object) array('filter' => array('submission' => $submission->nid));
        $comments = $comments_service->getComments($options);
        $encoded_submission->relationships->comments = new stdClass();
        $encoded_submission->relationships->comments->data = $comments;
      }
      // Actions
      $encoded_submission->actions = null;
      drupal_alter('cle_open_studio_app_encode_submission', $encoded_submission);
      return $encoded_submission;
    }
    return NULL;
  }

  protected function decodeSubmission($payload, $node) {
    if ($payload) {
      if ($payload->attributes) {
        if ($payload->attributes->title) {
          $node->title = $payload->attributes->title;
        }
        if ($payload->attributes->body) {
          $node->field_submission_text[LANGUAGE_NONE][0]['value'] = $payload->attributes->body;
        }
        if ($payload->attributes->state) {
          $node->field_submission_state[LANGUAGE_NONE][0]['value'] = $payload->attributes->state;
        }
        if ($payload->attributes->links) {
          $node->field_links[LANGUAGE_NONE] = $this->objectToArray($payload->attributes->links);
        }
        if ($payload->attributes->files) {
          $node->field_files[LANGUAGE_NONE] = $this->objectToArray($payload->attributes->files);
        }
        if (isset($payload->attributes->video)) {
          $videos = array();
          foreach ($payload->attributes->video as $key => $video) {
            $videos[$key]['video_url'] = $video->video_url;
          }
          $node->field_video[LANGUAGE_NONE] = $videos;
        }
        if (isset($payload->attributes->images)) {
          $node->field_images[LANGUAGE_NONE] = $this->objectToArray($payload->attributes->images);
        }
      }
    }
    drupal_alter('cle_open_studio_app_decode_submission', $node, $payload);
    return $node;
  }

  // Convert multidimentional Object to arrays
  private function objectToArray($obj) {
    if (is_object($obj)) $obj = (array)$obj;
    if (is_array($obj)) {
        $new = array();
        foreach ($obj as $key => $val) {
            $new[$key] = $this->objectToArray($val);
        }
    } else {
        $new = $obj;
    }
    return $new;
  }

  private function fileFieldTypes($entity_type, $field_name, $bundle_name) {
    $instance = field_info_instance($entity_type, $field_name, $bundle_name);
    if ($instance && is_array($instance)) {
      if (isset($instance['settings'])) {
        if (isset($instance['settings']['file_extensions'])) {
          $extensions = trim($instance['settings']['file_extensions']);
          $extensions = explode(' ', $extensions);
          foreach ($extensions as &$extension) {
            $extension = '.' . trim($extension);
          }
          $extensions = implode(',', $extensions);
          return $extensions;
        }
      }
    }
    return '';
  }
}