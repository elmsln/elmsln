<?php

/**
 * @file
 * Generate form elments for the Metatags for Mobile settings.
 */
function at_core_metatags_form(&$form) {
  $form['at-settings']['meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metatags'),
    '#description' => t('<h3>Mobile Metatags</h3><p>Configure metatags for mobile devices. To omit a metatag leave it empty.'),
  );
  $form['at-settings']['meta']['mobile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile Metatags'),
  );

  // Viewport
  $form['at-settings']['meta']['mobile']['adaptivetheme_meta_viewport'] = array(
    '#type' => 'textfield',
    '#title' => t('viewport'),
    '#default_value' => check_plain(at_get_setting('adaptivetheme_meta_viewport')),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  // MobileOptimized
  $form['at-settings']['meta']['mobile']['adaptivetheme_meta_mobileoptimized'] = array(
    '#type' => 'textfield',
    '#title' => t('MobileOptimized'),
    '#default_value' => check_plain(at_get_setting('adaptivetheme_meta_mobileoptimized')),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  // HandheldFriendly
  $form['at-settings']['meta']['mobile']['adaptivetheme_meta_handheldfriendly'] = array(
    '#type' => 'textfield',
    '#title' => t('HandheldFriendly'),
    '#default_value' => check_plain(at_get_setting('adaptivetheme_meta_handheldfriendly')),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  // apple-mobile-web-app-capable
  $form['at-settings']['meta']['mobile']['adaptivetheme_meta_apple_mobile_web_app_capable'] = array(
    '#type' => 'textfield',
    '#title' => t('apple-mobile-web-app-capable'),
    '#default_value' => check_plain(at_get_setting('adaptivetheme_meta_apple_mobile_web_app_capable')),
    '#description' => t('See <a target="_blank" href="!webkithelp">http://developer.apple.com...</a>', array('!webkithelp' => 'http://developer.apple.com/library/safari/#documentation/AppleApplications/Reference/SafariHTMLRef/Articles/MetaTags.html')),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  // IE Document mode
  $form['at-settings']['meta']['mobile']['adaptivetheme_meta_ie_document_mode'] = array(
    '#type' => 'textfield',
    '#title' => t('IE Document Mode'),
    '#default_value' => at_get_setting('adaptivetheme_meta_ie_document_mode'),
    '#description' => t('Use to set legacy document mode - often used to set IE-Edge, for example "IE=edge, chrome=1". See <a target="_blank" href="!mshelp">http://msdn.microsoft.com...</a>', array('!mshelp' => 'http://msdn.microsoft.com/en-us/library/jj676915(v=vs.85).aspx')),
  );

  // Clear type
  $form['at-settings']['meta']['mobile']['adaptivetheme_meta_clear_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Cleartype in IE Mobile devices'),
    '#default_value' => at_get_setting('adaptivetheme_meta_clear_type'),
  );
}
