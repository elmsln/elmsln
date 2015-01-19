<?php
/**
 * @file
 * Admin-pages for managing the ClamAV module.
 */

/**
 * Admin settings page for ClamAV
 */
function clamav_admin_settings($form, &$form_state) {
  // Load the include helper so that the form can test connectivity to ClamAV
  // and report success/failure.
  module_load_include('inc', 'clamav');

  $form = array();

  $form['antivirus'] = array(
    '#type' => 'fieldset',
    '#title' => t('ClamAV'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['antivirus']['clamav_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable ClamAV anti-virus scans'),
    '#default_value' => variable_get('clamav_enabled', TRUE),
  );
  $form['antivirus']['clamav_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Select scan method'),
    '#options' => array(
      CLAMAV_USE_DAEMON => t('Daemon mode'),
      CLAMAV_USE_EXECUTABLE => t('Executable'),
    ),
    '#default_value' => variable_get('clamav_mode', CLAMAV_DEFAULT_MODE),
    '#description' => t("Set the scan-method according to how the ClamAV software is configured on the server.<br /><strong>Daemon-mode is recommended</strong>, because it is usually quicker than running as an executable.  The Daemon will not require read-access to the file: it is streamed directly to the daemon by the web-server."),
  );
  $form['antivirus']['clamav_unchecked_files'] = array(
    '#type' => 'radios',
    '#title' => t('Action when ClamAV is not available'),
    //Allow file uploads if the daemon is not running or program is not found'),
    '#options' => array(
      CLAMAV_BLOCK_UNCHECKED => t('Block unchecked files'),
      CLAMAV_ALLOW_UNCHECKED => t('Allow unchecked files'),
    ),
    '#default_value' => variable_get('clamav_unchecked_files', CLAMAV_DEFAULT_UNCHECKED),
    '#description' => t('Scans may fail - for example: if ClamAV is not running, or the path to the executable is invalid.  Choose whether files should be blocked or allowed when a scan cannot be completed.'),
  );
  $form['antivirus']['clamav_verbose'] = array(
    '#type' => 'checkbox',
    '#title' => t('Verbose'),
    '#default_value' => variable_get('clamav_verbose', CLAMAV_VERBOSE_DEFAULT),
    '#description' => t('Log all scanned files, including files which pass the virus-check.'),
  );


  // ---
  // --- DAEMON MODE configuration
  // ---
  // Check for a daemon on the current settings.
  $daemon_config = array(
    'host' => variable_get('clamav_daemon_host', CLAMAV_DEFAULT_HOST),
    'port' => variable_get('clamav_daemon_port', CLAMAV_DEFAULT_PORT),
  );
  $clamav_daemon_version = clamav_get_version($daemon_config);

  $clamav_daemon_version = preg_match('/ClamAV/', $clamav_daemon_version) ? $clamav_daemon_version : NULL;
  $message = isset($clamav_daemon_version)
     ? t("The clamav-daemon at %host:%port gives the version:<br /><code>@version_string</code>", array('%host' => $daemon_config['host'], '%port' => $daemon_config['port'], '@version_string' => $clamav_daemon_version))
     : t('The clamav-daemon was not found at %host:%port.', array('%host' => $daemon_config['host'], '%port' => $daemon_config['port']));

  $form['daemon'] = array(
    '#type' => 'fieldset',
    '#title' => t('ClamAV daemon'),
    '#description' => t("Configure the connection settings when using Daemon-mode.") . '<br />' . $message,
    '#collapsible' => TRUE,
    // Uncollapse the fieldset if the current config is 'Daemon mode'.
    '#collapsed' => !(variable_get('clamav_mode', CLAMAV_DEFAULT_MODE) == CLAMAV_USE_DAEMON),
  );
  $form['daemon']['clamav_daemon_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Hostname'),
    '#default_value' => variable_get('clamav_daemon_host', CLAMAV_DEFAULT_HOST),
    '#maxlength' => 255,
    '#description' => t('The hostname for the Clam-AV daemon.  Defaults to localhost.'),
  );
  $form['daemon']['clamav_daemon_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Port'),
    '#default_value' => variable_get('clamav_daemon_port', CLAMAV_DEFAULT_PORT),
    '#size' => 6,
    '#maxlength' => 8,
    '#description' => t('The port for the Clam-AV daemon.  Defaults to port 3310.  Must be between 0 and 65535.'),
  );




  // ---
  // --- EXECUTABLE MODE configuration
  // ---
  // Check that the executable-path matches the default clamscan
  $msg = '';

  $executable = variable_get('clamav_executable_path', CLAMAV_DEFAULT_PATH);
  $version_string = clamav_get_version($executable);
  if ($version_string) {
    $msg .= t("The clamscan at %executable_filepath gives the version:<br /><code>@version_string</code>.", array('%executable_filepath' => $executable, '@version_string' => $version_string));
  }
  else {
    $msg .= t("The clamscan at %executable_filepath did not respond.", array('%executable_filepath' => $executable));
  }

  $default_executable_path = exec('which clamscan 2>/dev/null');
  if ($default_executable_path && $default_executable_path != variable_get('clamav_executable_path', CLAMAV_DEFAULT_PATH)) {
    $version_string = clamav_get_version($default_executable_path);
    if ($default_executable_version_string) {
      $msg .= "<br />";
      $msg .= t("The clamscan at %executable_filepath gives the version:<br />@version_string.", array('%executable_filepath' => $default_executable_path, '@version_string' => $version_string));
    }
  }

  $form['executable'] = array(
    '#type' => 'fieldset',
    '#title' => t('ClamAV executable'),
    '#description' => t('These settings will be used if you have chosen "Executable" as the scan-method.') . '<br />' . $msg,
    '#collapsible' => TRUE,
    // Uncollapse the fieldset if the current config is 'Executable mode'.
    '#collapsed' => !(variable_get('clamav_mode', CLAMAV_DEFAULT_MODE) == CLAMAV_USE_EXECUTABLE),
  );

  $form['executable']['clamav_executable_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Executable path'),
    '#default_value' => variable_get('clamav_executable_path', CLAMAV_DEFAULT_PATH),
    '#maxlength' => 255,
    '#description' => t("Full path to the 'clamscan' utility."),
  );





  $form['integration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Integration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['integration']['clamav_enable_element_file_widget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scan file field uploads'),
    '#default_value' => module_exists('file') && variable_get('clamav_enable_element_file_widget', TRUE),
    '#disabled' => !module_exists('file'),
  );
  $form['integration']['clamav_enable_element_image_widget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scan image field uploads'),
    '#default_value' => module_exists('image') && variable_get('clamav_enable_element_image_widget', TRUE),
    '#disabled' => !module_exists('image'),
  );


  return system_settings_form($form);
}
