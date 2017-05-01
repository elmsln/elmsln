<?php

/**
 * @file
 * Administration page callbacks for the Media module.
 */

/**
 * Displays the media administration page.
 */
function media_admin_config_browser($form, &$form_state) {
  $theme_options = array();
  $theme_options[NULL] = t('Default administration theme');

  foreach (list_themes() as $key => $theme) {
    if ($theme->status) {
      $theme_options[$key] = $theme->info['name'];
    }
  }

  $form['media_dialog_theme'] = array(
    '#type' => 'select',
    '#title' => t('Media browser theme'),
    '#options' => $theme_options,
    '#description' => t("This theme will be used for all media related dialogs. It can be different from your site's theme because many site themes do not work well in the small windows which media uses."),
    '#default_value' => variable_get('media_dialog_theme', ''),
  );

  $form['array_filter'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

  $form['mediapopup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Media Popup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['mediapopup']['media_dialogclass'] = array(
    '#type' => 'textfield',
    '#title' => t('Dialog Class'),
    '#default_value' => variable_get('media_dialogclass', 'media-wrapper'),
    '#description' => t('The class used to identify the popup wrapper element.'),
  );
  $form['mediapopup']['media_modal'] = array(
    '#type' => 'select',
    '#title' => t('Modal'),
    '#options' => array(
      FALSE => t('False'),
      TRUE => t('True'),
    ),
    '#default_value' => variable_get('media_modal', TRUE),
    '#description' => t('Open as modal window.'),
  );
  $form['mediapopup']['media_draggable'] = array(
    '#type' => 'select',
    '#title' => t('Draggable'),
    '#options' => array(
      FALSE => t('False'),
      TRUE => t('True'),
    ),
    '#default_value' => variable_get('media_draggable', FALSE),
    '#description' => t('Draggable modal window.'),
  );
  $form['mediapopup']['media_resizable'] = array(
    '#type' => 'select',
    '#title' => t('Resizable'),
    '#options' => array(
      FALSE => t('False'),
      TRUE => t('True'),
    ),
    '#default_value' => variable_get('media_resizable', FALSE),
    '#description' => t('Resizable modal window.'),
  );
  $form['mediapopup']['media_minwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Min Width'),
    '#default_value' => variable_get('media_minwidth', 500),
    '#description' => t('CSS property min-width.'),
  );
  $form['mediapopup']['media_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => variable_get('media_width', 670),
    '#description' => t('CSS property width.'),
  );
  $form['mediapopup']['media_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => variable_get('media_height', 280),
    '#description' => t('CSS property height.'),
  );
  $form['mediapopup']['media_position'] = array(
    '#type' => 'textfield',
    '#title' => t('Position'),
    '#default_value' => variable_get('media_position', 'center'),
    '#description' => t('CSS property position.'),
  );
  $form['mediapopup']['media_zindex'] = array(
    '#type' => 'textfield',
    '#title' => t('Z-Index'),
    '#default_value' => variable_get('media_zindex', 10000),
    '#description' => t('CSS property z-index.'),
  );
  $form['mediapopup']['overlay'] = array(
    '#type' => 'fieldset',
    '#title' => t('Overlay'),
  );
  $form['mediapopup']['overlay']['media_backgroundcolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Background Color'),
    '#default_value' => variable_get('media_backgroundcolor', '#000000'),
    '#description' => t('CSS property background-color; used with overlay.'),
  );
  $form['mediapopup']['overlay']['media_opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Opacity'),
    '#default_value' => variable_get('media_opacity', 0.4),
    '#description' => t('CSS property opacity; used with overlay.'),
  );

  $form['#submit'][] = 'media_admin_config_browser_pre_submit';

  return system_settings_form($form);
}

/**
 * Form submission handler for media_admin_config_browser().
 */
function media_admin_config_browser_pre_submit(&$form, &$form_state) {
  if (!$form_state['values']['media_dialog_theme']) {
    variable_del('media_dialog_theme');
    unset($form_state['values']['media_dialog_theme']);
  }
}
