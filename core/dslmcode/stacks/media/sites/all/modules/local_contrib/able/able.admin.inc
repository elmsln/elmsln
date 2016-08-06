<?php

/**
 * @file
 * Admin only functionality for the ableplayer module.
 */

/**
 * Menu form callback; Display the ableplayer admin form.
 */
function able_admin_form() {
  $form = array();

  // Detect if the library is available. If it is not available display a
  // message.
  $libraries = libraries_get_libraries();
  if (!isset($libraries['ableplayer'])) {
    $form['message'] = array(
      '#markup' => '<p>' . t('The ableplayer library is not installed. Please download the library from <a href="!url">ableplayer</a> and place it in your libraries folder.', array('!url' => 'https://github.com/ableplayer/ableplayer')) . '</p>',
    );
  }

  $form['ableplayer_sitewide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable ableplayer.js site wide'),
    '#default_value' => variable_get('ableplayer_sitewide', FALSE),
  );

  // Display a sample video. We add the library here because we cannot be sure
  // it is otherwise included in the page.
  drupal_add_library('ableplayer', 'ableplayer');
  drupal_add_js(drupal_get_path('module', 'ableplayer') . '/ableplayer.js');
  drupal_add_js(array('ableplayerAll' => TRUE), array('type' => 'setting'));
  $path = libraries_get_path('ableplayer', TRUE);
  $form['test'] = array(
    '#markup' => '
    <video id="video1" preload="auto" width="480" height="360" poster="' . $path . '/media/wwa.jpg" data-able-player>
      <source type="video/webm" src="' . $path . '/media/wwa.webm"/>
      <source type="video/mp4" src="' . $path . '/media/wwa.mp4"/>
      <track kind="captions" src="' . $path . '/media/wwa_captions_en.vtt"/>
    </video>'
  );

  return system_settings_form($form);
}