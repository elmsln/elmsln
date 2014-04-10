<?php

/**
 * @file
 * Generate settings for the CSS exclude form.
 */
function at_core_css_exclude_form(&$form, $theme_name) {
  // We need some getters.
  include_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/get.inc');

  // Get the relevent CSS file data for building the form.
  $css_data = at_get_css_files($theme_name);

  // regex pattern
  $pattern = '/[^a-zA-Z0-9-]+/';

  // -- DIE CSS DIE -- //
  $form['at']['cssexcludes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unset CSS'),
    '#weight' => 20,
  );
  $form['at']['cssexcludes']['die-css-die'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unset CSS'),
    '#description' => t('<h2>Unset CSS</h2><p>Stylesheet names are cached, if some are not showing in this list you may need to clear the cache.</p><p>In for some reason (it happens) the CSS files you want to unset never show here you can explicitly declare them in your info file as "unset_css", see your sub-themes info file under "Stylesheets" for instructions.</p>'),
    '#attached' => array(
      'js' => array(drupal_get_path('theme', 'adaptivetheme') . '/scripts/check-all.js'),
    ),
  );

  // Core
  $core_defined = FALSE;
  $form['at']['cssexcludes']['die-css-die']['core-excludes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unset Core CSS'),
    '#description' => t('<h3>Unset Core Module CSS</h3>'),
  );
  foreach ($css_data as $key => $value) {
    if ($value['type'] == 'unset_core') {
      $core_defined = TRUE;
      $setting = 'unset_css_' . preg_replace($pattern, '_', $key);
      $title_parts = explode('/', $key);
      $title = array_pop($title_parts);
      $form['at']['cssexcludes']['die-css-die']['core-excludes'][$setting] = array(
        '#type' => 'checkbox',
        '#title' => t('<b>@title</b> <small>(@key)</small>', array('@title' => $title, '@key' => $key)),
        '#default_value' => at_get_setting($setting) ? at_get_setting($setting) : 0,
        '#attributes' => array('class' => array('drupal-core-css-file')),
        '#weight' => 0,
      );
    }
  }
  if ($core_defined === TRUE) {
    $form['at']['cssexcludes']['die-css-die']['core-excludes']['core_check_all'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Unset All</strong>'),
      '#default_value' => at_get_setting('core_check_all') ? at_get_setting('core_check_all') : 0,
      '#weight' => -1,
    );
  }
  if ($core_defined === FALSE) {
    $form['at']['cssexcludes']['die-css-die']['libraries-excludes']['nothing_core_defined'] = array(
      '#markup' => t('No core stylesheets to unset? Hmmm, something is not right here, try clearning the sites cache, otherwise you might need to <a href="!link" target="_blank">post an issue</a>.', array('!link' => 'http://drupal.org/project/issues/adaptivetheme')),
    );
  }

  // Contrib
  $contrib_defined = FALSE;
  $form['at']['cssexcludes']['die-css-die']['contrib-excludes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unset Contrib Module CSS'),
    '#description' => t('<h3>Unset Contrib Module CSS</h3>'),
  );
  foreach ($css_data as $key => $value) {
    if ($value['type'] == 'contrib') {
      $contrib_defined = TRUE;
      $setting = 'unset_css_' . preg_replace($pattern, '_', $key);
      $title_parts = explode('/', $key);
      $title = array_pop($title_parts);
      $form['at']['cssexcludes']['die-css-die']['contrib-excludes'][$setting] = array(
        '#type' => 'checkbox',
        '#title' => t('<b>@title</b> <small>(@key)</small>', array('@title' => $title, '@key' => $key)),
        '#default_value' => at_get_setting($setting) ? at_get_setting($setting) : 0,
        '#attributes' => array('class' => array('contrib-module-css-file')),
        '#weight' => 0,
      );
    }
  }
  if ($contrib_defined === TRUE) {
    $form['at']['cssexcludes']['die-css-die']['contrib-excludes']['contrib_check_all'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Unset All</strong>'),
      '#default_value' => at_get_setting('contrib_check_all') ? at_get_setting('contrib_check_all') : 0,
      '#weight' => -1,
    );
  }
  if ($contrib_defined === FALSE) {
    $form['at']['cssexcludes']['die-css-die']['libraries-excludes']['nothing_contrib_defined'] = array(
      '#markup' => t('No contrib module stylesheets to unset. If you think there should be, try clearing the sites cache. If they still do not show you may need to explicitly declare them in your sub-theme info file.'),
    );
  }

  // Libs
  $libraries_defined = FALSE;
  $form['at']['cssexcludes']['die-css-die']['libraries-excludes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unset Libraries CSS'),
    '#description' => t('<h3>Unset Libraries CSS</h3>'),
  );
  foreach ($css_data as $key => $value) {
    if ($value['type'] == 'library') {
      $libraries_defined = TRUE;
      $setting = 'unset_css_' . preg_replace($pattern, '_', $key);
      $title_parts = explode('/', $key);
      $title = array_pop($title_parts);
      $form['at']['cssexcludes']['die-css-die']['libraries-excludes'][$setting] = array(
        '#type' => 'checkbox',
        '#title' => t('<b>@title</b> <small>(@key)</small>', array('@title' => $title, '@key' => $key)),
        '#default_value' => at_get_setting($setting) ? at_get_setting($setting) : 0,
        '#attributes' => array('class' => array('library-css-file')),
        '#weight' => 0,
      );
    }
  }
  if ($libraries_defined === TRUE) {
    $form['at']['cssexcludes']['die-css-die']['libraries-excludes']['libraries_check_all'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Unset All</strong>'),
      '#default_value' => at_get_setting('libraries_check_all') ? at_get_setting('libraries_check_all') : 0,
      '#weight' => -1,
    );
  }
  if ($libraries_defined === FALSE) {
    $form['at']['cssexcludes']['die-css-die']['libraries-excludes']['nothing_libraries_defined'] = array(
      '#markup' => t('No libraries stylesheets to unset. If you think there should be, try clearing the sites cache. If they still do not show you may need to explicitly declare them in your sub-theme info file.'),
    );
  }

  // Explicit (user defined in their sub-themes info file)
  $user_defined = FALSE;
  $form['at']['cssexcludes']['die-css-die']['explicit-excludes'] = array(
    '#type' => 'fieldset',
    '#title' => t('My Unset CSS Files'),
    '#description' => t('<h3>My Unset CSS Files</h3>'),
  );
  foreach ($css_data as $key => $value) {
    if ($value['type'] == 'user_defined') {
      $user_defined = TRUE;
      $setting = 'unset_css_' . preg_replace($pattern, '_', $key);
      $title_parts = explode('/', $key);
      $title = array_pop($title_parts);
      $form['at']['cssexcludes']['die-css-die']['explicit-excludes'][$setting] = array(
        '#type' => 'checkbox',
        '#title' => t('<b>@title</b> <small>(@key)</small>', array('@title' => $title, '@key' => $key)),
        '#default_value' => at_get_setting($setting) ? at_get_setting($setting) : 0,
        '#attributes' => array('class' => array('user-defined-css-file')),
        '#weight' => 0,
      );
    }
  }
  if ($user_defined === TRUE) {
    $form['at']['cssexcludes']['die-css-die']['explicit-excludes']['explicit_check_all'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Unset All</strong>'),
      '#default_value' => at_get_setting('explicit_check_all') ? at_get_setting('explicit_check_all') : 0,
      '#weight' => -1,
    );
  }
  if ($user_defined === FALSE) {
    $form['at']['cssexcludes']['die-css-die']['explicit-excludes']['nothing_user_defined'] = array(
      '#markup' => t('No user defined stylesheets to unset. If you wish to define your own, see your sub-theme info file for details under the "Stylesheets" section.'),
    );
  }
}
