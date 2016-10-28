<?php
/**
 * @file
 * cle_submission.flexslider_default_preset.inc
 */

/**
 * Implements hook_flexslider_default_presets().
 */
function cle_submission_flexslider_default_presets() {
  $export = array();

  $preset = new stdClass();
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->name = 'cle_images';
  $preset->title = 'CLE images';
  $preset->theme = 'classic';
  $preset->imagestyle_normal = 'cle_square';
  $preset->options = array(
    'animation' => 'slide',
    'animationDuration' => 600,
    'slideDirection' => 'vertical',
    'slideshow' => 1,
    'slideshowSpeed' => 2000,
    'animationLoop' => 1,
    'randomize' => 0,
    'slideToStart' => 0,
    'directionNav' => 0,
    'controlNav' => 0,
    'keyboardNav' => 1,
    'mousewheel' => 1,
    'prevText' => '',
    'nextText' => '',
    'pausePlay' => 0,
    'pauseText' => '',
    'playText' => '',
    'pauseOnAction' => 0,
    'controlsContainer' => '.flex-nav-container',
    'manualControls' => '',
  );
  $export['cle_images'] = $preset;

  $preset = new stdClass();
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->name = 'cle_submission';
  $preset->title = 'CLE submission';
  $preset->theme = 'classic';
  $preset->imagestyle_normal = 'cle_submission';
  $preset->options = array(
    'animation' => 'fade',
    'animationDuration' => 600,
    'slideDirection' => 'horizontal',
    'slideshow' => 0,
    'slideshowSpeed' => 7000,
    'animationLoop' => 1,
    'randomize' => 0,
    'slideToStart' => 0,
    'directionNav' => 1,
    'controlNav' => 1,
    'keyboardNav' => 1,
    'mousewheel' => 1,
    'prevText' => 'Previous',
    'nextText' => 'Next',
    'pausePlay' => 1,
    'pauseText' => 'Pause',
    'playText' => 'Play',
    'pauseOnAction' => 1,
    'controlsContainer' => '.flex-nav-container',
    'manualControls' => '',
  );
  $export['cle_submission'] = $preset;

  return $export;
}
