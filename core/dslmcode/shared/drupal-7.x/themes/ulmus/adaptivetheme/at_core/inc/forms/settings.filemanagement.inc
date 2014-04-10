<?php

/**
 * @file
 * Generate form elments for the File Management settings.
 */
function at_core_filemanagement_form(&$form, $theme_name) {
  $file_settings_path = url('admin/config/media/file-system');
  $public_files = variable_get('file_public_path', conf_path() . '/files') . '/adaptivetheme/' . $theme_name . '_files/';
  $theme_directory = drupal_get_path('theme', $theme_name) . '/generated_files/';
  $css_mode = variable_get('preprocess_css', '') == 1 ? TRUE : FALSE;
  $js_mode = variable_get('preprocess_js', '') == 1 ? TRUE : FALSE;

  // File Management
  $form['at-settings']['file-management'] = array(
    '#type' => 'fieldset',
    '#title' => t('File Management'),
    '#description' => t('<h3>File Management Settings</h3><p>Set the path to generated files and configure CSS and JS aggregation optimizations. Please read the help descriptions carefully. </p>'),
  );

  // Path to generated files
  $form['at-settings']['file-management']['files-path'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path to Generated Files'),
    '#description' => t('<h3>Path to Generated Files</h3>'),
  );
  $form['at-settings']['file-management']['files-path']['global_files_path'] = array(
    '#type' => 'select',
    '#title' => t('By default the generated files are saved in <a href="!file_settings_path" target="_blank">public files</a>. You can change this to your theme directory or a custom directory. These files include all the generated CSS files, the info file backup and color scheme backups if you are using the Color module. For more information see the docs on the <a href="!file_generation_system" target="_blank">file generation system</a>.', array('!file_settings_path' => $file_settings_path, '!file_generation_system' => 'http://adaptivethemes.com/documentation/file-generation-system')),
    '#default_value' => at_get_setting('global_files_path'),
    '#options' => array(
      'public_files' => t('Public files'),
      'theme_directory' => t('Theme directory'),
      'custom_path' => t('Custom path'),
    ),
  );
  // Message for public files
  $form['at-settings']['file-management']['files-path']['public_files_path'] = array(
    '#type' => 'fieldset',
    '#states' => array(
      'visible' => array('select[name="global_files_path"]' => array('value' => 'public_files')),
    ),
  );
  $form['at-settings']['file-management']['files-path']['public_files_path']['message'] = array(
    '#markup' => t('<div class="description">Files will be saved to: <code>@public_files</code></div>', array('@public_files' => $public_files)),
  );
  // message for theme dir
  $form['at-settings']['file-management']['files-path']['theme_directory_files_path'] = array(
    '#type' => 'fieldset',
    '#states' => array(
      'visible' => array('select[name="global_files_path"]' => array('value' => 'theme_directory')),
    ),
  );
  $form['at-settings']['file-management']['files-path']['theme_directory_files_path']['message'] = array(
    '#markup' => t('<div class="description">Files will be saved to: <code>@theme_directory</code></div>', array('@theme_directory' => $theme_directory)),
  );
  // Text field for custom path
  $form['at-settings']['file-management']['files-path']['custom_files_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the custom path:'),
    '#default_value' => at_get_setting('custom_files_path'),
    '#description' => t('This directory must exist and be writable by Drupal. This directory must be relative to the Drupal installation directory and be accessible over the web. Do not try to use something like <code>../css</code>, it will fail. Use someting like <code>sites/default/css</code>.'),
    '#states' => array(
      'visible' => array('select[name="global_files_path"]' => array('value' => 'custom_path')),
    ),
  );

  // Aggregation overrides, see http://drupal.org/node/1115026
  if ($css_mode == FALSE) {
    $css_mode_message = t('CSS aggregation is OFF. This settings will have no effect until CSS aggregation is turned ON.');
  }
  else {
    $css_mode_message = t('CSS aggregation is ON. This settings will take effect.');
  }
  if ($js_mode == FALSE) {
    $js_mode_message = t('JavaScript aggregation is OFF. This settings will have no effect until JavaScript aggregation is turned ON.');
  }
  else {
    $js_mode_message = t('JavaScript aggregation is ON. This settings will take effect.');
  }
  $form['at-settings']['file-management']['aggregation-overrides'] = array(
    '#type' => 'fieldset',
    '#title' => t('Combine Aggregated Files'),
    '#description' => t('<h3>Combine Aggregated Files <sup>(beta)</sup></h3><p>When CSS aggregation is on Drupal aggregates CSS and JS files by group. These settings will override this and create one CSS stylesheet per type and only one JavaScript file. This reduces HTTP requests and improves site performance. Note: this is beta and while well tested you should check your site carefully, both the style and behavior.</p><p>Warning: Internet Explorer cannot handle more than 4095 selectors in one stylesheet - combining CSS files using this setting could result in more than 4095 selectors. If you see probems such as no style in IE then turn this off.</p>'),
  );
  // Combine CSS
  $form['at-settings']['file-management']['aggregation-overrides']['combine_css_files'] = array(
    '#type' => 'checkbox',
    '#title'  => t('Combine CSS Files'),
    '#description' => t('<p>In AT you will normally get three media type CSS files after this is enabled and CSS aggregation is turned on - all, screen and only screen. If you are using a print stylesheet this will be seperate also. Browser specific stylesheets for Internet Explorer are ignored.</p><p>!css_mode_message</p>', array('!css_mode_message' => $css_mode_message)),
    '#default_value' => at_get_setting('combine_css_files'),
  );
  // Combine JS
  $form['at-settings']['file-management']['aggregation-overrides']['combine_js_files'] = array(
    '#type' => 'checkbox',
    '#title'  => t('Combine JS Files'),
    '#description' => t('<p>This will force all aggregated JavaScript files into one file.</p><p>!js_mode_message</p>', array('!js_mode_message' => $js_mode_message)),
    '#default_value' => at_get_setting('combine_js_files'),
  );
}
