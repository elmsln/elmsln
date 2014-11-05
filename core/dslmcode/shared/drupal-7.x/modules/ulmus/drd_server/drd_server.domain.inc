<?php

/**
 * @file
 * Provides domain related functionality triggered by DRD.
 */

/**
 * DRD Server Action to retrieve all kind of information from the current domain.
 *
 * @return string
 *   Array prepared as returnable string to DRD containing domain information.
 */
function drd_server_domain_info() {
  if (module_exists('mollom')) {
    $mollom_status = _mollom_status(TRUE);
    if (is_array($mollom_status)) {
      if (empty($mollom_status['isVerified'])) {
        /*
         * The index 'isVerified' is either not defined (pre Mollom version 2.9)
         * or it is set to false, from version 2.9 onwards.
         *
         * In both cases, mollom doesn't work and therefore gets disabled.
         */
        module_disable(array('mollom'));
      }
    }
  }
  $result = array(
    'drd_db' => array(
      'drd_domain' => array(
        'mode' => 'update',
        'field' => 'name',
        'value' => variable_get('site_name', ''),
        'where' => 'did = @id',
      ),
      'drd_server' => array(
        'mode' => 'update',
        'field' => 'drupalversion',
        'value' => VERSION,
        'where' => 'sid = @sid',
      ),
    ),
  );

  // Load .install files.
  include_once DRUPAL_ROOT . '/includes/install.inc';
  drupal_load_updates();
  // Check run-time requirements and status information.
  $requirements = module_invoke_all('requirements', 'runtime');

  $result['cache']['info']['domain'] = array(
    'title' => 'Information',
    'callback' => 'theme',
    'arguments' => array('status_report', 'variables' => array('requirements' => $requirements)),
  );
  $vars = $GLOBALS;
  $result['cache']['variable']['domain'] = array(
    'title' => 'Variables',
    'callback' => '_drd_variables_block',
    'arguments' => array(serialize($vars['conf'])),
  );
  unset($vars['conf']);
  $result['cache']['globals']['domain'] = array(
    'title' => 'Globals',
    'callback' => '_drd_variables_block',
    'arguments' => array(serialize($vars)),
  );
  return drd_server_result('info', $result);
}

/**
 * DRD Server Action to flush all caches from the current domain.
 *
 * @param boolean $redirect
 *   If TRUE, a redirect will be performed at the end, otherwise it returns normally.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_domain_flush_cache($redirect = FALSE) {
  drupal_flush_all_caches();
  registry_rebuild();
  drupal_set_message('Caches cleared');
  if ($redirect) {
    $destination = empty($_SERVER['HTTP_REFERER']) ? NULL : $_SERVER['HTTP_REFERER'];
    drupal_goto($destination);
  }
  return drd_server_result('cache.flush', '');
}

/**
 * Callback to mark the job scheduler to be rebuilt during next cron run.
 */
function drd_server_domain_rebuild_scheduler() {
  job_scheduler_rebuild_all();
  drupal_goto();
}

/**
 * DRD Server Action to run cron on the current domain.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_domain_run_cron() {
  drupal_cron_run();
  drupal_set_message('Cron completed');
  return drd_server_result('run.cron', '');
}

/**
 * DRD Server Action to determine all available updates for the current domain.
 *
 * @param string $mode
 *   Whether to return available updates into the domain field of the array or the server key.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_domain_list_updates($mode = 'domain') {
  if (!module_exists('update')) {
    drupal_set_message(t('Update module not installed.'));
    return drd_server_result('list.updates', '');
  }

  $frequency = variable_get('update_check_frequency', 1);
  $interval = 60 * 60 * 24 * $frequency;
  if ((REQUEST_TIME - variable_get('update_last_check', 0)) > $interval) {
    update_refresh();
    module_load_include('inc', 'update', 'update.fetch');
    $queue = DrupalQueue::get('update_fetch_tasks');
    while ($item = $queue->claimItem()) {
      _update_process_fetch_task($item->data);
      $queue->deleteItem($item);
    }
  }
  else {
    update_get_available(TRUE);
  }
  update_clear_update_disk_cache();

  module_load_include('inc', 'update', 'update.manager');
  $form = drupal_get_form('update_manager_update_form', 'report');
  $result['cache']['update'][$mode] = array(
    'title' => 'Available Updates',
    'callbacks' => array(
      '0' => array(
        'callback' => 'theme',
        'arguments' => array(
          'update_last_check' => 'update_last_check',
          'variables' => array('last' => variable_get('update_last_check', 0))
        ),
      ),
      '1' => array(
        'callback' => 'drupal_render',
        'arguments' => array('form' => array($form)),
      ),
    ),
  );
  $prj_cache = _update_cache_get('update_project_data');
  $result['projects'] = $prj_cache->data;
  return drd_server_result('list.updates', $result);
}

/**
 * DRD Server Action to run update.php on the current domain.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_domain_run_update() {
  global $user;
  $user = user_load(1);
  $old_mode = variable_get('maintenance_mode', FALSE);
  variable_set('maintenance_mode', TRUE);
  $batch = array(
    'operations' => array(array('drd_server_domain_find_required_updates', array())),
  );
  batch_set($batch);
  $batch = &batch_get();
  $batch['progressive'] = FALSE;
  $base_url = DRUPAL_ROOT;
  $_GET['token'] = drupal_get_token('update');
  $_REQUEST['op'] = 'Apply pending updates';
  $_POST['start'] = array();
  include_once './update.php';
  variable_set('maintenance_mode', $old_mode);
  drupal_set_message('Update completed');
  return drd_server_result('run.update', '');
}

/**
 * DRD Server Action to update all translations on the current domain.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_domain_update_translation() {
  module_load_include('inc', 'drd_server', 'drd_server.admin');
  drd_server_admin_update_translation(FALSE);
  return drd_server_result('update.translation', '');
}

/**
 * DRD Server Action to switch maintenance mode on/off on the current domain.
 *
 * @param boolean $flag
 *   TRUE to turn maintenance mode on, FALSE otherwise.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_domain_switch_maintenance($flag) {
  variable_set('maintenance_mode', $flag);
  cache_clear_all('*', 'cache_page', TRUE);
  $text = $flag ? 'Turned maintenance mode on' : 'Turned maintenance mode off';
  drupal_set_message($text);
  return drd_server_result('switch.maintenance', '');
}

/**
 * Internal function called by update.php
 */
function drd_server_domain_find_required_updates() {
  drupal_get_messages();
  $form = array();
  $form_state = array();
  $form = update_script_selection_form($form, $form_state);
  $operations = array();
  if (isset($form) && isset($form['start'])) {
    $start = array();
    foreach ($form['start'] as $module => $def) {
      if (isset($def['#value']) && module_exists($module)) {
        $start[$module] = $def['#value'];
      }
    }
    $updates = update_resolve_dependencies($start);
    $dependency_map = array();
    foreach ($updates as $function => $update) {
      $dependency_map[$function] = !empty($update['reverse_paths']) ? array_keys($update['reverse_paths']) : array();
    }
    foreach ($updates as $update) {
      if ($update['allowed']) {
        if (isset($start[$update['module']])) {
          drupal_set_installed_schema_version($update['module'], $update['number'] - 1);
          unset($start[$update['module']]);
        }
        $function = $update['module'] . '_update_' . $update['number'];
        $operations[] = array(
          'update_do_one',
          array(
            $update['module'],
            $update['number'],
            $dependency_map[$function]
          ),
        );
        watchdog('DRD Server', 'Updating ' . $update['module'] . ': version ' . $update['number']);
        drupal_set_message('Updating ' . $update['module'] . ': version ' . $update['number']);
      }
    }
  }
  $operations[] = array('drd_server_domain_capture_update_messages', array());
  $batch = array(
    'operations' => $operations,
    'title' => 'Updating',
    'init_message' => 'Starting updates',
    'error_message' => 'An unrecoverable error has occurred. You can find the error message below. It is advised to copy it to the clipboard for reference.',
  );
  batch_set($batch);
}

/**
 * Internal function called by update.php
 */
function drd_server_domain_capture_update_messages() {
  $batch_set = &_batch_current_set();
  update_finished(TRUE, $batch_set['results'], array(), format_interval($batch_set['elapsed'] / 1000));
  drupal_set_message(update_results_page());
}

/**
 * Define name and password for the special user 1.
 *
 * @param string $username
 *   The username for user 1.
 * @param string $password1
 *   The new password for user 1.
 * @param string $password2
 *   Conirming the new password.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_domain_reset_user1($username, $password1, $password2) {
  $check = user_validate_name($username);
  if (!empty($check)) {
    return drd_server_error($check);
  }
  $user = user_load_by_name($username);
  if (!empty($user) && $user->uid !== 1) {
    return drd_server_error(t('Username already taken.'));
  }
  if (empty($password1)) {
    return drd_server_error(t('Password can not be empty.'));
  }
  if ($password1 !== $password2) {
    return drd_server_error(t('Passwords do not patch.'));
  }

  $account = user_load(1);
  $edit = array(
    'name' => $username,
    'pass' => $password1,
  );
  if (!user_save($account, $edit)) {
    return drd_server_error(t('Changing user credentials failed.'));
  }
  return drd_server_result('set.user1', '');
}

/**
 * @param string $php
 * @return string
 */
function drd_server_domain_php($php) {
  try {
    if (module_exists('php')) {
      php_eval($php);
    }
  }
  catch (Exception $ex) {
    watchdog_exception('DRD Server', $ex, 'Error while executing PHP.');
  }
  return drd_server_result('php', '');
}
