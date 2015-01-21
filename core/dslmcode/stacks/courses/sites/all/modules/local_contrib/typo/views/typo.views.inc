<?php
/**
 * @file
 * Provide views data and handlers for typo.module
 */


/**
 * Implementation of hook_views_data()
 */
function typo_views_data() {
  // Basic table information.

  $data['typo']['table']['group']  = t('Typos');

  // Advertise this table as a possible base table
  $data['typo']['table']['base'] = array(
    'field' => 'typo_id',
    'title' => t('Typo report'),
    'help' => t('Typo report messages.'),
    'weight' => 100,
  );

  // Typo url
  $data['typo']['url'] = array(
    'title' => t('Typo URL'),
    'help' => t('URL where typo found.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Typo text
  $data['typo']['text'] = array(
    'title' => t('Typo text'),
    'help' => t('Typo text.'),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'click sortable' => TRUE,
      'format' => filter_default_format(),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Typo comment
  $data['typo']['comment'] = array(
    'title' => t('Typo comment'),
    'help' => t('Comment for typo.'),
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
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Typo created
  $data['typo']['created'] = array(
    'title' => t('Typo created'),
    'help' => t('Time when typo report was sent.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  
  // Typo uid
  $data['typo']['uid'] = array(
    'title' => t('Typo report author UID'),
    'help' => t('UID of user who sent typo report.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  // Typo moderator uid
  $data['typo']['moderator_uid'] = array(
    'title' => t('Typo moderator UID'),
    'help' => t('UID if user who moderated typo.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  // Typo status
  $data['typo']['status'] = array(
    'title' => t('Status'),
    'help' => t('Status of typo.'),
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
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );


  return $data;
}