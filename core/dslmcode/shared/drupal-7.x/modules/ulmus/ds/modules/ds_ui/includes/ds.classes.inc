<?php

/**
 * @file
 * Administrative functions for managing CSS classes.
 */

/**
 * Menu callback, show CSS classes form.
 */
function ds_classes_form($form, $form_state) {
  $form = array();

  $form['ds_classes_regions'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS classes for regions'),
    '#default_value' => variable_get('ds_classes_regions', ''),
    '#description' => t('Configure CSS classes which you can add to regions on the "manage display" screens. Add multiple CSS classes line by line.<br />If you want to have a friendly name, separate class and friendly name by |, but this is not required. eg:<br /><em>class_name_1<br />class_name_2|Friendly name<br />class_name_3</em>')
  );

  if (module_exists('token')) {
    $tokens_mapping = token_get_entity_mapping();
    $tokens_list = array();
    foreach($tokens_mapping as $token_map => $entity_map) {
      $tokens_list[] = $token_map;
    }
    $form['token'] = array(
      '#type' => 'container',
      '#theme' => 'token_tree',
      '#token_types' => $tokens_list,
      '#dialog' => TRUE,
    );
  }

  $form['ds_classes_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS classes for fields'),
    '#default_value' => variable_get('ds_classes_fields', ''),
    '#description' => t('Configure CSS classes which you can add to fields on the "manage display" screens. Add multiple CSS classes line by line.<br />If you want to have a friendly name, separate class and friendly name by |, but this is not required. eg:<br /><em>class_name_1<br />class_name_2|Friendly name<br />class_name_3</em>')
  );

  return system_settings_form($form);
}
