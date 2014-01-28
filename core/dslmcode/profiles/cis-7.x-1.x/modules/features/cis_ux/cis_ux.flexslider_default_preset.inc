<?php
/**
 * @file
 * cis_ux.flexslider_default_preset.inc
 */

/**
 * Implements hook_flexslider_default_presets().
 */
function cis_ux_flexslider_default_presets() {
  $export = array();

  $preset = new stdClass();
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->name = 'course';
  $preset->title = 'course';
  $preset->theme = 'classic';
  $preset->imagestyle_normal = 'flexslider_full';
  $preset->options = array(
    'animation' => 'slide',
    'animationDuration' => 800,
    'slideDirection' => 'horizontal',
    'slideshow' => 1,
    'slideshowSpeed' => 6000,
    'animationLoop' => 1,
    'randomize' => 0,
    'slideToStart' => 0,
    'directionNav' => 0,
    'controlNav' => 1,
    'keyboardNav' => 1,
    'mousewheel' => 1,
    'prevText' => 'Previous',
    'nextText' => 'Next',
    'pausePlay' => 0,
    'pauseText' => 'Pause',
    'playText' => 'Play',
    'pauseOnAction' => 1,
    'controlsContainer' => '.flex-nav-container',
    'manualControls' => '',
  );
  $export['course'] = $preset;

  return $export;
}
