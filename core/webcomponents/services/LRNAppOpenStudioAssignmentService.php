<?php

include_once 'LRNAppOpenStudioSubmissionService.php';

class LRNAppOpenStudioAssignmentService {
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
    $node->field_critique_method[LANGUAGE_NONE][0]['value'] = 'none';
    // associate to the currently active section
    $node->og_group_ref[LANGUAGE_NONE][0]['target_id'] = _cis_section_load_section_by_id(_cis_connector_section_context());
    if (entity_access('create', 'node', $node)) {
      try {
        node_save($node);
        if (isset($node->nid)) {
          return $node;
        }
      }
      catch (Exception $e) {
        throw new Exception($e->getMessage(), 1);
      }
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
    if ($section) {
      $field_conditions = array(
        'og_group_ref' => array('target_id', $section, '='),
      );
    }
    // things unpublished are considered "deleted"
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    $orderby = array('property' => array(array('changed', 'DESC')));
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
    return $items;
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
    $encode = (isset($options['encode']) ? $options['encode'] : TRUE);
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    if ($section) {
      $field_conditions = array(
        'og_group_ref' => array('target_id', $section, '='),
      );
    }
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
      $item = array_shift($items);
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
        if ($node && isset($node->type) && $node->type == 'cle_assignment' && entity_access('update', 'node', $node)) {
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
      if ($node && isset($node->type) && $node->type == 'cle_assignment' && entity_access('delete', 'node', $node)) {
        // unpublish the node
        $node->status = 0;
        try {
          node_save($node);
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
   * Find out an assignment is complete assignment of a submission is complete
   *
   * @param [string] $assignment_id
   * @return boolean
   */
  public function assignmentComplete($assignment_id) {
    $submission_service = new LRNAppOpenStudioSubmissionService();
    $submission = $submission_service->getSubmissionByAssignment($assignment_id);
    if ($submission->field_submission_state[LANGUAGE_NONE][0]['value'] == 'submission_ready') {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Get an assignment's parent assignment
   *
   * @param [string] $assignment_id
   * @return object/false
   */
  public function getAssignmentDependency($assignment_id) {
    $assignment = $this->getAssignment($assignment_id);
    if ($assignment) {
      // if we have a dependency
      if (isset($assignment->field_assignment_dependencies[LANGUAGE_NONE][0]['target_id'])) {
        return $this->getAssignment($assignment->field_assignment_dependencies[LANGUAGE_NONE][0]['target_id']);
      }
    }
    return FALSE;
  }

  /**
   * Find out if an assignment's dependecy has unmet dependencies
   *
   * @param [type] $assignment_id
   * @return boolean
   */
  public function assignmentHasUnmetDependencies($assignment_id) {
    $parent = $this->getAssignmentDependency($assignment_id);
    if ($parent) {
      $complete = $this->assignmentComplete($parent->nid);
      if (!$complete) {
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * Prepare a list of assignments to be outputed in json
   *
   * @param array $assignments
   *  An array of assignment node objects
   *
   * @return array
   */
  public function encodeAssignments($assignments, $app_route, $truncate = array()) {
    if (is_array($assignments)) {
      foreach ($assignments as &$assignment) {
        $assignment = $this->encodeAssignment($assignment, $app_route, $truncate);
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
  public function encodeAssignment($assignment, $app_route = '', $truncate = array()) {
    global $user;
    global $base_url;
    $account = $user;
    $encoded_assignment = new stdClass();
    if (is_object($assignment)) {
      $encoded_assignment->type = $assignment->type;
      $encoded_assignment->id = $assignment->nid;
      // Attributes
      $encoded_assignment->attributes = new stdClass();
      $encoded_assignment->attributes->title = $assignment->title;
      $encoded_assignment->attributes->body = $assignment->field_assignment_description[LANGUAGE_NONE][0]['safe_value'];
      $encoded_assignment->attributes->critiqueOutline = $assignment->field_critique_outline[LANGUAGE_NONE][0]['safe_value'];
      // Meta Info
      $encoded_assignment->meta = new stdClass();
      $encoded_assignment->meta->created = Date('c', $assignment->created);
      $encoded_assignment->meta->changed = Date('c', $assignment->changed);
      $encoded_assignment->meta->humandate = Date("F j, Y, g:i a", $assignment->changed);
      $encoded_assignment->meta->revision_timestamp = Date('c', $assignment->revision_timestamp);
      $encoded_assignment->meta->canUpdate = 0;
      $encoded_assignment->meta->canDelete = 0;
      $encoded_assignment->meta->afterDueDate = 0;
      $encoded_assignment->meta->canCritique = 0;
      // see the operations they can perform here
      if (entity_access('update', 'node', $assignment)) {
        $encoded_assignment->meta->canUpdate = 1;
      }
      if (entity_access('delete', 'node', $assignment)) {
        $encoded_assignment->meta->canDelete = 1;
      }
      // add in related submissions
      if (!isset($truncate['relatedSubmissions'])) {
        $encoded_assignment->meta->relatedSubmissions = _cle_submission_submission_status($assignment);
      }
      else {
        $encoded_assignment->meta->relatedSubmissions = NULL;
      }
      // see if this allows late submissions
      $allowLate = (bool)$assignment->field_assignment_late_submission[LANGUAGE_NONE][0]['value'];
      // calculate if this is on time / can be active for submissions
      // as well as providing a rationale behind this response
      // this helps in both debugging and messages to the end user
      // so logic all stays server side
      $time = REQUEST_TIME;
      $rationale = array();
      // see if this has a due date and if it is after as a result
      if (isset($assignment->field_assignment_due_date[LANGUAGE_NONE][0]['value'])) {
        // time is greater than the due date, meaning its late
        // see if it's allowed to be late though
        if ($time > $assignment->field_assignment_due_date['und'][0]['value2'] && $allowLate) {
          $submissionActive = 1;
          $rationale['text'] = t('The assignment was due @date, but late submissions are accepted.', array('@date' => date('M d, Y - h:iA', $assignment->field_assignment_due_date['und'][0]['value2'])));
          $rationale['code'] = 'date-late';
          $rationale['data'] = array($assignment->field_assignment_due_date['und'][0]['value2']);
        }
        // time is greater than the due date and they can't submit
        else if ($time > $assignment->field_assignment_due_date['und'][0]['value2'] && !$allowLate) {
          $submissionActive = 0;
          $rationale['text'] = t('The assignment was due @date and submissions are now closed.', array('@date' => date('M d, Y - h:iA', $assignment->field_assignment_due_date['und'][0]['value2'])));
          $rationale['code'] = 'date-closed';
          $rationale['data'] = array($assignment->field_assignment_due_date['und'][0]['value2']);
        }
        // time greater than 1st date (within it starting) and less than 2nd (due date)
        else if ($time > $assignment->field_assignment_due_date['und'][0]['value'] && $time < $assignment->field_assignment_due_date['und'][0]['value2']) {
          $submissionActive = 1;
          $rationale['text'] = t('Assignment submissions opened @date1 and are due by @date2.', array('@date1' => date('M d, Y - h:iA', $assignment->field_assignment_due_date['und'][0]['value']), '@date2' => date('M d, Y - h:iA', $assignment->field_assignment_due_date['und'][0]['value2'])));
          $rationale['code'] = 'date-open';
          $rationale['data'] = array($assignment->field_assignment_due_date['und'][0]['value'], $assignment->field_assignment_due_date['und'][0]['value2']);

        }
        // time is less than the start of the date range meaning it hasn't opened yet
        else if ($time < $assignment->field_assignment_due_date['und'][0]['value'] && $assignment->field_assignment_due_date['und'][0]['value'] != $assignment->field_assignment_due_date['und'][0]['value2'] && !is_null($assignment->field_assignment_due_date['und'][0]['value2'])) {
          $submissionActive = 0;
          $rationale['text'] = t('Assignment submissions are currently closed. This assignment will open @date1 and is due by @date2.', array('@date1' => date('M d, Y - h:iA', $assignment->field_assignment_due_date['und'][0]['value']), '@date2' => date('M d, Y - h:iA', $assignment->field_assignment_due_date['und'][0]['value2'])));
          $rationale['code'] = 'date-closed';
          $rationale['data'] = array($assignment->field_assignment_due_date['und'][0]['value'], $assignment->field_assignment_due_date['und'][0]['value2']);
        }
        // time is before the due date, we're good.
        else if ($time < $assignment->field_assignment_due_date['und'][0]['value']) {
          $submissionActive = 1;
          $rationale['text'] = t('The assignment is accepting submissions and is due @date.', array('@date' => date('M d, Y - h:iA', $assignment->field_assignment_due_date['und'][0]['value'])));
          $rationale['code'] = 'date-open';
          $rationale['data'] = array($assignment->field_assignment_due_date['und'][0]['value']);
        }
      }
      else {
        $submissionActive = 1;
        $rationale['text'] = t('The assignment is open for submission, there is no due date.');
        $rationale['code'] = 'date-none';
      }
      // support for assignment dependencies
      if (isset($assignment->field_assignment_dependencies[LANGUAGE_NONE][0])) {
        // loop through dependencies and check if they have been met
        foreach ($assignment->field_assignment_dependencies[LANGUAGE_NONE] as $item) {
          $assignment_dependency = node_load($item['target_id']);
          $tmp = _cle_submission_submission_status($assignment_dependency);
          if (empty($tmp['complete']['submissions'])) {
            $submissionActive = 0;
            $rationale['text'] = t('This assignment won\'t open until dependencies have been met.');
            $rationale['code'] = 'dependencies-unmet';
            $rationale['data'][] = $assignment_dependency->nid;
          }
        }
      }
      // account for admin / staff / teacher roles which can submit things
      // regardless of due date stuff
      if (_cis_connector_role_groupings(array('staff', 'teacher')) && $submissionActive == 0) {
        $submissionActive = 1;
        $rationale['text'] .= ' ' . t('<em>Your privileges allow you to submit this regardless.</em>');
      }
      // see if this has a due date and if it is after as a result
      if (isset($assignment->field_assignment_due_date['und'][0]['value'])) {
        // check for due date 2
        if (isset($assignment->field_assignment_due_date['und'][0]['value2'])) {
          if ($time > $assignment->field_assignment_due_date['und'][0]['value2']) {
            $metadata['afterDueDate'] = 1;
          }
        }
        else {
          if ($time > $assignment->field_assignment_due_date['und'][0]['value']) {
            $metadata['afterDueDate'] = 1;
          }
        }
      }
      // bring along the rationale
      $encoded_assignment->meta->rationale = $rationale;
      // bring the submission active status
      $encoded_assignment->meta->submissionActive = $submissionActive;

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
      // shim till we remove these
      $encoded_assignment->links = array(
        'self' => $base_url . '/api/v1/cle/assignments/' . $assignment->nid,
        'url' => $base_url . '/cle/app/assignments/' . $assignment->nid,
        'direct' => $base_url . '/node/' . $assignment->nid,
        'delete' => $base_url . '/node/' . $assignment->nid . '/delete?destination=' . $app_route,
        'update' => $base_url . '/node/' . $assignment->nid . '/edit?destination=' . $app_route,
      );
      drupal_alter('cle_open_studio_app_encode_assignment', $encoded_assignment);
      return $encoded_assignment;
    }
    return NULL;
  }

  public function decodeAssignment($payload, $node) {
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
  public function objectToArray($obj) {
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

  public function fileFieldTypes($entity_type, $field_name, $bundle_name) {
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