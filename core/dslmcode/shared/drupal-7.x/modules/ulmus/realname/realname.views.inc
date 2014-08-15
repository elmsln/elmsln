<?php

/**
 * @file
 * Views integration for the realname module.
 */

/**
 * Implements hook_views_data().
 */
function realname_views_data() {
  $data['realname']['table']['group']  = t('Realname');
  $data['realname']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['realname']['realname'] = array(
    'title' => t('Real name'),
    'help' => t("The user's real name."),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'title' => t('Name'),
      'help' => t("The user's real name. This filter does not check if the user exists and allows partial matching. Does not utilize autocomplete.")
    ),
  );

  return $data;
}
