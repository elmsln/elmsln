<?php

function accessibility_content_admin_form() {
  $form = array();
  
  $form['accessibility_content_auto_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically check page'),
    '#default_value' => variable_get('accessibility_content_auto_check', FALSE),
  );
  
  $form['accessibility_content_show_toggle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show accessibility check toggle'),
    '#default_value' => variable_get('accessibility_content_show_toggle', TRUE),
  );
  
  $form['toggle'] = array(
    '#type' => 'fieldset',
    '#title' => t('Toggle settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['toggle']['accessibility_content_toggle_message_off'] = array(
    '#type' => 'textfield',
    '#title' => t('Message to show when accessibility checking is off'),
    '#default_value' => variable_get('accessibility_content_toggle_message_off', t('Check page for accessibility')),
  );
  
  $form['toggle']['accessibility_content_toggle_message_on'] = array(
    '#type' => 'textfield',
    '#title' => t('Message to show when accessibility checking is on'),
    '#default_value' => variable_get('accessibility_content_toggle_message_on', t('Hide checks for accessibility')),
  );

  $form['accessibility_disabled_form_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message to show when a user is prevented from submitting a form because of accessibility errors'),
    '#default_value' => variable_get('accessibility_disabled_form_message', t('You have been prevented from submitting this form because of the following accessibility errors.')),
    );
  
  return system_settings_form($form);
}