<?php

/**
 * @file
 * Generate settings for the Debuggers form.
 */
function at_core_debug_form(&$form) {
  $form['at-settings']['debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debuggers'),
  );
  $form['at-settings']['debug']['debug-layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debuggers'),
    '#description' => t('<h3>Debuggers</h3>'),
  );

  // Highlight regions
  $form['at-settings']['debug']['debug-layout']['expose_regions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Highlight regions'),
    '#default_value' => at_get_setting('expose_regions'),
  );

  // Window size bookmarklet
  $form['at-settings']['debug']['debug-layout']['show_window_size'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show window size - appears in the bottom right corner'),
    '#default_value' => at_get_setting('show_window_size'),
  );

  // Version test
  $form['at-settings']['debug']['debug-layout']['atcore_version_test'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sub-theme compatibility test'),
    '#default_value' => at_get_setting('atcore_version_test'),
  );

  // Debug panels
  $form['at-settings']['debug']['debug-panels'] = array(
    '#type' => 'fieldset',
    '#title' => t('<h3>Debug Panels and Gpanels Layouts</h3>'),
    '#description' => t('<h3>Debug Panels and Gpanels Layouts</h3>'),
  );
  $form['at-settings']['debug']['debug-panels']['load_all_panels'] = array(
    '#type' => 'checkbox',
    '#title' => t('Load all panels in the front page content region'),
    '#default_value' => at_get_setting('load_all_panels'),
    '#description' => t('This will only load the layouts that ship with AT Core, the test is hard coded.'),
  );
  $form['at-settings']['debug']['debug-panels']['load_all_panels_no_sidebars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable sidebars for the front page'),
    '#default_value' => at_get_setting('load_all_panels_no_sidebars'),
    '#states' => array(
      'visible' => array('input[name="load_all_panels"]' => array('checked' => TRUE)),
    ),
  );

  // All media queries
  $queries  = '<dl>';
  $queries .= '<dt>Standard layout</dt><dd>@media ' . at_get_setting('bigscreen_media_query') . '</dd>';
  $queries .= '<dt>Tablet landscape</dt><dd>@media ' . at_get_setting('tablet_landscape_media_query') . '</dd>';
  $queries .= '<dt>Tablet portrait</dt><dd>@media ' . at_get_setting('tablet_portrait_media_query') . '</dd>';
  $queries .= '<dt>Smalltouch landscape</dt><dd>@media ' . at_get_setting('smalltouch_landscape_media_query') . '</dd>';
  $queries .= '<dt>Smalltouch portrait</dt><dd>@media ' . at_get_setting('smalltouch_portrait_media_query') . '</dd>';
  $queries .= '</dl>';

  // Sanity check
  $queries = filter_xss($queries);

  $form['at-settings']['debug']['mediaqueries'] = array(
    '#type' => 'fieldset',
    '#title' => t('<h3>All Media Queries</h3>'),
    '#description' => t('<h3>All Media Queries</h3><p>This shows the media queries currently being used by your theme. This is provided so you can easily save a backup copy for reference.</p>'),
  );
  $form['at-settings']['debug']['mediaqueries']['output'] = array(
    '#markup' => $queries ? $queries : '',
  );
}
