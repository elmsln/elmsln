<?php
/**
* @file
* This file adds a warning message if the theme is beeing used disabled.
*/

// Define the base site url.
global $base_url;

// Display the warning in its own div.
print theme('html_tag', array(
  'element' => array(
    '#tag' => 'div',
    '#attributes' => array(
    'class' => 'messages theme-disabled',
  ),
  '#value' => t('Adminimal Theme must be enabled to work properly. Please enable it from the <a href="@link">Appearance page</a>.', array('@link' => $base_url . '/admin/appearance')),
  ),
));
