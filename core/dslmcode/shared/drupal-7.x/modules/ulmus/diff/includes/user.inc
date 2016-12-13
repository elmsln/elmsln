<?php

/**
 * @file
 * Provide diff functions for the user module.
 *
 * Note as users do not have revisions enabled, most use cases for comparisons
 * will be between two different users.
 */

/**
 * Private callback function to render the name field.
 */
function _user_entity_diff_additional_options_name($old_user, $new_user, $context) {
  $row = array(
    '#name' => t('Username'),
    '#states' => array(),
    '#weight' => -5,
    '#settings' => array(
      'show_header' => variable_get('diff_show_header_user', 1),
    ),
  );
  foreach ($context['states'] as $state) {
    switch ($state) {
      case 'rendered':
        $row['#states'][$state] = array(
          '#old' => theme('username', array('account' => $old_user)),
          '#new' => theme('username', array('account' => $old_user)),
        );
        break;

      // We specify a default so that the name is always compared.
      case 'raw':
      default:
        $row['#states'][$state] = array(
          '#old' => array($old_user->name),
          '#new' => array($new_user->name),
        );
        break;
    }
  }
  return $row;
}

/**
 * Private callback function to render the mail field.
 */
function _user_entity_diff_additional_options_mail($old_user, $new_user, $context) {
  $row = array(
    '#name' => t('E-mail address'),
    '#states' => array(),
    '#weight' => -4,
    '#settings' => array(),
  );

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array($old_user->mail),
      '#new' => array($new_user->mail),
    );
  }
  return $row;
}

/**
 * Private callback function to render the status field.
 */
function _user_entity_diff_additional_options_status($old_user, $new_user, $context) {
  $row = array(
    '#name' => t('Status'),
    '#states' => array(),
    '#weight' => -3,
    '#settings' => array(),
  );

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array($old_user->status ? t('Active') : t('Blocked')),
      '#new' => array($new_user->status ? t('Active') : t('Blocked')),
    );
  }
  return $row;
}

/**
 * Private callback function to render the timezone field.
 */
function _user_entity_diff_additional_options_timezone($old_user, $new_user, $context) {
  $row = array(
    '#name' => t('Time zone'),
    '#states' => array(),
    '#weight' => -1,
    '#settings' => array(),
  );
  $system_time_zones = system_time_zones(TRUE);
  $old_zone = isset($old_user->timezone) ? $old_user->timezone : '';
  $new_zone = isset($new_user->timezone) ? $new_user->timezone : '';

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array(isset($system_time_zones[$old_zone]) ? $system_time_zones[$old_zone] : t('- None selected -')),
      '#new' => array(isset($system_time_zones[$new_zone]) ? $system_time_zones[$new_zone] : t('- None selected -')),
    );
  }
  return $row;
}

/**
 * Private callback function to render the password field.
 */
function _user_entity_diff_additional_options_password($old_user, $new_user, $context) {
  $row = array(
    '#name' => t('Password Hash'),
    '#states' => array(),
    '#weight' => -1,
    '#settings' => array(),
  );

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array($old_user->pass),
      '#new' => array($new_user->pass),
    );
  }
  return $row;
}

/**
 * Private callback function to render the roles field.
 */
function _user_entity_diff_additional_options_roles($old_user, $new_user, $context) {
  $row = array(
    '#name' => t('Roles'),
    '#states' => array(),
    '#weight' => -1,
    '#settings' => array(),
  );

  $roles = user_roles(TRUE);
  unset($roles[DRUPAL_AUTHENTICATED_RID]);
  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array(implode("\n", array_intersect_key($roles, $old_user->roles))),
      '#new' => array(implode("\n", array_intersect_key($roles, $new_user->roles))),
    );
  }
  return $row;
}
