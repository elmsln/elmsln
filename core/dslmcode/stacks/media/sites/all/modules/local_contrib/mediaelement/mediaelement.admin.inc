<?php

/**
 * @file
 * Admin only functionality for the mediaelement module.
 */

/**
 * Menu form callback; Display the MediaElement admin form.
 */
function mediaelement_admin_form() {
  $form = array();

  // Detect if the library is available. If it is not available display a
  // message.
  $libraries = libraries_get_libraries();
  if (!isset($libraries['mediaelement'])) {
    $form['message'] = array(
      '#markup' => '<p>' . t('The MediaElement.js library is not installed. Please download the library from <a href="!url">MediaElementjs.com</a> and place it in your libraries folder.', array('!url' => 'http://mediaelementjs.com')) . '</p>',
    );
  }

  $form['mediaelement_sitewide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable MediaElement.js site wide'),
    '#default_value' => variable_get('mediaelement_sitewide', FALSE),
  );

  // Display a sample video. We add the library here because we cannot be sure
  // it is otherwise included in the page.
  drupal_add_library('mediaelement', 'mediaelement');
  drupal_add_js(drupal_get_path('module', 'mediaelement') . '/mediaelement.js');
  drupal_add_js(array('mediaelementAll' => TRUE), array('type' => 'setting'));
  $path = libraries_get_path('mediaelement', TRUE);
  $form['test'] = array(
    '#markup' => '<video width="360" height="203" id="player1" src="' . $path . '/media/echo-hereweare.mp4"><p>Your browser leaves much to be desired.</p></video>',
  );

  return system_settings_form($form);
}