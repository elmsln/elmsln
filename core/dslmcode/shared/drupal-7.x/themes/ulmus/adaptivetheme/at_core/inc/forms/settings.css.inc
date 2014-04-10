<?php

/**
 * @file
 * Generate form elments for the CSS settings.
 */
function at_core_css_form(&$form, $theme_name) {
  // Set variable for mode, we want to show a message based on this
  $mode = variable_get('preprocess_css', '') == 1 ? TRUE : FALSE;
  $performance_settings_path = url('admin/config/development/performance');

  // Global Settings
  $form['at-settings']['css-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS'),
    '#description' => t('<h3>CSS Settings</h3><p>Here you can get feedback on what mode your site is currently using, and enable the optional <code>responsive.custom.css</code> file.</p>'),
  );

  // Set message depending on the mode
  if ($mode == TRUE) {
    $mode_message = t('<p><strong><a href="!settings_path" target="_blank">CSS aggregation</a> is ON</strong>. Changes to your themes responsive CSS files will not show until you <strong>re-save the theme settings</strong> (click "Save configuration" at the bottom of this form) and clear the <a href="!settings_path" target="_blank">sites cache</a>.</p><div class="description"><p>This is required to re-write the production version of the responsive styles and is a performance optimization in Adaptivetheme, which saves your site at least 4 HTTP requests.</p></div>', array('!settings_path' => $performance_settings_path));
  }
  elseif ($mode == FALSE) {
    $mode_message = t('<p><strong><a href="!settings_path" target="_blank">CSS aggregation</a> is OFF</strong>. Changes to your themes responsive CSS files will show automatically.</p><p><div class="description"><p>Note: when CSS aggregation is ON you need to re-save the theme settings if you make any changes to your themes responsive stylesheets. This is required to re-write the production version of the responsive styles and is a performance optimization in Adaptivetheme, which saves your site at least 4 HTTP requests.</p></div>', array('!settings_path' => $performance_settings_path));
  }

  // Mode
  $form['at-settings']['css-settings']['mode'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS Mode'),
    '#description' => t('<h3>Mode</h3>') . $mode_message,
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  // Custom media queries
  $form['at-settings']['css-settings']['custom-mediaqueries'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Media Queries'),
    '#description' => t('<h3>Custom Media Queries</h3>'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-settings']['css-settings']['custom-mediaqueries']['enable_custom_media_queries'] = array(
    '#type' => 'checkbox',
    '#title'  => t('Enable the responsive.custom.css file'),
    '#description' => t('<p>Use this file if you need to use custom media queries, such as <a href="!zomigi" target="_blank">overlapped media queries</a>.</p><p><strong>File location:</strong> <code>@theme_path/css/responsive.custom.css</code>, .scss version: <code>@theme_path/sass/responsive.custom.scss</code></p>', array('!zomigi' => 'http://zomigi.com/blog/essential-considerations-for-crafting-quality-media-queries/#mq-overlap-stack', '@theme_path' => $theme_name)),
    '#default_value' => at_get_setting('enable_custom_media_queries'),
  );
}
