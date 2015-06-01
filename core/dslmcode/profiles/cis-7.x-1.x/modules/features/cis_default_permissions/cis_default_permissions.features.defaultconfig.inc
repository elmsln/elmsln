<?php
/**
 * @file
 * cis_default_permissions.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function cis_default_permissions_defaultconfig_features() {
  return array(
    'cis_default_permissions' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function cis_default_permissions_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access admin theme'.
  $permissions['access admin theme'] = array(
    'name' => 'access admin theme',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'admin_theme',
  );

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: 'access back_to_top settings'.
  $permissions['access back_to_top settings'] = array(
    'name' => 'access back_to_top settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'back_to_top',
  );

  // Exported permission: 'access cis get course list'.
  $permissions['access cis get course list'] = array(
    'name' => 'access cis get course list',
    'roles' => array(),
    'module' => 'cis_example_cis',
  );

  // Exported permission: 'access cis setup form'.
  $permissions['access cis setup form'] = array(
    'name' => 'access cis setup form',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'cis_helper',
  );

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access lti_tool_provider_consumer entities'.
  $permissions['access lti_tool_provider_consumer entities'] = array(
    'name' => 'access lti_tool_provider_consumer entities',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'lti_tool_provider',
  );

  // Exported permission: 'access private fields'.
  $permissions['access private fields'] = array(
    'name' => 'access private fields',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'access resource accessibility_test'.
  $permissions['access resource accessibility_test'] = array(
    'name' => 'access resource accessibility_test',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource field_collection_item'.
  $permissions['access resource field_collection_item'] = array(
    'name' => 'access resource field_collection_item',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource file'.
  $permissions['access resource file'] = array(
    'name' => 'access resource file',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource lti_tool_provider_consumer'.
  $permissions['access resource lti_tool_provider_consumer'] = array(
    'name' => 'access resource lti_tool_provider_consumer',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource user'.
  $permissions['access resource user'] = array(
    'name' => 'access resource user',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource wysiwyg_profile'.
  $permissions['access resource wysiwyg_profile'] = array(
    'name' => 'access resource wysiwyg_profile',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'user',
  );

  // Exported permission: 'admin_display_suite'.
  $permissions['admin_display_suite'] = array(
    'name' => 'admin_display_suite',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'ds',
  );

  // Exported permission: 'administer accessibility tests'.
  $permissions['administer accessibility tests'] = array(
    'name' => 'administer accessibility tests',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'accessibility',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer add another'.
  $permissions['administer add another'] = array(
    'name' => 'administer add another',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'addanother',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'block',
  );

  // Exported permission: 'administer breakpoints'.
  $permissions['administer breakpoints'] = array(
    'name' => 'administer breakpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'breakpoints',
  );

  // Exported permission: 'administer ckeditor link'.
  $permissions['administer ckeditor link'] = array(
    'name' => 'administer ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer contexts'.
  $permissions['administer contexts'] = array(
    'name' => 'administer contexts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'context_ui',
  );

  // Exported permission: 'administer data tables'.
  $permissions['administer data tables'] = array(
    'name' => 'administer data tables',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'data_ui',
  );

  // Exported permission: 'administer default config'.
  $permissions['administer default config'] = array(
    'name' => 'administer default config',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'defaultconfig',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'administer field collections'.
  $permissions['administer field collections'] = array(
    'name' => 'administer field collections',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_collection',
  );

  // Exported permission: 'administer field permissions'.
  $permissions['administer field permissions'] = array(
    'name' => 'administer field permissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'administer fieldgroups'.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_group',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'image',
  );

  // Exported permission: 'administer imce'.
  $permissions['administer imce'] = array(
    'name' => 'administer imce',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'imce',
  );

  // Exported permission: 'administer jquery colorpicker'.
  $permissions['administer jquery colorpicker'] = array(
    'name' => 'administer jquery colorpicker',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jquery_colorpicker',
  );

  // Exported permission: 'administer lti_tool_provider module'.
  $permissions['administer lti_tool_provider module'] = array(
    'name' => 'administer lti_tool_provider module',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'lti_tool_provider',
  );

  // Exported permission: 'administer masquerade'.
  $permissions['administer masquerade'] = array(
    'name' => 'administer masquerade',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer menu attributes'.
  $permissions['administer menu attributes'] = array(
    'name' => 'administer menu attributes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'menu_attributes',
  );

  // Exported permission: 'administer menu positions'.
  $permissions['administer menu positions'] = array(
    'name' => 'administer menu positions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'menu_position',
  );

  // Exported permission: 'administer module filter'.
  $permissions['administer module filter'] = array(
    'name' => 'administer module filter',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'module_filter',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer nodequeue'.
  $permissions['administer nodequeue'] = array(
    'name' => 'administer nodequeue',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer schema'.
  $permissions['administer schema'] = array(
    'name' => 'administer schema',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'schema',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'administer shadowbox'.
  $permissions['administer shadowbox'] = array(
    'name' => 'administer shadowbox',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'shadowbox',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer uuid'.
  $permissions['administer uuid'] = array(
    'name' => 'administer uuid',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'uuid',
  );

  // Exported permission: 'administer video styles'.
  $permissions['administer video styles'] = array(
    'name' => 'administer video styles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'video_embed_field',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: 'administer wysiwyg templates'.
  $permissions['administer wysiwyg templates'] = array(
    'name' => 'administer wysiwyg templates',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'wysiwyg_template',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass advanced aggregation'.
  $permissions['bypass advanced aggregation'] = array(
    'name' => 'bypass advanced aggregation',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'advagg',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'bypass redirection'.
  $permissions['bypass redirection'] = array(
    'name' => 'bypass redirection',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_redirection',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'cis setup admin options'.
  $permissions['cis setup admin options'] = array(
    'name' => 'cis setup admin options',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'cis_helper',
  );

  // Exported permission: 'context ajax block access'.
  $permissions['context ajax block access'] = array(
    'name' => 'context ajax block access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'context_ui',
  );

  // Exported permission: 'create academic_unit content'.
  $permissions['create academic_unit content'] = array(
    'name' => 'create academic_unit content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create cis_course content'.
  $permissions['create cis_course content'] = array(
    'name' => 'create cis_course content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create college_services content'.
  $permissions['create college_services content'] = array(
    'name' => 'create college_services content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create course content'.
  $permissions['create course content'] = array(
    'name' => 'create course content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_abbreviation'.
  $permissions['create field_abbreviation'] = array(
    'name' => 'create field_abbreviation',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_access_string'.
  $permissions['create field_access_string'] = array(
    'name' => 'create field_access_string',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_additional_notes'.
  $permissions['create field_additional_notes'] = array(
    'name' => 'create field_additional_notes',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_cis_ops'.
  $permissions['create field_cis_ops'] = array(
    'name' => 'create field_cis_ops',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_color'.
  $permissions['create field_color'] = array(
    'name' => 'create field_color',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_coordinators'.
  $permissions['create field_coordinators'] = array(
    'name' => 'create field_coordinators',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_course_archive'.
  $permissions['create field_course_archive'] = array(
    'name' => 'create field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_cron_key'.
  $permissions['create field_cron_key'] = array(
    'name' => 'create field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_data_location'.
  $permissions['create field_data_location'] = array(
    'name' => 'create field_data_location',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_distribution'.
  $permissions['create field_distribution'] = array(
    'name' => 'create field_distribution',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_first_name'.
  $permissions['create field_first_name'] = array(
    'name' => 'create field_first_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_instant_messenger'.
  $permissions['create field_instant_messenger'] = array(
    'name' => 'create field_instant_messenger',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_instructional_designer'.
  $permissions['create field_instructional_designer'] = array(
    'name' => 'create field_instructional_designer',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_instructor_of_record'.
  $permissions['create field_instructor_of_record'] = array(
    'name' => 'create field_instructor_of_record',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_last_name'.
  $permissions['create field_last_name'] = array(
    'name' => 'create field_last_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_ldap_campus'.
  $permissions['create field_ldap_campus'] = array(
    'name' => 'create field_ldap_campus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_ldap_department'.
  $permissions['create field_ldap_department'] = array(
    'name' => 'create field_ldap_department',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_lead_instructor'.
  $permissions['create field_lead_instructor'] = array(
    'name' => 'create field_lead_instructor',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_machine_name'.
  $permissions['create field_machine_name'] = array(
    'name' => 'create field_machine_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_method_of_access'.
  $permissions['create field_method_of_access'] = array(
    'name' => 'create field_method_of_access',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_service_data'.
  $permissions['create field_service_data'] = array(
    'name' => 'create field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_services'.
  $permissions['create field_services'] = array(
    'name' => 'create field_services',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_syllabus'.
  $permissions['create field_syllabus'] = array(
    'name' => 'create field_syllabus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_ta_documents'.
  $permissions['create field_ta_documents'] = array(
    'name' => 'create field_ta_documents',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_teaching_assistants'.
  $permissions['create field_teaching_assistants'] = array(
    'name' => 'create field_teaching_assistants',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_unit_head'.
  $permissions['create field_unit_head'] = array(
    'name' => 'create field_unit_head',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_welcome_letter'.
  $permissions['create field_welcome_letter'] = array(
    'name' => 'create field_welcome_letter',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create instructional_model content'.
  $permissions['create instructional_model content'] = array(
    'name' => 'create instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create news content'.
  $permissions['create news content'] = array(
    'name' => 'create news content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create page content'.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create person content'.
  $permissions['create person content'] = array(
    'name' => 'create person content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create program content'.
  $permissions['create program content'] = array(
    'name' => 'create program content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create resource content'.
  $permissions['create resource content'] = array(
    'name' => 'create resource content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create service content'.
  $permissions['create service content'] = array(
    'name' => 'create service content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create service_instance content'.
  $permissions['create service_instance content'] = array(
    'name' => 'create service_instance content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'path',
  );

  // Exported permission: 'delete any academic_unit content'.
  $permissions['delete any academic_unit content'] = array(
    'name' => 'delete any academic_unit content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any cis_course content'.
  $permissions['delete any cis_course content'] = array(
    'name' => 'delete any cis_course content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any college_services content'.
  $permissions['delete any college_services content'] = array(
    'name' => 'delete any college_services content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any course content'.
  $permissions['delete any course content'] = array(
    'name' => 'delete any course content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any instructional_model content'.
  $permissions['delete any instructional_model content'] = array(
    'name' => 'delete any instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any news content'.
  $permissions['delete any news content'] = array(
    'name' => 'delete any news content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page content'.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any person content'.
  $permissions['delete any person content'] = array(
    'name' => 'delete any person content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any program content'.
  $permissions['delete any program content'] = array(
    'name' => 'delete any program content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any resource content'.
  $permissions['delete any resource content'] = array(
    'name' => 'delete any resource content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any service content'.
  $permissions['delete any service content'] = array(
    'name' => 'delete any service content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any service_instance content'.
  $permissions['delete any service_instance content'] = array(
    'name' => 'delete any service_instance content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own academic_unit content'.
  $permissions['delete own academic_unit content'] = array(
    'name' => 'delete own academic_unit content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own cis_course content'.
  $permissions['delete own cis_course content'] = array(
    'name' => 'delete own cis_course content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own college_services content'.
  $permissions['delete own college_services content'] = array(
    'name' => 'delete own college_services content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own course content'.
  $permissions['delete own course content'] = array(
    'name' => 'delete own course content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own instructional_model content'.
  $permissions['delete own instructional_model content'] = array(
    'name' => 'delete own instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own news content'.
  $permissions['delete own news content'] = array(
    'name' => 'delete own news content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page content'.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own person content'.
  $permissions['delete own person content'] = array(
    'name' => 'delete own person content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own program content'.
  $permissions['delete own program content'] = array(
    'name' => 'delete own program content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own resource content'.
  $permissions['delete own resource content'] = array(
    'name' => 'delete own resource content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own service content'.
  $permissions['delete own service content'] = array(
    'name' => 'delete own service content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own service_instance content'.
  $permissions['delete own service_instance content'] = array(
    'name' => 'delete own service_instance content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'display drupal links'.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'edit any academic_unit content'.
  $permissions['edit any academic_unit content'] = array(
    'name' => 'edit any academic_unit content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any cis_course content'.
  $permissions['edit any cis_course content'] = array(
    'name' => 'edit any cis_course content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any college_services content'.
  $permissions['edit any college_services content'] = array(
    'name' => 'edit any college_services content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any course content'.
  $permissions['edit any course content'] = array(
    'name' => 'edit any course content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any instructional_model content'.
  $permissions['edit any instructional_model content'] = array(
    'name' => 'edit any instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any news content'.
  $permissions['edit any news content'] = array(
    'name' => 'edit any news content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page content'.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any person content'.
  $permissions['edit any person content'] = array(
    'name' => 'edit any person content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any program content'.
  $permissions['edit any program content'] = array(
    'name' => 'edit any program content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any resource content'.
  $permissions['edit any resource content'] = array(
    'name' => 'edit any resource content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any service content'.
  $permissions['edit any service content'] = array(
    'name' => 'edit any service content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any service_instance content'.
  $permissions['edit any service_instance content'] = array(
    'name' => 'edit any service_instance content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit field_abbreviation'.
  $permissions['edit field_abbreviation'] = array(
    'name' => 'edit field_abbreviation',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_access_string'.
  $permissions['edit field_access_string'] = array(
    'name' => 'edit field_access_string',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_additional_notes'.
  $permissions['edit field_additional_notes'] = array(
    'name' => 'edit field_additional_notes',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_cis_ops'.
  $permissions['edit field_cis_ops'] = array(
    'name' => 'edit field_cis_ops',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_color'.
  $permissions['edit field_color'] = array(
    'name' => 'edit field_color',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_coordinators'.
  $permissions['edit field_coordinators'] = array(
    'name' => 'edit field_coordinators',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_course_archive'.
  $permissions['edit field_course_archive'] = array(
    'name' => 'edit field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_cron_key'.
  $permissions['edit field_cron_key'] = array(
    'name' => 'edit field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_data_location'.
  $permissions['edit field_data_location'] = array(
    'name' => 'edit field_data_location',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_distribution'.
  $permissions['edit field_distribution'] = array(
    'name' => 'edit field_distribution',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_first_name'.
  $permissions['edit field_first_name'] = array(
    'name' => 'edit field_first_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_instant_messenger'.
  $permissions['edit field_instant_messenger'] = array(
    'name' => 'edit field_instant_messenger',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_instructional_designer'.
  $permissions['edit field_instructional_designer'] = array(
    'name' => 'edit field_instructional_designer',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_instructor_of_record'.
  $permissions['edit field_instructor_of_record'] = array(
    'name' => 'edit field_instructor_of_record',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_last_name'.
  $permissions['edit field_last_name'] = array(
    'name' => 'edit field_last_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_ldap_campus'.
  $permissions['edit field_ldap_campus'] = array(
    'name' => 'edit field_ldap_campus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_ldap_department'.
  $permissions['edit field_ldap_department'] = array(
    'name' => 'edit field_ldap_department',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_lead_instructor'.
  $permissions['edit field_lead_instructor'] = array(
    'name' => 'edit field_lead_instructor',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_machine_name'.
  $permissions['edit field_machine_name'] = array(
    'name' => 'edit field_machine_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_method_of_access'.
  $permissions['edit field_method_of_access'] = array(
    'name' => 'edit field_method_of_access',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_service_data'.
  $permissions['edit field_service_data'] = array(
    'name' => 'edit field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_services'.
  $permissions['edit field_services'] = array(
    'name' => 'edit field_services',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_syllabus'.
  $permissions['edit field_syllabus'] = array(
    'name' => 'edit field_syllabus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_ta_documents'.
  $permissions['edit field_ta_documents'] = array(
    'name' => 'edit field_ta_documents',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_teaching_assistants'.
  $permissions['edit field_teaching_assistants'] = array(
    'name' => 'edit field_teaching_assistants',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_unit_head'.
  $permissions['edit field_unit_head'] = array(
    'name' => 'edit field_unit_head',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_welcome_letter'.
  $permissions['edit field_welcome_letter'] = array(
    'name' => 'edit field_welcome_letter',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own academic_unit content'.
  $permissions['edit own academic_unit content'] = array(
    'name' => 'edit own academic_unit content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own cis_course content'.
  $permissions['edit own cis_course content'] = array(
    'name' => 'edit own cis_course content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own college_services content'.
  $permissions['edit own college_services content'] = array(
    'name' => 'edit own college_services content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own course content'.
  $permissions['edit own course content'] = array(
    'name' => 'edit own course content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_abbreviation'.
  $permissions['edit own field_abbreviation'] = array(
    'name' => 'edit own field_abbreviation',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_access_string'.
  $permissions['edit own field_access_string'] = array(
    'name' => 'edit own field_access_string',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_additional_notes'.
  $permissions['edit own field_additional_notes'] = array(
    'name' => 'edit own field_additional_notes',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_cis_ops'.
  $permissions['edit own field_cis_ops'] = array(
    'name' => 'edit own field_cis_ops',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_color'.
  $permissions['edit own field_color'] = array(
    'name' => 'edit own field_color',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_coordinators'.
  $permissions['edit own field_coordinators'] = array(
    'name' => 'edit own field_coordinators',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_course_archive'.
  $permissions['edit own field_course_archive'] = array(
    'name' => 'edit own field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_cron_key'.
  $permissions['edit own field_cron_key'] = array(
    'name' => 'edit own field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_data_location'.
  $permissions['edit own field_data_location'] = array(
    'name' => 'edit own field_data_location',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_distribution'.
  $permissions['edit own field_distribution'] = array(
    'name' => 'edit own field_distribution',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_first_name'.
  $permissions['edit own field_first_name'] = array(
    'name' => 'edit own field_first_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_instant_messenger'.
  $permissions['edit own field_instant_messenger'] = array(
    'name' => 'edit own field_instant_messenger',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_instructional_designer'.
  $permissions['edit own field_instructional_designer'] = array(
    'name' => 'edit own field_instructional_designer',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_instructor_of_record'.
  $permissions['edit own field_instructor_of_record'] = array(
    'name' => 'edit own field_instructor_of_record',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_last_name'.
  $permissions['edit own field_last_name'] = array(
    'name' => 'edit own field_last_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_ldap_campus'.
  $permissions['edit own field_ldap_campus'] = array(
    'name' => 'edit own field_ldap_campus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_ldap_department'.
  $permissions['edit own field_ldap_department'] = array(
    'name' => 'edit own field_ldap_department',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_lead_instructor'.
  $permissions['edit own field_lead_instructor'] = array(
    'name' => 'edit own field_lead_instructor',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_machine_name'.
  $permissions['edit own field_machine_name'] = array(
    'name' => 'edit own field_machine_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_method_of_access'.
  $permissions['edit own field_method_of_access'] = array(
    'name' => 'edit own field_method_of_access',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_service_data'.
  $permissions['edit own field_service_data'] = array(
    'name' => 'edit own field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_services'.
  $permissions['edit own field_services'] = array(
    'name' => 'edit own field_services',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_syllabus'.
  $permissions['edit own field_syllabus'] = array(
    'name' => 'edit own field_syllabus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_ta_documents'.
  $permissions['edit own field_ta_documents'] = array(
    'name' => 'edit own field_ta_documents',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_teaching_assistants'.
  $permissions['edit own field_teaching_assistants'] = array(
    'name' => 'edit own field_teaching_assistants',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_unit_head'.
  $permissions['edit own field_unit_head'] = array(
    'name' => 'edit own field_unit_head',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_welcome_letter'.
  $permissions['edit own field_welcome_letter'] = array(
    'name' => 'edit own field_welcome_letter',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own instructional_model content'.
  $permissions['edit own instructional_model content'] = array(
    'name' => 'edit own instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own news content'.
  $permissions['edit own news content'] = array(
    'name' => 'edit own news content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own page content'.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own person content'.
  $permissions['edit own person content'] = array(
    'name' => 'edit own person content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own program content'.
  $permissions['edit own program content'] = array(
    'name' => 'edit own program content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own resource content'.
  $permissions['edit own resource content'] = array(
    'name' => 'edit own resource content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own service content'.
  $permissions['edit own service content'] = array(
    'name' => 'edit own service content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own service_instance content'.
  $permissions['edit own service_instance content'] = array(
    'name' => 'edit own service_instance content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'field hidden administer'.
  $permissions['field hidden administer'] = array(
    'name' => 'field hidden administer',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_hidden',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'import wysiwyg templates'.
  $permissions['import wysiwyg templates'] = array(
    'name' => 'import wysiwyg templates',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'wysiwyg_template',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'manipulate all queues'.
  $permissions['manipulate all queues'] = array(
    'name' => 'manipulate all queues',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: 'manipulate queues'.
  $permissions['manipulate queues'] = array(
    'name' => 'manipulate queues',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: 'masquerade as admin'.
  $permissions['masquerade as admin'] = array(
    'name' => 'masquerade as admin',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'masquerade as any user'.
  $permissions['masquerade as any user'] = array(
    'name' => 'masquerade as any user',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'masquerade as user'.
  $permissions['masquerade as user'] = array(
    'name' => 'masquerade as user',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'rename features'.
  $permissions['rename features'] = array(
    'name' => 'rename features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'replicate entities'.
  $permissions['replicate entities'] = array(
    'name' => 'replicate entities',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'replicate_ui',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'search',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'show format selection for accessibility_test'.
  $permissions['show format selection for accessibility_test'] = array(
    'name' => 'show format selection for accessibility_test',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for field_collection_item'.
  $permissions['show format selection for field_collection_item'] = array(
    'name' => 'show format selection for field_collection_item',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for lti_tool_provider_consumer'.
  $permissions['show format selection for lti_tool_provider_consumer'] = array(
    'name' => 'show format selection for lti_tool_provider_consumer',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for node'.
  $permissions['show format selection for node'] = array(
    'name' => 'show format selection for node',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for user'.
  $permissions['show format selection for user'] = array(
    'name' => 'show format selection for user',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format tips'.
  $permissions['show format tips'] = array(
    'name' => 'show format tips',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show more format tips link'.
  $permissions['show more format tips link'] = array(
    'name' => 'show more format tips link',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'switch section context'.
  $permissions['switch section context'] = array(
    'name' => 'switch section context',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'cis_service_connection',
  );

  // Exported permission: 'unique_field_perm_admin'.
  $permissions['unique_field_perm_admin'] = array(
    'name' => 'unique_field_perm_admin',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'unique_field',
  );

  // Exported permission: 'unique_field_perm_bypass'.
  $permissions['unique_field_perm_bypass'] = array(
    'name' => 'unique_field_perm_bypass',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'unique_field',
  );

  // Exported permission: 'use PHP for title patterns'.
  $permissions['use PHP for title patterns'] = array(
    'name' => 'use PHP for title patterns',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'auto_nodetitle',
  );

  // Exported permission: 'use add another'.
  $permissions['use add another'] = array(
    'name' => 'use add another',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'addanother',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use ctools import'.
  $permissions['use ctools import'] = array(
    'name' => 'use ctools import',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'ctools',
  );

  // Exported permission: 'use text format textbook_editor'.
  $permissions['use text format textbook_editor'] = array(
    'name' => 'use text format textbook_editor',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view accessibility tests'.
  $permissions['view accessibility tests'] = array(
    'name' => 'view accessibility tests',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'accessibility',
  );

  // Exported permission: 'view author options'.
  $permissions['view author options'] = array(
    'name' => 'view author options',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view body options'.
  $permissions['view body options'] = array(
    'name' => 'view body options',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view comment preview button'.
  $permissions['view comment preview button'] = array(
    'name' => 'view comment preview button',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view comment settings'.
  $permissions['view comment settings'] = array(
    'name' => 'view comment settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view delete button'.
  $permissions['view delete button'] = array(
    'name' => 'view delete button',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view field_abbreviation'.
  $permissions['view field_abbreviation'] = array(
    'name' => 'view field_abbreviation',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_access_string'.
  $permissions['view field_access_string'] = array(
    'name' => 'view field_access_string',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_additional_notes'.
  $permissions['view field_additional_notes'] = array(
    'name' => 'view field_additional_notes',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_cis_ops'.
  $permissions['view field_cis_ops'] = array(
    'name' => 'view field_cis_ops',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_color'.
  $permissions['view field_color'] = array(
    'name' => 'view field_color',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_coordinators'.
  $permissions['view field_coordinators'] = array(
    'name' => 'view field_coordinators',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_course_archive'.
  $permissions['view field_course_archive'] = array(
    'name' => 'view field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_cron_key'.
  $permissions['view field_cron_key'] = array(
    'name' => 'view field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_data_location'.
  $permissions['view field_data_location'] = array(
    'name' => 'view field_data_location',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_distribution'.
  $permissions['view field_distribution'] = array(
    'name' => 'view field_distribution',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_first_name'.
  $permissions['view field_first_name'] = array(
    'name' => 'view field_first_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_instant_messenger'.
  $permissions['view field_instant_messenger'] = array(
    'name' => 'view field_instant_messenger',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_instructional_designer'.
  $permissions['view field_instructional_designer'] = array(
    'name' => 'view field_instructional_designer',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_instructor_of_record'.
  $permissions['view field_instructor_of_record'] = array(
    'name' => 'view field_instructor_of_record',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_last_name'.
  $permissions['view field_last_name'] = array(
    'name' => 'view field_last_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_ldap_campus'.
  $permissions['view field_ldap_campus'] = array(
    'name' => 'view field_ldap_campus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_ldap_department'.
  $permissions['view field_ldap_department'] = array(
    'name' => 'view field_ldap_department',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_lead_instructor'.
  $permissions['view field_lead_instructor'] = array(
    'name' => 'view field_lead_instructor',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_machine_name'.
  $permissions['view field_machine_name'] = array(
    'name' => 'view field_machine_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_method_of_access'.
  $permissions['view field_method_of_access'] = array(
    'name' => 'view field_method_of_access',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_service_data'.
  $permissions['view field_service_data'] = array(
    'name' => 'view field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_services'.
  $permissions['view field_services'] = array(
    'name' => 'view field_services',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_syllabus'.
  $permissions['view field_syllabus'] = array(
    'name' => 'view field_syllabus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_ta_documents'.
  $permissions['view field_ta_documents'] = array(
    'name' => 'view field_ta_documents',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_teaching_assistants'.
  $permissions['view field_teaching_assistants'] = array(
    'name' => 'view field_teaching_assistants',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_unit_head'.
  $permissions['view field_unit_head'] = array(
    'name' => 'view field_unit_head',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_welcome_letter'.
  $permissions['view field_welcome_letter'] = array(
    'name' => 'view field_welcome_letter',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view lmsless bar'.
  $permissions['view lmsless bar'] = array(
    'name' => 'view lmsless bar',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'cis_lmsless',
  );

  // Exported permission: 'view lmsless cis link'.
  $permissions['view lmsless cis link'] = array(
    'name' => 'view lmsless cis link',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'cis_lmsless',
  );

  // Exported permission: 'view lti info'.
  $permissions['view lti info'] = array(
    'name' => 'view lti info',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'lti_tool_provider',
  );

  // Exported permission: 'view menu options'.
  $permissions['view menu options'] = array(
    'name' => 'view menu options',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view own field_abbreviation'.
  $permissions['view own field_abbreviation'] = array(
    'name' => 'view own field_abbreviation',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_access_string'.
  $permissions['view own field_access_string'] = array(
    'name' => 'view own field_access_string',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_additional_notes'.
  $permissions['view own field_additional_notes'] = array(
    'name' => 'view own field_additional_notes',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_cis_ops'.
  $permissions['view own field_cis_ops'] = array(
    'name' => 'view own field_cis_ops',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_color'.
  $permissions['view own field_color'] = array(
    'name' => 'view own field_color',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_coordinators'.
  $permissions['view own field_coordinators'] = array(
    'name' => 'view own field_coordinators',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_course_archive'.
  $permissions['view own field_course_archive'] = array(
    'name' => 'view own field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_cron_key'.
  $permissions['view own field_cron_key'] = array(
    'name' => 'view own field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_data_location'.
  $permissions['view own field_data_location'] = array(
    'name' => 'view own field_data_location',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_distribution'.
  $permissions['view own field_distribution'] = array(
    'name' => 'view own field_distribution',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_first_name'.
  $permissions['view own field_first_name'] = array(
    'name' => 'view own field_first_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_instant_messenger'.
  $permissions['view own field_instant_messenger'] = array(
    'name' => 'view own field_instant_messenger',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_instructional_designer'.
  $permissions['view own field_instructional_designer'] = array(
    'name' => 'view own field_instructional_designer',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_instructor_of_record'.
  $permissions['view own field_instructor_of_record'] = array(
    'name' => 'view own field_instructor_of_record',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_last_name'.
  $permissions['view own field_last_name'] = array(
    'name' => 'view own field_last_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_ldap_campus'.
  $permissions['view own field_ldap_campus'] = array(
    'name' => 'view own field_ldap_campus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_ldap_department'.
  $permissions['view own field_ldap_department'] = array(
    'name' => 'view own field_ldap_department',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_lead_instructor'.
  $permissions['view own field_lead_instructor'] = array(
    'name' => 'view own field_lead_instructor',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_machine_name'.
  $permissions['view own field_machine_name'] = array(
    'name' => 'view own field_machine_name',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_method_of_access'.
  $permissions['view own field_method_of_access'] = array(
    'name' => 'view own field_method_of_access',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_service_data'.
  $permissions['view own field_service_data'] = array(
    'name' => 'view own field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_services'.
  $permissions['view own field_services'] = array(
    'name' => 'view own field_services',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_syllabus'.
  $permissions['view own field_syllabus'] = array(
    'name' => 'view own field_syllabus',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_ta_documents'.
  $permissions['view own field_ta_documents'] = array(
    'name' => 'view own field_ta_documents',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_teaching_assistants'.
  $permissions['view own field_teaching_assistants'] = array(
    'name' => 'view own field_teaching_assistants',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_unit_head'.
  $permissions['view own field_unit_head'] = array(
    'name' => 'view own field_unit_head',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_welcome_letter'.
  $permissions['view own field_welcome_letter'] = array(
    'name' => 'view own field_welcome_letter',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view path options'.
  $permissions['view path options'] = array(
    'name' => 'view path options',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view preview button'.
  $permissions['view preview button'] = array(
    'name' => 'view preview button',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view revision information'.
  $permissions['view revision information'] = array(
    'name' => 'view revision information',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view revision log textarea'.
  $permissions['view revision log textarea'] = array(
    'name' => 'view revision log textarea',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view submit button'.
  $permissions['view submit button'] = array(
    'name' => 'view submit button',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view teaser controls'.
  $permissions['view teaser controls'] = array(
    'name' => 'view teaser controls',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'system',
  );

  // Exported permission: 'view user delete button'.
  $permissions['view user delete button'] = array(
    'name' => 'view user delete button',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'jammer',
  );

  return $permissions;
}
