<?php

/**
 * @file
 * Implements a generic entity change owner action.
 */

/**
 * Implements hook_action_info().
 */
function views_bulk_operations_change_owner_action_info() {
  return array(
    'views_bulk_operations_change_owner_action' => array(
      'type' => 'entity',
      'label' => t('Change owner'),
      'configurable' => TRUE,
      'behavior' => array('changes_property'),
      'triggers' => array('any'),
    ),
  );
}

/**
 * Action function.
 */
function views_bulk_operations_change_owner_action($entity, $context) {
  $entity->uid = $context['owner_uid'];
}

/**
 * Action form function.
 */
function views_bulk_operations_change_owner_action_form($context, &$form_state) {
  $form['owner_username'] = array(
    '#type' => 'textfield',
    '#maxlength' => USERNAME_MAX_LENGTH,
    '#title' => t('Owner'),
    '#required' => TRUE,
    '#description' => t('Choose the user you would like to set as the owner.'),
    '#autocomplete_path' => 'user/autocomplete',
  );

  return $form;
}

/**
 * Action form validate function.
 *
 * Checks that the submitted text is a valid username.
 */
function views_bulk_operations_change_owner_action_validate($form, $form_state) {
  if (!user_load_by_name($form_state['values']['owner_username'])) {
    form_set_error('owner_username', t('Valid username required.'));
  }
}

/**
 * Action form submit function.
 *
 * Pass submitted username back to views_bulk_operations_change_owner.
 */
function views_bulk_operations_change_owner_action_submit($form, $form_state) {
  $user = user_load_by_name($form_state['values']['owner_username']);
  return array('owner_uid' => $user->uid);
}
