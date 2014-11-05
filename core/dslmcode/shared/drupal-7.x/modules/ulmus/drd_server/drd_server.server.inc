<?php

/**
 * @file
 * Provides core related functionality triggered by DRD.
 */

/**
 * DRD Action to find out all domains on this Drupal installation.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_server_domains() {
  $sites = drd_server_read_sites();
  $output = array();
  $error = array();
  foreach ($sites as $url => $id) {
    if (isset($output[$id])) {
      $output[$id]['aliases'][] = $url;
    }
    elseif (isset($error[$id])) {
      // Ignore this alias, it won't work.
    }
    else {
      $uses_ssl = FALSE;
      $code = drd_server_server_check_host($url, $uses_ssl);
      if ($code === FALSE) {
        $error[$id] = TRUE;
      }
      else {
        $output[$id] = array(
          'url' => $url,
          'aliases' => array(),
          'drd installed' => ($code === TRUE),
          'uses ssl' => $uses_ssl,
        );
      }
    }
  }
  return drd_server_result('server.domains', $output);
}

/**
 * Function called by drd_server_server_domains() to check a specific URL
 * if it really exists and if the module drd_server is installed.
 *
 * @param string $url
 *   The url that should be checked.
 * @param bool $uses_ssl
 *   A variable reference to hold the information if the URL uses SSL.
 *
 * @return boolean
 *   TRUE if domain is reachable, FALSE otherwise.
 */
function drd_server_server_check_host($url, &$uses_ssl) {
  $info = array();
  $options = array(
    'headers' => array(
      'User-Agent' => 'Drupal Remote Dashboard',
      'Accept' => 'text/plain',
      'Accept-Encoding' => 'utf-8',
    ),
  );
  try {
    $id = rand();
    $info[] = 'ID: ' . $id;
    $check_url = 'http://' . $url;
    $check = drupal_http_request($check_url . '/?q=admin/drd_server/' . $id, $options);
    $ok = (($check->code == 200) && (trim($check->data) == _drd_server_get_check_token($check_url, $id)));
    $info[] = array(
      'url' => $check_url,
      'ok' => $ok ? 'yes' : 'no',
      'result' => $check,
    );
    if (!$ok) {
      // Maybe the url is running https only, so we try that as well.
      $check_url = 'https://' . $url;
      $check = drupal_http_request($check_url . '/?q=admin/drd_server/' . $id, $options);
      $ok = (($check->code == 200) || (in_array($check->code, array(301, 302, 307)) && $check->redirect_code == 200));
      $info[] = array(
        'url' => $check_url,
        'ok' => $ok ? 'yes' : 'no',
        'result' => $check,
      );
      if ($ok) {
        $uses_ssl = TRUE;
      }
    }
    if ($ok && trim($check->data) == _drd_server_get_check_token($check_url, $id)) {
      $info[] = 'Host OK!';
      $result = TRUE;
    }
    else {
      $info[] = 'Host result: ' . $check->code;
      $result = $check->code;
    }
  }
  catch (Exception $e) {
    $info[] = array(
      'Exception' => $e,
    );
    $result = FALSE;
  }
  _drd_server_watchdog('Checking host @name (@result): <pre>!info</pre>', array('@result' => (string) $result, '@name' => $url, '!info' => print_r($info, TRUE)));
  return $result;
}

/**
 * DRD Action to determine all available updates for the current core including all disabled modules.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_server_list_updates() {
  if (!module_exists('update')) {
    module_enable(array('update'));
  }
  $org_setting = variable_get('update_check_disabled', FALSE);
  variable_set('update_check_disabled', TRUE);
  variable_set('update_last_check', 0);
  $result = drd_server_domain_list_updates('server');
  variable_set('update_check_disabled', $org_setting);

  // Just return result as is, it has been processed already.
  return $result;
}

/**
 * DRD Action to retrieve the PHP error log from the OS.
 *
 * @param int $max_length
 *   Number of bytes that shold be retrieved from the end of the php error log.
 *
 * @return string
 *   Returnable string to DRD.
 */
function drd_server_server_php_error_log($max_length = 5000) {
  $log_file = ini_get('error_log');
  if (!file_exists($log_file)) {
    return drd_server_error(t('PHP Error Log does not exist.'), DRD_ERROR_NO_LOG_PHP);
  }
  $offset = max(-1, (filesize($log_file) - $max_length));
  $log = file_get_contents($log_file, FILE_BINARY, NULL, $offset);
  $result['cache']['php_error_log']['server'] = array(
    'title' => 'PHP Error Log',
    'callback' => 'drupal_render',
    'arguments' => array(
      'data' => array(
        '#markup' => $log,
        '#prefix' => '<pre>',
        '#suffix' => '</pre>',
      ),
    ),
  );
  return drd_server_result('server.php.error.log', $result);
}
