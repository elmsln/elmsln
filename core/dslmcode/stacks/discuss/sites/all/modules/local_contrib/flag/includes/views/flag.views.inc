<?php

/**
 * @file
 * Provides support for the Views module.
 */

/**
 * Implements hook_views_plugins().
 */
function flag_views_plugins() {
  return array(
    'argument validator' => array(
      'flag_flaggable_node' => array(
        'title' => t('Flaggable node'),
        'flag type' => 'node',
        'handler' => 'flag_plugin_argument_validate_flaggability',
        'path' => drupal_get_path('module', 'flag') . '/includes',
      ),
      'flag_flaggable_user' => array(
        'title' => t('Flaggable user'),
        'flag type' => 'user',
        'handler' => 'flag_plugin_argument_validate_flaggability',
        'path' => drupal_get_path('module', 'flag') . '/includes',
      ),
      // A comment validator won't be very useful. Moreover, having it will
      // contribute to the argument object's $options polution, so let's skip
      // it.
    ),
  );
}
/**
 * Implements hook_views_data().
 */
function flag_views_data() {
  $data = array();

  $data['flagging']['table']['group'] = t('Flags');
  $data['flag_counts']['table']['group'] = t('Flags');

  // Notify views from flag 2.x of our changes to views data.
  // @see flag_update_7301().
  $data['flag_content']['moved to'] = 'flagging';
  // @see flag_update_7303().
  $data['flag_content']['content_id']['moved to'] = array('flagging', 'entity_id');

  $data['flagging']['uid'] = array(
    'title' => t('User uid'),
    'help' => t('The user that flagged an item. If you need more fields than the uid add the "Flags: User" relationship.'),
    'relationship' => array(
      'base' => 'users',
      'title' => t('User'),
      'help' => t('Relate an item to the user that flagged it.'),
      'handler' => 'views_handler_relationship',
      'label' => t('Flag user'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field_user',
    ),
  );

  $data['flagging']['timestamp'] = array(
    'title' => t('Flagged time'),
    'help' => t('Display the time the content was flagged by a user.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Argument for content ID, used for "Who's flagged this" views.
  $data['flagging']['entity_id'] = array(
    'title' => t('Entity ID'),
    'help' => t('The unique ID of the object that has been flagged.'),
    'argument' => array(
      'handler' => 'flag_handler_argument_entity_id',
    ),
  );

  // Specialized is null/is not null filter.
  $data['flagging']['flagged'] = array(
    'title' => t('Flagged'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'flag_handler_field_flagged',
      'label' => t('Flagged'),
      'help' => t('A boolean field to show whether the flag is set or not.'),
    ),
    'filter' => array(
      'handler' => 'flag_handler_filter_flagged',
      'label' => t('Flagged'),
      'help' => t('Filter to ensure content has or has not been flagged.'),
    ),
    'sort' => array(
      'handler' => 'flag_handler_sort_flagged',
      'label' => t('Flagged'),
      'help' => t('Sort by whether entities have or have not been flagged.'),
    ),
  );

  // Flag content links.
  $data['flagging']['ops'] = array(
    'title' => t('Flag link'),
    'help' => t('Display flag/unflag link.'),
    'field' => array(
      'handler' => 'flag_handler_field_ops',
    ),
  );

  $data['flagging']['sid'] = array(
    'title' => t('Flagging session ID'),
    'help' => t('The session ID of the flagging.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['flag_counts']['count'] = array(
    'title' => t('Flag counter'),
    'help' => t('The number of times a piece of content is flagged by any user.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['flag_counts']['last_updated'] = array(
    'title' => t('Time last flagged'),
    'help' => t('The time a piece of content was most recently flagged by any user.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function flag_views_data_alter(&$data) {

  foreach (array_keys(flag_fetch_definition()) as $flag_type) {
    $flag = flag_flag::factory_by_entity_type($flag_type);
    $info = $flag->get_views_info();

    if (!isset($info)) {
      continue;
    }

    if (!empty($info['join field'])) {
      // Add the flag relationship.
      $data[$info['views table']]['flag_content_rel'] = array(
        'group' => t('Flags'),
        'title' => $info['title'],
        'help' => $info['help'],
        'relationship' => array(
          'flag type' => $flag_type,
          'handler' => 'flag_handler_relationship_content',
          'label' => t('flag'),
          'base' => 'flagging',
          'base field' => 'entity_id',
          'relationship field' => $info['join field'],
        ),
      );

      // Add the flag counter relationship.
      $data[$info['views table']]['flag_count_rel'] = array(
        'group' => t('Flags'),
        'title' => $info['counter title'],
        'help' => $info['counter help'],
        'relationship' => array(
          'flag type' => $flag_type,
          'handler' => 'flag_handler_relationship_counts',
          'label' => t('counter'),
          'base' => 'flag_counts',
          'base field' => 'entity_id',
          'relationship field' => $info['join field'],
        ),
      );
    }
  }

  // Add a relationship for the user that flagged any type of content.
  $data['users']['flag_user_content_rel'] = array(
    'group' => t('Flags'),
    'title' => t("User's flaggings"),
    'help' => t('Relate users to the flaggings they have made on objects, using a particular flag.'),
    'relationship' => array(
      'base' => 'flagging',
      'base field' => 'uid',
      'relationship field' => 'uid',
      'handler' => 'flag_handler_relationship_user_content',
      'label' => t('user flagged content'),
    ),
  );
}

/**
 * Implements hook_views_query_substitutions().
 *
 * Allow replacement of current user's session id so we can cache these queries.
 */
function flag_views_query_substitutions() {
  return array(
    '***FLAG_CURRENT_USER_SID***' => flag_get_sid(),
  );
}
/**
 * A helper function that creates a radio list of available flags.
 *
 * This function is used to select the desired flag when setting up flag
 * relationships and fields.
 */
function flag_views_flag_config_form($form_type, $entity_type, $current_flag) {
  $flags = flag_get_flags($entity_type);

  $options = array();
  foreach ($flags as $flag) {
    $options[$flag->name] = $flag->get_title();
  }

  $form = array(
    '#type' => $form_type,
    '#title' => t('Flag'),
    '#options' => $options,
    '#default_value' => $current_flag,
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Helper function that gets the first defined flag and returns its name.
 */
function flag_views_flag_default($entity_type) {
  $default_flag = &drupal_static(__FUNCTION__, array());

  if (!array_key_exists($entity_type, $default_flag)) {
    $flags = flag_get_flags($entity_type);
    $flag = array_shift($flags);
    $default_flag[$entity_type] = $flag ? $flag->name : NULL;
  }

  return $default_flag[$entity_type];
}
