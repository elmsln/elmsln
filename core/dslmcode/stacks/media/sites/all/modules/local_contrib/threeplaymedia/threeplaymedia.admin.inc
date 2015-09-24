<?php

/**
 * Callback for admin settings.
 */
function threeplaymedia_admin_settings() {
	$form = array();
	$form['threeplaymedia_api'] = array(
	  '#type' => 'textfield',
		'#title' => t('3PlayMedia API key'),
		'#default_value' => variable_get('threeplaymedia_api', ''),
		'#required' => TRUE,
	);
	$form['threeplaymedia_secret'] = array(
	  '#type' => 'textfield',
		'#title' => t('3PlayMedia API secret'),
		'#default_value' => variable_get('threeplaymedia_secret', ''),
		'#required' => TRUE,
	);
	return system_settings_form($form);
}