<?php

/**
 * Implements hook_cis_lmsless_theme_vars_alter()
 *
 * This allows you to modify the theme variables used in assembly of the
 * top CIS "LMSless" bar. Because this is a module that provides the area
 * and "themes" it, it's harder to get at the underlying variables via
 * preprocess functions.
 * @param  array &$vars theme variables for rendering to the top bar.
 */
function hook_cis_lmsless_theme_vars_alter(&$vars) {
  $vars['services']['External']['youtube'] = array(
    'title' => t('YouTube'),
    'url' => 'http://youtube.com',
    'machine_name' => 'youtube',
  );
}