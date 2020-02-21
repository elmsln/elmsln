<?php

include_once 'LRNAppOpenStudioAssignmentService.php';

class LRNAppOpenStudioProjectService {
  /**
   * Create Stub Project based on assignment
   */
  public function createStubProject() {
    global $user;
    $node = new stdClass();
    $node->title = t('New project');
    $node->type = 'cle_project';
    $node->uid = $user->uid;
    $node->status = 1;
    // associate to the currently active section
    $node->og_group_ref[LANGUAGE_NONE][0]['target_id'] = _cis_section_load_section_by_id(_cis_connector_section_context());
    if (entity_access('create', 'node', $node)) {
      try {
        node_save($node);
        if (isset($node->nid)) {
          return $this->encodeProject($node);
        }
      }
      catch (Exception $e) {
        throw new Exception($e->getMessage(), 1);
      }
    }
    return FALSE;
  }

  /**
   * Get a list of projects
   */
  public function getProjects($options = NULL) {
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
          // support modified operator
          if (is_array($options->filter['author'])) {
            $property_conditions['uid'] = array($options->filter['author'][0], $options->filter['author'][1]);
          }
          else {
            $property_conditions['uid'] = array($options->filter['author'], '=');
          }
        }
        if (isset($options->filter['project'])) {
          $property_conditions['nid'] = array($options->filter['project'], '=');
        }
      }
      if (isset($options->order)) {
        $orderby = $options->order;
      }
      if (isset($options->limit)) {
        $limit = $options->limit;
      }
    }
    $items = _cis_connector_assemble_entity_list('node', 'cle_project', 'nid', '_entity', $field_conditions, $property_conditions, $orderby, TRUE, $limit);
    $items = $this->encodeProjects($items);
    // loop through the section projects in the order they are in
    $section_node = node_load($section);
    foreach ($section_node->field_section_projects['und'] as $key => $data) {
      if (isset($items[$data['target_id']])) {
        $return['project-' . $data['target_id']] = $items[$data['target_id']];
      }
    }
    return $return;
  }

  /**
   * Get a single project
   *
   * @param string $id
   *    Nid of the project
   *
   * @return object
   */
  public function getProject($id) {
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
    $items = _cis_connector_assemble_entity_list('node', 'cle_project', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
    /**
     * @todo add better checks to return status codes based on if none were found or if more than
     *       one was found.
     */
    if (count($items) == 1) {
      $item = $this->encodeProject(array_shift($items));
    }
    return $item;
  }

  public function updateProject($payload, $id) {
    if ($payload) {
      // make sure we have an id to work with
      if ($id && is_numeric($id)) {
        // load the project from drupal
        $node = node_load($id);
        // make sure the node is actually a project
        if ($node && isset($node->type) && $node->type == 'cle_project' && entity_access('update', 'node', $node)) {
          // decode the payload project to the drupal node
          $decoded_project = $this->decodeProject($payload, $node);
          // save the node
          try {
            // $decoded_project = new stdClass(); #fake error message
            node_save($decoded_project);
            // encode the project to send it back
            $encoded_project = $this->encodeProject($decoded_project);
            return $encoded_project;
          }
          catch (Exception $e) {
            throw new Exception($e->getMessage());
            return;
          }
        }
      }
    }
  }

  public function deleteProject($id) {
    if ($id && is_numeric($id)) {
      $node = node_load($id);
      if ($node && isset($node->type) && $node->type == 'cle_project' && entity_access('delete', 'node', $node)) {
        // unpublish the node
        $node->status = 0;
        $service = new LRNAppOpenStudioAssignmentService();
        // clean up assignments if they exist
        if (!empty($node->field_project_steps['und'])) {
          // loop through and clone assignments based on what we found
          foreach ($node->field_project_steps['und'] as $assignmentref) {
            $assignment = $service->deleteAssignment($assignmentref['target_id']);
          }
        }
        try {
          node_save($node);
          return TRUE;
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
   * Prepare a list of projects to be outputed in json
   *
   * @param array $projects
   *  An array of project node objects
   *
   * @return array
   */
  protected function encodeProjects($projects) {
    if (is_array($projects)) {
      foreach ($projects as &$project) {
        $project = $this->encodeProject($project);
      }
      return $projects;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single project to be outputed in json
   *
   * @param object $project
   *  A project node object
   *
   * @return Object
   */
  protected function encodeProject($project) {
    global $user;
    $account = $user;
    $encoded_project = new stdClass();
    if (is_object($project)) {
      $encoded_project->type = $project->type;
      $encoded_project->id = $project->nid;
      // Attributes
      $encoded_project->attributes = new stdClass();
      $encoded_project->attributes->title = $project->title;
      $encoded_project->attributes->body = $project->field_project_description[LANGUAGE_NONE][0]['safe_value'];

      $encoded_project->attributes->steps = array();
      if (isset($project->field_project_steps[LANGUAGE_NONE])) {
        $steps = $project->field_project_steps[LANGUAGE_NONE];
        if ($steps) {
          foreach ($steps as $key => &$step) {
            // load the assignment from target
            $step_node = node_load($step['target_id']);
            $step = new stdClass();
            $step->id = $step_node->nid;
            $step->title = $step_node->title;
          }
        }
        $encoded_project->attributes->steps = $steps;
      }
      // Meta Info
      $encoded_project->meta = new stdClass();
      $encoded_project->meta->created = Date('c', $project->created);
      $encoded_project->meta->changed = Date('c', $project->changed);
      $encoded_project->meta->humandate = Date("F j, Y, g:i a", $project->changed);
      $encoded_project->meta->revision_timestamp = Date('c', $project->revision_timestamp);
      $encoded_project->meta->canUpdate = 0;
      $encoded_project->meta->canDelete = 0;
      // see the operations they can perform here
      if (entity_access('update', 'node', $project)) {
        $encoded_project->meta->canUpdate = 1;
      }
      if (entity_access('delete', 'node', $project)) {
        $encoded_project->meta->canDelete = 1;
      }
      // Relationships
      $encoded_project->relationships = new stdClass();
      // project
      $encoded_project->relationships->project_parent = new stdClass();
      $encoded_project->relationships->project_parent->data = new stdClass();
      $encoded_project->relationships->project_parent->data->id = $project->field_project_parent[LANGUAGE_NONE][0]['target_id'];
      // group
      $encoded_project->relationships->group = new stdClass();
      $encoded_project->relationships->group->data = new stdClass();
      $encoded_project->relationships->group->data->id = $project->og_group_ref[LANGUAGE_NONE][0]['target_id'];
      // author
      $encoded_project->relationships->author = new stdClass();
      $encoded_project->relationships->author->data = new stdClass();
      $encoded_project->relationships->author->data->type = 'user';
      $encoded_project->relationships->author->data->id = $project->uid;
      $encoded_project->relationships->author->data->name = $project->name;
      // Actions
      $encoded_project->actions = null;
      drupal_alter('cle_open_studio_app_encode_project', $encoded_project);
      return $encoded_project;
    }
    return NULL;
  }

  protected function decodeProject($payload, $node) {
    if ($payload) {
      if ($payload->attributes) {
        if ($payload->attributes->title) {
          $node->title = $payload->attributes->title;
        }
        if ($payload->attributes->body) {
          $node->field_project_description[LANGUAGE_NONE][0]['value'] = $payload->attributes->body;
        }
      }
    }
    drupal_alter('cle_open_studio_app_decode_project', $node, $payload);
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