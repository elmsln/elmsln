<?php

/**
 * @file
 * Generate form elments for the Apple touch icons settings.
 */
function at_core_touch_icons_form(&$form, $theme_name) {
  $form['at']['ati'] = array(
    '#type' => 'fieldset',
    '#title' => t('Touch Icons'),
    '#description' => t('<h3>Touch Icons</h3><p>Different devices can support different sized touch icons - see the <a href="!apple_docs" target="_blank">iOS developer documentation</a>. Paths must be relative to your theme folder.</p><p>A plain set of icons are included by default that use the <a href="!icon_template" target="_blank">App Icon Template</a>.', array('!apple_docs' => 'https://developer.apple.com/library/ios/documentation/AppleApplications/Reference/SafariWebContent/ConfiguringWebApplications/ConfiguringWebApplications.html', '!icon_template' => 'http://appicontemplate.com')),
    '#weight' => 10,
  );
  $form['at']['ati']['icon-paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Touch Icons'),
  );

  // Default
  $form['at']['ati']['icon-paths']['icon_path_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Default: 60x60'),
    '#description' => t('If you only enter a path for this size it will be used by all devices.'),
    '#field_prefix' => $theme_name . '/',
    '#default_value' => check_plain(at_get_setting('icon_path_default')),
    '#states' => array(
      'required' => array('input[name="enable_apple_touch_icons"]' => array('checked' => TRUE)),
    ),
  );

  // iPad (standard display)
  $form['at']['ati']['icon-paths']['apple_touch_icon_path_ipad'] = array(
    '#type' => 'textfield',
    '#title' => t('iPad: 76x76'),
    '#description' => t('Apple touch icon for older iPads with standard displays.'),
    '#field_prefix' => $theme_name . '/',
    '#default_value' => check_plain(at_get_setting('apple_touch_icon_path_ipad')),
  );

  // iPhone retina
  $form['at']['ati']['icon-paths']['apple_touch_icon_path_iphone_retina'] = array(
    '#type' => 'textfield',
    '#title' => t('iPhone Retina: 120x120'),
    '#description' => t('Apple touch icon for iPhones with retina displays.'),
    '#field_prefix' => $theme_name . '/',
    '#default_value' => check_plain(at_get_setting('apple_touch_icon_path_iphone_retina')),
  );

  // iPad retina
  $form['at']['ati']['icon-paths']['apple_touch_icon_path_ipad_retina'] = array(
    '#type' => 'textfield',
    '#title' => t('iPad Retina: 156x156'),
    '#description' => t('Apple touch icon for iPads with retina displays.'),
    '#field_prefix' => $theme_name . '/',
    '#default_value' => check_plain(at_get_setting('apple_touch_icon_path_ipad_retina')),
  );

  $form['at']['ati']['icon-paths']['icon_rel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use apple-touch-icon-precomposed'),
    '#description' => t('Use precomposed if you want to remove icon effects in iOS6 or below. The default is <code>apple-touch-icon</code>. '),
  );
}
