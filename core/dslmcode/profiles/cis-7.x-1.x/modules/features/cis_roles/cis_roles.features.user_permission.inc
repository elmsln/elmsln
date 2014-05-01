<?php
/**
 * @file
 * cis_roles.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cis_roles_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
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
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
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

  // Exported permission: 'access overlay'.
  $permissions['access overlay'] = array(
    'name' => 'access overlay',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'overlay',
  );

  // Exported permission: 'access private fields'.
  $permissions['access private fields'] = array(
    'name' => 'access private fields',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
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

  // Exported permission: 'access resource node'.
  $permissions['access resource node'] = array(
    'name' => 'access resource node',
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
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Dean' => 'Dean',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'block',
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

  // Exported permission: 'administer field collections'.
  $permissions['administer field collections'] = array(
    'name' => 'administer field collections',
    'roles' => array(
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
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

  // Exported permission: 'administer lti_tool_provider module'.
  $permissions['administer lti_tool_provider module'] = array(
    'name' => 'administer lti_tool_provider module',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'lti_tool_provider',
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

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
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

  // Exported permission: 'cis setup admin options'.
  $permissions['cis setup admin options'] = array(
    'name' => 'cis setup admin options',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'cis_helper',
  );

  // Exported permission: 'create academic_unit content'.
  $permissions['create academic_unit content'] = array(
    'name' => 'create academic_unit content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create course content'.
  $permissions['create course content'] = array(
    'name' => 'create course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_abbreviation'.
  $permissions['create field_abbreviation'] = array(
    'name' => 'create field_abbreviation',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_access_string'.
  $permissions['create field_access_string'] = array(
    'name' => 'create field_access_string',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_additional_notes'.
  $permissions['create field_additional_notes'] = array(
    'name' => 'create field_additional_notes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_color'.
  $permissions['create field_color'] = array(
    'name' => 'create field_color',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_coordinators'.
  $permissions['create field_coordinators'] = array(
    'name' => 'create field_coordinators',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_course_archive'.
  $permissions['create field_course_archive'] = array(
    'name' => 'create field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_cron_key'.
  $permissions['create field_cron_key'] = array(
    'name' => 'create field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_distribution'.
  $permissions['create field_distribution'] = array(
    'name' => 'create field_distribution',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_first_name'.
  $permissions['create field_first_name'] = array(
    'name' => 'create field_first_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_instant_messenger'.
  $permissions['create field_instant_messenger'] = array(
    'name' => 'create field_instant_messenger',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_instructional_designer'.
  $permissions['create field_instructional_designer'] = array(
    'name' => 'create field_instructional_designer',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_instructor_of_record'.
  $permissions['create field_instructor_of_record'] = array(
    'name' => 'create field_instructor_of_record',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_last_name'.
  $permissions['create field_last_name'] = array(
    'name' => 'create field_last_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_ldap_campus'.
  $permissions['create field_ldap_campus'] = array(
    'name' => 'create field_ldap_campus',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_ldap_department'.
  $permissions['create field_ldap_department'] = array(
    'name' => 'create field_ldap_department',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_lead_instructor'.
  $permissions['create field_lead_instructor'] = array(
    'name' => 'create field_lead_instructor',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_machine_name'.
  $permissions['create field_machine_name'] = array(
    'name' => 'create field_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_method_of_access'.
  $permissions['create field_method_of_access'] = array(
    'name' => 'create field_method_of_access',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_service_data'.
  $permissions['create field_service_data'] = array(
    'name' => 'create field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_services'.
  $permissions['create field_services'] = array(
    'name' => 'create field_services',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_syllabus'.
  $permissions['create field_syllabus'] = array(
    'name' => 'create field_syllabus',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_ta_documents'.
  $permissions['create field_ta_documents'] = array(
    'name' => 'create field_ta_documents',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_teaching_assistants'.
  $permissions['create field_teaching_assistants'] = array(
    'name' => 'create field_teaching_assistants',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_unit_head'.
  $permissions['create field_unit_head'] = array(
    'name' => 'create field_unit_head',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_welcome_letter'.
  $permissions['create field_welcome_letter'] = array(
    'name' => 'create field_welcome_letter',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create instructional_model content'.
  $permissions['create instructional_model content'] = array(
    'name' => 'create instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create program content'.
  $permissions['create program content'] = array(
    'name' => 'create program content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create resource content'.
  $permissions['create resource content'] = array(
    'name' => 'create resource content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
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
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any academic_unit content'.
  $permissions['delete any academic_unit content'] = array(
    'name' => 'delete any academic_unit content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any course content'.
  $permissions['delete any course content'] = array(
    'name' => 'delete any course content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any instructional_model content'.
  $permissions['delete any instructional_model content'] = array(
    'name' => 'delete any instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any program content'.
  $permissions['delete any program content'] = array(
    'name' => 'delete any program content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any resource content'.
  $permissions['delete any resource content'] = array(
    'name' => 'delete any resource content',
    'roles' => array(
      'administrator' => 'administrator',
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
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own academic_unit content'.
  $permissions['delete own academic_unit content'] = array(
    'name' => 'delete own academic_unit content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own course content'.
  $permissions['delete own course content'] = array(
    'name' => 'delete own course content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own instructional_model content'.
  $permissions['delete own instructional_model content'] = array(
    'name' => 'delete own instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own program content'.
  $permissions['delete own program content'] = array(
    'name' => 'delete own program content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own resource content'.
  $permissions['delete own resource content'] = array(
    'name' => 'delete own resource content',
    'roles' => array(
      'administrator' => 'administrator',
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

  // Exported permission: 'edit any academic_unit content'.
  $permissions['edit any academic_unit content'] = array(
    'name' => 'edit any academic_unit content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any course content'.
  $permissions['edit any course content'] = array(
    'name' => 'edit any course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any instructional_model content'.
  $permissions['edit any instructional_model content'] = array(
    'name' => 'edit any instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any program content'.
  $permissions['edit any program content'] = array(
    'name' => 'edit any program content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any resource content'.
  $permissions['edit any resource content'] = array(
    'name' => 'edit any resource content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
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
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit boxes'.
  $permissions['edit boxes'] = array(
    'name' => 'edit boxes',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'boxes',
  );

  // Exported permission: 'edit field_abbreviation'.
  $permissions['edit field_abbreviation'] = array(
    'name' => 'edit field_abbreviation',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_access_string'.
  $permissions['edit field_access_string'] = array(
    'name' => 'edit field_access_string',
    'roles' => array(
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_additional_notes'.
  $permissions['edit field_additional_notes'] = array(
    'name' => 'edit field_additional_notes',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_color'.
  $permissions['edit field_color'] = array(
    'name' => 'edit field_color',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_coordinators'.
  $permissions['edit field_coordinators'] = array(
    'name' => 'edit field_coordinators',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_course_archive'.
  $permissions['edit field_course_archive'] = array(
    'name' => 'edit field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_cron_key'.
  $permissions['edit field_cron_key'] = array(
    'name' => 'edit field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_distribution'.
  $permissions['edit field_distribution'] = array(
    'name' => 'edit field_distribution',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_first_name'.
  $permissions['edit field_first_name'] = array(
    'name' => 'edit field_first_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_instant_messenger'.
  $permissions['edit field_instant_messenger'] = array(
    'name' => 'edit field_instant_messenger',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_instructional_designer'.
  $permissions['edit field_instructional_designer'] = array(
    'name' => 'edit field_instructional_designer',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_instructor_of_record'.
  $permissions['edit field_instructor_of_record'] = array(
    'name' => 'edit field_instructor_of_record',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_last_name'.
  $permissions['edit field_last_name'] = array(
    'name' => 'edit field_last_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_ldap_campus'.
  $permissions['edit field_ldap_campus'] = array(
    'name' => 'edit field_ldap_campus',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_ldap_department'.
  $permissions['edit field_ldap_department'] = array(
    'name' => 'edit field_ldap_department',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_lead_instructor'.
  $permissions['edit field_lead_instructor'] = array(
    'name' => 'edit field_lead_instructor',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_machine_name'.
  $permissions['edit field_machine_name'] = array(
    'name' => 'edit field_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_method_of_access'.
  $permissions['edit field_method_of_access'] = array(
    'name' => 'edit field_method_of_access',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_service_data'.
  $permissions['edit field_service_data'] = array(
    'name' => 'edit field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_services'.
  $permissions['edit field_services'] = array(
    'name' => 'edit field_services',
    'roles' => array(
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_syllabus'.
  $permissions['edit field_syllabus'] = array(
    'name' => 'edit field_syllabus',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_ta_documents'.
  $permissions['edit field_ta_documents'] = array(
    'name' => 'edit field_ta_documents',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_teaching_assistants'.
  $permissions['edit field_teaching_assistants'] = array(
    'name' => 'edit field_teaching_assistants',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_unit_head'.
  $permissions['edit field_unit_head'] = array(
    'name' => 'edit field_unit_head',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_welcome_letter'.
  $permissions['edit field_welcome_letter'] = array(
    'name' => 'edit field_welcome_letter',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own academic_unit content'.
  $permissions['edit own academic_unit content'] = array(
    'name' => 'edit own academic_unit content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own course content'.
  $permissions['edit own course content'] = array(
    'name' => 'edit own course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_abbreviation'.
  $permissions['edit own field_abbreviation'] = array(
    'name' => 'edit own field_abbreviation',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_access_string'.
  $permissions['edit own field_access_string'] = array(
    'name' => 'edit own field_access_string',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_additional_notes'.
  $permissions['edit own field_additional_notes'] = array(
    'name' => 'edit own field_additional_notes',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_color'.
  $permissions['edit own field_color'] = array(
    'name' => 'edit own field_color',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_coordinators'.
  $permissions['edit own field_coordinators'] = array(
    'name' => 'edit own field_coordinators',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_course_archive'.
  $permissions['edit own field_course_archive'] = array(
    'name' => 'edit own field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_cron_key'.
  $permissions['edit own field_cron_key'] = array(
    'name' => 'edit own field_cron_key',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_distribution'.
  $permissions['edit own field_distribution'] = array(
    'name' => 'edit own field_distribution',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_first_name'.
  $permissions['edit own field_first_name'] = array(
    'name' => 'edit own field_first_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_instant_messenger'.
  $permissions['edit own field_instant_messenger'] = array(
    'name' => 'edit own field_instant_messenger',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_instructional_designer'.
  $permissions['edit own field_instructional_designer'] = array(
    'name' => 'edit own field_instructional_designer',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_instructor_of_record'.
  $permissions['edit own field_instructor_of_record'] = array(
    'name' => 'edit own field_instructor_of_record',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_last_name'.
  $permissions['edit own field_last_name'] = array(
    'name' => 'edit own field_last_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_ldap_campus'.
  $permissions['edit own field_ldap_campus'] = array(
    'name' => 'edit own field_ldap_campus',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_ldap_department'.
  $permissions['edit own field_ldap_department'] = array(
    'name' => 'edit own field_ldap_department',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_lead_instructor'.
  $permissions['edit own field_lead_instructor'] = array(
    'name' => 'edit own field_lead_instructor',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_machine_name'.
  $permissions['edit own field_machine_name'] = array(
    'name' => 'edit own field_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_method_of_access'.
  $permissions['edit own field_method_of_access'] = array(
    'name' => 'edit own field_method_of_access',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_service_data'.
  $permissions['edit own field_service_data'] = array(
    'name' => 'edit own field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_services'.
  $permissions['edit own field_services'] = array(
    'name' => 'edit own field_services',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_syllabus'.
  $permissions['edit own field_syllabus'] = array(
    'name' => 'edit own field_syllabus',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_ta_documents'.
  $permissions['edit own field_ta_documents'] = array(
    'name' => 'edit own field_ta_documents',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_teaching_assistants'.
  $permissions['edit own field_teaching_assistants'] = array(
    'name' => 'edit own field_teaching_assistants',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_unit_head'.
  $permissions['edit own field_unit_head'] = array(
    'name' => 'edit own field_unit_head',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_welcome_letter'.
  $permissions['edit own field_welcome_letter'] = array(
    'name' => 'edit own field_welcome_letter',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own instructional_model content'.
  $permissions['edit own instructional_model content'] = array(
    'name' => 'edit own instructional_model content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own program content'.
  $permissions['edit own program content'] = array(
    'name' => 'edit own program content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own resource content'.
  $permissions['edit own resource content'] = array(
    'name' => 'edit own resource content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
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
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'masquerade as user'.
  $permissions['masquerade as user'] = array(
    'name' => 'masquerade as user',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'use text format textbook_editor'.
  $permissions['use text format textbook_editor'] = array(
    'name' => 'use text format textbook_editor',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Dean' => 'Dean',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view field_abbreviation'.
  $permissions['view field_abbreviation'] = array(
    'name' => 'view field_abbreviation',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_access_string'.
  $permissions['view field_access_string'] = array(
    'name' => 'view field_access_string',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_additional_notes'.
  $permissions['view field_additional_notes'] = array(
    'name' => 'view field_additional_notes',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_color'.
  $permissions['view field_color'] = array(
    'name' => 'view field_color',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_coordinators'.
  $permissions['view field_coordinators'] = array(
    'name' => 'view field_coordinators',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_course_archive'.
  $permissions['view field_course_archive'] = array(
    'name' => 'view field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_cron_key'.
  $permissions['view field_cron_key'] = array(
    'name' => 'view field_cron_key',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_distribution'.
  $permissions['view field_distribution'] = array(
    'name' => 'view field_distribution',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_first_name'.
  $permissions['view field_first_name'] = array(
    'name' => 'view field_first_name',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_instant_messenger'.
  $permissions['view field_instant_messenger'] = array(
    'name' => 'view field_instant_messenger',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_instructional_designer'.
  $permissions['view field_instructional_designer'] = array(
    'name' => 'view field_instructional_designer',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Dean' => 'Dean',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_instructor_of_record'.
  $permissions['view field_instructor_of_record'] = array(
    'name' => 'view field_instructor_of_record',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_last_name'.
  $permissions['view field_last_name'] = array(
    'name' => 'view field_last_name',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_ldap_campus'.
  $permissions['view field_ldap_campus'] = array(
    'name' => 'view field_ldap_campus',
    'roles' => array(
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_ldap_department'.
  $permissions['view field_ldap_department'] = array(
    'name' => 'view field_ldap_department',
    'roles' => array(
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_lead_instructor'.
  $permissions['view field_lead_instructor'] = array(
    'name' => 'view field_lead_instructor',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_machine_name'.
  $permissions['view field_machine_name'] = array(
    'name' => 'view field_machine_name',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_method_of_access'.
  $permissions['view field_method_of_access'] = array(
    'name' => 'view field_method_of_access',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_service_data'.
  $permissions['view field_service_data'] = array(
    'name' => 'view field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_services'.
  $permissions['view field_services'] = array(
    'name' => 'view field_services',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_syllabus'.
  $permissions['view field_syllabus'] = array(
    'name' => 'view field_syllabus',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_ta_documents'.
  $permissions['view field_ta_documents'] = array(
    'name' => 'view field_ta_documents',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_teaching_assistants'.
  $permissions['view field_teaching_assistants'] = array(
    'name' => 'view field_teaching_assistants',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Dean' => 'Dean',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_unit_head'.
  $permissions['view field_unit_head'] = array(
    'name' => 'view field_unit_head',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_welcome_letter'.
  $permissions['view field_welcome_letter'] = array(
    'name' => 'view field_welcome_letter',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view lti info'.
  $permissions['view lti info'] = array(
    'name' => 'view lti info',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'lti_tool_provider',
  );

  // Exported permission: 'view own field_abbreviation'.
  $permissions['view own field_abbreviation'] = array(
    'name' => 'view own field_abbreviation',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_access_string'.
  $permissions['view own field_access_string'] = array(
    'name' => 'view own field_access_string',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_additional_notes'.
  $permissions['view own field_additional_notes'] = array(
    'name' => 'view own field_additional_notes',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_color'.
  $permissions['view own field_color'] = array(
    'name' => 'view own field_color',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_coordinators'.
  $permissions['view own field_coordinators'] = array(
    'name' => 'view own field_coordinators',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Staff' => 'Staff',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_course_archive'.
  $permissions['view own field_course_archive'] = array(
    'name' => 'view own field_course_archive',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_cron_key'.
  $permissions['view own field_cron_key'] = array(
    'name' => 'view own field_cron_key',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_distribution'.
  $permissions['view own field_distribution'] = array(
    'name' => 'view own field_distribution',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_first_name'.
  $permissions['view own field_first_name'] = array(
    'name' => 'view own field_first_name',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_instant_messenger'.
  $permissions['view own field_instant_messenger'] = array(
    'name' => 'view own field_instant_messenger',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_instructional_designer'.
  $permissions['view own field_instructional_designer'] = array(
    'name' => 'view own field_instructional_designer',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Dean' => 'Dean',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_instructor_of_record'.
  $permissions['view own field_instructor_of_record'] = array(
    'name' => 'view own field_instructor_of_record',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_last_name'.
  $permissions['view own field_last_name'] = array(
    'name' => 'view own field_last_name',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_ldap_campus'.
  $permissions['view own field_ldap_campus'] = array(
    'name' => 'view own field_ldap_campus',
    'roles' => array(
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_ldap_department'.
  $permissions['view own field_ldap_department'] = array(
    'name' => 'view own field_ldap_department',
    'roles' => array(
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_lead_instructor'.
  $permissions['view own field_lead_instructor'] = array(
    'name' => 'view own field_lead_instructor',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_machine_name'.
  $permissions['view own field_machine_name'] = array(
    'name' => 'view own field_machine_name',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Learning Designer' => 'Learning Designer',
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_method_of_access'.
  $permissions['view own field_method_of_access'] = array(
    'name' => 'view own field_method_of_access',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_service_data'.
  $permissions['view own field_service_data'] = array(
    'name' => 'view own field_service_data',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_services'.
  $permissions['view own field_services'] = array(
    'name' => 'view own field_services',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_syllabus'.
  $permissions['view own field_syllabus'] = array(
    'name' => 'view own field_syllabus',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_ta_documents'.
  $permissions['view own field_ta_documents'] = array(
    'name' => 'view own field_ta_documents',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_teaching_assistants'.
  $permissions['view own field_teaching_assistants'] = array(
    'name' => 'view own field_teaching_assistants',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Dean' => 'Dean',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_unit_head'.
  $permissions['view own field_unit_head'] = array(
    'name' => 'view own field_unit_head',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_welcome_letter'.
  $permissions['view own field_welcome_letter'] = array(
    'name' => 'view own field_welcome_letter',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'Coordinator' => 'Coordinator',
      'Instructor' => 'Instructor',
      'Learning Designer' => 'Learning Designer',
      'Staff' => 'Staff',
      'Teaching Assistant' => 'Teaching Assistant',
      'Unit Head' => 'Unit Head',
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  return $permissions;
}
