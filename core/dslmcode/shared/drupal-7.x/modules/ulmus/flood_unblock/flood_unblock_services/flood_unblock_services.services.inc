<?php

/**
 * Implements hook_services_resources().
 */
function flood_unblock_services_services_resources() {
  return array(
    'flood_unblock' => array(
      'actions' => array(
        'all' => array(
          'help' => t('Clear flood for all events'),
          'callback' => '_flood_unblock_services_all',
          'access arguments' => array('access flood unblock'),
        ),
        'ip' => array(
          'help' => t('Clear flood for the ip event'),
          'callback' => '_flood_unblock_services_ip',
          'access arguments' => array('access flood unblock'),
          ),
        'user' => array(
          'help' => t('Clear flood for the user event'),
          'callback' => '_flood_unblock_services_user',
          'access arguments' => array('access flood unblock'),
        ),
      ),
    ),
  );
}

/**
 * Services unblock all operation callback.
 */
function _flood_unblock_services_all() {
  flood_unblock_clear_event('failed_login_attempt_ip', NULL);
  flood_unblock_clear_event('failed_login_attempt_user', NULL);
}

/**
 * Services unblock ip operation callback.
 */
function _flood_unblock_services_ip() {
  flood_unblock_clear_event('failed_login_attempt_ip', NULL);
}

/**
 * Services unblock user operation callback.
 */
function _flood_unblock_services_user() {
  flood_unblock_clear_event('failed_login_attempt_user', NULL);
}
