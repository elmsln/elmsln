<?php
// this is one of the stupidest named things ever...
class ELMSLNServiceService {
  private $name = 'ELMSLNServiceService';
  private $bundle = 'service';
  private $etype = 'node';
  private $etid = 'nid';
  private $load = 'node_load';
  private $publishStatus = NODE_PUBLISHED;
/**
   * Get a list of items
   * This will take into consideration what section the user is in and what section
   * they have access to.
   * @param object $options
   *                - filter
   *                -- author
   *                -- $bundle
   * @param boolean $network
   *  if the network topology should be sent along as well
   *  This is a more heavy call so it's default is FALSE.
   */
  public function getItems($options = array()) {
    $items = array();
    $field_conditions = array();
    $orderby = array();
    $limit = NULL;
    $property_conditions = array('status' => array($this->publishStatus, '='));
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
        if (isset($options->filter[$this->bundle])) {
          $property_conditions[$this->etid] = array($options->filter[$this->bundle], '=');
        }
      }
      if (isset($options->order)) {
        $orderby = $options->order;
      }
      if (isset($options->limit)) {
        $limit = $options->limit;
      }
    }
    $items = _cis_connector_assemble_entity_list($this->etype, $this->bundle, $this->etid, '_entity', $field_conditions, $property_conditions, $orderby, TRUE, $limit, array('node_access'));
    // sort the items
    usort($items, $this->name . '::sortItems');
    $items = $this->encodeItems($items, $network);
    return $items;
  }
  /**
   * Sort by title.
   */
  private static function sortItems($a, $b) {
    return strcmp($a->title, $b->title);
  }

  /**
   * Get a single encoded entity
   * This will take into consideration access control systems.
   *
   * @param string  $id
   *    id of the entity
   * @param boolean $network
   *    if the network topology should be sent along as well
   *    This is a more heavy call so it's default is FALSE.
   * @return object
   */
  public function getItem($id) {
    $entity = call_user_func($this->loadFunction, array($id));
    if ($entity && isset($entity->{$this->etid}) && entity_access('view', $this->bundle, $entity)) {
      return $this->encodeItem($entity, $network);
    }
    return NULL;
  }

  /**
   * Prepare a list of items to be outputed in json
   *
   * @param array $items
   *  An array of entity objects
   *
   * @return array
   */
  protected function encodeItems($items, $network = FALSE) {
    if (is_array($items)) {
      foreach ($items as &$item) {
        $item = $this->encodeItem($item);
      }
      return $items;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single item to be outputed in json
   *
   * @param object $entity
   *  A entity object
   *
   * @return Object
   */
  protected function encodeItem($entity) {
    global $user;
    $account = $user;
    $encoded = new stdClass();
    if (is_object($entity)) {
      $encoded->type = $entity->type;
      $encoded->id = $entity->{$this->etid};
      // Attributes
      $encoded->attributes = new stdClass();
      $encoded->attributes->title = $entity->title;
      $encoded->attributes->body = $entity->body[LANGUAGE_NONE][0]['safe_value'];
      $encoded->attributes->machine_name = $entity->field_machine_name['und'][0]['value'];
      $encoded->attributes->distro = $entity->field_distribution['und'][0]['safe_value'];
      // load registry for this to fill in the gaps
      $reg = _cis_connector_build_registry($encoded->attributes->distro);
      $encoded->attributes->color = $reg['color'];
      $encoded->attributes->weight = $reg['weight'];
      $encoded->attributes->icon = $reg['icon'];
      $encoded->attributes->url = url(_cis_connector_format_address($reg, '/', 'front'));
      // links
      $encoded->uris = new stdClass();
      $encoded->uris->uri = base_path() . $this->etype . '/' . $entity->{$this->etid};
      // Meta Info
      $encoded->meta = new stdClass();
      $encoded->meta->created = Date('c', $entity->created);
      $encoded->meta->changed = Date('c', $entity->changed);
      $encoded->meta->humandate = Date("F j, Y, g:i a", $entity->changed);
      $encoded->meta->revision_timestamp = Date('c', $entity->revision_timestamp);
      $encoded->meta->canUpdate = 0;
      $encoded->meta->canDelete = 0;
      $destination = '?destination=' . arg(0) . '/' . arg(1);
      // see the operations they can perform here
      if (entity_access('update', $this->etype, $entity)) {
        $encoded->meta->canUpdate = 1;
        $encoded->uris->edit = $encoded->uris->uri . '/edit' . $destination;
      }
      if (entity_access('delete', $this->etype, $entity)) {
        $encoded->meta->canDelete = 1;
        $encoded->uris->delete = $encoded->uris->uri . '/delete' . $destination;
      }
      // Relationships
      $encoded->relationships = new stdClass();
      $encoded->relationships->author = new stdClass();
      $encoded->relationships->author->attributes = new stdClass();
      $encoded->relationships->author->attributes->type = 'user';
      $encoded->relationships->author->attributes->id = $entity->uid;
      $encoded->relationships->author->attributes->name = $entity->name;
      drupal_alter('elmsln_core_encode' . $this->bundle, $encoded);
      return $encoded;
    }
    return NULL;
  }

  protected function decodeItem($payload, $entity) {
    if ($payload) {
      if ($payload->attributes) {
        if ($payload->attributes->title) {
          $entity->title = $payload->attributes->title;
        }
      }
    }
    drupal_alter('elmsln_core_decode_' . $this->bundle, $entity, $payload);
    return $entity;
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

  // Create a new service instance from a machine name of course / service
  public function createServiceInstance($course, $service) {
    global $user;
    $node = new stdClass();
    $node->status = 1;
    $node->title = t('@course - @service', array('@course' => $course, '@service' => $service));
    $node->type = 'service_instance';
    $node->uid = $user->uid;
    // entity field query to load a section by id
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', 'course')
      ->fieldCondition('field_machine_name', 'value', $course, '=');
    $query->propertyCondition('status', 1)
    // execute this as user 1 to avoid object conflicts
    ->addMetaData('account', user_load(1))
    // only return 1 value
    ->range(0, 1);
    $result = $query->execute();
    // flip the results if it found them
    if (isset($result['node'])) {
      // we know there's only 1 value in this array
      $key = array_keys($result['node']);
      $node->field_course['und'][0]['target_id'] = array_pop(($key));
    }
    // now same for service
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', 'service')
      ->fieldCondition('field_machine_name', 'value', $service, '=');
    $query->propertyCondition('status', 1)
    // execute this as user 1 to avoid object conflicts
    ->addMetaData('account', user_load(1))
    // only return 1 value
    ->range(0, 1);
    $result = $query->execute();
    // flip the results if it found them
    if (isset($result['node'])) {
      // we know there's only 1 value in this array
      $key = array_keys($result['node']);
      $node->field_services['und'][0]['target_id'] = array_pop(($key));
    }
    // ensure the above did something
    if (isset($node->field_course['und'][0]['target_id']) && isset($node->field_services['und'][0]['target_id']) && entity_access('create', 'node', $node)) {
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
}