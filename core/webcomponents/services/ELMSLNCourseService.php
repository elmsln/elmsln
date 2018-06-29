<?php

class ELMSLNCourseService {

/**
   * Get a list of items
   * This will take into consideration what section the user is in and what section
   * they have access to.
   * @param object $options
   *                - filter
   *                -- author
   *                -- course
   * @param boolean $network
   *  if the network topology should be sent along as well
   *  This is a more heavy call so it's default is FALSE.
   */
  public function getCourses($options = array(), $network = FALSE) {
    $items = array();
    $field_conditions = array();
    $orderby = array();
    $limit = NULL;
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
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
        if (isset($options->filter['course'])) {
          $property_conditions['nid'] = array($options->filter['course'], '=');
        }
      }
      if (isset($options->order)) {
        $orderby = $options->order;
      }
      if (isset($options->limit)) {
        $limit = $options->limit;
      }
    }
    $items = _cis_connector_assemble_entity_list('node', 'course', 'nid', '_entity', $field_conditions, $property_conditions, $orderby, TRUE, $limit, array('node_access'));
    // sort the items
    usort($items, 'ELMSLNCourseService::sortCourses');
    $items = $this->encodeCourses($items, $network);
    return $items;
  }
  /**
   * Sort by title.
   */
  private static function sortCourses($a, $b) {
    return strcmp($a->title, $b->title);
  }

  /**
   * Get a single course
   * This will take into consideration access control systems.
   *
   * @param string  $id
   *    nid of the course
   * @param boolean $network
   *    if the network topology should be sent along as well
   *    This is a more heavy call so it's default is FALSE.
   * @return object
   */
  public function getCourse($id, $network = FALSE) {
    $node = node_load($id);
    if ($node && isset($node->nid) && entity_access('view', 'node', $node)) {
      return $this->encodeCourse($node, $network);
    }
    return NULL;
  }

  /**
   * Prepare a list of courses to be outputed in json
   *
   * @param array $courses
   *  An array of course node objects
   *
   * @return array
   */
  protected function encodeCourses($courses, $network = FALSE) {
    if (is_array($courses)) {
      foreach ($courses as &$course) {
        $course = $this->encodeCourse($course, $network);
      }
      return $courses;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single course to be outputed in json
   *
   * @param object $course
   *  A course node object
   *
   * @return Object
   */
  protected function encodeCourse($node, $network = FALSE) {
    global $user;
    $account = $user;
    $encoded = new stdClass();
    if (is_object($node)) {
      $encoded->type = $node->type;
      $encoded->id = $node->nid;
      // Attributes
      $encoded->attributes = new stdClass();
      $encoded->attributes->name = $node->title;
      $encoded->attributes->title = $node->field_course_title['und'][0]['value'];
      $encoded->attributes->body = $node->body[LANGUAGE_NONE][0]['safe_value'];
      $encoded->attributes->machine_name = $node->field_machine_name['und'][0]['value'];
      $encoded->attributes->image = file_create_url($node->field_banner['und'][0]['uri']);
      $encoded->attributes->color = (isset($node->field_primary_color['und'][0]['safe_value']) ? $node->field_primary_color['und'][0]['safe_value'] : 'red');
      // links
      $encoded->uris = new stdClass();
      $encoded->uris->uri = base_path() . 'node/' . $node->nid;
      $encoded->uris->offerings = $encoded->uris->uri .'/offerings' . $destination;
      // Meta Info
      $encoded->meta = new stdClass();
      $encoded->meta->created = Date('c', $node->created);
      $encoded->meta->changed = Date('c', $node->changed);
      $encoded->meta->humandate = Date("F j, Y, g:i a", $node->changed);
      $encoded->meta->revision_timestamp = Date('c', $node->revision_timestamp);
      $encoded->meta->canUpdate = 0;
      $encoded->meta->canDelete = 0;
      $destination = '?destination=' . arg(0) . '/' . arg(1);
      // see the operations they can perform here
      if (entity_access('update', 'node', $node)) {
        $encoded->meta->canUpdate = 1;
        $encoded->uris->edit = $encoded->uris->uri . '/edit' . $destination;
        $encoded->uris->sync = $encoded->uris->uri . '/sync-roster' . $destination;
        $encoded->uris->addOffering = base_path() . 'cis-add-offering' . $destination;
      }
      if (entity_access('delete', 'node', $node)) {
        $encoded->meta->canDelete = 1;
        $encoded->uris->delete = $encoded->uris->uri . '/delete' . $destination;
      }
      // Relationships
      $encoded->relationships = new stdClass();
      $encoded->relationships->program = new stdClass();
      $encoded->relationships->program->attributes = new stdClass();
      // test and make sure program home exists
      if (isset($node->field_program_classification['und'][0]['target_id'])) {
        $program = node_load($node->field_program_classification['und'][0]['target_id']);
        $encoded->relationships->program->id = $program->nid;
        $encoded->relationships->program->attributes->name = $program->title;
      }
      $encoded->relationships->academic = new stdClass();
      $encoded->relationships->academic->attributes = new stdClass();
      // test and make sure academic home exists
      if (isset($node->field_academic_home['und'][0]['target_id'])) {
        $academic = node_load($node->field_academic_home['und'][0]['target_id']);
        $encoded->relationships->academic->id = $academic->nid;
        $encoded->relationships->academic->attributes->name = $academic->title;
      }
      $encoded->relationships->author = new stdClass();
      $encoded->relationships->author->attributes = new stdClass();
      $encoded->relationships->author->attributes->type = 'user';
      $encoded->relationships->author->attributes->id = $node->uid;
      $encoded->relationships->author->attributes->name = $node->name;
      // optional Topology
      if ($network) {
        // load entire registry
        $reg = _cis_connector_build_registry();
        $encoded->topology = array();
        // test for assembing services by faking a global override of context
        // Never assume the internet works agent Mulder. Trust No One.
        $_SESSION['cis_course_context'] = $encoded->attributes->machine_name;
        if ($services = _cis_connector_transaction('other_services')) {
          foreach ($services as $service) {
            // ensure we don't get two of these to display
            $encoded->topology[$reg[$service['field_distribution']]['group']][$service['field_machine_name']] = array(
              'title' => $service['title'],
              'url' => url(_cis_connector_format_address($reg[$service['field_distribution']], '/' . $encoded->attributes->machine_name, 'front')),
              'machine_name' => $service['field_machine_name'],
              'color' => $reg[$service['field_distribution']]['color'],
              'distro' => $service['field_distribution'],
              'weight' => $reg[$service['field_distribution']]['weight'],
              'icon' => $reg[$service['field_distribution']]['icon'],
              '_exists' => TRUE,
            );
          }
        }
      }
      drupal_alter('elmsln_core_encode_course', $encoded);
      return $encoded;
    }
    return NULL;
  }

  protected function decodeCourse($payload, $node) {
    if ($payload) {
      if ($payload->attributes) {
        if ($payload->attributes->title) {
          $node->title = $payload->attributes->title;
        }
      }
    }
    drupal_alter('elmsln_core_decode_course', $node, $payload);
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

}