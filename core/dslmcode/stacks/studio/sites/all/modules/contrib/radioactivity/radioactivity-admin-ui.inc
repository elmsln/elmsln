<?php

function radioactivity_admin_general_form() {

  module_load_include("inc", "radioactivity", "radioactivity-bootstrap");

  _radioactivity_check_warnings();

  $vars = array(
    "@file" => _radioactivity_get_config_file_path(),
  );

  $form = array();

  $form['security'] = array(
    '#type' => 'fieldset',
    '#title' => t('Security'),
    '#collapsible' => TRUE,
    '#description' => t('Radioactivity security features prevent manipulation of popularity by 3rd parties.'),
  );

  $form['security']['radioactivity_checksum_salt'] = array(
    '#type' => 'textfield',
    '#title' => t('Salt for checksums'),
    '#description' => t(
      'A string used to salt the data on eg. ajax callback. This should be as random and as long as possible.'
    ),
    '#size' => 128,
    '#required' => TRUE,
    '#default_value' => variable_get('radioactivity_checksum_salt', 'undefined'),
  );

  $form['security']['radioactivity_flood_protection'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable flood protection'),
    '#description' => t(
      'This prevents users from boosting entities by refreshing the page multiple times or by ' .
      'calling the callback function directly. With flood protection enabled Radioactivity ' .
      'metrics are also more accurate but consume more resources.'
    ),
    '#default_value' => variable_get('radioactivity_flood_protection', FALSE),
  );

  $form['security']['radioactivity_flood_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Flood protection timeout'),
    '#description' => t(
      'How many minutes are required to pass between calls to emit energy for a single field. ' .
      'One incident per field per given amount of minutes.'
    ),
    '#size' => 5,
    '#default_value' => variable_get('radioactivity_flood_timeout', 15),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Advanced'),
    '#description' => t('Advanced'),
  );

  $root = variable_get('radioactivity_drupal_root', $_SERVER['DOCUMENT_ROOT']);

  $form['advanced']['radioactivity_drupal_root'] = array(
    '#type' => 'textfield',
    '#title' => t('Drupal root'),
    '#description' => t('Drupal installation path. This is required by Drupal bootstrap dependant incident storages. You should only need to change this if the field emitters fail and you know that this automatically detected path is incorrect.'),
    '#size' => 128,
    '#required' => TRUE,
    '#default_value' => $root,
  );

  $temp_dir = variable_get('radioactivity_temp_dir', sys_get_temp_dir());

  $form['advanced']['radioactivity_temp_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Radioactivity temporary dir'),
    '#description' => t('Temporary directory used by the file incident storage. If no directory is specified, value defaults to system temporary directory.'),
    '#size' => 128,
    '#required' => TRUE,
    '#default_value' => $temp_dir,
  );

  $settings = "";

  $form['memcache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Memcached settings'),
    '#collapsible' => TRUE,
    '#description' => t('Settings for the Memcache incident storage'),
  );

  $form['redis'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redis settings'),
    '#collapsible' => TRUE,
    '#description' => t('Settings for the Redis incident storage'),
  );

  if (class_exists("Memcache") || class_exists("Memcached")) {
    $form['memcache'] = array(
      '#type' => 'fieldset',
      '#title' => t('Memcached settings'),
      '#collapsible' => TRUE,
      '#description' => t('Settings for the Memcache incident storage'),
    );

    $host = variable_get('radioactivity_memcached_host', 'localhost');
    $port = variable_get('radioactivity_memcached_port', '11211');

    $form['memcache']['radioactivity_memcached_host'] = array(
      '#type' => 'textfield',
      '#title' => t('Host name'),
      '#description' => t('Usually localhost'),
      '#size' => 128,
      '#required' => TRUE,
      '#default_value' => $host,
    );

    $form['memcache']['radioactivity_memcached_port'] = array(
      '#type' => 'textfield',
      '#title' => t('Port'),
      '#description' => t('Default is 11211'),
      '#size' => 128,
      '#required' => TRUE,
      '#default_value' => $port,
    );

    $settings .= "define('VAR_RADIOACTIVITY_MEMCACHED_HOST', '$host');" . PHP_EOL;
    $settings .= "define('VAR_RADIOACTIVITY_MEMCACHED_PORT', '$port');" . PHP_EOL;
  }
  else {
    $form['memcache']['#description'] = t('PHP memcache(d) extension is not enabled! Memcached storage type is not available.');
  }

  if (class_exists("Redis")) {
    $form['redis'] = array(
      '#type' => 'fieldset',
      '#title' => t('Redis settings'),
      '#collapsible' => TRUE,
      '#description' => t('Settings for the Redis incident storage'),
    );

    $host = variable_get('radioactivity_redis_host', 'localhost');
    $port = variable_get('radioactivity_redis_port', '6379');

    $form['redis']['radioactivity_redis_host'] = array(
      '#type' => 'textfield',
      '#title' => t('Host name'),
      '#description' => t('Usually localhost or path to socket'),
      '#size' => 128,
      '#required' => TRUE,
      '#default_value' => $host,
    );

    $form['redis']['radioactivity_redis_port'] = array(
      '#type' => 'textfield',
      '#title' => t('Port'),
      '#description' => t('Default is 6379 (leave empty if using sockets)'),
      '#size' => 128,
      '#required' => FALSE,
      '#default_value' => $port,
    );

    $settings .= "define('VAR_RADIOACTIVITY_REDIS_HOST', '$host');" . PHP_EOL;
    $settings .= "define('VAR_RADIOACTIVITY_REDIS_PORT', '$port');" . PHP_EOL;
  }
  else {
    $form['redis']['#description'] = t('PhpRedis extension is not enabled! See https://github.com/nicolasff/phpredis for further information on enabling it.');
  }

  $salt = variable_get('radioactivity_checksum_salt', 'undefined');

  $form['security']['radioactivity_checksum_salt'] = array(
    '#type' => 'textfield',
    '#title' => t('Salt for checksums'),
    '#description' => t(
      'A string used to salt the data on eg. ajax callback. This should be as random and as long as possible.'
    ),
    '#size' => 128,
    '#required' => TRUE,
    '#default_value' => $salt,
  );

  $form['assist'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Configuration assist'),
  );

  // Set up the configuration preset with the form values
  $cfg = <<<EOCFG
<?php
define('VAR_RADIOACTIVITY_CHECKSUM_SALT', '$salt');
define('VAR_RADIOACTIVITY_DRUPAL_ROOT', '$root');
define('VAR_RADIOACTIVITY_TEMP_DIR', '$temp_dir');
$settings
EOCFG;

  $form['assist']['config'] = array(
    '#type' => 'textarea',
    '#title' => t('Configuration assist'),
    '#description' => t(
      'Copy the contents of this box to @file. Remember that on production servers this file should be made read only.',
      $vars
    ),
    '#size' => 5,
    '#default_value' => $cfg,
  );

  $form['assist']['auto'] = array(
    '#type' => 'checkbox',
    '#title' => t('Try to create the file automatically'),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Radioactivity settings form submit handler
 */
function radioactivity_admin_general_form_submit($form_id, $form_state) {

  variable_set('radioactivity_checksum_salt', $form_state['values']['radioactivity_checksum_salt']);

  variable_set('radioactivity_flood_protection', $form_state['values']['radioactivity_flood_protection']);
  variable_set('radioactivity_flood_timeout', $form_state['values']['radioactivity_flood_timeout']);

  variable_set('radioactivity_drupal_root', $form_state['values']['radioactivity_drupal_root']);
  variable_set('radioactivity_temp_dir', $form_state['values']['radioactivity_temp_dir']);

  if (class_exists('Memcache') || class_exists("Memcached")) {
    variable_set('radioactivity_memcached_host', $form_state['values']['radioactivity_memcached_host']);
    variable_set('radioactivity_memcached_port', $form_state['values']['radioactivity_memcached_port']);
  }

  if (class_exists('Redis')) {
    variable_set('radioactivity_redis_host', $form_state['values']['radioactivity_redis_host']);
    variable_set('radioactivity_redis_port', $form_state['values']['radioactivity_redis_port']);
  }

  if ($form_state['values']['auto']) {

    $file = drupal_get_path("module", "radioactivity") . "/radioactivity-bootstrap.cfg.inc";
    $cfg = $form_state['values']['config'];
    if (!@file_put_contents($file, $cfg)) {
      drupal_set_message(t('Unable to create the file. Please create it manually.'), 'error');
    }
  }
}
