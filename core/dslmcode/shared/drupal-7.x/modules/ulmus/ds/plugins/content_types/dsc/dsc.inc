<?php

/**
 * @file
 * Plugin to handle the Display Suite content type.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Display Suite content'),
  'category' => t('Display Suite'),
  'single' => TRUE,
  'defaults' => array(
    'title' => '',
    'body' => '',
    'format' => 'ds_code',
    'context' => array(),
  ),
  'description' => t('Add custom content with the possibility to use the entity object when using the Display Suite format.'),
  'js' => array('misc/textarea.js', 'misc/collapse.js'),
  'all contexts' => TRUE,
);

/**
 * Output function for the 'Display Suite' content type.
 */
function ds_dsc_content_type_render($subtype, $conf, $panel_args, $context, $incoming) {
  $block = new stdClass();

  $field = array();

  $entity = array_shift($context);
  $field['entity'] = isset($entity->data) ? $entity->data : NULL;
  $field['properties']['code']['format'] = $conf['format'];
  $field['properties']['code']['value'] = $conf['body'];

  $block->module = 'ds';
  $block->title = $conf['title'];
  $block->content = ds_render_code_field($field);

  return $block;
}

/**
 * The form to add or edit Display Suite content.
 */
function ds_dsc_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['title'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($conf['title']) ? $conf['title'] : '',
    '#title' => t('Title'),
  );

  $form['body'] = array(
    '#type' => 'text_format',
    '#title' => t('Body'),
    '#default_value' => isset($conf['body']) ? $conf['body'] : '',
    '#format' => isset($conf['format']) ? $conf['format'] : 'ds_code',
  );

  return $form;
}

/**
 * Save the Display Suite content.
 */
function ds_dsc_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['title'] = $form_state['values']['title'];
  $form_state['conf']['body'] = $form_state['values']['body']['value'];
  $form_state['conf']['format'] = $form_state['values']['body']['format'];
  $form_state['conf']['context'] = array();
}

/**
 * Returns the administrative title for a Display Suite content.
 */
function ds_dsc_content_type_admin_title($subtype, $conf) {
  return (!empty($conf['title'])) ? $conf['title'] : t('Display Suite content');
}

/**
 * Display the administrative information for a Display Suite content pane.
 */
function ds_dsc_content_type_admin_info($subtype, $conf) {
  return 'Display Suite content can only be rendered on the frontend.';
}
