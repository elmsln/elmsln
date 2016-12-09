<?php

/**
 * @file
 *   Expose CAS user name to views.
 */

function cas_views_data() {
  // cas_user table

  $data['cas_user']['table']['group'] = t('User');

  $data['cas_user']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'node' => array(
      'left_table' => 'users',
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['cas_user']['cas_name'] = array(
    'title' => t('CAS user name'),
    'help' => t('CAS user name(s) associated with a user.'),
    'field' => array(
      'handler' => 'cas_handler_field_cas_name',
      'no group by' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
