<?php
/**
 * @file
 * editorial_perms.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function editorial_perms_defaultconfig_features() {
  return array(
    'editorial_perms' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function editorial_perms_defaultconfig_user_default_permissions() {
  $permissions = array();

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

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
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
      'guest' => 'guest',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access iframe version'.
  $permissions['access iframe version'] = array(
    'name' => 'access iframe version',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'entity_iframe',
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
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource og_membership'.
  $permissions['access resource og_membership'] = array(
    'name' => 'access resource og_membership',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource og_membership_type'.
  $permissions['access resource og_membership_type'] = array(
    'name' => 'access resource og_membership_type',
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

  // Exported permission: 'create editorial_blog_post content'.
  $permissions['create editorial_blog_post content'] = array(
    'name' => 'create editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create editorial_journal_entry content'.
  $permissions['create editorial_journal_entry content'] = array(
    'name' => 'create editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create editorial_story_seeds content'.
  $permissions['create editorial_story_seeds content'] = array(
    'name' => 'create editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any editorial_blog_post content'.
  $permissions['delete any editorial_blog_post content'] = array(
    'name' => 'delete any editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any editorial_journal_entry content'.
  $permissions['delete any editorial_journal_entry content'] = array(
    'name' => 'delete any editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any editorial_story_seeds content'.
  $permissions['delete any editorial_story_seeds content'] = array(
    'name' => 'delete any editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own editorial_blog_post content'.
  $permissions['delete own editorial_blog_post content'] = array(
    'name' => 'delete own editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own editorial_journal_entry content'.
  $permissions['delete own editorial_journal_entry content'] = array(
    'name' => 'delete own editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own editorial_story_seeds content'.
  $permissions['delete own editorial_story_seeds content'] = array(
    'name' => 'delete own editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any editorial_blog_post content'.
  $permissions['edit any editorial_blog_post content'] = array(
    'name' => 'edit any editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any editorial_journal_entry content'.
  $permissions['edit any editorial_journal_entry content'] = array(
    'name' => 'edit any editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any editorial_story_seeds content'.
  $permissions['edit any editorial_story_seeds content'] = array(
    'name' => 'edit any editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own editorial_blog_post content'.
  $permissions['edit own editorial_blog_post content'] = array(
    'name' => 'edit own editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own editorial_journal_entry content'.
  $permissions['edit own editorial_journal_entry content'] = array(
    'name' => 'edit own editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own editorial_story_seeds content'.
  $permissions['edit own editorial_story_seeds content'] = array(
    'name' => 'edit own editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'switch section context'.
  $permissions['switch section context'] = array(
    'name' => 'switch section context',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'cis_service_connection',
  );

  // Exported permission: 'view cis shortcode'.
  $permissions['view cis shortcode'] = array(
    'name' => 'view cis shortcode',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'cis_shortcodes',
  );

  // Exported permission: 'view iframe embed code'.
  $permissions['view iframe embed code'] = array(
    'name' => 'view iframe embed code',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'entity_iframe',
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
    ),
    'module' => 'cis_lmsless',
  );

  return $permissions;
}
