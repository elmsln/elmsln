<?php

/**
 * @file
 * Scheduling options for node forms.
 *
 * This content type contains the publish and unpublish scheduling date fields.
 */

$plugin = array(
  'single' => TRUE,
  'edit form' => 'scheduler_form_pane_node_form_menu_content_type_edit_form',
  'render callback' => 'scheduler_form_pane_content_type_render',
  'title' => t('Node form scheduler'),
  'icon' => drupal_get_path('module', 'ctools') . '/plugins/content_types/node_form/icon_node_form.png',
  'description' => t('Scheduler date options on the Node form.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => t('Form'),
);

/**
 * Content type render callback.
 */
function scheduler_form_pane_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = 'node_form';
  $block->title = t('Scheduler options');
  $block->delta = 'scheduler-options';

  if (isset($context->form)) {
    if (isset($context->form['scheduler_settings'])) {
      // Lift the form elements from the original form and make sure it renders.
      $block->content['scheduler_settings'] = $context->form['scheduler_settings'];
      unset($block->content['scheduler_settings']['#pre_render']);
      unset($block->content['scheduler_settings']['#theme_wrappers']);
      $block->content['scheduler_settings']['#type'] = '';

      // Deny access on the original form element rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['scheduler_settings']['#access'] = FALSE;
    }
  }
  else {
    // Display placeholder information.
    $block->content = t('Scheduler options');
  }
  return $block;
}

/**
 * Content type form callback.
 */
function scheduler_form_pane_node_form_menu_content_type_edit_form($form, &$form_state) {
  return $form;
}
