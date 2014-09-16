<?php
/**
 * @file
 * Provides the filtering form on the analytics dashboard page.
 */

/**
 * Provide a simple form to change time periods
 */
function analytics_dashboard_form() {
  $form = array();

  // Load some javascript for datepicker
  drupal_add_library('system', 'ui.datepicker');
  drupal_add_js('jQuery(document).ready(function(){jQuery( ".pickadate" ).datepicker({
      dateFormat: "dd.mm.yy",
      autoSize: true
    });});', 'inline');

  $period_options = array(
    '1_week' => t('1 week'),
    '2_weeks' => t('2 weeks'),
    '1_month' => t('1 month'),
    '3_months' => t('3 months'),
    '6_months' => t('6 months'),
    '1_year' => t('1 year'),
    '2_years' => t('2 years'),
  );

  $period = isset($_GET['period']) ? filter_xss($_GET['period']) : NULL;
  if (!$period || !array_key_exists($period, $period_options)) {
    $period = '1_month'; // Default value
  }

  $form['option'] = array(
    '#type' => 'radios',
    '#options' => array(
      'period' => '',
      'custom' => '',
    ),
    '#default_value' => isset($_GET['option']) ? filter_xss($_GET['option']) : 'period',
  );

  $form['period'] = array(
    '#type' => 'select',
    '#options' => $period_options,
    '#default_value' => $period,
  );

  $form['custom_from'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#attributes' => array('class' => array('pickadate')),
    '#default_value' => isset($_GET['from']) ? filter_xss($_GET['from']) : '',
  );

  $form['custom_to'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#attributes' => array('class' => array('pickadate')),
    '#default_value' => isset($_GET['to']) ? filter_xss($_GET['to']) : '',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}

/**
 * Validate handler for analytics_dashboard_form()
 */
function analytics_dashboard_form_validate($form, &$form_state) {
  $values = $form_state['values'];

  // Make sure a time option is checked
  if (!$values['option']) {
    form_set_error('error', t('An option must be selected'));
  }

  // If custom option, make sure we have both dates
  if ($values['option'] == 'custom' &&
    !($values['custom_from'] && $values['custom_to'])) {
    form_set_error('option', t('You must specify both dates'));
  }
  elseif ($values['option'] == 'custom') {
    // Convert the times
    $now = time();
    $from = strtotime($values['custom_from']);
    $to = strtotime($values['custom_to']);

    // Make sure from date exists
    if (!$from) {
      form_set_error('custom_from', t('The from date must be formatted correctly %format.', array('%format' => '(MM/DD/YY)')));
    }

    // Make sure to date exists
    if (!$to) {
      form_set_error('custom_to', t('The to date must be formatted correctly %format.', array('%format' => '(MM/DD/YY)')));
    }

    // Make sure from is less than to
    if ($from > $to) {
      form_set_error('custom_from', t('The from date must be before the to date'));
    }

    // Make sure to date is not past current time
    if ($to > $now) {
      form_set_error('custom_to', t('The to date must not be past today'));
    }
  }
}

/**
 * Submit handler for analytics_dashboard_form()
 */
function analytics_dashboard_form_submit(&$form, $form_state) {
  // Add a query to the URL which will be used to determine the query
  switch ($form_state['values']['option']) {
    case 'period':
      drupal_goto($_GET['q'], array('query' => array('option' => 'period', 'period' => $form_state['values']['period'])));
      break;

    case 'custom':
      drupal_goto($_GET['q'], array('query' => array('option' => 'custom', 'from' => $form_state['values']['custom_from'], 'to' => $form_state['values']['custom_to'])));
      break;
  }
}