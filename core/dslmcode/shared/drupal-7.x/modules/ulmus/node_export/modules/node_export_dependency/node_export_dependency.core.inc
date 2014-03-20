<?php

/**
 * @file
 * Contains hook implementations for all relevant core module.
 */

/**
 * Implements hook_node_export_dependency().
 */
function node_node_export_dependency($entity, $entity_type) {
  if ($entity_type == 'node') {
    $dependencies = array();
    // The node has a 'user' dependency through the 'uid' and
    // 'revision_uid' properties.
    node_export_dependency_add($dependencies, $entity, 'user', array('uid', 'revision_uid'));
    // The node has a 'node' dependency through the 'tnid' property.
    node_export_dependency_add($dependencies, $entity, 'node', 'tnid');
    return $dependencies;
  }
}

/**
 * Implements hook_node_export_dependency()
 */
function taxonomy_node_export_dependency($entity, $entity_type) {
  if ($entity_type == 'taxonomy_term') {
    $dependencies = array();
    $terms = taxonomy_get_parents($entity->tid);
    $delta = 0;
    foreach ($terms as $tid => $term) {
      $dependencies[] = array(
        'type' => 'taxonomy_term',
        'id' => $tid,
        'property' => 'parent',
        'delta' => $delta++,
      );
    }
    return $dependencies;
  }
}

/**
 * Implements hook_node_export_dependency().
 */
function book_node_export_dependency($entity, $entity_type) {
  if ($entity_type == 'node' && !empty($entity->book)) {
    $dependencies = array();

    // Book page's root book node.
    if (!empty($entity->book['bid'])) {
       $dependencies[] = array(
         'type' => 'node',
         'id' => $entity->book['bid'],
         'property' => array(array('book', 'bid')),
       );
    }

    // Book page's immediate parent.
    if (!empty($entity->book['plid'])) {
       $parent_nid = db_query(
         'SELECT nid FROM {book} WHERE mlid = :mlid',
         array(':mlid' => $entity->book['plid'])
       )->fetchField();
       $dependencies[] = array(
         'type' => 'node',
         'id' => $parent_nid,
         'property' => array(array('book', 'plid')),
         // Recognise the relationship is not done through the entity id key.
         'relationship' => array(
           'key' => array('menu', 'mlid'),
           'value' => $entity->book['plid'],
         ),
       );
    }

    // Book page's immediate children.
    $flat = book_get_flat_menu($entity->book);
    $children = array();
    if ($entity->book['has_children']) {
      // Walk through the array until we find the current page.
      do {
        $link = array_shift($flat);
      } while ($link && ($link['mlid'] != $entity->book['mlid']));
      // Continue through the array and collect the links whose parent is this page.
      while (($link = array_shift($flat)) && $link['plid'] == $entity->book['mlid']) {
        $matches = array();
        if (preg_match('/^node\/([\d]+)$/', $link['href'], $matches)) {
          $dependencies[] = array(
            'type' => 'node',
            'id' => $matches[1],
          );
        }
      }
    }

    return $dependencies;
  }
}

/**
 * Implements hook_node_export_dependency().
 */
function og_node_export_dependency($entity, $entity_type) {
  if ($entity_type == 'node') {
    $dependencies = array();

    if (!empty($entity->og_groups)) {
      foreach (array_keys($entity->og_groups) as $delta) {
         entity_dependency_add($dependencies, $entity, 'node', array(array('og_groups', $delta)));
      }
    }

    if (!empty($entity->og_parent->nid)) {
      entity_dependency_add($dependencies, $entity, 'node', array(array('og_parent', 'nid')));
    }

    if (!empty($dependencies)) {
      return $dependencies;
    }
  }
}

/**
 * Implements hook_node_export_dependency().
 */
function field_node_export_dependency($entity, $entity_type) {
  $dependencies = array();
  list(,, $bundle_name) = entity_extract_ids($entity_type, $entity);
  $instances = field_info_instances($entity_type, $bundle_name);

  foreach ($instances as $field_name => $instance) {
    $field = field_info_field($field_name);
    foreach ($entity->{$field_name} as $langcode => $items) {
      $field_dependencies = module_invoke($field['module'], 'node_export_dependency_field', $entity_type, $entity, $field, $instance, $langcode, $items);

      // Let other modules alter dependencies for this field.
      drupal_alter('node_export_dependency_field', $field_dependencies, $entity_type, $entity, $field, $instance, $langcode, $items);

      if (!empty($field_dependencies)) {
        foreach ($field_dependencies as &$field_dependency) {
          if (empty($field_dependency['module'])) {
            $field_dependency['module'] = $field['module'];
          }
          if (empty($field_dependency['field_name'])) {
            $field_dependency['field_name'] = $field_name;
          }
          if (empty($field_dependency['langcode'])) {
            $field_dependency['langcode'] = $langcode;
          }
        }
        $dependencies = array_merge_recursive($dependencies, $field_dependencies);
      }
    }
  }
  return $dependencies;
}

/**
 * Implements hook_node_export_dependency_field().
 */
function taxonomy_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items) {
  // No need to check for the field type here, since this hook is only called
  // for the owner of this field. Taxonomy module only owns one field.
  $dependencies = array();
  node_export_dependency_add($dependencies, $items, 'taxonomy_term', 'tid');
  return $dependencies;
}

/**
 * Implements hook_node_export_dependency_field().
 */
function file_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items) {
  $dependencies = array();
  node_export_dependency_add($dependencies, $items, 'file', 'fid');
  node_export_dependency_add($dependencies, $items, 'user', 'uid');
  return $dependencies;
}

/**
 * Implements hook_node_export_dependency_field().
 */
function image_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items) {
  return file_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_node_export_dependency_field().
 */
function node_reference_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items) {
  $dependencies = array();
  node_export_dependency_add($dependencies, $items, 'node', 'nid');
  return $dependencies;
}

/**
 * Implements hook_node_export_dependency_field().
 */
function user_reference_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items) {
  $dependencies = array();
  node_export_dependency_add($dependencies, $items, 'user', 'uid');
  return $dependencies;
}

/**
 * Implements hook_node_export_dependency_field().
 */
function entityreference_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items) {
  $dependencies = array();
  node_export_dependency_add($dependencies, $items, $field['settings']['target_type'], 'target_id');
  return $dependencies;
}

/**
 * Implements hook_node_export_dependency_field().
 */
function field_collection_node_export_dependency_field($entity_type, $entity, $field, $instance, $langcode, $items) {
  $dependencies = array();
  node_export_dependency_add($dependencies, $items, 'field_collection_item', 'value');
  return $dependencies;
}

