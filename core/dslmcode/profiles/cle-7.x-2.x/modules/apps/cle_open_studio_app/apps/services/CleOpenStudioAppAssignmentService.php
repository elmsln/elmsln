<?php

class CleOpenStudioAppAssignmentService {
  /**
   * Create Stub Assignment based on assignment
   * @param string node ID of this assignments parent project
   * @return object node encoded for api output. Return FALSE if it could not create one.
   */
  public function createStubAssignment($project_id) {
    global $user;
    $node = new stdClass();
    $node->title = t('New assignment');
    $node->type = 'cle_assignment';
    $node->uid = $user->uid;
    $node->status = 1;
    $node->field_assignment_project['und'][0]['target_id'] = $project_id;
    node_save($node);
    try {
      node_save($node);
      if (isset($node->nid)) {
        return $this->encodeAssignment($node);
      }
    }
    catch (Exception $e) {
      throw new Exception($e->getMessage(), 1);
    }
    return FALSE;
  }

  /**
   * Get a list of assignments
   */
  public function getAssignments($options) {
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
          $property_conditions['uid'] = array($options->filter['author'], '=');
        }
        if (isset($options->filter['assignment'])) {
          $property_conditions['nid'] = array($options->filter['assignment'], '=');
        }
      }
      if (isset($options->order)) {
        $orderby = $options->order;
      }
      if (isset($options->limit)) {
        $limit = $options->limit;
      }
    }
    $items = _cis_connector_assemble_entity_list('node', 'cle_assignment', 'nid', '_entity', $field_conditions, $property_conditions, $orderby, TRUE, $limit);
    $items = $this->encodeAssignments($items);
    foreach ($items as $key => $data) {
      $return['assignment-' . $key] = $data;
    }
    return $return;
  }

  /**
   * Get a single assignment
   *
   * @param string $id
   *    Nid of the assignment
   *
   * @return object
   */
  public function getAssignment($id) {
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
    $items = _cis_connector_assemble_entity_list('node', 'cle_assignment', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
    /**
     * @todo add better checks to return status codes based on if none were found or if more than
     *       one was found.
     */
    if (count($items) == 1) {
      $item = $this->encodeAssignment(array_shift($items));
    }
    return $item;
  }
  
  public function updateAssignment($payload, $id) {
    if ($payload) {
      // make sure we have an id to work with
      if ($id && is_numeric($id)) {
        // load the assignment from drupal
        $node = node_load($id);
        // make sure the node is actually a assignment
        if ($node && isset($node->type) && $node->type == 'cle_assignment') {
          // decode the payload assignment to the drupal node
          $decoded_assignment = $this->decodeAssignment($payload, $node);
          // save the node
          try {
            // $decoded_assignment = new stdClass(); #fake error message
            node_save($decoded_assignment);
            // encode the assignment to send it back
            $encoded_assignment = $this->encodeAssignment($decoded_assignment);
            return $encoded_assignment;
          }
          catch (Exception $e) {
            throw new Exception($e->getMessage());
            return;
          }
        }
      }
    }
  }

  public function deleteAssignment($id) {
    if ($id && is_numeric($id)) {
      $node = node_load($id);
      if ($node && isset($node->type) && $node->type == 'cle_assignment') {
        $decoded_assignment = $this->deleteAssignment($payload, $node);
        // unpublish the node
        $decoded_assignment->status = 0;
        try {
          node_save($decoded_assignment);
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
   * Prepare a list of assignments to be outputed in json
   *
   * @param array $assignments
   *  An array of assignment node objects
   *
   * @return array
   */
  protected function encodeAssignments($assignments) {
    if (is_array($assignments)) {
      foreach ($assignments as &$assignment) {
        $assignment = $this->encodeAssignment($assignment);
      }
      return $assignments;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single assignment to be outputed in json
   *
   * @param object $assignment
   *  A assignment node object
   *
   * @return Object
   */
  protected function encodeAssignment($assignment) {
    global $user;
    $account = $user;
    $encoded_assignment = new stdClass();
    if (is_object($assignment)) {
      $encoded_assignment->type = $assignment->type;
      $encoded_assignment->id = $assignment->nid;
      // Attributes
      $encoded_assignment->attributes = new stdClass();
      $encoded_assignment->attributes->title = $assignment->title;
      $encoded_assignment->attributes->body = $assignment->field_assignment_description[LANGUAGE_NONE][0]['safe_value'];
      // Meta Info
      $encoded_assignment->meta = new stdClass();
      $encoded_assignment->meta->created = Date('c', $assignment->created);
      $encoded_assignment->meta->changed = Date('c', $assignment->changed);
      $encoded_assignment->meta->humandate = Date("F j, Y, g:i a", $assignment->changed);
      $encoded_assignment->meta->revision_timestamp = Date('c', $assignment->revision_timestamp);
      $encoded_assignment->meta->canUpdate = 0;
      $encoded_assignment->meta->canDelete = 0;
      // see the operations they can perform here
      if (entity_access('update', 'node', $assignment)) {
        $encoded_assignment->meta->canUpdate = 1;
      }
      if (entity_access('delete', 'node', $assignment)) {
        $encoded_assignment->meta->canDelete = 1;
      }
      // Relationships
      $encoded_assignment->relationships = new stdClass();
      // assignment
      $encoded_assignment->relationships->project = new stdClass();
      $encoded_assignment->relationships->project->data = new stdClass();
      $encoded_assignment->relationships->project->data->id = $assignment->field_assignment_project[LANGUAGE_NONE][0]['target_id'];
      // group
      $encoded_assignment->relationships->group = new stdClass();
      $encoded_assignment->relationships->group->data = new stdClass();
      $encoded_assignment->relationships->group->data->id = $assignment->og_group_ref[LANGUAGE_NONE][0]['target_id'];
      // author
      $encoded_assignment->relationships->author = new stdClass();
      $encoded_assignment->relationships->author->data = new stdClass();
      $encoded_assignment->relationships->author->data->type = 'user';
      $encoded_assignment->relationships->author->data->id = $assignment->uid;
      $encoded_assignment->relationships->author->data->name = $assignment->name;
      // Actions
      $encoded_assignment->actions = null;
      drupal_alter('cle_open_studio_app_encode_assignment', $encoded_assignment);
      return $encoded_assignment;
    }
    return NULL;
  }

  protected function decodeAssignment($payload, $node) {
    if ($payload) {
      if ($payload->attributes) {
        if ($payload->attributes->title) {
          $node->title = $payload->attributes->title;
        }
        if ($payload->attributes->body) {
          $node->field_assignment_description[LANGUAGE_NONE][0]['value'] = $payload->attributes->body;
        }
      }
    }
    drupal_alter('cle_open_studio_app_decode_assignment', $node, $payload);
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