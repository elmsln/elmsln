<?php

/**
 * @file
 * Provide views data and handlers for user.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function user_views_data() {
  // ----------------------------------------------------------------
  // 'users' table.
  // Define the base group of this table. Fields that don't have a group
  // defined will go into this field by default.
  $data['users']['table']['group']  = t('User');

  $data['users']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('User'),
    'help' => t('Users who have created accounts on your site.'),
    'access query tag' => 'user_access',
  );
  $data['users']['table']['entity type'] = 'user';

  $data['users']['table']['default_relationship'] = array(
    'node' => array(
      'table' => 'node',
      'field' => 'uid',
    ),
    'node_revision' => array(
      'table' => 'node_revision',
      'field' => 'uid',
    ),
    'file' => array(
      'table' => 'file',
      'field' => 'uid',
    ),
  );

  // User ID / 'uid'.
  $data['users']['uid'] = array(
    // The item it appears as on the UI,
    'title' => t('Uid'),
    // The help that appears on the UI,
    'help' => t('The user ID'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      // Display this field in the summary.
      'name field' => 'name',
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'title' => t('Content authored'),
      'help' => t('Relate content to the user who created it. This relationship will create one record for each content item created by the user.'),
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'uid',
      'field' => 'uid',
      'label' => t('nodes'),
    ),
  );

  // The raw user ID / 'uid_raw'.
  $data['users']['uid_raw'] = array(
    'help' => t('The raw numeric user ID.'),
    'real field' => 'uid',
    'filter' => array(
      'title' => t('The user ID'),
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // Representative node for the user.
  $data['users']['uid_representative'] = array(
    'relationship' => array(
      'title' => t('Representative node'),
      'label'  => t('Representative node'),
      'help' => t('Obtains a single representative node for each user, according to a chosen sort criterion.'),
      'handler' => 'views_handler_relationship_groupwise_max',
      'relationship field' => 'uid',
      'outer field' => 'users.uid',
      'argument table' => 'users',
      'argument field' => 'uid',
      'base'   => 'node',
      'field'  => 'nid',
    ),
  );

  // Current user's ID / 'uid'.
  $data['users']['uid_current'] = array(
    'real field' => 'uid',
    'title' => t('Current'),
    'help' => t('Filter the view to the currently logged in user.'),
    'filter' => array(
      'handler' => 'views_handler_filter_user_current',
      'type' => 'yes-no',
    ),
  );

  // Comments authored.
  $data['users']['uid_comment'] = array(
    'relationship' => array(
      'title' => t('Comments authored'),
      'help' => t('Relate comments to the user who created it. This relationship will create one record for each comment created by the user.'),
      'handler' => 'views_handler_relationship',
      'base' => 'comment',
      'base field' => 'uid',
      'field' => 'uid',
      'label' => t('comments'),
    ),
  );

  // User name.
  $data['users']['name'] = array(
    // The item it appears as on the UI,
    'title' => t('Name'),
    // The help that appears on the UI,
    'help' => t('The user or author name.'),
    'field' => array(
      'handler' => 'views_handler_field_user_name',
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
      'title' => t('Name (raw)'),
      'help' => t('The user or author name. This filter does not check if the user exists and allows partial matching. Does not utilize autocomplete.'),
    ),
  );

  // Email address.
  // Note that this field implements field level access control.
  $data['users']['mail'] = array(
    // The item it appears as on the UI,
    'title' => t('E-mail'),
    // The help that appears on the UI,
    'help' => t('E-mail address for a given user. This field is normally not shown to users, so be cautious when using it.'),
    'field' => array(
      'handler' => 'views_handler_field_user_mail',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Language.
  $data['users']['language'] = array(
    // The item it appears as on the UI,
    'title' => t('Language'),
    'help' => t('Language of the user'),
    'field' => array(
      'handler' => 'views_handler_field_user_language',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_node_language',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_node_language',
    ),
  );

  // Picture.
  $data['users']['picture_fid']['moved to'] = array('users', 'picture');
  $data['users']['picture'] = array(
    // The item it appears as on the UI,
    'title' => t('Picture'),
    // The help that appears on the UI,
    'help' => t("The user's picture, if allowed."),
    // Information for displaying the uid.
    'field' => array(
      'handler' => 'views_handler_field_user_picture',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Has Avatar'),
      'type' => 'yes-no',
    ),
  );

  // Link.
  $data['users']['view_user'] = array(
    'field' => array(
      'title' => t('Link to user'),
      'help' => t('Provide a simple link to the user.'),
      'handler' => 'views_handler_field_user_link',
    ),
  );

  // Created field.
  $data['users']['created'] = array(
    // The item it appears as on the UI,
    'title' => t('Created date'),
    // The help that appears on the UI,
    'help' => t('The date the user was created.'),
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
  );

  $data['users']['created_fulldate'] = array(
    'title' => t('Created date'),
    'help' => t('Date in the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['users']['created_year_month'] = array(
    'title' => t('Created year + month'),
    'help' => t('Date in the form of YYYYMM.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['users']['timestamp_year']['moved to'] = array('users', 'created_year');
  $data['users']['created_year'] = array(
    'title' => t('Created year'),
    'help' => t('Date in the form of YYYY.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['users']['created_month'] = array(
    'title' => t('Created month'),
    'help' => t('Date in the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['users']['created_day'] = array(
    'title' => t('Created day'),
    'help' => t('Date in the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['users']['created_week'] = array(
    'title' => t('Created week'),
    'help' => t('Date in the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  // Access field.
  $data['users']['access'] = array(
    // The item it appears as on the UI,
    'title' => t('Last access'),
    // The help that appears on the UI,
    'help' => t("The user's last access date."),
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
  );

  // Login field.
  $data['users']['login'] = array(
    // The item it appears as on the UI,
    'title' => t('Last login'),
    // The help that appears on the UI,
    'help' => t("The user's last login date."),
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
  );

  // Active status.
  $data['users']['status'] = array(
    // The item it appears as on the UI,
    'title' => t('Active status'),
    // The help that appears on the UI,
    'help' => t('Whether a user is active or blocked.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'active-blocked' => array(t('Active'), t('Blocked')),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Log field.
  $data['users']['signature'] = array(
    // The item it appears as on the UI,
    'title' => t('Signature'),
    // The help that appears on the UI,
    'help' => t("The user's signature."),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'format' => filter_fallback_format(),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['users']['edit_node'] = array(
    'field' => array(
      'title' => t('Link to edit user'),
      'help' => t('Provide a simple link to edit the user.'),
      'handler' => 'views_handler_field_user_link_edit',
    ),
  );

  $data['users']['cancel_node'] = array(
    'field' => array(
      'title' => t('Link to cancel user'),
      'help' => t('Provide a simple link to cancel the user.'),
      'handler' => 'views_handler_field_user_link_cancel',
    ),
  );

  $data['users']['data'] = array(
    'title' => t('Data'),
    'help' => t('Provide serialized data of the user'),
    'field' => array(
      'handler' => 'views_handler_field_serialized',
    ),
  );

  // ----------------------------------------------------------------------
  // 'users_roles' table.
  $data['users_roles']['table']['group']  = t('User');

  // Explain how this table joins to others.
  $data['users_roles']['table']['join'] = array(
     // Directly links to users table.
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['users_roles']['table']['default_relationship'] = array(
    'node' => array(
      'table' => 'node',
      'field' => 'uid',
    ),
    'node_revision' => array(
      'table' => 'node_revision',
      'field' => 'uid',
    ),
  );

  $data['users_roles']['rid'] = array(
    'title' => t('Roles'),
    'help' => t('Roles that a user belongs to.'),
    'field' => array(
      'handler' => 'views_handler_field_user_roles',
      'no group by' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_roles',
      'numeric' => TRUE,
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_users_roles_rid',
      'name table' => 'role',
      'name field' => 'name',
      'empty field name' => t('No role'),
      'zero is null' => TRUE,
      'numeric' => TRUE,
    ),
  );

  // ----------------------------------------------------------------------
  // 'role' table.
  $data['role']['table']['join'] = array(
     // Directly links to users table.
    'users' => array(
      'left_table' => 'users_roles',
      'left_field' => 'rid',
      'field' => 'rid',
    ),
    // Needed for many to one helper sometimes.
    'users_roles' => array(
      'left_field' => 'rid',
      'field' => 'rid',
    ),
  );

  $data['role']['table']['default_relationship'] = array(
    'node' => array(
      'table' => 'node',
      'field' => 'uid',
    ),
    'node_revision' => array(
      'table' => 'node_revision',
      'field' => 'uid',
    ),
  );

  // 'permission' table.
  $data['role_permission']['table']['group']  = t('User');
  $data['role_permission']['table']['join'] = array(
     // Directly links to users table.
    'users' => array(
      'left_table' => 'users_roles',
      'left_field' => 'rid',
      'field' => 'rid',
    ),
  );

  $data['role_permission']['permission'] = array(
    'title' => t('Permission'),
    'help' => t('The user permissions.'),
    'field' => array(
      'handler' => 'views_handler_field_user_permissions',
      'no group by' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_permissions',
    ),
  );

  // ----------------------------------------------------------------------
  // 'authmap' table.
  $data['authmap']['table']['group']  = t('User');
  $data['authmap']['table']['join'] = array(
     // Directly links to users table.
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['authmap']['table']['default_relationship'] = array(
    'node' => array(
      'table' => 'node',
      'field' => 'uid',
    ),
    'node_revision' => array(
      'table' => 'node_revision',
      'field' => 'uid',
    ),
  );

  $data['authmap']['aid'] = array(
    'title' => t('Authmap ID'),
    'help' => t('The Authmap ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'numeric' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
  );
  $data['authmap']['authname'] = array(
    'title' => t('Authentication name'),
    'help' => t('The unique authentication name.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['authmap']['module'] = array(
    'title' => t('Authentication module'),
    'help' => t('The name of the module managing the authentication entry.'),
    'field' => array(
      'handler' => 'views_handler_field',
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

/**
 * Implements hook_views_plugins().
 */
function user_views_plugins() {
  return array(
    // This just tells our themes are elsewhere.
    'module' => 'views',
    'row' => array(
      'user' => array(
        'title' => t('User'),
        'help' => t('Display the user with standard user view.'),
        'handler' => 'views_plugin_row_user_view',
        // Only works with 'users' as base.
        'base' => array('users'),
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-users',
      ),
    ),
    'argument default' => array(
      'user' => array(
        'title' => t('User ID from URL'),
        'handler' => 'views_plugin_argument_default_user',
        // Not necessary for most modules.
        'path' => drupal_get_path('module', 'views') . '/modules/user',
      ),
      'current_user' => array(
        'title' => t('User ID from logged in user'),
        'handler' => 'views_plugin_argument_default_current_user',
        // Not necessary for most modules.
        'path' => drupal_get_path('module', 'views') . '/modules/user',
      ),
    ),
    'argument validator' => array(
      'user' => array(
        'title' => t('User'),
        'handler' => 'views_plugin_argument_validate_user',
        // Not necessary for most modules.
        'path' => drupal_get_path('module', 'views') . '/modules/user',
      ),
    ),
  );
}

/**
 * Allow replacement of current userid so we can cache these queries.
 */
function user_views_query_substitutions($view) {
  global $user;
  return array('***CURRENT_USER***' => intval($user->uid));
}
