<?php

/**
 * @file
 * Build CSS for Google fonts
 *
 * This file exists for backwards compatibility for pre 7.x-3.x themes, it is
 * never used in 7.x-3.x themes or newer.
 */

global $theme_key, $theme_name;
$theme_name = $theme_key;
$path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

// Include the font definition arrays
include_once($path_to_at_core . '/inc/fonts.inc');

// Backwards compatibility cruft for pre 7.x-3.x subthemes that have google fonts
// We dont want them to use this but if saves the site blowing up if a user tries...
// Return a list of options
function google_web_fonts_list_options() {
  $google_web_font_families = array();
  $fonts = google_font_names();
  foreach ($fonts as $font) {
    $google_web_font_families[] = $font;
  }
  return $google_web_font_families;
}

// Return the style name
function google_web_fonts_get_style_name($key, $font_type, $font_value) {
  $font_value = trim($font_value);
  $font_value = strtolower($font_value);
  $font_value = str_replace(' ', '-', $font_value);
  return $key . (!empty($font_type) ? '-' . $font_type :  "") . "-" . $font_value;
}

// Process font families, this is not specific to Google fonts but makes sense including it here
function get_font_families($fonts, $theme_name) {
  $google_font_families = array();
  $font_type = '';
  $font_families = array();
  foreach ($fonts as $key => $value) {
    $font_type = theme_get_setting($value . '_type', $theme_name);
    $font_value = theme_get_setting($value . (!empty($font_type) ? '_' . $font_type : ''), $theme_name);
    if ($font_type == '') {
      $font_families[] = $font_value;
    }
    else {
      if ($font_type == 'gwf') {
        $gff = str_replace(' ', '+', $font_value);
        $google_font_families[] = $gff;
        $font_value = preg_replace('/[^\w\d_ -]/si', '', $font_value);
        $style_name = google_web_fonts_get_style_name($key, $font_type, $font_value);
        $font_families[] = $style_name;
        switch ($key) {
          case 'bf':
            drupal_add_css("body.$style_name, .$style_name .form-text {font-family: '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
          case 'snf':
            drupal_add_css("body.$style_name #site-name {font-family : '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
          case 'ssf':
            drupal_add_css("body.$style_name #site-slogan {font-family: '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
          case 'mmf':
            drupal_add_css(".$style_name #nav-wrapper {font-family: '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
          case 'ptf':
            drupal_add_css("body.$style_name #page-title {font-family: '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
          case 'ntf':
            drupal_add_css("body.$style_name .article-title {font-family: '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
          case 'ctf':
            drupal_add_css("body.$style_name .comment-title {font-family: '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
          case 'btf':
            drupal_add_css("body.$style_name .block-title {font-family: '" . $font_value . "'}", array('group' => CSS_DEFAULT, 'type' => 'inline'));
            break;
        }
      }
    }
  }
  if (!empty($google_font_families)) {
    $array = array_unique($google_font_families);
    $google_fonts = trim(implode('|', $array));
    drupal_add_css('//fonts.googleapis.com/css?family=' . $google_fonts, array(
      'group' => CSS_THEME,
      'type' => 'external',
      'weight' => -1,
      'preprocess' => FALSE,
      )
    );
  }
  return $font_families;
}
