<?php
/**
 * @file
 * ecd_entityforms.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ecd_entityforms_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'entityform-ecd_access-field_account_request'
  $field_instances['entityform-ecd_access-field_account_request'] = array(
    'bundle' => 'ecd_access',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The account name you are requesting access for.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_account_request',
    'label' => 'Account Request',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'entityform-ecd_access-field_course_access'
  $field_instances['entityform-ecd_access-field_course_access'] = array(
    'bundle' => 'ecd_access',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'What course would you like to grant access to?',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_course_access',
    'label' => 'Course access',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'entityform-ecd_access-field_documentation'
  $field_instances['entityform-ecd_access-field_documentation'] = array(
    'bundle' => 'ecd_access',
    'deleted' => 0,
    'description' => 'Any documentation about why this access request should be granted. This can be a screenshot, a word document, an email, anything that would justify this granting of access for record keeping purposes.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_documentation',
    'label' => 'Documentation',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'access_documentation',
      'file_extensions' => 'txt jpg png doc docx',
      'max_filesize' => '1MB',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'entityform-ecd_access-field_role'
  $field_instances['entityform-ecd_access-field_role'] = array(
    'bundle' => 'ecd_access',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Role you wish to grant this person',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_role',
    'label' => 'Role',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'entityform-ecd_access-field_system_access'
  $field_instances['entityform-ecd_access-field_system_access'] = array(
    'bundle' => 'ecd_access',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Systems you want this user to have access to',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_system_access',
    'label' => 'System access',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Account Request');
  t('Any documentation about why this access request should be granted. This can be a screenshot, a word document, an email, anything that would justify this granting of access for record keeping purposes.');
  t('Course access');
  t('Documentation');
  t('Role');
  t('Role you wish to grant this person');
  t('System access');
  t('Systems you want this user to have access to');
  t('The account name you are requesting access for.');
  t('What course would you like to grant access to?');

  return $field_instances;
}
