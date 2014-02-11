<?php
/**
 * @file
 * Token module integration.
 */

/**
 * Implements hook_custom_formatters_form_ctools_export_ui_edit_item_form_alter_alter()
 * on behalf of token.module.
 */
function token_custom_formatters_form_ctools_export_ui_edit_item_form_alter_alter(&$form, $form_state) {
  if (isset($form['#formatters']) && $form['#formatters'] && 'token' == $form['info']['mode']['#default_value']) {
    // Add token tree.
    $fieldable = array();
    $entity_types = entity_get_info();
    foreach ($entity_types as $entity_type => $entity) {
      if ($entity['fieldable']) {
        $fieldable[] = $entity['token type'];
      }
    }
    $token_types = $fieldable;
    $field_type = $form['engine']['field_types']['#default_value'];
    drupal_alter('custom_formatters_token_tree_types', $token_types, $field_type);
    $form['engine']['tokens'] = array(
      '#title' => t('Tokens'),
      '#type' => 'fieldset',
      '#description' => theme('token_tree', array('token_types' => $token_types)),
      '#weight' => 50,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
  }
}

/**
 * Implements hook_custom_formatters_form_builder_types_alter() on behalf of
 * token.module.
 */
function token_custom_formatters_form_builder_types_alter(&$fields) {
  $fields['token_tree'] = array(
    'title' => t('Token tree'),
    'properties' => array(
      'title',
      'key'
    ),
    'default' => array(
      '#title' => t('Tokens'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#theme' => 'token_tree',
      '#token_types' => 'all',
    ),
  );
}
