<?php
/**
 * @file
 * Provides settings for analytices dashboard page.
 */

/**
 * Provide admin settings form
 */
function analytics_dashboard_admin_settings($form, &$form_state) {
  $form = array();
  // Get available charts
  $options = array();
  $charts = analytics_dashboard_get_charts();
  foreach ($charts as $chart) {
    $options[$chart['id']] = $chart['title'];
  }

  // Generate default charts selection
  $default = variable_get('chart_visible', array());

  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['display']['chart_visible'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show analytics for the following site items'),
    '#default_value' => $default,
    '#options' => $options,
    '#description' => t('The checked charts will be shown on the analytics page.'),
  );

  return system_settings_form($form);
}