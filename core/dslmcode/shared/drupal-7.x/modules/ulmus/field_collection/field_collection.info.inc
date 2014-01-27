<?php

/**
 * @file
 * Provides entity property info for field collection items.
 */

class FieldCollectionItemMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info['field_collection_item']['properties'];

    $properties['field_name']['label'] = t('Field name');
    $properties['field_name']['description'] = t('The machine-readable name of the field collection field containing this item.');
    $properties['field_name']['required'] = TRUE;

    $properties['host_entity'] = array(
      'label' => t('Host entity'),
      'type' => 'entity',
      'description' => t('The entity containing the field collection field.'),
      'getter callback' => 'field_collection_item_get_host_entity',
      'setter callback' => 'field_collection_item_set_host_entity',
      'required' => TRUE,
    );

    return $info;
  }

}