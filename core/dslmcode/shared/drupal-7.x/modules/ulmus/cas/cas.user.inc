<?php

/**
 * @file
 * Provides CAS user registration administrative pages.
 */

/**
 * Creates a CAS user registration page.
 */
function cas_add_user_form() {
  $form = array();

  $form['account']['cas_name'] = array(
    '#type' => 'textarea',
    '#title' => t('CAS username(s)'),
    '#required' => TRUE,
    '#default_value' => '',
    '#description' => t('Enter a single username, or multiple usernames, one per line. Registration will proceed as if the user(s) with the specified CAS username just logged in.'),
    '#element_validate' => array('_cas_name_element_validate'),
    '#weight' => -10,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create new account(s)'),
  );
  return $form;
}

function cas_add_user_form_submit($form, &$form_state) {
  $cas_names = preg_split('/[\n\r|\r|\n]+/', $form_state['values']['cas_name']);

  foreach ($cas_names as $cas_name) {
    $operations[] = array('cas_batch_user_add', array($cas_name));
  }

  $batch = array(
    'title' => t('Creating users...'),
    'operations' => $operations,
    'finished' => 'cas_batch_user_finished',
    'progress_message' => t('Processed @current out of @total.'),
    'file' => drupal_get_path('module', 'cas') . '/cas.batch.inc',
  );

  batch_set($batch);
}
