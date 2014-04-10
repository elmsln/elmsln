<?php

/**
 * @file
 * Generate form elments for the Global settings.
 */
function at_core_global_form(&$form, $theme_name) {
  // Set variable for mode, we want to show a message based on this
  $mode = variable_get('preprocess_css', '') == 1 ? TRUE : FALSE;
  $performance_settings_path = url('admin/config/development/performance');
  $file_settings_path = url('admin/config/media/file-system');

  // Global Settings
  $form['at-settings']['global-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Settings'),
    '#description' => t('<h3>Global Settings</h3><p>These settings are primarly set during development - do not change these unless you are actively developing or modifying your theme.</p>'),
  );

  // Set default layout
  $form['at-settings']['global-settings']['default-layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile first or Mobile last'),
    '#description' => t('<h3>Mobile first or Desktop first</h3>'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-settings']['global-settings']['default-layout']['global_default_layout_toggle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Change default layout method <small>(checking this will expose new settings)</small>'),
    '#description' => t('<strong>Use with caution!</strong> If you are using a pre-styled sub-theme such as Pixture Reloaded, Sky, Corolla, AT Commerce or any of the commerical sub-themes you should NOT change this!'),
    '#default_value' => at_get_setting('global_default_layout_toggle'),
  );
  $form['at-settings']['global-settings']['default-layout']['toggle'] = array(
    '#type' => 'fieldset',
    '#title' => t('Change default layout method'),
    '#states' => array(
      'visible' => array('input[name="global_default_layout_toggle"]' => array('checked' => TRUE)),
    ),
  );
  // Backwards compatibility with pre 7.x-3.x themes
  $global_default_layout_default_value = at_get_setting('global_default_layout') ? at_get_setting('global_default_layout') : 'standard-layout';
  if ($global_default_layout_default_value == 'smartphone-portrait') {
    $global_default_layout_default_value = 'smalltouch-portrait';
  }
  $form['at-settings']['global-settings']['default-layout']['toggle']['global_default_layout'] = array(
    '#type' => 'radios',
    '#description' => t('<p>Adaptivetheme supports both mobile first and desktop first design approaches. Please review the <a href="!docs_link" target="_blank">online documentation</a>.</p><p>This setting fundementally alters what CSS is loaded and how it is loaded. At the most basic level if you select Mobile first the Smalltouch portrait layout will load as the default, if you select Desktop first the Standard layout will load as the default. Many other changes take place regarding loading of CSS for Internet Explorer, Responsive Gpanels and Panels as well.</p> ', array('!docs_link' => 'http://adaptivethemes.com/documentation/mobile-first-design-with-adaptivetheme')),
    '#default_value' => $global_default_layout_default_value,
    '#options' => array(
      'smalltouch-portrait' => t('Mobile first'),
      'standard-layout' => t('Desktop first'),
    ),
  );

  // Disable responsive layout
  $form['at-settings']['global-settings']['disable-rs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Disable Responsive Layout'),
    '#description' => t('<h3>Disable Responsive Layout</h3>'),
  );
  $form['at-settings']['global-settings']['disable-rs']['disable_responsive_styles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable responsive layout and styles'),
    '#description' => t('By checking this setting the site will use only the Standard layout and the global styles. You can turn this back on at any time.'),
    '#default_value' => at_get_setting('disable_responsive_styles'),
  );
}
