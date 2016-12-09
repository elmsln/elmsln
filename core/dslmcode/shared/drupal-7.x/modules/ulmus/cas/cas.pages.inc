<?php

/**
 * @file
 * User page callbacks for the cas module.
 */

/**
 * Menu callback; Manage CAS identities for the specified user.
 */
function cas_user_identities($account) {
  drupal_set_title(check_plain(format_username($account)));

  $header = array(t('CAS username'), t('Operations'));
  $rows = array();
  foreach ($account->cas_names as $aid => $cas_name) {
    $rows[] = array(check_plain($cas_name), l(t('Delete'), 'user/' . $account->uid . '/cas/delete/' . $aid));
  }

  $build['cas_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  $build['cas_user_add'] = drupal_get_form('cas_user_add', $account);

  return $build;
}

/**
 * Form builder; Add a CAS identity.
 *
 * @ingroup forms
 * @see cas_user_add_validate()
 */
function cas_user_add($form, &$form_state, $account) {
  $form['cas_name'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS username'),
    '#element_validate' => array('_cas_name_element_validate'),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Add a CAS username'));
  return $form;
}

function cas_user_add_submit($form, &$form_state) {
  $query = db_insert('cas_user')
    ->fields(array(
      'uid' => $form_state['build_info']['args'][0]->uid,
      'cas_name' => $form_state['values']['cas_name'],
    ))
    ->execute();
  drupal_set_message(t('CAS username %cas_name added.', array('%cas_name' => $form_state['values']['cas_name'])));
}

/**
 * Menu callback; Delete the specified CAS username from the system.
 */
function cas_user_delete_form($form, $form_state, $account, $aid = 0) {
  return confirm_form(array(), t('Are you sure you want to delete the CAS username %cas_name for %user?', array('%cas_name' => $account->cas_names[$aid], '%user' => $account->name)), 'user/' . $account->uid . '/cas');
}

function cas_user_delete_form_submit($form, &$form_state) {
  $query = db_delete('cas_user')
    ->condition('uid', $form_state['build_info']['args'][0]->uid)
    ->condition('aid', $form_state['build_info']['args'][1])
    ->execute();
  if ($query) {
    drupal_set_message(t('CAS username deleted.'));
  }
  $form_state['redirect'] = 'user/' . $form_state['build_info']['args'][0]->uid . '/cas';
}
