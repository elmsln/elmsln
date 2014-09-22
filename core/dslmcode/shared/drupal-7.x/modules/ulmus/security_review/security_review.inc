<?php

/**
 * @file
 * Stand-alone security checks and review system.
 */

// Define the version of this file in case it's used outside of its module.
define('SECURITY_REVIEW_VERSION', '7.x-1.1');

/**
 * Public function for running Security Review checklist and returning results.
 *
 * @param array $checklist Array of checks to run, indexed by module namespace.
 * @param boolean $log Whether to log check processing using security_review_log.
 * @param boolean $help Whether to load the help file and include in results.
 * @return array Results from running checklist, indexed by module namespace.
 */
function security_review_run($checklist = NULL, $log = FALSE, $help = FALSE) {
  if (!$checklist && module_exists('security_review')) {
    $checklist = module_invoke_all('security_checks');
  }
  $results = _security_review_run($checklist, $log);

  // Fill out the descriptions of the results if $help is requested.
  if ($help && module_exists('security_review') && module_load_include('inc', 'security_review', 'security_review.help')) {
    foreach ($results as $module => $checks) {
      foreach ($checks as $check_name => $check) {
        $function = $check['callback'] . '_help';
        // We should have loaded all necessary include files.
        if (function_exists($function)) {
          $element = call_user_func($function, $check);
          // @todo run through theme?
          $results[$module][$check_name]['help'] = $element;
        }
      }
    }
  }

  return $results;
}

/**
 * Private function the review and returns the full results.
 */
function _security_review_run($checklist, $log = FALSE) {
  $results = array();
  foreach ($checklist as $module => $checks) {
    foreach ($checks as $check_name => $arguments) {
      $check_result = _security_review_run_check($module, $check_name, $arguments, $log);
      if (!empty($check_result)) {
        $results[$module][$check_name] = $check_result;
      }
    }
  }
  return $results;
}

/**
 * Run a single Security Review check.
 */
function _security_review_run_check($module, $check_name, $check, $log, $store = FALSE) {
  $last_check = array();
  if ($store) {
    // Get the results of the last check.
    $last_check = security_review_get_last_check($module, $check_name);
  }
  $check_result = array();
  $return = array('result' => NULL);
  if (isset($check['file'])) {
    // Handle Security Review defining checks for other modules.
    if (isset($check['module'])) {
      $module = $check['module'];
    }
    module_load_include('inc', $module, $check['file']);
  }
  $function = $check['callback'];
  if (function_exists($function)) {
    $return = call_user_func($function, $last_check);
  }
  $check_result = array_merge($check, $return);
  $check_result['lastrun'] = REQUEST_TIME;

  if ($log && !is_null($return['result'])) { // Do not log if result is NULL.
    $variables = array('!name' => $check_result['title']);
    if ($check_result['result']) {
      _security_review_log($module, $check_name, '!name check passed', $variables, WATCHDOG_INFO);
    }
    else {
      _security_review_log($module, $check_name, '!name check failed', $variables, WATCHDOG_ERROR);
    }
  }
  return $check_result;
}

/**
 * Core Security Review's checks.
 *
 * @see security_review_get_checklist().
 */
function _security_review_security_checks() {
  $checks = array();
  $checks['file_perms'] = array(
    'title' => t('File system permissions'),
    'callback' => 'security_review_check_file_perms',
    'success' => t('Drupal installation files and directories (except required) are not writable by the server.'),
    'failure' => t('Some files and directories in your install are writable by the server.'),
  );
  $checks['input_formats'] = array(
    'title' => t('Text formats'),
    'callback' => 'security_review_check_input_formats',
    'success' => t('Untrusted users are not allowed to input dangerous HTML tags.'),
    'failure' => t('Untrusted users are allowed to input dangerous HTML tags.'),
  );
  $checks['field'] = array(
    'title' => t('Content'),
    'callback' => 'security_review_check_field',
    'success' => t('Dangerous tags were not found in any submitted content (fields).'),
    'failure' => t('Dangerous tags were found in submitted content (fields).'),
  );
  $checks['error_reporting'] = array(
    'title' => t('Error reporting'),
    'callback' => 'security_review_check_error_reporting',
    'success' => t('Error reporting set to log only.'),
    'failure' => t('Errors are written to the screen.'),
  );
  $checks['private_files'] = array(
    'title' => t('Private files'),
    'callback' => 'security_review_check_private_files',
    'success' => t('Private files directory is outside the web server root.'),
    'failure' => t('Private files is enabled but the specified directory is not secure outside the web server root.'),
  );
  // Checks dependent on dblog.
  if (module_exists('dblog')) {
    $checks['query_errors'] = array(
      'title' => t('Database errors'),
      'callback' => 'security_review_check_query_errors',
      'success' => t('Few query errors from the same IP.'),
      'failure' => t('Query errors from the same IP. These may be a SQL injection attack or an attempt at information disclosure.'),
    );

    $checks['failed_logins'] = array(
      'title' => t('Failed logins'),
      'callback' => 'security_review_check_failed_logins',
      'success' => t('Few failed login attempts from the same IP.'),
      'failure' => t('Failed login attempts from the same IP. These may be a brute-force attack to gain access to your site.'),
    );
  }
  $checks['upload_extensions'] = array(
    'title' => t('Allowed upload extensions'),
    'callback' => 'security_review_check_upload_extensions',
    'success' => t('Only safe extensions are allowed for uploaded files and images.'),
    'failure' => t('Unsafe file extensions are allowed in uploads.'),
  );
  $checks['admin_permissions'] = array(
    'title' => t('Drupal permissions'),
    'callback' => 'security_review_check_admin_permissions',
    'success' => t('Untrusted roles do not have administrative or trusted Drupal permissions.'),
    'failure' => t('Untrusted roles have been granted administrative or trusted Drupal permissions.'),
  );
  /*$checks['name_passwords'] = array(
    'title' => t('Username as password'),
    'callback' => 'security_review_check_name_passwords',
    'success' => t('Trusted accounts do not have their password set to their username.'),
    'failure' => t('Some trusted accounts have set their password the same as their username.'),
  );*/
  // Check dependent on PHP filter being enabled.
  if (module_exists('php')) {
    $checks['untrusted_php'] = array(
      'title' => t('PHP access'),
      'callback' => 'security_review_check_php_filter',
      'success' => t('Untrusted users do not have access to use the PHP input format.'),
      'failure' => t('Untrusted users have access to use the PHP input format.'),
    );
  }
  $checks['executable_php'] = array(
    'title' => t('Executable PHP'),
    'callback' => 'security_review_check_executable_php',
    'success' => t('PHP files in the Drupal files directory cannot be executed.'),
    'failure' => t('PHP files in the Drupal files directory can be executed.'),
  );
  $checks['base_url_set'] = array(
    'title' => t('Drupal base URL'),
    'callback' => 'security_review_check_base_url',
    'success' => t('Base URL is set in settings.php.'),
    'failure' => t('Base URL is not set in settings.php.'),
  );
  $checks['temporary_files'] = array(
    'title' => t('Temporary files'),
    'callback' => 'security_review_check_temporary_files',
    'success' => t('No sensitive temporary files were found.'),
    'failure' => t('Sensitive temporary files were found on your files system.'),
  );

  return array('security_review' => $checks);
}

/**
 * Checks for security_review_get_checklist() when Views is enabled.
 */
function views_security_checks() {
  $checks = array();
  $checks['access'] = array(
    'title' => t('Views access'),
    'callback' => 'security_review_check_views_access',
    'success' => t('Views are access controlled.'),
    'failure' => t('There are Views that do not provide any access checks.'),
    'module' => 'security_review',
    // Specify this file because the callback is here.
    'file' => 'security_review',
  );
  return array('views' => $checks);
}

/**
 * Check that files aren't writeable by the server.
 */
function security_review_check_file_perms() {
  $result = TRUE;
  // Extract ending folder for file directory path.
  $file_path = './' . rtrim(variable_get('file_public_path', conf_path() . '/files'), '/');
  // Set files to ignore.
  $ignore = array('..', 'CVS', '.git', '.svn', '.bzr', realpath($file_path));
  // Add temporary files directory if it's set.
  $temp_path = variable_get('file_temporary_path', '');
  if (!empty($temp_path)) {
    $ignore[] = realpath('./' . rtrim($temp_path, '/'));
  }
  // Add private files directory if it's set.
  $private_files = variable_get('file_private_path', '');
  if (!empty($private_files)) {
    // Remove leading slash if set.
    if (strrpos($private_files, '/') !== FALSE) {
      $private_files = substr($private_files, strrpos($private_files, '/') + 1);
    }
    $ignore[] = $private_files;
  }
  drupal_alter('security_review_file_ignore', $ignore);
  $parsed = array(realpath('.'));
  $files = _security_review_check_file_perms_scan('.', $parsed, $ignore);

  // Try creating or appending files.
  // Assume it doesn't work.
  $create_status = $append_status = FALSE;

  $append_message = t("Your web server should not be able to write to your modules directory. This is a security vulnerable. Consult the Security Review file permissions check help for mitigation steps.");

  $directory = drupal_get_path('module', 'security_review');
  // Write a file with the timestamp
  $file = './' . $directory . '/file_write_test.' . date('Ymdhis');
  if ($file_create = @fopen($file, 'w')) {
    $create_status = fwrite($file_create, date('Ymdhis') . ' - ' . $append_message . "\n");
    fclose($file_create);
  }
  // Try to append to our IGNOREME file.
  $file = './'. $directory . '/IGNOREME.txt';
  if ($file_append = @fopen($file, 'a')) {
    $append_status = fwrite($file_append, date('Ymdhis') . ' - ' . $append_message . "\n");
    fclose($file_append);
  }

  if (count($files) || $create_status || $append_status) {
    $result = FALSE;
  }
  return array('result' => $result, 'value' => $files);
}

function _security_review_check_file_perms_scan($directory, &$parsed, $ignore) {
  $items = array();
  if ($handle = opendir($directory)) {
    while (($file = readdir($handle)) !== FALSE) {
      // Don't check hidden files or ones we said to ignore.
      $path = $directory . "/" . $file;
      if ($file[0] != "." && !in_array($file, $ignore) && !in_array(realpath($path), $ignore)) {
        if (is_dir($path) && !in_array(realpath($path), $parsed)) {
          $parsed[] = realpath($path);
          $items = array_merge($items, _security_review_check_file_perms_scan($path, $parsed, $ignore));
          if (is_writable($path)) {
            $items[] = preg_replace("/\/\//si", "/", $path);
          }
        }
        elseif (is_writable($path)) {
          $items[] = preg_replace("/\/\//si", "/", $path);
        }
      }

    }
    closedir($handle);
  }
  return $items;
}

/**
 * Check for formats that either do not have HTML filter that can be used by
 * untrusted users, or if they do check if unsafe tags are allowed.
 */
function security_review_check_input_formats() {
  $result = TRUE;
  $formats = filter_formats();
  $check_result_value = array();
  // Check formats that are accessible by untrusted users.
  $untrusted_roles = security_review_untrusted_roles();
  $untrusted_roles = array_keys($untrusted_roles);
  foreach ($formats as $id => $format) {
    $format_roles = filter_get_roles_by_format($format);
    $intersect = array_intersect(array_keys($format_roles), $untrusted_roles);
    if (!empty($intersect)) {
      // Untrusted users can use this format.
      $filters = filter_list_format($format->format);
      // Check format for enabled HTML filter.
      if (in_array('filter_html', array_keys($filters)) && $filters['filter_html']->status) {
        $filter = $filters['filter_html'];
        // Check for unsafe tags in allowed tags.
        $allowed_tags = $filter->settings['allowed_html'];
        $unsafe_tags = security_review_unsafe_tags();
        drupal_alter('security_review_unsafe_tags', $unsafe_tags);
        foreach ($unsafe_tags as $tag) {
          if (strpos($allowed_tags, '<' . $tag . '>') !== FALSE) {
            // Found an unsafe tag
            $check_result_value['tags'][$id] = $tag;
          }
        }
      }
      elseif (!in_array('filter_html_escape', array_keys($filters)) || !$filters['filter_html_escape']->status) {
        // Format is usable by untrusted users but does not contain the HTML Filter or the HTML escape.
        $check_result_value['formats'][$id] = $format;
      }
    }
  }

  if (!empty($check_result_value)) {
    $result = FALSE;
  }
  return array('result' => $result, 'value' => $check_result_value);
}

function security_review_check_php_filter() {
  $result = TRUE;
  $formats = filter_formats();
  $check_result_value = array();
  // Check formats that are accessible by untrusted users.
  $untrusted_roles = security_review_untrusted_roles();
  $untrusted_roles = array_keys($untrusted_roles);
  foreach ($formats as $id => $format) {
    $format_roles = filter_get_roles_by_format($format);
    $intersect = array_intersect(array_keys($format_roles), $untrusted_roles);
    if (!empty($intersect)) {
      // Untrusted users can use this format.
      $filters = filter_list_format($format->format);
      // Check format for enabled PHP filter.
      if (in_array('php_code', array_keys($filters)) && $filters['php_code']->status) {
        $result = FALSE;
        $check_result_value['formats'][$id] = $format;
      }
    }
  }

  return array('result' => $result, 'value' => $check_result_value);
}

function security_review_check_error_reporting() {
  $error_level = variable_get('error_level', NULL);
  if (is_null($error_level) || intval($error_level) >= 1) {
    // When the variable isn't set, or its set to 1 or 2 errors are printed to the screen.
    $result = FALSE;
  }
  else {
    $result = TRUE;
  }
  return array('result' => $result, 'value' => $error_level);
}

/**
 * If private files is enabled check that the directory is not under the web root.
 *
 * There is ample room for the user to get around this check. @TODO get more sophisticated?
 */
function security_review_check_private_files() {
  $file_directory_path = variable_get('file_private_path', '');
  if (empty($file_directory_path)) {
    $result = NULL; // Ignore this check.
  }
  elseif (strpos(realpath($file_directory_path), DRUPAL_ROOT) === 0) {
    // Path begins at root.
    $result = FALSE;
  }
  else {
    $result = TRUE;
  }
  return array('result' => $result, 'value' => $file_directory_path);
}

function security_review_check_query_errors($last_check = NULL) {
  $timestamp = NULL;
  $check_result_value = array();
  $query = db_select('watchdog', 'w')->fields('w', array('message', 'hostname'))
    ->condition('type', 'php')
    ->condition('severity', WATCHDOG_ERROR);
  if (isset($last_check['lastrun'])) {
    $query->condition('timestamp', $last_check['lastrun'], '>=');
  }
  $result = $query->execute();
  foreach ($result as $row) {
    if (strpos($row->message, 'SELECT') !== FALSE) {
      $entries[$row->hostname][] = $row;
    }
  }
  $result = TRUE;
  if (!empty($entries)) {
    foreach ($entries as $ip => $records) {
      if (count($records) > 10) {
        $check_result_value[] = $ip;
      }
    }
  }
  if (!empty($check_result_value)) {
    $result = FALSE;
  }
  else {
    // Rather than worrying the user about the idea of query errors we skip reporting a pass.
    $result = NULL;
  }
  return array('result' => $result, 'value' => $check_result_value);
}

function security_review_check_failed_logins($last_check = NULL) {
  $result = TRUE;
  $timestamp = NULL;
  $check_result_value = array();
  $query = db_select('watchdog', 'w')->fields('w', array('message', 'hostname'))
    ->condition('type', 'php')
    ->condition('severity', WATCHDOG_NOTICE);
  if (isset($last_check['lastrun'])) {
    $query->condition('timestamp', $last_check['lastrun'], '>=');
  }
  $result = $query->execute();
  foreach ($result as $row) {
    if (strpos($row->message, 'Login attempt failed') !== FALSE) {
      $entries[$row->hostname][] = $row;
    }
  }
  if (!empty($entries)) {
    foreach ($entries as $ip => $records) {
      if (count($records) > 10) {
        $check_result_value[] = $ip;
      }
    }
  }
  if (!empty($check_result_value)) {
    $result = FALSE;
  }
  else {
    // Rather than worrying the user about the idea of failed logins we skip reporting a pass.
    $result = NULL;
  }
  return array('result' => $result, 'value' => $check_result_value);
}

/**
 * Look for admin permissions granted to untrusted roles.
 */
function security_review_check_admin_permissions() {
  $result = TRUE;
  $check_result_value = array();
  $untrusted_roles = security_review_untrusted_roles();
  // Collect permissions marked as for trusted users only.
  $all_permissions = module_invoke_all('permission');
  $all_keys = array_keys($all_permissions);
  // Get permissions for untrusted roles.
  $untrusted_permissions = user_role_permissions($untrusted_roles);
  foreach ($untrusted_permissions as $rid => $permissions) {
    $intersect = array_intersect($all_keys, array_keys($permissions));
    foreach ($intersect as $permission) {
      if (isset($all_permissions[$permission]['restrict access'])) {
        $check_result_value[$rid][] = $permission;
      }
    }
  }

  if (!empty($check_result_value)) {
    $result = FALSE;
  }
  return array('result' => $result, 'value' => $check_result_value);
}

function security_review_check_field($last_check = NULL) {
  $check_result = TRUE;
  $check_result_value = $tables = $found = array();
  $timestamp = NULL;
  $instances = field_info_instances();
  // Loop through instances checking for fields of type text.
  foreach ($instances as $entity_type => $type_bundles) {
    foreach ($type_bundles as $bundle => $bundle_instances) {
      foreach ($bundle_instances as $field_name => $instance) {
        $field = field_info_field($field_name);
        // Check into text fields that are stored in SQL.
        if ($field['module'] == 'text' && $field['storage']['module'] == 'field_sql_storage') {
          // Build array of tables and columns to search.
          $current_table = key($field['storage']['details']['sql'][FIELD_LOAD_CURRENT]);
          $revision_table = key($field['storage']['details']['sql'][FIELD_LOAD_REVISION]);
          if (!array_key_exists($current_table, $tables)) {
            $tables[$current_table] = array(
              'column' => $field['storage']['details']['sql'][FIELD_LOAD_CURRENT][$current_table]['value'],
              'name' => $field['field_name'],
            );
          }
          if (!array_key_exists($revision_table, $tables)) {
            $tables[$revision_table] = array(
              'column' => $field['storage']['details']['sql'][FIELD_LOAD_REVISION][$revision_table]['value'],
              'name' => $field['field_name'],
            );
          }
        }
      }
    }
  }
  if (empty($tables)) {
    return array('result' => $check_result, 'value' => $check_result_value);
  }
  // Search for PHP or Javascript tags in text columns.
  foreach ($tables as $table => $info) {
    $sql = "SELECT DISTINCT entity_id, entity_type FROM {" . $table . "} WHERE " . $info['column'] . " LIKE :text";
    // Handle changed? @todo
    foreach (array('Javascript' => '%<script%', 'PHP' => '%<?php%') as $vuln_type => $comparison) {
      $results = db_query($sql, array(':text' => $comparison)); // @pager query?
      foreach ($results as $result) {
        $check_result = FALSE;
        if (!isset($check_result_value[$result->entity_type]) || !array_key_exists($result->entity_id, $check_result_value[$result->entity_type])) {
          $check_result_value[$result->entity_type][$result->entity_id] = array(
            'type' => $vuln_type,
            'field' => $info['name'],
          );
        }
      }
    }
  }

  return array('result' => $check_result, 'value' => $check_result_value);
}

function security_review_check_upload_extensions($last_check = NULL) {
  $check_result = TRUE;
  $check_result_value = array();
  $instances = field_info_instances();
  $unsafe_extensions = security_review_unsafe_extensions();
  // Loop through instances checking for fields of file.
  foreach ($instances as $entity_type => $type_bundles) {
    foreach ($type_bundles as $bundle => $bundle_instances) {
      foreach ($bundle_instances as $field_name => $instance) {
        $field = field_info_field($field_name);
        if ($field['module'] == 'image' || $field['module'] == 'file') {
          // Check instance file_extensions.
          foreach ($unsafe_extensions as $unsafe_extension) {
            if (strpos($instance['settings']['file_extensions'], $unsafe_extension) !== FALSE) {
              // Found an unsafe extension.
              $check_result_value[$instance['field_name']][$instance['bundle']] = $unsafe_extension;
              $check_result = FALSE;
            }
          }
        }
      }
    }
  }

  return array('result' => $check_result, 'value' => $check_result_value);
}

function security_review_check_name_passwords($last_check = NULL) {
  $result = TRUE;
  $check_result_value = array();
  $timestamp = NULL;

  // Check whether trusted roles have weak passwords.
  $trusted_roles = security_review_trusted_roles();
  if (!empty($trusted_roles)) {
    $trusted_roles = array_keys($trusted_roles);
    $check_result_value = _security_review_weak_passwords($trusted_roles);
  }
  if (!empty($check_result_value)) {
    $result = FALSE;
  }

  return array('result' => $result, 'value' => $check_result_value);
}

function _security_review_weak_passwords($trusted_roles) {
  $weak_users = array();

  // Select users with a trusted role whose password is their username.
  // @todo need to generate passwords in PHP to get salt.
  $sql = "SELECT u.uid, u.name, COUNT(rid) AS count FROM {users} u LEFT JOIN
    {users_roles} ur ON u.uid = ur.uid AND ur.rid in (:rids)
    WHERE pass = md5(name) GROUP BY uid";
  $results = db_query($sql, array(':rids' => $trusted_roles)); // @todo pager_query?
  foreach ($results as $row) {
    $record[] = $row;
    if ($row->count > 0) {
      $weak_users[$row->uid] = $row->name;
    }
  }

  // Explicitly check uid 1 in case they have no roles.
  $weak_uid1 = db_fetch_object(db_query("SELECT u.uid, u.name, 1 AS count FROM {users} u WHERE pass = md5(name) AND uid = 1"));
  if (!empty($weak_uid1->count)) {
    $weak_users[$weak_uid1->uid] = $weak_uid1->name;
  }

  return $weak_users;
}

/**
 * Check if PHP files written to the files directory can be executed.
 */
function security_review_check_executable_php($last_check = NULL) {
  global $base_url;
  $result = TRUE;
  $check_result_value = array();

  $message = 'Security review test ' . date('Ymdhis');
  $content = "<?php\necho '" . $message . "';";
  $directory = variable_get('file_public_path', 'sites/default/files');
  $file = '/security_review_test.php';
  if ($file_create = @fopen('./' . $directory . $file, 'w')) {
    $create_status = fwrite($file_create, $content);
    fclose($file_create);
  }
  $response = drupal_http_request($base_url . '/' . $directory . $file);
  if ($response->code == 200 && $response->data === $message) {
    $result = FALSE;
    $check_result_value[] = 'executable_php';
  }
  if (file_exists('./' . $directory . $file)) {
    @unlink('./' . $directory . $file);
  }
  // Check for presence of the .htaccess file and if the contents are correct.
  if (!file_exists($directory . '/.htaccess')) {
    $result = FALSE;
    $check_result_value[] = 'missing_htaccess';
  }
  elseif (!function_exists('file_htaccess_lines')) {
    $result = FALSE;
    $check_result_value[] = 'outdated_core';
  }
  else {
    $contents = file_get_contents($directory . '/.htaccess');
    // Text from includes/file.inc.
    $expected = file_htaccess_lines(FALSE);
    if (trim($contents) !== trim($expected)) {
      $result = FALSE;
      $check_result_value[] = 'incorrect_htaccess';
    }
    if (is_writable($directory . '/.htaccess')) {
      // Don't modify $result.
      $check_result_value[] = 'writable_htaccess';
    }
  }

  return array('result' => $result, 'value' => $check_result_value);
}

/**
 * Check if $base_url is set in settings.php.
 */
function security_review_check_base_url($last_check = NULL) {
  // Support different methods to check for $base_url.
  $method = variable_get('security_review_base_url_method', 'token');
  $result = NULL;
  if ($method === 'token') {
    if (file_exists(DRUPAL_ROOT . '/' . conf_path() . '/settings.php')) {
      $content = file_get_contents(DRUPAL_ROOT . '/' . conf_path() . '/settings.php');
      $tokens = token_get_all($content);
    }
    $result = FALSE;
    foreach ($tokens as $token) {
      if (is_array($token) && $token[0] === T_VARIABLE && $token[1] == '$base_url') {
        $result = TRUE;
        break;
      }
    }
  }
  elseif ($method === 'include') {
    if (file_exists(DRUPAL_ROOT . '/' . conf_path() . '/settings.php')) {
      include DRUPAL_ROOT . '/' . conf_path() . '/settings.php';
    }
    if (isset($base_url)) {
      $result = TRUE;
    }
    else {
      $result = FALSE;
    }
  }
  return array('result' => $result, 'value' => '');
}

/**
 * Check for sensitive temporary files like settings.php~.
 */
function security_review_check_temporary_files($last_check = NULL) {
  $result = TRUE;
  $check_result_value = array();
  $files = array();
  $dir = scandir(DRUPAL_ROOT . '/' . conf_path() . '/');
  foreach ($dir as $file) {
    // Set full path to only files.
    if (!is_dir($file)) {
      $files[] = DRUPAL_ROOT . '/' . conf_path() . '/' . $file;
    }
  }
  drupal_alter('security_review_temporary_files', $files);
  foreach ($files as $path) {
    $matches = array();
    if (file_exists($path) && preg_match('/.*(~|\.sw[op]|\.bak|\.orig|\.save)$/', $path, $matches) !== FALSE && !empty($matches)) {
      $result = FALSE;
      $check_result_value[] = $path;
    }
  }
  return array('result' => $result, 'value' => $check_result_value);
}

/**
 * Get core Security Review checks and checks from any hook_security_checks().
 *
 * @return array
 *   Array of checks indexed by module name. e.g.:
 *   'security_review' => array(
 *     'check_name' => array(...)
 *   )
 */
function security_review_get_checklist() {
  $checks = _security_review_security_checks();
  $checks = array_merge($checks, module_invoke_all('security_checks'));
  return $checks;
}

function security_review_check_views_access($last_check = NULL) {
  $result = TRUE;
  $check_result_value = array();
  $timestamp = NULL;
  // Load and loop through every view, checking the access type in displays.
  $views = views_get_all_views();
  foreach ($views as $view) {
    if ($view->disabled !== TRUE) {
      // Access is set in display options of a display.
      foreach ($view->display as $display_name => $display) {
        if (isset($display->display_options['access']) && $display->display_options['access']['type'] == 'none') {
          $check_result_value[$view->name][] = $display_name;
        }
      }
    }
  }
  if (!empty($check_result_value)) {
    $result = FALSE;
  }
  return array('result' => $result, 'value' => $check_result_value);
}

/**
 * Helper function defines HTML tags that are considered unsafe.
 *
 * Based on wysiwyg_filter_get_elements_blacklist(),
 * https://www.owasp.org/index.php/XSS_Filter_Evasion_Cheat_Sheet, and
 * html5sec.org.
 */
function security_review_unsafe_tags() {
  return array(
    'applet',
    'area',
    'audio',
    'base',
    'basefont',
    'body',
    'button',
    'comment',
    'embed',
    'eval',
    'form',
    'frame',
    'frameset',
    'head',
    'html',
    'iframe',
    'image',
    'img',
    'input',
    'isindex',
    'label',
    'link',
    'map',
    'math',
    'meta',
    'noframes',
    'noscript',
    'object',
    'optgroup',
    'option',
    'param',
    'script',
    'select',
    'style',
    'svg',
    'table',
    'td',
    'textarea',
    'title',
    'video',
    'vmlframe',
  );
}

/**
 * Helper function defines file extensions considered unsafe.
 */
function security_review_unsafe_extensions() {
  return array(
    'swf',
    'exe',
    'html',
    'htm',
    'php',
    'phtml',
    'py',
    'js',
    'vb',
    'vbe',
    'vbs',
  );
}

/**
 * Helper function defines the default untrusted Drupal roles.
 */
function _security_review_default_untrusted_roles() {
  $roles = array(DRUPAL_ANONYMOUS_RID => t('anonymous user'));
  $user_register = variable_get('user_register', 1);
  // If visitors are allowed to create accounts they are considered untrusted.
  if ($user_register != USER_REGISTER_ADMINISTRATORS_ONLY) {
    $roles[DRUPAL_AUTHENTICATED_RID] = t('authenticated user');
  }
  return $roles;
}

/**
 * Helper function for user-defined or default unstrusted Drupal roles.
 *
 * @return An associative array with the role id as the key and the role name as value.
 */
function security_review_untrusted_roles() {
  $defaults = _security_review_default_untrusted_roles();
  $roles = variable_get('security_review_untrusted_roles', $defaults);
  // array_filter() to remove roles with 0 (meaning they are trusted) @todo
  return array_filter($roles);
}

/**
 * Helper function collects the permissions untrusted roles have.
 */
function security_review_untrusted_permissions() {
  static $permissions;
  if (empty($permissions)) {
    $permissions = array();
    // Collect list of untrusted roles' permissions.
    $untrusted_roles = security_review_untrusted_roles();
    foreach ($untrusted_roles as $rid) {
      $perms = array();
      $results = db_query('SELECT r.rid, p.permission FROM {role} r LEFT JOIN {role_permission} p ON r.rid = p.rid WHERE r.rid = :rid', array(':rid' => $rid))
        ->fetchArray();
      if ($results !== FALSE) {
        $perms = explode(',', str_replace(', ', ',', $results['permission']));
        $permissions[$rid] = $perms;
      }
    }
  }
  return $permissions;
}

/**
 * Helper function for assumed trusted roles.
 */
function security_review_trusted_roles() {
  $trusted_roles = array();
  $untrusted_roles = security_review_untrusted_roles();
  $results = db_query('SELECT rid, name FROM {role} WHERE rid NOT IN (:rids)', array(':rids' => $untrusted_roles));
  foreach ($results as $role) {
    $trusted_roles[$role->rid] = $role->name;
  }
  return array_filter($trusted_roles);
}

/**
 * Check if role has been granted a permission.
 */
function security_review_role_permission($rid, $permission) {
  $return = FALSE;
  $result = db_select('role_permission', 'p')->fields('p', array('permission'))->condition('rid', $rid)->execute()->fetchField();
  if ($result['permission'] && strpos($result['permission'], $permission) !== FALSE) {
    $return = TRUE;
  }
  return $return;
}

function _security_review_log($module, $check_name, $message, $variables, $type) {
  module_invoke_all('security_review_log', $module, $check_name, $message, $variables, $type);
}
