<?php
/**
 * @file
 * Process theme data.
 *
 * IMPORTANT WARNING: DO NOT MODIFY THIS FILE OR ANY OF THE INCLUDED FILES.
 */
global $theme_key, $path_to_at_core;
$theme_key = $GLOBALS['theme_key'];
$path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

include_once($path_to_at_core . '/inc/get.inc');        // get theme info, settings, css etc
include_once($path_to_at_core . '/inc/plugins.inc');    // the plugin system with wrapper and helper functions
include_once($path_to_at_core . '/inc/generate.inc');   // CSS class generators
include_once($path_to_at_core . '/inc/fonts.inc');      // Required functions for the fonts and headings settings
include_once($path_to_at_core . '/inc/load.inc');       // drupal_add_css() wrappers
include_once($path_to_at_core . '/inc/alter.inc');      // hook_alters
include_once($path_to_at_core . '/inc/preprocess.inc'); // all preprocess functions
include_once($path_to_at_core . '/inc/process.inc');    // all process functions
include_once($path_to_at_core . '/inc/theme.inc');      // theme function overrides
