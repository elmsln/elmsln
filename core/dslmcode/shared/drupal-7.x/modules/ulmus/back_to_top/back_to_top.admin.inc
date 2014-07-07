<?php

/**
 * @file
 * Contains the administration pages for Back To Top.
 *
 */

function back_to_top_settings($form_state) {

  // Include Farbtastic color picker library and other necessary resources.
  drupal_add_library('system', 'farbtastic');
  drupal_add_js(drupal_get_path('module', 'back_to_top') . '/js/back_to_top.admin.js');
  drupal_add_css(drupal_get_path('module', 'back_to_top') . '/css/back_to_top.admin.css');

  $form['back_to_top_prevent_on_mobile'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prevent on mobile and touch devices'),
    '#description' => t('Do you want to prevent Back To Top on touch devices?'),
    '#default_value' => variable_get('back_to_top_prevent_on_mobile', TRUE),
  );
  $form['back_to_top_prevent_in_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prevent on administration pages and node edit'),
    '#description' => t('Do you want to prevent Back To Top on admin pages?'),
    '#default_value' => variable_get('back_to_top_prevent_in_admin', TRUE),
  );
  $form['back_to_top_prevent_in_front'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prevent on front page'),
    '#description' => t('Do you want to prevent Back To Top on front page?'),
    '#default_value' => variable_get('back_to_top_prevent_in_front', FALSE),
  );
  $form['back_to_top_button_trigger'] = array(
    '#type' => 'textfield',
    '#title' => t('Trigger'),
    '#description' => t('Set the number of pixel which trigger the Back To Top button default 100'),
    '#default_value' => variable_get('back_to_top_button_trigger', 100),
    '#size' => 10,
    '#maxlength' => 4,
  );
  $form['back_to_top_button_place'] = array(
    '#title' => t('Placement'),
    '#description' => t('Where should the Back To Top button appear?'),
    '#type' => 'select',
    '#options' => array(
      1 => t('Bottom right'),
      2 => t('Bottom left'),
      3 => t('Botton center'),
      4 => t('Top right'),
      5 => t('Top left'),
      6 => t('Top center'),
      7 => t('Mid right'),
      8 => t('Mid left'),
      9 => t('Mid center'),
    ),
    '#default_value' => variable_get('back_to_top_button_place', 1),
  );
  $form['back_to_top_button_text'] = array(
    '#type' => 'textfield',
    '#title' => 'Button text',
    '#description' => 'Set the text of the Back To Top button',
    '#default_value' => variable_get('back_to_top_button_text', "Back to top"),
    '#size' => 30,
    '#maxlength' => 30,
  );
  $form['back_to_top_button_type'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want Back To Top to use a PNG-24 image or a Text/Css button?'),
    '#options' => array(
    'image' => t('Image (default)'),
    'text' => t('Text/Css')
    ),
    '#default_value' => variable_get('back_to_top_button_type', 'image'),
  );

  // Wrap Text/Css button settings in a fieldset.
  $form['text_button'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text/Css button settings'),
    '#collapsible' => TRUE,
    '#collapsed' => ($form['back_to_top_button_type']['#default_value'] == 'image' ? TRUE : FALSE),
  );
  $form['text_button']['back_to_top_bg_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color'),
    '#description' => t('Button background color default #F7F7F7'),
    '#default_value' => variable_get('back_to_top_bg_color', '#F7F7F7'),
    '#size' => 10,
    '#maxlength' => 7,
    '#suffix' => '<div class="color-field" id="back_to_top_bg_color"></div>',
  );
  $form['text_button']['back_to_top_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border color'),
    '#description' => t('Border color default #CCCCCC'),
    '#default_value' => variable_get('back_to_top_border_color', '#CCCCCC'),
    '#size' => 10,
    '#maxlength' => 7,
    '#suffix' => '<div class="color-field" id="back_to_top_border_color"></div>',
  );
  $form['text_button']['back_to_top_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Hover color'),
    '#description' => t('Hover color default #EEEEEE'),
    '#default_value' => variable_get('back_to_top_hover_color', '#EEEEEE'),
    '#size' => 10,
    '#maxlength' => 7,
    '#suffix' => '<div class="color-field" id="back_to_top_hover_color"></div>',
  );
  $form['text_button']['back_to_top_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#description' => t('Text color default #333333'),
    '#default_value' => variable_get('back_to_top_text_color', '#333333'),
    '#size' => 10,
    '#maxlength' => 7,
    '#suffix' => '<div class="color-field" id="back_to_top_text_color"></div>',
  );
  return system_settings_form($form);
}
