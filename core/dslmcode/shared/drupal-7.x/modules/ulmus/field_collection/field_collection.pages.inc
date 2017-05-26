<?php

/**
 * @file
 * Provides the field collection item view / edit / delete pages.
 */

// TODO: fix being embedded in a host with revisions.

/**
 * Field collection item view page.
 */
function field_collection_item_page_view($field_collection_item) {
  // @todo: Set breadcrumb including the host.
  drupal_set_title($field_collection_item->label());
  return $field_collection_item->view('full', NULL, TRUE);
}

/**
 * Form for editing a field collection item.
 * @todo implement hook_forms().
 */
function field_collection_item_form($form, &$form_state, $field_collection_item) {
  if (!isset($field_collection_item->is_new)) {
    drupal_set_title($field_collection_item->label());
  }
  $form_state += array('field_collection_item' => $field_collection_item);

  // Hack: entity_form_field_validate() needs the bundle to be set.
  // @todo: Fix core and remove the hack.
  $form['field_name'] = array('#type' => 'value', '#value' => $field_collection_item->field_name);

  $langcode = entity_language('field_collection_item', $field_collection_item);
  field_attach_form('field_collection_item', $field_collection_item, $form, $form_state, $langcode);

  $form['actions'] = array('#type' => 'actions', '#weight' => 50);
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
  return $form;
}

/**
 * Validation callback.
 */
function field_collection_item_form_validate($form, &$form_state) {
  entity_form_field_validate('field_collection_item', $form, $form_state);
}

/**
 * Submit builder. Extracts the form values and updates the entity.
 */
function field_collection_item_form_submit_build_field_collection($form, $form_state) {
  entity_form_submit_build_entity('field_collection_item', $form_state['field_collection_item'], $form, $form_state);
  return $form_state['field_collection_item'];
}

/**
 * Submit callback that permanently saves the changes to the entity.
 */
function field_collection_item_form_submit($form, &$form_state) {
  $field_collection_item = field_collection_item_form_submit_build_field_collection($form, $form_state);
  $field_collection_item->save();
  drupal_set_message(t('The changes have been saved.'));
  $form_state['redirect'] = $field_collection_item->path();
}

/**
 * Form for deleting a field collection item.
 */
function field_collection_item_delete_confirm($form, &$form_state, $field_collection_item) {
  $form_state += array('field_collection_item' => $field_collection_item);
  return confirm_form($form,
    t('Are you sure you want to delete %label?', array('%label' => $field_collection_item->label())),
    $field_collection_item->path(),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit callback for deleting a field collection item.
 */
function field_collection_item_delete_confirm_submit($form, &$form_state) {
  $field_collection_item = $form_state['field_collection_item'];
  $field_collection_item->deleteRevision();
  drupal_set_message(t('%label has been deleted.', array('%label' => drupal_ucfirst($field_collection_item->label()))));
  $form_state['redirect'] = '<front>';
}

/**
 * Add a new field collection item.
 *
 * @todo: Support optionally passing in the revision_id and langcode parameters.
 */
function field_collection_item_add($field_name, $entity_type, $entity_id, $revision_id = NULL, $langcode = NULL) {
  $info = entity_get_info();
  if (!isset($info[$entity_type])) {
    return MENU_NOT_FOUND;
  }
  $result = entity_load($entity_type, array($entity_id));
  $entity = reset($result);
  if (!$entity) {
    return MENU_NOT_FOUND;
  }
  // Ensure the given entity is of a bundle that has an instance of the field.
  list($id, $rev_id, $bundle) = entity_extract_ids($entity_type, $entity);
  $instance = field_info_instance($entity_type, $field_name, $bundle);
  if (!$instance) {
    return MENU_NOT_FOUND;
  }

  // Check field cardinality.
  $field = field_info_field($field_name);
  $langcode = !empty($field['translatable']) ? entity_language($entity_type, $entity) : LANGUAGE_NONE;

  if (!($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED || !isset($entity->{$field_name}[$langcode]) || count($entity->{$field_name}[$langcode]) < $field['cardinality'])) {
    drupal_set_message(t('Too many items.'), 'error');
    return '';
  }

  $field_collection_item = entity_create('field_collection_item', array('field_name' => $field_name));
  // Do not link the field collection item with the host entity at this point,
  // as during the form-workflow we have multiple field collection item entity
  // instances, which we don't want link all with the host.
  // That way the link is going to be created when the item is saved.
  $field_collection_item->setHostEntity($entity_type, $entity, $langcode, FALSE);

  $label = $field_collection_item->translatedInstanceLabel();
  $title = ($field['cardinality'] == 1) ? $label : t('Add new !instance_label', array('!instance_label' => $label));
  drupal_set_title($title);

  // Make sure the current user has access to create a field collection item.
  if (!entity_access('create', 'field_collection_item', $field_collection_item)) {
    return MENU_ACCESS_DENIED;
  }
  return drupal_get_form('field_collection_item_form', $field_collection_item);
}
