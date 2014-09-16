<?php

/**
 * Implementation of hook_views_pre_render().
 */
function achievements_views_views_pre_render(&$view) {
    achievements_views_filter_group($view);
}

function achievements_views_filter_group(&$view) {
    if (!isset($view->filter) || !isset($view->filter['achievement_group']))
        return;

    $filters = array();
    $filters[] = $view->filter['achievement_group'];

    foreach ($view->result as $index => $result) {
        foreach ($filters as $filter) {
            if (!($achievement_id = $result->{$filter->table . '_achievement_id'})) {
                continue;
            }

            $group = achievements_views_get_group($achievement_id);

            switch ($filter->operator) {
                case '=':
                    if (!($group['title'] == $filter->value))
                        unset($view->result[$index]);
                    break;
                case '!=':
                    if (!($group['title'] != $filter->value))
                        unset($view->result[$index]);
                    break;
            }
        }
    }
}

/**
 * Implementation of hook_views_data().
 */
function achievements_views_views_data() {
  $data['achievement_totals']['table']['group']  = t('Achievement Totals');

  $data['achievement_totals']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );

  // uid
  $data['achievement_totals']['uid'] = array(
    'title' => t('User'),
    'help' => t('The user who received achievement points.'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Individual achievement user'),
    ),
  );

  // points
  $data['achievement_totals']['points'] = array(
    'title' => t('Total points'), // The item it appears as on the UI,
    'help' => t('The user\'s combined achievement point total.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // unlocks
  $data['achievement_totals']['unlocks'] = array(
    'title' => t('Total unlocks'),
    'help' => t('The user\'s total number of achievement unlocks.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // timestamp
  $data['achievement_totals']['timestamp'] = array(
    'title' => t('Last achievement received date'),
    'help' => t('The Unix timestamp when the user last received an achievement.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  // achievement id
  $data['achievement_totals']['achievement_id'] = array(
    'title' => t('Last achievement received ID'),
    'help' => t('The ID of the achievement the user has most recently unlocked.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // achievement title
  $data['achievement_totals']['achievement_title'] = array(
    'title' => t('Achievement Title'),
    'help' => t('The title for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_title',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // achievement group
  $data['achievement_totals']['achievement_group'] = array(
    'title' => t('Achievement Group'),
    'help' => t('The group that this achievement belongs to.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_group',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'achievements_views_handler_filter_achievements_group',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // unlock image
  $data['achievement_totals']['achievement_image_unlocked'] = array(
    'title' => t('Unlock image'),
    'help' => t('The unlock image for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_unlocked_image',
      'click sortable' => FALSE,
    ),
  );

  // lock image
  $data['achievement_totals']['achievement_image_locked'] = array(
    'title' => t('Lock image'),
    'help' => t('The lock image for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_locked_image',
      'click sortable' => FALSE,
    ),
  );

  $data['achievement_unlocks']['table']['group']  = t('Achievement Unlocks');

  $data['achievement_unlocks']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );

  // achievement id
  $data['achievement_unlocks']['achievement_id']  = array(
    'title' => t('Achievement ID'),
    'help' => t('The ID of the achievement the user has unlocked.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // achievement title
  $data['achievement_unlocks']['achievement_title'] = array(
    'title' => t('Achievement Title'),
    'help' => t('The title for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_title',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // achievement group
  $data['achievement_unlocks']['achievement_group'] = array(
    'title' => t('Achievement Group'),
    'help' => t('The group that this achievement belongs to.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_group',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'achievements_views_handler_filter_achievements_group',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // unlock image
  $data['achievement_unlocks']['achievement_image_unlocked'] = array(
    'title' => t('Unlock image'),
    'help' => t('The unlock image for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_unlocked_image',
      'click sortable' => FALSE,
    ),
  );

  // lock image
  $data['achievement_unlocks']['achievement_image_locked'] = array(
    'title' => t('Lock image'),
    'help' => t('The lock image for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_locked_image',
      'click sortable' => FALSE,
    ),
  );

  // rank
  $data['achievement_unlocks']['rank'] = array(
    'title' => t('Unlocked rank'),
    'help' => t('The rank earned for unlocking this achievement.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // uid
  $data['achievement_unlocks']['uid'] = array(
    'title' => t('User'),
    'help' => t('The user that has unlocked the achievement.'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Individual achievement user'),
    ),
  );

  // timestamp
  $data['achievement_unlocks']['timestamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('The Unix timestamp when the user last received an achievement.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  // seen
  $data['achievement_unlocks']['seen'] = array(
    'title' => t('Notified of unlock'),
    'help' => t('A boolean indicating whether the user has been notified of this unlock.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['achievement_storage']['table']['group']  = t('Achievement Storage');

  $data['achievement_storage']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );

  // achievement id
  $data['achievement_storage']['achievement_id']  = array(
    'title' => t('Achievement ID'),
    'help' => t('The ID of the achievement the user has unlocked.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // achievement title
  $data['achievement_storage']['achievement_title'] = array(
    'title' => t('Achievement Title'),
    'help' => t('The title for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_title',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // achievement group
  $data['achievement_storage']['achievement_group'] = array(
    'title' => t('Achievement Group'),
    'help' => t('The group that this achievement belongs to.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_group',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'achievements_views_handler_filter_achievements_group',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // unlock image
  $data['achievement_storage']['achievement_image_unlocked'] = array(
    'title' => t('Unlock image'),
    'help' => t('The unlock image for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_unlocked_image',
      'click sortable' => FALSE,
    ),
  );

  // lock image
  $data['achievement_storage']['achievement_image_locked'] = array(
    'title' => t('Lock image'),
    'help' => t('The lock image for this achievement.'),
    'field' => array(
      'handler' => 'achievements_views_handler_field_achievements_locked_image',
      'click sortable' => FALSE,
    ),
  );

  // uid
  $data['achievement_storage']['uid'] = array(
    'title' => t('User'),
    'help' => t('The user that the stored data relates to.'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Individual achievement user'),
    ),
  );

  // data
  $data['achievement_storage']['data']  = array(
    'title' => t('Achievement data'),
    'help' => t('A serialized string of the stored data.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
