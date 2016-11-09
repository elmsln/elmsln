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
  $alignment_options = array(t("Taxonomy Term"), t("Constant Variable"), t("None"));
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
    '#description' => t('Identifies the submitter, publisher and author of a Learning Registry resource document.'),
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
  $form['learning_registry_lrmi_alignment'] = array(
    '#type' => 'fieldset', 
    '#title' => t('LRMI/DCMI Alignment'),
  );
  $form['learning_registry_lrmi_alignment']['standarts'] = array(
	'#title' => t('Standards'),
    '#type' => 'fieldset', 
	'#prefix' => '<div id="lrmi-standarts">',
    '#suffix' => '</div>',
  );
  $option = variable_get('learning_registry_standarts-select', 2);
  $form['learning_registry_lrmi_alignment']['standarts']['learning_registry_standarts-select'] = array(
    '#type' => 'select',
    '#title' => t('Standards:'),
    '#options' => $alignment_options,
	'#default_value' => $option,
    '#ajax' => array(
      'callback' => 'learning_registry_form_lrmi_alignment_standarts_ajax_callback',
      'wrapper' => 'lrmi-standarts',
      'method' => 'replace',
      'effect' => 'none',
    ),
	'#prefix' => '<div style="float:left;margin-right:20px;">',
    '#suffix' => '</div>',
  );
  learning_registry_form_lrmi_alignment_standarts($form, $form_state, $option);
  $form['learning_registry_lrmi_alignment']['levels'] = array(
	'#title' => t('Grade Levels'),
    '#type' => 'fieldset', 
	'#prefix' => '<div id="lrmi-levels">',
    '#suffix' => '</div>',
  );
  $option = variable_get('learning_registry_levels-select', 2);
  $form['learning_registry_lrmi_alignment']['levels']['learning_registry_levels-select'] = array(
    '#type' => 'select',
    '#title' => t('Grade Levels:'),
    '#options' => $alignment_options,
	'#default_value' => $option,
    '#ajax' => array(
      'callback' => 'learning_registry_form_lrmi_alignment_levels_ajax_callback',
      'wrapper' => 'lrmi-levels',
      'method' => 'replace',
      'effect' => 'none',
    ),
	'#prefix' => '<div style="float:left;margin-right:20px;">',
    '#suffix' => '</div>',
  );
  learning_registry_form_lrmi_alignment_levels($form, $form_state, $option);
  $form['learning_registry_lrmi_alignment']['subjects'] = array(
	'#title' => t('Subjects'),
    '#type' => 'fieldset', 
	'#prefix' => '<div id="lrmi-subjects">',
    '#suffix' => '</div>',
  );
  $option = variable_get('learning_registry_subjects-select', 2);
  $form['learning_registry_lrmi_alignment']['subjects']['learning_registry_subjects-select'] = array(
    '#type' => 'select',
    '#title' => t('Subjects:'),
    '#options' => $alignment_options,
	'#default_value' => $option,
    '#ajax' => array(
      'callback' => 'learning_registry_form_lrmi_alignment_subjects_ajax_callback',
      'wrapper' => 'lrmi-subjects',
      'method' => 'replace',
      'effect' => 'none',
    ),
	'#prefix' => '<div style="float:left;margin-right:20px;">',
    '#suffix' => '</div>',
  );
  learning_registry_form_lrmi_alignment_subjects($form, $form_state, $option);
  $form['learning_registry_lrmi_alignment']['type'] = array(
	'#title' => t('Learning Resource Type'),
    '#type' => 'fieldset', 
	'#prefix' => '<div id="lrmi-type">',
    '#suffix' => '</div>',
  );
  $option = variable_get('learning_registry_type-select', 2);
  $form['learning_registry_lrmi_alignment']['type']['learning_registry_type-select'] = array(
    '#type' => 'select',
    '#title' => t('Learning Resource Type:'),
    '#options' => $alignment_options,
	'#default_value' => $option,
    '#ajax' => array(
      'callback' => 'learning_registry_form_lrmi_alignment_type_ajax_callback',
      'wrapper' => 'lrmi-type',
      'method' => 'replace',
      'effect' => 'none',
    ),
	'#prefix' => '<div style="float:left;margin-right:20px;">',
    '#suffix' => '</div>',
  );
  learning_registry_form_lrmi_alignment_type($form, $form_state, $option);
  $form['#submit'][] = 'learning_registry_form_submit_callback';
  return system_settings_form($form);
}

/**
 * learning_registry_content_form() submit callback.
 * @param array $form
 *   The array that describes the configuration form.
 * @param array $form_state
 *   The values of the array.
 *
 */
 
function learning_registry_form_submit_callback(&$form, &$form_state){
	$form_state['rebuild'] = TRUE;
}

/**
 * Helper functions for each "LRMI/DCMI Alignment" fieldset in the learning_registry_content_form().
 *
 * @param array $form
 *   The array that describes the configuration form.
 * @param array $form_state
 *   The values of the array.
 * @param $option
 *   option from the left dropdown of current fieldset.
 */
 
 /*
 *	"Sandarts" feldset:
 */
 
 function learning_registry_form_lrmi_alignment_standarts(&$form, $form_state, $option = null){
	$option = isset($form_state['values']['learning_registry_standarts-select']) ? $form_state['values']['learning_registry_standarts-select'] : $option;
	switch ($option){
	  case '0':
		$vocabularies = taxonomy_get_vocabularies();
		foreach ($vocabularies as $vocab) {
            $items[$vocab->vid]= $vocab->name;
		}
		$form['learning_registry_lrmi_alignment']['standarts']['learning_registry_standarts-term-select'] = array(
			'#type' => 'select',
			'#title' => t("Vocabulary:"),
			'#options' => $items,
			'#prefix' => '<div style="float:left;margin-right:20px;">',
			'#suffix' => '</div>',
		);
		$form['learning_registry_lrmi_alignment']['standarts']['learning_registry_standarts-framework'] = array(
			'#type' => 'textfield',
			'#title' => t('Framework:'),
			'#size' => 30,
			'#maxlength' => 30,
			'#default_value' => variable_get('learning_registry_standarts-framework', NULL),
			'#prefix' => '<div style="width:200px;display:inline-block;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '1':
		$form['learning_registry_lrmi_alignment']['standarts']['learning_registry_standarts-variable'] = array(
			'#type' => 'textfield',
			'#title' => t("Variable:"),
			'#size' => 30,
			'#maxlength' => 30,
			'#default_value' => variable_get('learning_registry_standarts-variable', NULL),
			'#prefix' => '<div style="width:200px;display:inline-block;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '2':
	  break;
	}
	return $form['learning_registry_lrmi_alignment']['standarts'];
}

 /*
 *	"Levels" feldset:
 */
 
function learning_registry_form_lrmi_alignment_levels(&$form, $form_state, $option = null){
	$option = isset($form_state['complete form']['learning_registry_lrmi_alignment']['levels']['learning_registry_levels-select']['#value']) ? $form_state['complete form']['learning_registry_lrmi_alignment']['levels']['learning_registry_levels-select']['#value'] : $option;
	switch ($option){
	  case '0':
		$vocabularies = taxonomy_get_vocabularies();
		foreach ($vocabularies as $vocab) {
            $items[$vocab->vid]= $vocab->name;
		}
		$form['learning_registry_lrmi_alignment']['levels']['learning_registry_levels-term-select'] = array(
			'#type' => 'select',
			'#title' => t("Vocabulary:"),
			'#options' => $items,
			'#prefix' => '<div style="float:left;margin-right:20px;">',
			'#suffix' => '</div>',
		);
		$form['learning_registry_lrmi_alignment']['levels']['learning_registry_levels-framework'] = array(
			'#type' => 'textfield',
			'#title' => t('Framework:'),
			'#size' => 30,
			'#maxlength' => 30,
			'#default_value' => variable_get('learning_registry_levels-framework', null),
			'#prefix' => '<div style="width:200px;display:inline-block;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '1':
		$form['learning_registry_lrmi_alignment']['levels']['learning_registry_levels-variable'] = array(
			'#type' => 'textfield',
			'#title' => t("Variable:"),
			'#size' => 30,
			'#maxlength' => 30,
			'#default_value' => variable_get('learning_registry_levels-variable', null),
			'#prefix' => '<div style="width:200px;display:inline-block;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '2':
	  break;
	}
	return $form['learning_registry_lrmi_alignment']['levels'];
}

 /*
 *	"Subjects" feldset:
 */

function learning_registry_form_lrmi_alignment_subjects(&$form, $form_state, $option = null){
	$option = isset($form_state['complete form']['learning_registry_lrmi_alignment']['subjects']['learning_registry_subjects-select']['#value']) ? $form_state['complete form']['learning_registry_lrmi_alignment']['subjects']['learning_registry_subjects-select']['#value'] : $option;
	switch ($option){
	  case '0':
		$vocabularies = taxonomy_get_vocabularies();
		foreach ($vocabularies as $vocab) {
            $items[$vocab->vid]= $vocab->name;
		}
		$form['learning_registry_lrmi_alignment']['subjects']['learning_registry_subjects-term-select'] = array(
			'#type' => 'select',
			'#title' => t("Vocabulary:"),
			'#options' => $items,
			'#prefix' => '<div style="float:left;margin-right:20px;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '1':
		$form['learning_registry_lrmi_alignment']['subjects']['learning_registry_subjects-variable'] = array(
			'#type' => 'textfield',
			'#title' => t("Variable:"),
			'#size' => 30,
			'#maxlength' => 30,
			'#default_value' => variable_get('learning_registry_subjects-variable', null),
			'#prefix' => '<div style="width:200px;display:inline-block;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '2':
	  break;
	}
	return $form['learning_registry_lrmi_alignment']['subjects'];
}

 /*
 *	"Type" feldset:
 */

function learning_registry_form_lrmi_alignment_type(&$form, $form_state, $option = null){
	$option = isset($form_state['complete form']['learning_registry_lrmi_alignment']['type']['learning_registry_type-select']['#value']) ? $form_state['complete form']['learning_registry_lrmi_alignment']['type']['learning_registry_type-select']['#value'] : $option;
	switch ($option){
	  case '0':
		$vocabularies = taxonomy_get_vocabularies();
		foreach ($vocabularies as $vocab) {
            $items[$vocab->vid]= $vocab->name;
		}
		$form['learning_registry_lrmi_alignment']['type']['learning_registry_type-term-select'] = array(
			'#type' => 'select',
			'#title' => t("Vocabulary:"),
			'#options' => $items,
			'#prefix' => '<div style="float:left;margin-right:20px;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '1':
		$form['learning_registry_lrmi_alignment']['type']['learning_registry_type-variable'] = array(
			'#type' => 'textfield',
			'#title' => t("Variable:"),
			'#size' => 30,
			'#maxlength' => 30,
			'#default_value' => variable_get('learning_registry_type-variable', null),
			'#prefix' => '<div style="width:200px;display:inline-block;">',
			'#suffix' => '</div>',
		);
	  break;
	  case '2':
	  break;
	}
	return $form['learning_registry_lrmi_alignment']['type'];
}


 

/**
 * "LRMI/DCMI Alignment" ajax callbacks for learning_registry_content_form().
 *
 * @param array $form
 *   The array that describes the configuration form.
 * @param array $form_state
 *   The values of the array.
 */
 

function learning_registry_form_lrmi_alignment_standarts_ajax_callback(&$form, $form_state){
	return $form['learning_registry_lrmi_alignment']['standarts'];
}

function learning_registry_form_lrmi_alignment_levels_ajax_callback(&$form, $form_state){
	return $form['learning_registry_lrmi_alignment']['levels'];
}

function learning_registry_form_lrmi_alignment_subjects_ajax_callback(&$form, $form_state){
	return $form['learning_registry_lrmi_alignment']['subjects'];
}

function learning_registry_form_lrmi_alignment_type_ajax_callback(&$form, $form_state){
	return $form['learning_registry_lrmi_alignment']['type'];
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
  if((!$salt)){
    drupal_set_message(t('Warning: the Learning Registry module cannot publish until the settings below are configured. To obtain these values, visit http://[Learning Registry node URL]/auth.'), 'warning', TRUE);
  }
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
  $key = (isset($variable['key'])) ? $variable['key'] : '';
  $secret = (isset($variable['secret'])) ? $variable['secret'] : '';
  $variable['key'] = rtrim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $salt, $key, MCRYPT_MODE_ECB));
  $variable['secret'] = rtrim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $salt, $secret, MCRYPT_MODE_ECB));
  return $variable;
}
