<?php

/**
 * Flat out stolen from commerce_kickstart, thanks for solving this problem!
 * https://www.drupal.org/project/commerce_kickstart
 *
 * Force-set a theme at any point during the execution of the request.
 *
 * Drupal doesn't give us the option to set the theme during the installation
 * process and forces enable the maintenance theme too early in the request
 * for us to modify it in a clean way.
 */
function _harmony_set_theme($target_theme) {
  if ($GLOBALS['theme'] != $target_theme) {
    unset($GLOBALS['theme']);

    drupal_static_reset();
    $GLOBALS['conf']['maintenance_theme'] = $target_theme;
    _drupal_maintenance_theme();
  }
}

/**
 * Implements hook_install_tasks_alter().
 */
function harmony_install_tasks_alter(&$tasks, $install_state) {
  // Set the installation theme.
  _harmony_set_theme('harmony_install_theme');

  // Swap out various steps for our own.
  $harmony_tasks['install_select_locale'] = array(
    'index' => 'harmony_install_select_locale',
    'display_name' => st('Choose language'),
    'run' => INSTALL_TASK_RUN_IF_REACHED,
  );
  $harmony_tasks['install_verify_requirements'] = array(
    'index' => 'harmony_install_verify_requirements',
    'display_name' => st('Verify server &amp; application requirements'),
  );

  // Build up the new tasks array.
  $new_tasks = array();
  foreach ($tasks as $task => $info) {
    // If we've got our own task, push that in to the array.
    if (isset($harmony_tasks[$task])) {
      $harmony_task = $harmony_tasks[$task];
      $new_tasks[$harmony_task['index']] = $harmony_task;
    }
    // Otherwise use what's there.
    else {
      $new_tasks[$task] = $info;
    }
  }
  $tasks = $new_tasks;

  // Load the include file.
  include_once DRUPAL_ROOT . '/profiles/harmony/harmony.steps.inc';
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function harmony_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the Harmony!
  $form['site_information']['site_name']['#default_value'] = st('Harmony');

  // Yoinked from Panopoly distro :3
  // Hide some messages from various modules that are just too chatty.
  drupal_get_messages('status');
  drupal_get_messages('warning');

  // Define a default email address if we can guess a valid one.
  if (valid_email_address('admin@' . $_SERVER['HTTP_HOST'])) {
    $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  }
}
