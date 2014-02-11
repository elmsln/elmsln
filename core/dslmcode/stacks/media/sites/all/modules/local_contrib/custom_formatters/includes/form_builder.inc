<?php
/**
 * @file
 * Form Builder module integration.
 */

/**
 * Implements hook_custom_formatters_form_alter_alter() on behalf of
 * form_builder.module.
 */
function form_builder_custom_formatters_form_alter_alter(&$form, &$form_state, $form_id) {
  if (in_array($form_id, array('ctools_export_ui_edit_item_form', 'ctools_export_ui_edit_item_wizard_form')) && isset($form['#formatters']) && isset($form['engine']['settings'])) {
    if ($form_state['op'] == 'add' || ($form_state['op'] == 'edit' && !custom_formatters_formatter_is_active($form_state['item']))) {
      drupal_add_css(drupal_get_path('module', 'custom_formatters') . '/styles/custom_formatters.form_builder.css');

      $form['engine']['settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Formatter settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#tree' => TRUE,
      );

      module_load_include('inc', 'form_builder', 'includes/form_builder.admin');
      module_load_include('inc', 'form_builder', 'includes/form_builder.api');
      module_load_include('inc', 'form_builder', 'includes/form_builder.cache');

      $form_type = 'custom_formatters';
      $form_id = drupal_substr($form['#build_id'], 0, 32);

      // Set the current form type (used for display of the sidebar block).
      form_builder_active_form($form_type, $form_id);

      // Load the current state of the form.
      $form_structure = _custom_formatters_form_builder_load_form($form['#item'], $form_id);

      $form['engine']['settings']['preview'] = form_builder_preview($form, $form_state, $form_structure, $form_type, $form_id);
      $form['#submit'][] = 'custom_formatters_form_builder_submit';
    }
  }
}

/**
 *
 */
function custom_formatters_form_builder_submit($form, &$form_state) {
  module_load_include('inc', 'form_builder', 'includes/form_builder.admin');
  module_load_include('inc', 'form_builder', 'includes/form_builder.api');
  module_load_include('inc', 'form_builder', 'includes/form_builder.cache');

  // @TODO - Reproduce this functionality or require form_builder_examples.module.
  include drupal_get_path('module', 'form_builder') . '/examples/form_builder_examples.module';

  $form_id = drupal_substr($form['form_build_id']['#value'], 0, 32);
  $form_cache = form_builder_cache_load('custom_formatters', $form_id);
  if (is_array($form_cache)) {
    $form_state['item']->fapi = form_builder_examples_export_recurse($form_cache);
  }

  // Remove the cached form_builder form.
  form_builder_cache_delete('custom_formatters', $form_id);
}

/**
 * Load Form Builder form.
 */
function _custom_formatters_form_builder_load_form($formatter, $form_id) {
  $form = array();

  // Load form from cache during AJAX callback.
  if (strstr(request_uri(), 'system/ajax')) {
    $form = form_builder_cache_load('custom_formatters', $form_id);
  }

  // Load form from formatter.
  elseif (!empty($formatter->name) && isset($formatter->fapi)) {
    ob_start();
    eval($formatter->fapi);
    ob_get_clean();

    if (isset($form)) {
      foreach ($form as $key => &$element) {
        $element['#key'] = $key;
        $element['#form_builder'] = array(
          'element_id' => $key,
          'element_type' => $element['#type'],
          'configurable' => TRUE,
          'removable' => TRUE,
        );
      }
    }
    form_builder_cache_save('custom_formatters', $form_id, $form);
  }

  return $form;
}

/**
 * Implements hook_form_builder_types().
 */
function custom_formatters_form_builder_types() {
  $fields = array();

  $fields['select'] = array(
    'title' => t('Select list'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'options',
      'multiple', // Handled by options element.
      'key_type', // Handled by options element.
      'key_type_toggle', // Handled by options element.
      'key_type_toggled', // Handled by options element.
      'key',
    ),
    'default' => array(
      '#title' => t('New select list'),
      '#type' => 'select',
      '#options' => array('1' => 'one', '2' => 'two', '3' => 'three'),
      '#multiple_toggle' => TRUE,
    ),
  );

  $fields['checkboxes'] = array(
    'title' => t('Checkboxes'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'options',
      'multiple',
      'key_type', // Handled by options element.
      'key_type_toggle', // Handled by options element.
      'key_type_toggled', // Handled by options element.
      'key',
    ),
    'default' => array(
      '#title' => t('New checkboxes'),
      '#type' => 'checkboxes',
      '#options' => array('one' => 'one', 'two' => 'two', 'three' => 'three'),
    ),
  );

  $fields['radios'] = array(
    'title' => t('Radios'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'options',
      'key_type', // Handled by options element.
      'key_type_toggle', // Handled by options element.
      'key_type_toggled', // Handled by options element.
      'key',
    ),
    'default' => array(
      '#title' => t('New radios'),
      '#type' => 'radios',
      '#options' => array('one' => 'one', 'two' => 'two', 'three' => 'three'),
    ),
  );

  $fields['textfield'] = array(
    'title' => t('Textfield'),
    'properties' => array(
      'title',
      'description',
      'field_prefix',
      'field_suffix',
      'default_value',
      'required',
      'size',
      'key',
    ),
    'default' => array(
      '#title' => t('New textfield'),
      '#type' => 'textfield',
    ),
  );

  $fields['textarea'] = array(
    'title' => t('Textarea'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'rows',
      'cols',
      'key',
    ),
    'default' => array(
      '#title' => t('New textarea'),
      '#type' => 'textarea',
    ),
  );

  // Allow other modules to modify the fields.
  drupal_alter('custom_formatters_form_builder_types', $fields);

  return array(
    'custom_formatters' => $fields
  );
}
