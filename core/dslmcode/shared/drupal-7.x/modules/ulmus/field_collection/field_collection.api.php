<?php

/**
 * @file
 * Contains API documentation and examples for the Field collection module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter whether a field collection item is considered empty.
 *
 * This hook allows modules to determine whether a field collection is empty
 * before it is saved.
 *
 * @param boolean $empty
 *   Whether or not the field should be considered empty.
 * @param FieldCollectionItemEntity $item
 *   The field collection we are currently operating on.
 */
function hook_field_collection_is_empty_alter(&$is_empty, FieldCollectionItemEntity $item) {
  if (isset($item->my_field) && empty($item->my_field)) {
    $is_empty = TRUE;
  }
}

/**
 * Acts on field collections being loaded from the database.
 *
 * This hook is invoked during field collection item loading, which is handled
 * by entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of field collection item entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_field_collection_item_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a field collection item is inserted.
 *
 * This hook is invoked after the field collection item is inserted into the
 * database.
 *
 * @param FieldCollectionItemEntity $field_collection_item
 *   The field collection item that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_field_collection_item_insert(FieldCollectionItemEntity $field_collection_item) {
  db_insert('mytable')->fields(array(
    'id' => entity_id('field_collection_item', $field_collection_item),
    'extra' => print_r($field_collection_item, TRUE),
  ))->execute();
}

/**
 * Acts on a field collection item being inserted or updated.
 *
 * This hook is invoked before the field collection item is saved to the database.
 *
 * @param FieldCollectionItemEntity $field_collection_item
 *   The field collection item that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_field_collection_item_presave(FieldCollectionItemEntity $field_collection_item) {
  $field_collection_item->name = 'foo';
}

/**
 * Responds to a field collection item being updated.
 *
 * This hook is invoked after the field collection item has been updated in the
 * database.
 *
 * @param FieldCollectionItemEntity $field_collection_item
 *   The field collection item that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_field_collection_item_update(FieldCollectionItemEntity $field_collection_item) {
  db_update('mytable')
    ->fields(array('extra' => print_r($field_collection_item, TRUE)))
    ->condition('id', entity_id('field_collection_item', $field_collection_item))
    ->execute();
}

/**
 * Responds to field collection item deletion.
 *
 * This hook is invoked after the field collection item has been removed from
 * the database.
 *
 * @param FieldCollectionItemEntity $field_collection_item
 *   The field collection item that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_field_collection_item_delete(FieldCollectionItemEntity $field_collection_item) {
  db_delete('mytable')
    ->condition('pid', entity_id('field_collection_item', $field_collection_item))
    ->execute();
}

/**
 * Act on a field collection item that is being assembled before rendering.
 *
 * @param $field_collection_item
 *   The field collection item entity.
 * @param $view_mode
 *   The view mode the field collection item is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $field_collection_item->content prior to
 * rendering. The structure of $field_collection_item->content is a renderable
 * array as expected by drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_field_collection_item_view($field_collection_item, $view_mode, $langcode) {
  $field_collection_item->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for field collection items.
 *
  * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * field collection item content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the field collection item
 * rather than the structured content array, it may use this hook to add a
 * #post_render callback. See drupal_render() and theme() documentation
 * respectively for details.
 *
 * @param $build
 *   A renderable array representing the field collection item content.
 *
 * @see hook_entity_view_alter()
 */
function hook_field_collection_item_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}

/**
 * Alter the label for a field collection.
 *
 * @param FieldCollectionItemEntity $item
 *   The field collection item object.
 * @param $host
 *   The host entity of the field collection item.
 * @param $field
 *   The field information about the item.
 *
 * @return $label
 *   A string to represent the label for this item type.
 */
function hook_field_collection_item_label($item, $host, $field) {
  switch ($item->field_name) {
    case 'field_my_first_collection':
      $item_wrapper = entity_metadata_wrapper('field_collection_item', $item);

      $title  = $item_wrapper->field_title->value();
      $author = $item_wrapper->field_author->value();

      return "{$title} by {$author}";
  }
}


/**
 * @}
 */
