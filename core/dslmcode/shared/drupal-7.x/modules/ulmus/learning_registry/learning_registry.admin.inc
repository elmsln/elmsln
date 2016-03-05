<?php

/**
 * @file
 * Administration callbacks for the learning_registry module
 */

/**
 * Form constructor to configure learning_registry module.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function learning_registry_admin_settings($form, &$form_state) {
  // Get node types with internal names as keys and "friendly" names as
  // values.
  $options = node_type_get_types();
  $type_names = array();
  $node_fields = array();

  foreach ($options as $option) {
    $type_names[$option->type] = check_plain($option->name);
    $node_fields[$option->type] = field_info_instances('node', $option->type);
  }
  
  $form = array();

  $form['learning_registry_node_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Learning Registry node URL'),
    '#size' => 128,
    '#maxlength' => 1024,
    '#default_value' => variable_get('learning_registry_node_url', NULL),
    '#description' => t('The URL of the Learning Registry node.'),
    '#required' => TRUE,
  );

  $form['learning_registry_submitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Submitter'),
    '#size' => 128,
    '#maxlength' => 1024,
    '#default_value' => variable_get('learning_registry_submitter', NULL),
    '#description' => t('Identifies the submitter of a Learning Registry resource document.'),
    '#required' => TRUE,
  );

  $form['learning_registry_tos'] = array(
    '#type' => 'textfield',
    '#title' => t('Terms of service URL'),
    '#size' => 128,
    '#maxlength' => 1024,
    '#default_value' => variable_get('learning_registry_tos', NULL),
    '#description' => t('Specifies the terms of service URL for the items submitted to the Learning Registry.'),
    '#required' => TRUE,
  );

  $form['learning_registry_queuing'] = array(
    '#type' => 'radios',
    '#title' => t('Immediate or queued publishing'),
    '#default_value' => variable_get('learning_registry_queuing', 0),
    '#description' => t('Selects if submissions to the Learning Registry will publish immediately or queued in a batch to publish when cron executes.'),
    '#options' => array(
      LEARNING_REGISTRY_QUEUE_IMMEDIATE => t('Immediate'),
      LEARNING_REGISTRY_QUEUE_QUEUED => t('Queued'),
    ),
    '#required' => TRUE,
  );

  $form['learning_registry_url_type'] = array(
    '#type' => 'radios',
    '#title' => t('Publish URL type'),
    '#default_value' => variable_get('learning_registry_url_type', 0),
    '#description' => t('Determines the URL to the published Drupal node.  Node ID is the internal Drupal node (node/1234).  Node alias is the alias provided for the node (blog/this-is-a-test).'),
    '#options' => array(t('Node ID'), t('Node alias')),
    '#required' => TRUE,
  );

  $form['learning_registry_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Publish metadata for these content types'),
    '#options' => $type_names,
    '#default_value' => variable_get('learning_registry_node_types', array()),
    '#description' => t('Metadata for these node types will be published to the specified Learning Registry node.'),
  );
  
  $form['learning_registry_submitter_type'] = array(
    '#type' => 'radios',
    '#title' => t('Submitter Type'),
    '#options' => drupal_map_assoc(array(t('Person'), t('Organization'))),
    '#default_value' => variable_get('learning_registry_submitter_type', 0),
  );
  
   $form['learning_registry_allow_keywords'] = array(
    '#type' => 'checkbox',
    '#title' => t('Publish Taxonomy Tags as keywords'),
    '#default_value' => variable_get('learning_registry_allow_keywords', 1),
//  '#description' => t(''),
  );
  
  foreach ($type_names as $type_key => $type_name) {
    if (count($node_fields[$type_key])) {
      $checkboxes = array();
      // Loop through and build a list of checkboxes.
      foreach ($node_fields[$type_key] as $field) {
        $checkboxes[$field['field_name']] = check_plain($field['label']);
      }

      $type_name = check_plain($type_name);
    }
  }

  return system_settings_form($form);
}


/**
 * Form validation handler for learning_registry_content_form().
 *
 * @param array $form
 *   The array that describes the configuration form.
 * @param array $form_state
 *   The values of the array.
 */
function learning_registry_admin_settings_validate($form, &$form_state) {
  $lr_node_url = $form_state['values']['learning_registry_node_url'];
  if (!valid_url($lr_node_url, TRUE)) {
    form_set_error('learning_registry_node_url', t('Please provide a valid Learning Registry node URL.'));
  }

  $tos_url = $form_state['values']['learning_registry_tos'];
  if (!valid_url($tos_url, TRUE)) {
    form_set_error('learning_registry_node_url', t('Please provide a valid Terms of Service URL.'));
  }

}
/**
 * Form builder function for OAuth settings.
 */
function learning_registry_admin__oauth_settings($form, &$form_state) {

  $salt = variable_get('learning_registry_oauth_salt', '');
  $oauth_consumer = learning_registry_admin_var_get('learning_registry_oauth_consumer');
  $oauth_token = learning_registry_admin_var_get('learning_registry_oauth_token');
  
  $form['learning_registry_oauth_consumer']['#tree'] = TRUE;
  $form['learning_registry_oauth_token']['#tree'] = TRUE;
  $form['learning_registry_oauth_consumer']['key'] = array(
    '#title' => t('Consumer Key'),
    '#type' => 'textfield',
	'#default_value' => $oauth_consumer['key'],
    '#required' => TRUE,
  );
  $form['learning_registry_oauth_consumer']['secret'] = array(
    '#title' => t('Consumer Secret'),
    '#type' => 'textfield',
	'#default_value' => $oauth_consumer['secret'],
    '#required' => TRUE,
  );
  $form['learning_registry_oauth_token']['key'] = array(
    '#title' => t('Token Key'),
    '#type' => 'textfield',
	'#default_value' => $oauth_token['key'],
    '#required' => TRUE,
  );
  $form['learning_registry_oauth_token']['secret'] = array(
    '#title' => t('Token Secret'),
    '#type' => 'textfield',
	'#default_value' => $oauth_token['secret'],
    '#required' => TRUE,
  );
  $form['learning_registry_oauth_salt'] = array(
    '#title' => t('Salt'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => $salt,
    '#description' => t('This is a salt for the encryption and decryption of keys.'),
  );
  return system_settings_form($form);
}

/**
 * Validation handler for OAuth settings form.
 */
function learning_registry_admin__oauth_settings_validate($form, &$form_state) {
  $form_values = $form_state['values'];
  $consumer = $form_values['learning_registry_oauth_consumer'];
  $token = $form_values['learning_registry_oauth_token'];
  $salt = md5($form_values['learning_registry_oauth_salt']);
  
  // Encrypt the consumer key and secret.
  $learning_registry_oauth_consumer_key = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $salt, $consumer['key'], MCRYPT_MODE_ECB);
  $learning_registry_oauth_consumer_secret = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $salt, $consumer['secret'], MCRYPT_MODE_ECB);

  // Encrypt the token key and secret.
  $learning_registry_oauth_token_key = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $salt, $token['key'], MCRYPT_MODE_ECB);
  $learning_registry_oauth_token_secret = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $salt, $token['secret'], MCRYPT_MODE_ECB);

  $form_state['values']['learning_registry_oauth_consumer'] = array(
    'key' => $learning_registry_oauth_consumer_key,
    'secret' => $learning_registry_oauth_consumer_secret,
  );

  $form_state['values']['learning_registry_oauth_token'] = array(
    'key' => $learning_registry_oauth_token_key,
    'secret' => $learning_registry_oauth_token_secret,
  );
}
/**
 * Wrapper for the variable_get function.
 *
 * @param string $name
 *   The name of the variable to fetch
 * @param string $default
 *   A default value if the variable does not exist
 *
 * @return mixed
 *   Returns the variable.
 */
function learning_registry_admin_var_get($name, $default = '') {
  $variable = variable_get($name, $default);
  $salt = md5(variable_get('learning_registry_oauth_salt', ''));
  $variable['key'] = rtrim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $salt, $variable['key'], MCRYPT_MODE_ECB));
  $variable['secret'] = rtrim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $salt, $variable['secret'], MCRYPT_MODE_ECB));
  return $variable;
}
