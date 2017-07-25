<?php

include_once 'CleOpenStudioAppCommentService.php';

class CleOpenStudioAppSubmissionService {

  /**
   * Get a list of submissions
   * This will take into concideration what section the user is in and what section
   * they have access to.
   */
  public function getSubmissions() {
    $items = array();
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    $field_conditions = array(
      'og_group_ref' => array('target_id', $section, '='),
    );
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    $orderby = array();
    $items = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
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
          node_save($decoded_submission);
          // encode the submission to send it back
          $encoded_submission = $this->encodeSubmission($decoded_submission);
          return $encoded_submission;
        }
      }
    }
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
    $encoded_submission = new stdClass();
    if (is_object($submission)) {
      $encoded_submission->type = $submission->type;
      $encoded_submission->id = $submission->nid;
      // Attributes
      $encoded_submission->attributes = new stdClass();
      $encoded_submission->attributes->title = $submission->title;
      $encoded_submission->attributes->body = $submission->field_submission_text[LANGUAGE_NONE][0]['safe_value'];
      $encoded_submission->attributes->state = $submission->field_submission_state[LANGUAGE_NONE][0]['value'];
      // Images
      $encoded_submission->attributes->images = NULL;
      if (isset($submission->field_images[LANGUAGE_NONE])) {
        foreach ($submission->field_images[LANGUAGE_NONE] as $file) {
          $encoded_submission->attributes->images[] = _elmsln_api_v1_file_output($file);
        }
      }
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
      $encoded_submission->attributes->video = NULL;
      $videos = $submission->field_video[LANGUAGE_NONE];
      if ($videos) {
        foreach ($videos as $key => &$video) {
          // add a video_src property to give the correct embed src to an iframe
          $video['video_src'] = _elmsln_api_video_url($video['video_url']);
        }
      }
      $encoded_submission->attributes->video = $videos;
      // Meta Info
      $encoded_submission->meta = new stdClass();
      $encoded_submission->meta->created = Date('c', $submission->created);
      $encoded_submission->meta->changed = Date('c', $submission->changed);
      $encoded_submission->meta->revision_timestamp = Date('c', $submission->revision_timestamp);
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
      // comments
      $encoded_submission->relationships->comments = null;
      $encoded_submission->meta->comment_count = $submission->comment_count;
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
        // if ($payload->attributes->links) {
        //   $node->field_links[LANGUAGE_NONE] = (array) $payload->attributes->links;
        // }
        // if ($payload->attributes->videos) {
        //   $node->field_video[LANGUAGE_NONE] = $payload->attributes->videos;
        // }
        // if ($payload->attributes->images) {
        //   $node->field_images[LANGUAGE_NONE] = $payload->attributes->images;
        // }
      }
    }
    return $node;
  }
}