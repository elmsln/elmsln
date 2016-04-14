<?php
/**
 * @file
 * Hooks provided by the Simplify module.
 */

/**
 * Alter the list of fields that can be hidden.
 *
 * @param array $fields
 *   An associative array of fields that can be hidden, where the key is the
 *   machine name of the field and the value is the human-readable name of the
 *   field.
 * @param string $type
 *   The type of fields passed to the $fields parameter. Can be one of:
 *   nodes, users, comments, taxonomy, blocks.
 *   See simplify_get_fields() for examples.
 */
function hook_simplify_get_fields_alter(&$fields, $type) {
  // Allow our module's custom 'foo' node field to be hidden.
  if ($type == 'nodes') {
    $fields['foo'] = t('Foo field');
  }
}

/**
 * Alter the way fields are hidden, or hide fields defined in
 * hook_simplify_get_fields_alter().
 *
 * @param array $form
 *   The form array in which the field to be hidden resides. Hiding a field is
 *   generally done by setting its '#access' form value to FALSE.
 * @param array $field
 *   The machine name of the field to be hidden as defined in
 *   simplify_get_fields() or hook_simplify_get_fields_alter().
 */
function hook_simplify_hide_field_alter(&$form, $field) {
  // Hide our module's custom 'foo' node field.
  if ($field == 'foo') {
    $form['foo']['#access'] = FALSE;
  }
}
