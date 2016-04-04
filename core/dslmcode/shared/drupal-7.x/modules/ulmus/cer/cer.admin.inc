<?php

/**
 * Form builder to create or edit presets.
 */
function cer_form(array $form, array &$form_state, CerPreset $preset, $do = 'edit', $entity_type = NULL) {
  field_attach_form('cer', $preset, $form, $form_state);

  $form['cer_right']['#id'] = 'edit-cer-right';

  $form['cer_left'][LANGUAGE_NONE]['#ajax'] = array(
    'callback' => 'cer_update_right',
    'wrapper' => $form['cer_right']['#id'],
  );

  $form['actions'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
    '#weight' => 10,
  );

  return $form;
}

function cer_form_submit(array &$form, array &$form_state) {
  $preset = entity_ui_form_submit_build_entity($form, $form_state)->save();

  drupal_set_message(t('The preset has been saved.'));
  $form_state['redirect'] = 'admin/config/content/cer';
}

function cer_update_right(array &$form, array &$form_state) {
  $preset = $form_state['build_info']['args'][0];
  field_attach_submit('cer', $preset, $form, $form_state, array('field_name' => 'cer_left'));

  $left = $preset->wrapper->cer_left->chain->value();
  $left_identifier = $left->__toString();
  $left_re = $left->regex();

  $hierarchy = new FieldHierarchy();
  foreach (CerFieldChain::collectAll() as $chain) {
    if (preg_match($left_re, $chain->__toString()) && preg_match($chain->regex(), $left_identifier)) {
      $hierarchy->addChain($chain);
    }
  }

  $options = $hierarchy->options();
  if ($options) {
    $form['cer_right'][LANGUAGE_NONE]['#options'] = $options;
  }
  else {
    drupal_set_message(t('There are no fields which can correspond with your selection.'), 'warning');
  }

  return $form['cer_right'];
}

/**
 * Enables or disables a preset, depending on its current status. This callback
 * is defined by CerUIController::hook_menu().
 */
function cer_toggle_preset(CerPreset $preset) {
  $preset->wrapper->cer_enabled->set(! $preset->wrapper->cer_enabled->value());
  $preset->save();

  drupal_goto(isset($_GET['destination']) ? $_GET['destination'] : 'admin/config/content/cer');
}

/**
 * Permanently inverts a preset (i.e., deletes the original). This callback
 * is defined by CerUIController::hook_menu().
 */
function cer_invert_preset(CerPreset $original) {
  $original->invert()->save();
  $original->delete();

  drupal_goto(isset($_GET['destination']) ? $_GET['destination'] : 'admin/config/content/cer');
}

/**
 * Allows batch updating of existing entities.
 */
function cer_bulk_update_form(array $form, array &$form_state) {
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Entity type'),
    '#required' => TRUE,
    '#options' => array(),
    '#description' => t('Select the entity type that you want to update.'),
  );
  foreach (entity_get_info() as $type => $class) {
    $form['type']['#options'][$type] = $class['label'];
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * The update form. Allows bulk updating of current entities.
 */
function cer_bulk_update_form_submit(array $form, array &$form_state) {
  $batch = array(
    'finished' => 'cer_batch_update_existing_finished',
    'title' => t('Processing'),
    'init_message' => t('Preparing to update corresponding entity references for existing entities...'),
    'progress_message' => t('Processing entities...'),
    'error_message' => t('Corresponding entity references - existing entity update has encountered an error.'),
    'operations' => array(),
  );

  $entity_type = $form_state['values']['type'];
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', $entity_type);
  if ($entity_type == 'user') {
    $query->entityCondition('entity_id', 0, '>');
  }
  $result = $query->execute();

  if (isset($result[$entity_type])) {
    foreach (array_keys($result[$entity_type]) as $entity_id) {
      $batch['operations'][] = array('cer_processing_entity', array('update', $entity_id, $entity_type));
    }
  }

  batch_set($batch);
}
