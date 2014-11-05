<?php

/**
 * @file
 * Provides functionality for configuring drd_server and to return blocks for the admin module.
 */

/**
 * Settings form for the current module.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form_state array.
 *
 * @return array
 *   Array containing the system settings form.
 */
function drd_server_settings($form, $form_state) {
  $form = array();
  $form['drd_allowed_referer'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed referer IP addresses'),
    '#default_value' => variable_get('drd_allowed_referer', ''),
    '#description' => t('Separate multiple values with spaces, commas or semicolons.')
  );
  $form['drd_aes_keys'] = array(
    '#type' => 'container',
  );
  $keys = variable_get('drd_aes_keys', array());
  foreach (drd_get_allowed_referers() as $ip) {
    $ip = trim($ip);
    if (empty($ip)) {
      continue;
    }
    if (!isset($keys[$ip])) {
      $keys[$ip] = array();
    }
    $keys[$ip] += array(
      'key' => '',
      'cipher' => '',
      'iv' => '',
      'impl' => '',
      'cluster_mode' => FALSE,
      'cluster_ips' => '',
    );
    $form['drd_aes_keys'][$ip] = array(
      '#type' => 'fieldset',
      '#title' => $ip,
    );
    $form['drd_aes_keys'][$ip]['impl'] = array(
      '#type' => 'textfield',
      '#title' => 'Implementation',
      '#default_value' => $keys[$ip]['impl'],
      '#disabled' => TRUE,
    );
    $form['drd_aes_keys'][$ip]['cipher'] = array(
      '#type' => 'textfield',
      '#title' => 'Cipher',
      '#default_value' => $keys[$ip]['cipher'],
      '#disabled' => TRUE,
    );
    $form['drd_aes_keys'][$ip]['key'] = array(
      '#type' => 'textfield',
      '#title' => 'Key',
      '#default_value' => $keys[$ip]['key'],
      '#disabled' => TRUE,
    );
    $form['drd_aes_keys'][$ip]['iv'] = array(
      '#type' => 'textfield',
      '#title' => 'IV',
      '#default_value' => $keys[$ip]['iv'],
      '#disabled' => TRUE,
    );
    $form['drd_aes_keys'][$ip]['cluster_ips'] = array(
      '#type' => 'textarea',
      '#title' => 'IP addresses in cluster mode',
      '#default_value' => $keys[$ip]['cluster_ips'],
      '#disabled' => TRUE,
      '#access' => $keys[$ip]['cluster_mode']
    );
    $form['drd_aes_keys'][$ip]['edit'] = array(
      '#type' => 'submit',
      '#value' => 'Edit ' . $ip,
    );
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  $form['actions']['drd_server_debug_export'] = array('#type' => 'submit', '#value' => t('Export Debug Log'));
  return $form;
}

/**
 * Submit handler for the settings form.
 *
 * @param array $form
 *   Form definition.
 * @param array $form_state
 *   Form_state array including form values and more.
 */
function drd_server_settings_submit($form, $form_state) {
  if ($form_state['values']['op'] == $form_state['values']['drd_server_debug_export']) {
    _drd_server_export_debug_log();
    drupal_goto('admin/config/system/drd_settings');
  }

  if ($form_state['values']['op'] != $form['actions']['submit']['#value']) {
    // An edit button was clicked.
    foreach ($form['drd_aes_keys'] as $ip => $key_form) {
      if (is_array($key_form)) {
        if ($key_form['edit']['#value'] == $form_state['values']['op']) {
          drupal_goto('admin/config/system/drd_settings/' . $ip);
        }
      }
    }
    // No valid button was found
    drupal_goto('admin/config/system/drd_settings');
  }

  variable_set('drd_allowed_referer', $form_state['values']['drd_allowed_referer']);
  $ips = drd_get_allowed_referers($form_state['values']['drd_allowed_referer']);
  $aes_keys = variable_get('drd_aes_keys', array());
  foreach ($aes_keys as $key => $def) {
    $aes_keys[$key]['keep'] = FALSE;
  }
  $changed = FALSE;
  if (!empty($aes_keys)) {
    $keys = array_keys($aes_keys);
    $master = $aes_keys[$keys[0]];
    foreach ($ips as $ip) {
      if (!array_key_exists($ip, $aes_keys)) {
        $aes_keys[$ip] = $master;
        $aes_keys[$ip]['keep'] = TRUE;
        $changed = TRUE;
      }
      else {
        $aes_keys[$ip]['keep'] = TRUE;
      }
    }
  }
  foreach ($aes_keys as $key => $def) {
    if (!$aes_keys[$key]['keep']) {
      unset($aes_keys[$key]);
      $changed = TRUE;
    }
  }
  if ($changed) {
    variable_set('drd_aes_keys', $aes_keys);
    $sites = drd_server_read_sites();
    drd_server_key_remote($sites, $aes_keys);
  }
}

/**
 * AES key settings form for an IP of an accepted DRD instance.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form_state array.
 * @param string $ip
 *   The IP address for which the settings should be edited
 *
 * @return array
 *   Array containing the form.
 */
function drd_server_settings_keys($form, $form_state, $ip) {
  $allowed = drd_get_allowed_referers();
  if (!in_array($ip, $allowed)) {
    drupal_not_found();
    exit;
  }

  drupal_set_title(t('Set AES keys for !ip', array('!ip' => $ip)));

  $keys = variable_get('drd_aes_keys', array());
  if (!isset($keys[$ip])) {
    $keys[$ip] = array();
  }
  $keys[$ip] += array(
    'key' => '',
    'cipher' => '',
    'iv' => '',
    'impl' => '',
    'cluster_mode' => FALSE,
    'cluster_ips' => '',
  );

  $form['#ip'] = $ip;

  $form += aes_config();
  unset($form['aes']['aes_convert']);
  unset($form['aes']['view_method']);
  unset($form['aes']['aes_key']);
  unset($form['aes']['aes_key_c']);
  unset($form['aes']['aes_key_storage_method']);
  unset($form['aes']['aes_key_path']);
  unset($form['aes']['submit']);
  $form['aes']['aes_implementation']['#default_value'] = $keys[$ip]['impl'];
  $form['aes']['aes_cipher']['#default_value'] = $keys[$ip]['cipher'];
  $form['aes']['aes_key'] = array(
    '#type' => 'textfield',
    '#title' => 'Key',
    '#default_value' => $keys[$ip]['key'],
  );
  $form['aes']['aes_iv'] = array(
    '#type' => 'textfield',
    '#title' => 'IV',
    '#default_value' => $keys[$ip]['iv'],
  );
  $form['aes']['cluster_mode'] = array(
    '#type' => 'checkbox',
    '#title' => 'Operate on a cluster behind load balancer',
    '#default_value' => $keys[$ip]['cluster_mode'],
  );
  $form['aes']['cluster_ips'] = array(
    '#type' => 'textarea',
    '#title' => 'IP addresses in cluster mode',
    '#default_value' => $keys[$ip]['cluster_ips'],
    '#description' => t('One IP address per line'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  $form['actions']['cancel'] = array('#type' => 'submit', '#value' => t('Cancel'));
  return $form;
}

/**
 * Submit handler for the AES key settings form.
 *
 * @param array $form
 *   Form definition.
 * @param array $form_state
 *   Form_state array including form values and more.
 */
function drd_server_settings_keys_submit($form, $form_state) {
  if ($form_state['values']['op'] == $form_state['values']['submit']) {
    $ip = $form['#ip'];
    $keys = variable_get('drd_aes_keys', array());
    $old_key = isset($keys[$ip]) ? serialize($keys[$ip]) : '';
    $keys[$ip] = array(
      'key' => $form_state['values']['aes_key'],
      'cipher' => $form_state['values']['aes_cipher'],
      'iv' => $form_state['values']['aes_iv'],
      'impl' => $form_state['values']['aes_implementation'],
      'cluster_mode' => $form_state['values']['cluster_mode'],
      'cluster_ips' => $form_state['values']['cluster_ips'],
    );
    $new_key = serialize($keys[$ip]);
    if ($old_key != $new_key) {
      variable_set('drd_aes_keys', $keys);
      $sites = drd_server_read_sites();
      drd_server_key_remote($sites, $keys);
    }
  }
  drupal_goto('admin/config/system/drd_settings');
}

/**
 * DRD Server Admin block.
 *
 * @return array
 *   Renderable array containing admin details.
 */
function drd_server_admin_block() {
  $block = array(
    'subject' => t('Extra Admin'),
    'content' => '',
  );
  $menu = array();
  if (user_access('administer site configuration')) {
    $menu[] = array(
      'data' => l(t('Run Cron'), 'admin/reports/status/run-cron'),
      'class' => array('leaf'),
    );
    $menu[] = array(
      'data' => l(t('Run Update'), 'update.php'),
      'class' => array('leaf'),
    );
    if (module_exists('job_scheduler')) {
      $destination = drupal_get_destination();
      $menu[] = array(
        'data' => l(t('Rebuild Scheduler'), 'admin/drd_server/rebuild_scheduler', array('query' => $destination)),
        'class' => array('leaf'),
      );
    }
  }
  if (user_access('flush cache')) {
    $destination = drupal_get_destination();
    $menu[] = array(
      'data' => l(t('Flush Cache'), 'admin/drd_server/flush/cache', array('query' => $destination)),
      'class' => array('leaf'),
    );
  }
  if (user_access('translate interface')) {
    $menu[] = array(
      'data' => l(t('Update Translation'), 'admin/drd_server/update/translation'),
      'class' => array('leaf'),
    );
  }
  drupal_alter('drd_server_admin_block', $menu);
  if (empty($menu)) {
    return FALSE;
  }
  $block['content'] = theme('item_list', array('items' => $menu, 'attributes' => array('class' => array('menu'))));
  return $block;
}

/**
 * Function to update translations of the current domain.
 *
 * @param boolean $redirect
 *   If TRUE, this function will perform a redirect using drupal_goto() instead of just returning after completion.
 */
function drd_server_admin_update_translation($redirect = TRUE) {
  if (module_exists('l10n_update')) {
    set_time_limit(0);

    module_load_include('admin.inc', 'l10n_update');
    $steps = array(
      t('Refresh information'),
      t('Update translations'),
    );

    foreach ($steps as $step) {
      $projects = l10n_update_get_projects();
      $languages = l10n_update_language_list('name');
      if ($languages) {
        $history = l10n_update_get_history();
        $available = l10n_update_available_releases();
        $updates = l10n_update_build_updates($history, $available);
        $form_state = array(
          'values' => array(
            'op' => $step,
            'mode' => variable_get('l10n_update_import_mode', LOCALE_IMPORT_KEEP),
            // Send the empty array so that all languages get updated.
            'languages' => array(),
            'updates' => $updates,
          ),
        );
        $form = array();
        l10n_update_admin_import_form_submit($form, $form_state);
      }
    }
    $batch = &batch_get();
    if ($batch && !isset($batch['current_set'])) {
      // Set progressive to FALSE if called from xmlrpc.php.
      $batch['progressive'] = $redirect;
      $batch['form_state'] = array(
        'rebuild' => FALSE,
        'programmed' => FALSE,
      );
      batch_process();
    }
  }

  // Allow other modules as well to jump in with translation update routines.
  module_invoke_all('drd_server_update_translation');

  if ($redirect) {
    drupal_goto($_SERVER['HTTP_REFERER']);
  }
}

/**
 * Exports all current debug log entries from watchdog to an HTML file.
 */
function _drd_server_export_debug_log() {
  if (!module_exists('dblog')) {
    drupal_set_message('Module dblog not enabled, nothing to export.', 'error');
    return;
  }
  $entries = db_select('watchdog', 'w')
    ->fields('w', array('message', 'variables', 'timestamp'))
    ->condition('w.type', 'DRD Server')
    ->orderBy('w.wid')
    ->execute()
    ->fetchAll();
  if (empty($entries)) {
    drupal_set_message('No debug entries available.', 'warning');
    return;
  }
  $filename = 'drd_server_debug_' . format_date(REQUEST_TIME, 'custom', 'Ymd_hi') . '.html';
  $n = 0;
  $html = '<html><body><h1>DRD Server Debug Log</h1>';
  foreach ($entries as $entry) {
    $n++;
    $html .= '<p><span>' . $entry->timestamp . '</span> ' . t($entry->message, unserialize($entry->variables)) . '</p>';
  }
  $html .= '</body></html>';
  file_put_contents(file_directory_temp() . '/' . $filename, $html);
  drupal_set_message(t('DRD Server debug exported with !n records. !link', array('!n' => $n, '!link' => l('Download', 'system/temporary/' . $filename))));
}
