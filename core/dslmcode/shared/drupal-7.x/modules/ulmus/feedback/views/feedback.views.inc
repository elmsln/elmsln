<?php

/**
 * @file
 * Provides views integration.
 */

/**
 * Implements hook_views_data().
 */
function feedback_views_data() {
  $data['feedback']['table']['group'] = t('Feedback');
  $data['feedback']['table']['base'] = array(
    'field' => 'fid',
    'title' => t('Feedback'),
    'help' => t('Feedback messages submitted to the site.'),
  );
  $data['feedback']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );
  $data['feedback']['fid'] = array(
    'title' => t('Feedback ID'),
    'help' => t('The primary identifier for a feedback message.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_numeric',
    ),
  );
  $data['feedback']['view_entry'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the feedback entry.'),
      'handler' => 'feedback_handler_field_feedback_link',
    ),
  );
  $data['feedback']['view_entry_delete'] = array(
    'field' => array(
      'title' => t('Delete entry'),
      'help' => t('Provide a simple link to delete the feedback entry.'),
      'handler' => 'feedback_handler_field_feedback_link_delete',
    ),
  );
  $data['feedback']['view_entry_edit'] = array(
    'field' => array(
      'title' => t('Edit entry'),
      'help' => t('Provide a simple link to the edit feedback entry.'),
      'handler' => 'feedback_handler_field_feedback_link_edit',
    ),
  );
  $data['feedback']['uid'] = array(
    'title' => t('User Id'),
    'help' => t('The user id of the author of a feedback message.'),
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User'),
    ),
  );
  $data['feedback']['status'] = array(
    'title' => t('Status'),
    'help' => t('The status of a feedback message.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Feedback status is processed'),
      'type' => 'yes-no',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_boolean',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['feedback']['message'] = array(
    'title' => t('Message'),
    'help' => t('The actual feedback message.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['feedback']['location'] = array(
    'title' => t('Location'),
    'help' => t('The internal Drupal path of the page the feedback message was submitted on.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['feedback']['location_masked'] = array(
    'title' => t('Location Masked'),
    'help' => t('The masked Drupal path of the page the feedback message was submitted on.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['feedback']['url'] = array(
    'title' => t('URL'),
    'help' => t('The absolute URL of the page the feedback message was submitted on.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['feedback']['useragent'] = array(
    'title' => t('User agent'),
    'help' => t('The user agent of the feedback message author.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['feedback']['timestamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('The UNIX timestamp when the feedback message was created.'),
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'views_handler_field_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  return $data;
}
