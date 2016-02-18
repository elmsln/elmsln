<?php

/**
 * @file
 * Hooks provided by the Inline Entity Form module.
 */

/**
 * Perform alterations before an entity form is included in the IEF widget.
 *
 * @param $entity_form
 *   Nested array of form elements that comprise the entity form.
 * @param $form_state
 *   The form state of the parent form.
 */
function hook_inline_entity_form_entity_form_alter(&$entity_form, &$form_state) {
  if ($entity_form['#entity_type'] == 'commerce_line_item') {
    $entity_form['quantity']['#description'] = t('New quantity description.');
  }
}

/**
 * Perform alterations before the reference form is included in the IEF widget.
 *
 * The reference form is used to add existing entities through an autocomplete
 * field
 *
 * @param $reference_form
 *   Nested array of form elements that comprise the reference form.
 * @param $form_state
 *   The form state of the parent form.
 */
function hook_inline_entity_form_reference_form_alter(&$reference_form, &$form_state) {
  $reference_form['entity_id']['#description'] = t('New autocomplete description');
}

/**
 * Perform alterations to the IEF field type settings.
 *
 * This allows modules to enable IEF to work on custom field types.
 *
 * @param $settings
 *   An array with the following keys:
 *   - entity_type - The entity_type being managed.
 *   - bundles - Bundles of entities that the user is allowed to create.
 *   - column - The name of the ref. field column that stores the entity id.
 * @param $field
 *   The field array of the reference field.
 * @param $instance
 *   The instance array of the reference field.
 */
function hook_inline_entity_form_settings_alter(&$settings, $field, $instance) {
  if ($field['type'] == 'mycustom_reference') {
    $settings['entity_type'] = 'mycustom';
    $settings['column'] = 'mycustom_id';
  }
}

/**
 * Alter the fields used to represent an entity in the IEF table.
 *
 * The fields can be either Field API fields or properties defined through
 * hook_entity_property_info().
 *
 * @param $fields
 *   The table fields to alter. Each field is represented by an associative
 *   array containing the following keys:
 *   - type: either 'property', 'field' or 'callback' to specify how the data is
 *     defined on the related entity.
 *   - label: the title of the table field's column in the IEF table.
 *   - sanitized: for 'property' type table fields, a boolean indicating whether
 *     or not the data has already been sanitized for output; if not present or
 *     FALSE, theme_inline_entity_form_entity_table() will sanitize the data for
 *     output using check_plain().
 *   - formatter: for 'field' type table fields, the machine-name of the display
 *     formatter to use to render the field data. If this is used, then further
 *     keys will be set in the array passed to field_view_field() as the
 *     $display parameter. This allows any of the settings defined in the field
 *     formatter's hook_field_formatter_info() to be used.
 *   - weight: the sort order of the column in the IEF table.
 *   - render_callback: for 'callback' type table fields, a function name that
 *     returns a renderable array.
 * @param $context
 *   An array with the following keys:
 *   - parent_entity_type: The type of the parent entity.
 *   - parent_bundle: The bundle of the parent entity.
 *   - field_name: The name of the reference field on which IEF is operating.
 *   - entity_type: The type of the referenced entities.
 *   - allowed_bundles: Bundles allowed on the reference field.
 *
 * @see EntityInlineEntityFormController::tableFields()
 */
function hook_inline_entity_form_table_fields_alter(&$fields, $context) {
  // IEF is managing products on a node form.
  if ($context['parent_entity_type'] == 'node' && $context['entity_type'] == 'commerce_product') {
    // Commerce Simple Stock is enabled.
    if (module_exists('commerce_ss')) {
      // Make sure there's a stock field on each of the allowed product types.
      $has_stock_field = TRUE;
      foreach ($context['allowed_bundles'] as $bundle) {
        if (!commerce_ss_product_type_enabled($bundle)) {
          $has_stock_field = FALSE;
        }
      }

      if ($has_stock_field) {
        $fields['commerce_stock'] = array(
          'type' => 'field',
          'label' => t('Stock'),
          'weight' => 101,
        );
      }
    }
  }
}
