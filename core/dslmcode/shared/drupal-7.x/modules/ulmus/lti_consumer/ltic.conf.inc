<?php

/**
 * Implements hook_form().
 */
function ltic_config_form($form, &$form_state) {
  $form['tool_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tool Settings'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['tool_settings']['ltic_tool_description'] = [
    '#type' => 'textfield',
    '#title' => t('Description'),
    //'#description' => t('Utilization vs. time curve'),
    '#default_value' => variable_get('ltic_tool_description', ''),
    '#required' => TRUE,
      //'#weight' => 1,
  ];
  $form['tool_settings']['ltic_tool_launch_url'] = [
    '#type' => 'textfield',
    '#title' => t('Launch URL'),
    //'#description' => t('the maximum utilization'),
    '#default_value' => variable_get('ltic_tool_launch_url', ''),
    '#required' => TRUE,
      //'#weight' => 1,
  ];
  $form['tool_settings']['ltic_tool_consumer_key'] = [
    '#type' => 'textfield',
    '#title' => t('Consumer Key'),
    //'#description' => t('the maximum utilization'),
    '#default_value' => variable_get('ltic_tool_consumer_key', ''),
    '#required' => TRUE,
      //'#weight' => 1,
  ];
  $form['tool_settings']['ltic_tool_consumer_secret'] = [
    '#type' => 'textfield',
    '#title' => t('Consumer secret'),
    //'#description' => t('the maximum utilization'),
    '#default_value' => variable_get('ltic_tool_consumer_secret', ''),
    '#required' => TRUE,
      //'#weight' => 1,
  ];
  $form['tool_settings']['ltic_tool_custom_param'] = [
    '#type' => 'textarea',
    '#title' => t('Custom Parameters'),
    //'#description' => t('the maximum utilization'),
    '#default_value' => variable_get('ltic_tool_custom_param', ''),
      //'#required' => TRUE,
      //'#weight' => 1,
  ];
  $form['tool_settings']['ltic_tool_supress_email'] = [
    '#type' => 'checkbox',
    '#title' => t('Suppress email'),
    '#description' => t('Stops email details being sent with launch details.'),
    '#default_value' => variable_get('ltic_tool_supress_email', FALSE),
      //'#required' => TRUE,
      //'#weight' => 1,
  ];
  $form['tool_settings']['ltic_tool_supress_ui_details'] = [
    '#type' => 'checkbox',
    '#title' => t('Suppress user details'),
    '#description' => t('Stops all user identifiable information from being sent.'),
    '#default_value' => variable_get('ltic_tool_supress_ui_details', FALSE),
  ];
  $form['outcomes_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('LTI Outcomes'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];
  $form['outcomes_settings']['ltic_outcomes_launch_path'] = [
    '#type' => 'textfield',
    '#title' => t('Outcomes Launch Path'),
    '#description' => t('This is the path that callbacks for outcomes are passed to.'),
    '#default_value' => variable_get('ltic_outcomes_launch_path', 'ltic_outcomes'),
  ];
  $form['module_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('LTI Module Settings'),
    '#weight' => 3,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['module_settings']['ltic_tool_launch_path'] = [
    '#type' => 'textfield',
    '#title' => t('Launch Path'),
    '#default_value' => variable_get('ltic_tool_launch_path', 'ltic/test'),
  ];
  $form['module_settings']['ltic_tool_locale'] = [
    '#type' => 'textfield',
    '#title' => t('Locale'),
    '#default_value' => variable_get('ltic_tool_locale', 'en-UK'),
  ];

  $form['module_fur_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('LTI Further Settings'),
    '#weight' => 4,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['module_fur_settings']['ltic_ltiversion'] = [
    '#type' => 'textfield',
    '#title' => t('LTI Version Code'),
    '#default_value' => variable_get('ltic_ltiversion', "LTI-1p0"),
  ];
  $form['module_fur_settings']['ltic_tool_consumer_info_product_family_code'] = [
    '#type' => 'textfield',
    '#title' => t('Product Family Code'),
    '#default_value' => variable_get('ltic_tool_consumer_info_product_family_code', 'ltic_drupal7'),
  ];

  $form['module_fur_settings']['ltic_tool_consumer_info_version'] = [
    '#type' => 'textfield',
    '#title' => t('Consumer Version Information'),
    '#default_value' => variable_get('ltic_tool_consumer_info_version', "0.1"),
  ];

  $form['module_fur_settings']['ltic_tool_consumer_instance_name'] = [
    '#type' => 'textfield',
    '#title' => t('Consumer Instance Name'),
    '#default_value' => variable_get('ltic_tool_consumer_instance_name', 'LTI Module Drupal 7'),
  ];

  $form['module_fur_settings']['ltic_tool_consumer_instance_description'] = [
    '#type' => 'textfield',
    '#title' => t('Consumer Instance Description'),
    '#default_value' => variable_get('ltic_tool_consumer_instance_description', 'A generic LTI Module Drupal 7'),
  ];
  $form['module_fur_settings']['ltic_tool_consumer_instance_guid'] = [
    '#type' => 'textfield',
    '#title' => t('Consumer Instance GUID'),
    '#default_value' => variable_get('ltic_tool_consumer_instance_guid', 'drupal.lti.module'),
  ];
  if(!ltic_check_user_attributes()){
    drupal_set_message(t('You need to create mappings for first and surname (!link)',array('!link'=>l('User Attributes','admin/config/ltic/user-attributes'))), 'warning');
  }
  return system_settings_form($form);
}

/**
 * Admin form for the global roles.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function ltic_global_roles($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Map LTI Roles to Global Drupal Roles'),
    '#description' => t('Map each LTI role to a global Drupal role.'),
  );
  $select_roles = user_roles(TRUE, NULL);
  $old_role_array = variable_get('ltic_global_role_array');
  $form['roles'] = array(
    '#tree' => TRUE,
    '#theme' => 'table',
    '#header' => array(t('LTI Roles'), t('Global Roles')),
    '#rows' => array(),
  );
  foreach (ltic_lti_roles() as $role) {
    $lti_role = array(
      '#type' => 'item',
      '#title' => $role,
    );
    $global_role = array(
      '#type' => 'select',
      '#options' => $select_roles,
    );
    if (isset($old_role_array[$role]) && isset($select_roles[$old_role_array[$role]])) {
      $global_role['#default_value'] = $old_role_array[$role];
    }
    else {
      $global_role['#default_value'] = array_search(DRUPAL_AUTHENTICATED_RID, $select_roles);
    }
    $form['roles'][] = array(
      'lti_role' => &$lti_role,
      'global_role' => &$global_role,
    );
    $form['roles']['#rows'][] = array(
      array('data' => &$lti_role),
      array('data' => &$global_role),
    );
    unset($lti_role);
    unset($global_role);
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Global Roles'),
    '#submit' => array('ltic_global_roles_submit'),
  );
  return $form;
}

/**
 * Submit handler for the global roles form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function ltic_global_roles_submit($form, &$form_state) {
  $settings = array();
  foreach (ltic_lti_roles() as $key => $role) {
    $settings[$role] = $form_state['values']['roles'][$key]['global_role'];
  }
  variable_set('ltic_global_role_array', $settings);
  drupal_set_message(t('LTI global roles mapping saved.'));
}

/**
 * Get the LTI roles.
 *
 * @return array
 *   An array containing the roles.
 */
function ltic_lti_roles() {
  return [
    'Learner',
    'Instructor',
    'ContentDeveloper',
    'Member',
    'Manager',
    'Mentor',
    'Administrator',
    'TeachingAssistant',
  ];
}

/**
 * Menu page callback.
 *
 * Configure settings for mapping user attributes from the
 * LTI context variables.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function ltic_user_attributes($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('LTI Context to User Attribute Mapping'),
    '#description' => 'Choose the user attributes to be mapped from each LTI context variable.',
  );
  // which profile type to add to
  $form['profile_entity_type'] = array(
    '#type' => 'select',
    '#options' => _ltic_user_attribute_bundles(),
    '#default_value' => variable_get('ltic_user_attribute_entity_type', 'user:user'),
    '#title' => t('Destination for user attributes'),
    '#description' => t('Which object / fields should be available for automatically populating values.'),
    '#required' => TRUE,
  );
  $fields_array = _ltic_retrieve_user_field_types('TEXT');
  $lis_list = ltic_user_mapping_lis_details();
  $saved_settings = variable_get('ltic_user_attribute_mapping', array());
  $form['mapping'] = array(
    '#tree' => TRUE,
    '#theme' => 'table',
    '#header' => array(t('LTI Context Variable'), t('User Attribute')),
    '#rows' => array(),
  );
  foreach ($lis_list as $detail) {
    $variable = array(
      '#type' => 'item',
      '#title' => check_plain($detail),
    );
    $value = isset($saved_settings[$detail]) ? $saved_settings[$detail] : '';
    $attribute = array(
      '#type' => 'select',
      '#options' => $fields_array,
      '#default_value' => $value,
    );
    $form['mapping'][] = array(
      'variable' => &$variable,
      'attribute' => &$attribute,
    );
    $form['mapping']['#rows'][] = array(
      array('data' => &$variable),
      array('data' => &$attribute),
    );
    unset($variable);
    unset($attribute);
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save User Attributes'),
  );
  return $form;
}

function ltic_check_user_attributes() {
  $user_att = variable_get('ltic_user_attribute_mapping', array());
  if (!empty($user_att)) {
    if ($user_att['lis_person_name_given'] != 'none' && $user_att['lis_person_name_family'] != 'none') {
      return TRUE;
    }
  }
  return FALSE; 
}

/**
 * Validation for the user attributes form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function ltic_user_attributes_validate($form, &$form_state) {
  $check = TRUE;
  $lis_list = ltic_user_mapping_lis_details();
  $field_options = _ltic_retrieve_user_field_types('TEXT');
  $counters = array();
  foreach ($field_options as $field => $desc) {
    $counters[$field] = 0;
  }
  foreach ($lis_list as $key => $variable) {
    $counters[$form_state['values']['mapping'][$key]['attribute']] ++;
  }
  foreach ($field_options as $field => $desc) {
    if ($field != 'none' && $counters[$field] > 1) {
      $check = FALSE;
      break;
    }
  }
  if (!$check) {
    form_set_error('mapping', t('You may not map multiple values to the same attribute.'));
  }
}

/**
 * Submit handler for the user attributes form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function ltic_user_attributes_submit($form, &$form_state) {
  $lis_list = ltic_user_mapping_lis_details();
  $settings = array();
  // check for a state change on profile type to map to
  if (variable_get('ltic_user_attribute_entity_type', 'user:user') != $form_state['values']['profile_entity_type']) {
    // set value as it has changed
    variable_set('ltic_user_attribute_entity_type', $form_state['values']['profile_entity_type']);
    // set all settings to none as this is a new entity:bundle pair
    foreach ($lis_list as $key => $lis) {
      $setting[$lis] = 'none';
    }
  }
  else {
    foreach ($lis_list as $key => $lis) {
      $setting[$lis] = $form_state['values']['mapping'][$key]['attribute'];
    }
  }
  variable_set('ltic_user_attribute_mapping', $setting);
  drupal_set_message(t('User attribute mapping saved.'));
}
