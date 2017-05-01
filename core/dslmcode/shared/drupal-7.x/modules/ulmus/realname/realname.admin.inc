<?php

/**
 * @file
 * Administrative page callbacks for the realname module.
 */

/**
 * Form constructor for the Real name settings form.
 *
 * @see realname_settings_form_validate()
 * @see realname_settings_form_submit()
 */
function realname_settings_form($form, &$form_state) {
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );

  $note = '<div>';
  $note .= t('Note that if it is changed, all current Realnames will be deleted and the list in the database will be rebuilt as needed.');
  $note .= '</div>';

  $form['general']['realname_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Realname pattern'),
    '#default_value' => variable_get('realname_pattern', '[user:name-raw]'),
    '#element_validate' => array('token_element_validate'),
    '#token_types' => array('user'),
    '#min_tokens' => 1,
    '#required' => TRUE,
    '#maxlength' => 256,
    '#description' => t('This pattern will be used to construct Realnames for all users.') . $note,
  );
  // Add the token tree UI.
  $form['general']['token_help'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('user'),
    '#global_types' => FALSE,
    '#dialog' => TRUE,
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
  );
  $form['advanced']['realname_suppress_user_name_mail_validation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Suppress missing token warning in e-mail templates'),
    '#description' => t('With Real name module enabled you need to replace the token <code>[user:name]</code> with <code>[user:name-raw]</code> in your <a href="@people">e-mail</a> templates. If you are running modules like <em>Email Registration</em> you may like to suppress this warning and use a different token.', array('@people' => url('admin/config/people/accounts', array('fragment' => 'edit-email-admin-created')))),
    '#default_value' => variable_get('realname_suppress_user_name_mail_validation', FALSE),
  );

  $form['#submit'][] = 'realname_settings_form_submit';
  return system_settings_form($form);
}

/**
 * Form validation handler for realname_settings_form().
 *
 * @see realname_settings_form_submit()
 */
function realname_settings_form_validate($form, &$form_state) {
  if (strpos($form_state['values']['realname_pattern'], '[user:name]') !== FALSE) {
    form_set_error('realname_pattern', t('The %token token cannot be used as it will cause recursion.', array('%token' => '[user:name]')));
  }
}

/**
 * Form submission handler for realname_settings_form().
 *
 * @see realname_settings_form_validate()
 */
function realname_settings_form_submit($form, $form_state) {
  if ($form['general']['realname_pattern']['#default_value'] != $form_state['values']['realname_pattern']) {
    // Only clear the realname cache if the pattern was changed.
    realname_delete_all();
  }
}
