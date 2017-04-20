<?php

/**
 * @file
 * Views integration for field collection fields.
 */

/**
 * Implements hook_field_views_data().
 *
 * Adds a relationship to the default field data.
 *
 * @see field_views_field_default_views_data()
 */
function field_collection_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $field_name = $field['field_name'];

  if (isset($data['field_data_' . $field_name])) {
    $data['field_data_' . $field_name][$field_name . '_value']['relationship'] = array(
      'handler' => 'field_collection_handler_relationship',
      'base' => 'field_collection_item',
      'base field' => 'item_id',
      'label' => t('field collection item from !field_name', array('!field_name' => $field['field_name'])),
      'field_name' => $field['field_name'],
    );
    $data['field_revision_' . $field_name][$field_name . '_revision_id']['relationship'] = array(
      'handler' => 'field_collection_handler_relationship',
      'base' => 'field_collection_item_revision',
      'base field' => 'revision_id',
      'label' => t('field collection item revision from !field_name', array('!field_name' => $field['field_name'])),
      'field_name' => $field['field_name'],
    );
  }

  foreach ($field['bundles'] as $entity_type => $bundles) {
    $entity_info = entity_get_info($entity_type);
    $pseudo_field_name = $field['field_name'] . '_' . $entity_type;

    list($label, $all_labels) = field_views_field_label($field['field_name']);
    $entity = $entity_info['label'];
    if ($entity == t('Node')) {
      $entity = t('Content');
    }

    $data['field_collection_item'][$pseudo_field_name]['relationship'] = array(
      'title' => t('Entity with the @field (@field_name)', array('@entity' => $entity, '@field' => $label, '@field_name' => $field['field_name'])),
      'help' => t('Relate each @entity using @field.', array('@entity' => $entity, '@field' => $label)),
      'handler' => 'views_handler_relationship_entity_reverse',
      'field_name' => $field['field_name'],
      'field table' => _field_sql_storage_tablename($field),
      'field field' => $field['field_name'] . '_value',
      'base' => $entity_info['base table'],
      'base field' => $entity_info['entity keys']['id'],
      'label' => t('!field_name', array('!field_name' => $field['field_name'])),
    );
  }

  return $data;
}
