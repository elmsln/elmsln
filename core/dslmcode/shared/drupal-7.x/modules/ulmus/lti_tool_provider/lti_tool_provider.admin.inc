<?php

/**
 * @file
 * Admin forms for LTI Tool Provider module.
 */


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
function lti_tool_provider_user_attributes($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('LTI Context to User Attribute Mapping'),
    '#description' => 'Choose the user attributes to be mapped from each LTI context variable.',
  );
  $fields_array = _lti_tool_provider_retrieve_user_field_types('TEXT');
  $lis_list = lti_tool_provider_user_mapping_lis_details();
  $saved_settings = variable_get('lti_tool_provider_user_attribute_mapping', array());
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
    $value = $saved_settings[$detail];
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

/**
 * Validation for the user attributes form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_user_attributes_validate($form, &$form_state) {
  $check = TRUE;
  $lis_list = lti_tool_provider_user_mapping_lis_details();
  $field_options = _lti_tool_provider_retrieve_user_field_types('TEXT');
  $counters = array();
  foreach ($field_options as $field => $desc) {
    $counters[$field] = 0;
  }
  foreach ($lis_list as $key => $variable) {
    $counters[$form_state['values']['mapping'][$key]['attribute']]++;
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
function lti_tool_provider_user_attributes_submit($form, &$form_state) {
  $lis_list = lti_tool_provider_user_mapping_lis_details();
  $settings = array();
  foreach ($lis_list as $key => $lis) {
    $setting[$lis] = $form_state['values']['mapping'][$key]['attribute'];
  }
  variable_set('lti_tool_provider_user_attribute_mapping', $setting);
  drupal_set_message(t('User attribute mapping saved.'));
}

/**
 * Admin form for the global roles.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_global_roles($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Map LTI Roles to Global Drupal Roles'),
    '#description' => t('Map each LTI role to a global Drupal role.'),
  );
  $select_roles = user_roles(TRUE, NULL);
  $old_role_array = variable_get('lti_tool_provider_global_role_array');
  $form['roles'] = array(
    '#tree' => TRUE,
    '#theme' => 'table',
    '#header' => array(t('LTI Roles'), t('Global Roles')),
    '#rows' => array(),
  );
  foreach (lti_tool_provider_get_lti_roles() as $role) {
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
    '#submit' => array('lti_tool_provider_global_roles_submit'),
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
function lti_tool_provider_global_roles_submit($form, &$form_state) {
  $settings = array();
  foreach (lti_tool_provider_get_lti_roles() as $key => $role) {
    $settings[$role] = $form_state['values']['roles'][$key]['global_role'];
  }
  variable_set('lti_tool_provider_global_role_array', $settings);
  drupal_set_message(t('LTI global roles mapping saved.'));
}

/**
 * Generate the consumer admin form.
 *
 * @return array
 *   The form array.
 */
function lti_tool_provider_consumers_admin() {
  $content = array();
  $content[] = array(
    '#type' => 'item',
    '#markup' => t('Administration page for LTI Tool Consumers.'),
  );
  $content[] = array(
    '#type' => 'item',
    '#markup' => l(t('Add a new LTI Tool Consumer'), 'lti_tool_provider_consumer/add'),
  );
  $content['table'] = array();
  // Load all of our entities.
  $consumers = lti_tool_provider_consumer_load_multiple();
  $content['consumer_table'] = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => array(
      t('ID'),
      t('Consumer'),
      t('Key'),
      t('Secret'),
      t('Domain'),
      t('Dummy Account'),
      t('Alt. User'),
      t('Alt. Email'),
      t('Date Joined'),
      t('Operations'),
    ),
  );
  $destination = drupal_get_destination();
  $loop_counter = 0;
  foreach ($consumers as $key => $consumer) {

    // Create tabular rows for our entities.
    $id = $consumer->lti_tool_provider_consumer_id;
    // This statement can create url to view individual keys.
    $consumer_name = array(
      '#type' => 'link',
      '#title' => t('@consumer', array('@consumer' => $consumer->lti_tool_provider_consumer_consumer)),
      '#href' => 'lti_tool_provider_consumer/' . $consumer->lti_tool_provider_consumer_id . '/view',
      '#options' => array('query' => $destination),
    );
    $key = $consumer->lti_tool_provider_consumer_key;
    $secret = $consumer->lti_tool_provider_consumer_secret;
    $domain = $consumer->lti_tool_provider_consumer_domain;
    $dummy_pref = lti_tool_provider_trans_bool($consumer->lti_tool_provider_consumer_dummy_pref);
    $alt_user_id = $consumer->lti_tool_provider_consumer_alternative_user_id_field;
    $alt_email = $consumer->lti_tool_provider_consumer_alternative_email_field;
    $date_joined = format_date($consumer->date_joined);
    // Build a list of all the operations for the current consumer.
    $operations = array(
      'edit' => array(
        '#type' => 'link',
        '#title' => t('edit'),
        '#href' => 'lti_tool_provider_consumer/' . $consumer->lti_tool_provider_consumer_id . '/edit',
        '#options' => array('query' => $destination),
      ),
      'nbsp' => array('#markup' => '&nbsp;&nbsp;'),
      'delete' => array(
        '#type' => 'link',
        '#title' => t('delete'),
        '#href' => 'lti_tool_provider_consumer/' . $consumer->lti_tool_provider_consumer_id . '/delete',
        '#options' => array('query' => $destination),
      ),
    );
    $content['consumer_table'][] = array(
      'id' => &$id,
      'Consumer' => &$consumer_name,
      'Key' => &$key,
      'Secret' => &$secret,
      'Domain' => &$domain,
      'Dummy_Pref' => &$dummy_pref,
      'alternative_user_id_field' => &$alt_user_id,
      'alternative_email_field' => &$alt_email,
      'Date Joined' => &$date_joined,
      'operations' => &$operations,
    );
    $content['consumer_table']['#rows'][] = array(
      array('data' => &$id),
      array('data' => &$consumer_name),
      array('data' => &$key),
      array('data' => &$secret),
      array('data' => &$domain),
      array('data' => &$dummy_pref),
      array('data' => &$alt_user_id),
      array('data' => &$alt_email),
      array('data' => &$date_joined),
      array('data' => &$operations),
    );
    unset($id);
    unset($consumer_name);
    unset($key);
    unset($secret);
    unset($domain);
    unset($dummy_pref);
    unset($alt_user_id);
    unset($alt_email);
    unset($date_joined);
    unset($operations);
  }
  $content['consumer_table']['#empty'] = t('No LTITP Consumer entities currently exist.');
  return $content;
}

/**
 * Add a consumer.
 *
 * @return array
 *   A consumer add form.
 */
function lti_tool_provider_consumer_add() {
  // Create a basic entity structure to be used and passed to the
  // validation and submission functions.
  $entity = entity_get_controller('lti_tool_provider_consumer')->create();
  return drupal_get_form('lti_tool_provider_consumer_form', $entity);
}

/**
 * Generate the consumer entity form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 * @param object $consumer
 *   The consumer entity to display.
 *
 * @return array
 *   The form array.
 */
function lti_tool_provider_consumer_form($form, &$form_state, $consumer) {

  if (!isset($form_state['#consumer'])) {
    $form_state['#consumer'] = $consumer;
  }
  $form['lti_tool_provider_consumer_consumer'] = array(
    '#type' => 'textfield',
    '#title' => t('Consumer'),
    '#required' => TRUE,
    '#default_value' => $consumer->lti_tool_provider_consumer_consumer,
  );
  $form['lti_tool_provider_consumer_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#required' => TRUE,
    '#default_value' => $consumer->lti_tool_provider_consumer_key,
  );
  $form['lti_tool_provider_consumer_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret'),
    '#required' => TRUE,
    '#default_value' => $consumer->lti_tool_provider_consumer_secret,
  );
  $form['lti_tool_provider_consumer_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#required' => FALSE,
    '#default_value' => $consumer->lti_tool_provider_consumer_domain,
  );
  $form['lti_tool_provider_consumer_dummy_pref'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use a dummy account for unidentified users'),
    '#default_value' => $consumer->lti_tool_provider_consumer_dummy_pref,
  );
  $form['lti_tool_provider_consumer_alternative_user_id_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Alternative User ID Field'),
    '#description' => t('The LTI field to get the users ID from if you dont want to use the "user_id" field. You can determine the proper field to use by viewing the LTI Info. Some examples are: "lis_person_sourcedid", "custom_canvas_user_login_id", "lis_person_contact_email_primary" '),
    '#default_value' => $consumer->lti_tool_provider_consumer_alternative_user_id_field,
  );
  $form['lti_tool_provider_consumer_alternative_email_field'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternative Email Field'),
      '#description' => t('The LTI field to get the users email from if you dont want to use the "primary_email" field. This is useful if the primary email may not be your schools email. Some examples are: "lis_person_sourcedid", "custom_canvas_user_login_id" '),
      '#default_value' => $consumer->lti_tool_provider_consumer_alternative_email_field,
  );
  $form['lti_tool_provider_consumer_id'] = array(
    '#type' => 'value',
    '#value' => $consumer->lti_tool_provider_consumer_id,
  );
  $form['lti_tool_provider_consumer'] = array(
    '#type' => 'value',
    '#value' => $consumer,
  );
  field_attach_form('lti_tool_provider_consumer', $consumer, $form, $form_state);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  if ($consumer->lti_tool_provider_consumer_id != 0) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('lti_tool_provider_consumer_form_delete_submit'),
      '#weight' => 200,
    );
  }

  return $form;
}

/**
 * Validate the consumer entity form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_consumer_form_validate($form, &$form_state) {
  $check_key = FALSE;
  $check_domain = FALSE;
  $new_consumer = $form_state['values']['lti_tool_provider_consumer_id'];
  if ($new_consumer == 0) {
    // Create.
    $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'lti_tool_provider_consumer')
    ->propertyCondition('lti_tool_provider_consumer_key', $form_state['values']['lti_tool_provider_consumer_key']);
    $result = $query->execute();
    if (empty($result)) {
      $check_key = TRUE;
    }
    if ($form_state['values']['lti_tool_provider_consumer_domain'] == '') {
      $check_domain = TRUE;
    }
    else {
      $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'lti_tool_provider_consumer')
      ->propertyCondition('lti_tool_provider_consumer_domain', $form_state['values']['lti_tool_provider_consumer_domain']);
      $result = $query->execute();
      if (empty($result)) {
        $check_domain = TRUE;
      }
    }
  }
  else {
    // Edit or delete.
    $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'lti_tool_provider_consumer')
    ->propertyCondition('lti_tool_provider_consumer_key', $form_state['values']['lti_tool_provider_consumer_key'])
    ->propertyCondition('lti_tool_provider_consumer_id', $form_state['values']['lti_tool_provider_consumer_id'], '!=');
    $result = $query->execute();
    if (empty($result)) {
      $check_key = TRUE;
    }
    if ($form_state['values']['lti_tool_provider_consumer_domain'] == '') {
      $check_domain = TRUE;
    }
    else {
      $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'lti_tool_provider_consumer')
      ->propertyCondition('lti_tool_provider_consumer_domain', $form_state['values']['lti_tool_provider_consumer_domain'])
      ->propertyCondition('lti_tool_provider_consumer_id', $form_state['values']['lti_tool_provider_consumer_id'], '!=');
      $result = $query->execute();
      if (empty($result)) {
        $check_domain = TRUE;
      }
    }
  }
  if ($check_key && $check_domain) {
    $submitted = (object) $form_state['values']['lti_tool_provider_consumer'];
    field_attach_form_validate('lti_tool_provider_consumer', $submitted, $form, $form_state);
  }
  if (!$check_domain) {
    form_set_error('lti_tool_provider_consumer_domain', t('Domains must be unique.'));
  }
  if (!$check_key) {
    form_set_error('lti_tool_provider_consumer_key', t('Keys must be unique.'));
  }
  $pattern = '/([A-Z0-9 _!@#$%=+*.?<>\/\r\n])/';
  $domain_char_check = preg_match($pattern, $form_state['values']['lti_tool_provider_consumer_domain']);
  if ($domain_char_check) {
    form_set_error('lti_tool_provider_consumer_domain', t('The domain must not contain numeric value, special characters, spaces and upper cases'));
  }
}

/**
 * Update or create a consumer entity.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_consumer_form_submit($form, &$form_state) {

  $entity = $form_state['values']['lti_tool_provider_consumer'];
  $entity->lti_tool_provider_consumer_key = $form_state['values']['lti_tool_provider_consumer_key'];
  $entity->lti_tool_provider_consumer_secret = $form_state['values']['lti_tool_provider_consumer_secret'];
  $entity->lti_tool_provider_consumer_consumer = $form_state['values']['lti_tool_provider_consumer_consumer'];
  $entity->lti_tool_provider_consumer_domain = $form_state['values']['lti_tool_provider_consumer_domain'];
  $entity->lti_tool_provider_consumer_dummy_pref = $form_state['values']['lti_tool_provider_consumer_dummy_pref'];
  $entity->lti_tool_provider_consumer_alternative_user_id_field = $form_state['values']['lti_tool_provider_consumer_alternative_user_id_field'];
  $entity->lti_tool_provider_consumer_alternative_email_field = $form_state['values']['lti_tool_provider_consumer_alternative_email_field'];
  if ($form_state['values']['lti_tool_provider_consumer_dummy_pref'] && $form['lti_tool_provider_consumer_dummy_pref']['#default_value'] == 0) {
    lti_tool_provider_create_dummy_account($form_state['values']['lti_tool_provider_consumer_domain']);
    drupal_set_message(t('Dummy user has been created.'));
  }
  else {
    if ($form_state['values']['lti_tool_provider_consumer_id'] != 0  && $form_state['values']['lti_tool_provider_consumer_dummy_pref'] == 0 && $form['lti_tool_provider_consumer_dummy_pref']['#default_value'] == 1) {
      lti_tool_provider_remove_dummy_account($form_state['values']['lti_tool_provider_consumer_domain']);
      drupal_set_message(t('Dummy user has been removed.'));
    }
  }
  field_attach_submit('lti_tool_provider_consumer', $entity, $form, $form_state);

  $entity = lti_tool_provider_consumer_save($entity);
  drupal_set_message(t('Configurations saved.'));
  $form_state['redirect'] = 'admin/config/lti-tool-provider/lti-tool-consumers';
}

/**
 * Button submit function: handle the 'Delete' button on the consumer form.
 */
function lti_tool_provider_consumer_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $consumer = $form_state['#consumer'];
  $form_state['redirect'] = array('admin/config/lti-tool-provider/lti-tool-consumer/' . $consumer->lti_tool_provider_consumer_id . '/delete', array('query' => $destination));
}

/**
 * Edit or delete a consumer entity.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_consumer_edit_delete($form, &$form_state) {
  $entity = $form_state['values']['lti_tool_provider_consumer'];
  lti_tool_provider_remove_dummy_account($entity->lti_tool_provider_consumer_domain);
  lti_tool_provider_consumer_delete($entity);
  drupal_set_message(t('The entity %lti_tool_provider_consumer_consumer (ID %lti_tool_provider_consumer_id) has been deleted.', array(
  '%lti_tool_provider_consumer_consumer' => $entity->lti_tool_provider_consumer_consumer,
  '%lti_tool_provider_consumer_id' => $entity->lti_tool_provider_consumer_id,
  '%lti_tool_provider_consumer_alternative_user_id_field' => $entity->lti_tool_provider_consumer_alternative_user_id_field,
  '%lti_tool_provider_consumer_alternative_email_field' => $entity->lti_tool_provider_consumer_alternative_email_field,
  )));
  $form_state['redirect'] = 'admin/config/lti-tool-provider/lti-tool-consumers';
}

/**
 * View a single consumer entity.
 *
 * @param object $entity
 *   The consumer to view.
 * @param string $view_mode
 *   The requested view mode.
 *
 * @return array
 *   The content array from the entity.
 */
function lti_tool_provider_consumer_view($entity, $view_mode = 'tweaky') {
  $entity_type = 'lti_tool_provider_consumer';
  $entity->content = array(
    '#view_mode' => $view_mode,
  );
  field_attach_prepare_view($entity_type, array($entity->lti_tool_provider_consumer_id => $entity), $view_mode);
  entity_prepare_view($entity_type, array($entity->lti_tool_provider_consumer_id => $entity));
  $entity->content += field_attach_view($entity_type, $entity, $view_mode);
  $entity->content['lti_tool_provider_consumer_consumer'] = array(
    '#type' => 'item',
    '#title' => t('Consumer'),
    '#markup' => $entity->lti_tool_provider_consumer_consumer,
  );
  $entity->content['lti_tool_provider_consumer_key'] = array(
    '#type' => 'item',
    '#title' => t('Key'),
    '#markup' => $entity->lti_tool_provider_consumer_key,
  );
  $entity->content['lti_tool_provider_consumer_secret'] = array(
    '#type' => 'item',
    '#title' => t('Secret'),
    '#markup' => $entity->lti_tool_provider_consumer_secret,
  );
  $entity->content['lti_tool_provider_consumer_domain'] = array(
    '#type' => 'item',
    '#title' => t('Domain'),
    '#markup' => $entity->lti_tool_provider_consumer_domain,
  );
  $entity->content['lti_tool_provider_consumer_dummy_pref'] = array(
    '#type' => 'item',
    '#title' => t('Activate Dummy Account'),
    '#markup' => lti_tool_provider_trans_bool($entity->lti_tool_provider_consumer_dummy_pref),
  );
  $entity->content['lti_tool_provider_consumer_alternative_user_id_field'] = array(
      '#type' => 'item',
      '#title' => t('Alternative user_id Field'),
      '#markup' => $entity->lti_tool_provider_consumer_alternative_user_id_field,
  );
  $entity->content['lti_tool_provider_consumer_alternative_email_field'] = array(
      '#type' => 'item',
      '#title' => t('Alternative email Field'),
      '#markup' => $entity->lti_tool_provider_consumer_alternative_email_field,
  );
  $entity->content['date_joined'] = array(
    '#type' => 'item',
    '#title' => t('Date Joined'),
    '#markup' => format_date($entity->date_joined),
  );
  global $language;
  $langcode = $language->language;
  $entity->content['#language'] = $langcode;
  module_invoke_all('entity_view', $entity, $entity_type, $view_mode, $langcode);
  drupal_alter(array('lti_tool_provider_consumer_view', 'entity_view'),
  $entity->content, $entity_type);
  return $entity->content;
}

/**
 * Confirms the delete action.
 *
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Confirm form array.
 */
function lti_tool_provider_consumer_confirm_delete_form($form, &$form_state, $consumer) {
  $form['consumer_delete'] = array(
    '#type' => 'value',
    '#value' => $consumer,
  );
  return confirm_form($form,
    t('Are you sure you want to delete the consumer @name?', array('@name' => $consumer->lti_tool_provider_consumer_consumer)),
    'admin/config/lti-tool-provider/lti-tool-consumer/' . $consumer->lti_tool_provider_consumer_id,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel'));
}

/**
 * Submit handler for the consumer form delete.
 *
 * @param array $form
 *   Form array
 * @param array $form_state
 *   Form state array
 */
function lti_tool_provider_consumer_confirm_delete_form_submit($form, &$form_state) {
  $consumer = $form['consumer_delete']['#value'];
  lti_tool_provider_consumer_delete($consumer);
  drupal_set_message(t('The consumer @name has been deleted.', array(
  '@name' => $consumer->lti_tool_provider_consumer_consumer,
  )));
  $form_state['redirect'] = 'admin/config/lti-tool-provider/lti-tool-consumers';
}
