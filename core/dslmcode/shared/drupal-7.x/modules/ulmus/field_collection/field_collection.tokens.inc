<?php

/**
 * @file
 * Provides host entity tokens for field_collection.module
 */

/**
 * Implements hook_token_info().
 */
function field_collection_token_info() {
  $type = array(
    'name' => t('Field collection host entity'),
    'description' => t('Tokens related to field collection host entities.'),
    'needs-data' => 'field_collection_item',
  );

  // Simple tokens.
  $host['type'] = array(
    'name' => t('Host entity type'),
    'description' => t('The entity type of the host. Common types are <em>node</em> and <em>user</em>.'),
  );
  $host['bundle'] = array(
    'name' => t('Host entity bundle'),
    'description' => t('For <em>node</em> entity types this is the content type, otherwise available as <code>[node:content-type:machine-name]</code>.'),
  );
  $host['id'] = array(
    'name' => t('Host entity ID'),
    'description' => t('The entity ID of the host. For nodes this is <code>nid</code>, for users <code>uid</code>.'),
  );

  // Chained tokens.
  foreach (field_collection_host_entity_types() as $entity_type => $entity_info) {
    $host[$entity_type] = array(
      'name' => t('Entity: @entity_type', array('@entity_type' => $entity_info['label'])),
      'description' => t('Host entity tokens when it is of type %entity_type', array('%entity_type' => $entity_info['label'])),
      'type' => $entity_type,
    );
  }

  return array(
    'types' => array('host' => $type),
    'tokens' => array('host' => $host),
  );
}

/**
 * Implements hook_token_info_alter().
 *
 * Inject an additional 'host' token to the 'field_collection_item' token type.
 */
function field_collection_token_info_alter(&$data) {
  $data['types']['field_collection_item'] = array(
    'name' => t('Field collection'),
    'description' => t('Tokens related to field collection.'),
    'needs-data' => 'field_collection_item',
  );
  $data['tokens']['field_collection_item']['host'] = array(
    'name' => t('Host entity'),
    'description' => t('The host entity of this field collection item.'),
    'type' => 'host',
  );
}


/**
 * Implements hook_tokens().
 */
function field_collection_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  // Provide a complete set of tokens for type == 'host', and a supplementary
  // token 'host' for type == 'field_collection_item'.
  if (($type == 'field_collection_item' or $type == 'host') and !empty($data['field_collection_item'])) {
    $collection = $data['field_collection_item'];
    // When saving revisions, only $collection->original has valid state about
    // its host entity.
    if (!empty($collection->original)) {
      $collection = $collection->original;
    }

    if ($type == 'field_collection_item') {
      if (!empty($tokens['host'])) {
        $replacements[$tokens['host']] = $collection->hostEntityId();
      }
      if ($host_tokens = token_find_with_prefix($tokens, 'host')) {
        $replacements += token_generate('host', $host_tokens, $data, $options);
      }
    }

    // $type == 'host'
    else {
      // Mapping between token and the FieldCollectionItemEntity method used to
      // retrieve the token with.
      $token_method_map = array(
        'type' => 'hostEntityType',
        'bundle' => 'hostEntityBundle',
        'id' => 'hostEntityId',
      );
      $entity_types = field_collection_host_entity_types();
      foreach ($tokens as $name => $orig) {
        if (isset($token_method_map[$name])) {
          $replacements[$orig] = $collection->{$token_method_map[$name]}();
        }
        // This replaces e.g. [host:node] and [host:user] with their respective
        // nid and uid.
        if (!empty($entity_types[$name])) {
          $replacements[$orig] = $collection->hostEntityId();
        }
      }
      foreach ($entity_types as $entity_type => $entity_info) {
        if ($entity_tokens = token_find_with_prefix($tokens, $entity_type)) {
          $host = $collection->hostEntity();
          $replacements += token_generate($entity_type, $entity_tokens, array($entity_type => $host), $options);
        }
      }
    }
  }
  return $replacements;
}

/**
 * Entity types that serve as host for field collections.
 *
 * @return array
 *   The list of entities as provided by entity_get_info(), filtered by field
 *   collection usage.
 */
function field_collection_host_entity_types() {
  $host_entity_types = &drupal_static(__FUNCTION__, FALSE);

  if ($host_entity_types === FALSE) {
    $host_entity_types = array();
    $entity_types = entity_get_info();
    // Look for all field instances, filter them by type == 'field_collection'
    // and map the entity type it's connected to to the returned list.
    foreach (field_info_field_map() as $field_instance) {
      if ($field_instance['type'] == 'field_collection') {
        foreach (array_keys($field_instance['bundles']) as $entity_type) {
          if (!isset($host_entity_types[$entity_type])) {
            // No need to test for existence in $entity_types. If it's not there
            // your site is broken.
            $host_entity_types[$entity_type] = $entity_types[$entity_type];
          }
        }
      }
    }
  }
  return $host_entity_types;
}
