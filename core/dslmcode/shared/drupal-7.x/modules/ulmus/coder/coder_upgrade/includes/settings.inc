<?php
/**
 * @file
 * Provides module conversion settings form.
 *
 * Copyright 2008-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Form builder for the settings form.
 */
function coder_upgrade_settings_form($form, &$form_state) {
  // Build the form.
  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'edit-upgrade',
  );
  // Set weight on fieldsets so other modules can easily insert a tab at a specific position.
  $form['tabs']['general'] = coder_upgrade_general_build();
  $form['tabs']['performance'] = coder_upgrade_performance_build();

  $form['#submit'][] = 'coder_upgrade_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Returns form content for general settings tab.
 *
 * @return array
 *   Form item.
 */
function coder_upgrade_general_build() {
  require_once DRUPAL_ROOT . '/' . libraries_get_path('grammar_parser') . '/engine/parser.inc';
  $parser = new PGPParser();

  $form = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#description' => t('These settings apply to all modules utilizing the Coder Upgrade conversion routine API.'),
    '#weight' => 0,
  );

  $path = coder_upgrade_directory_path('', FALSE);
  $form['coder_upgrade_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Module base directory'),
    '#required' => TRUE,
    '#default_value' => variable_get('coder_upgrade_dir', DEADWOOD_DIR),
    '#description' => t('Directory beneath the file system path (@path) in which are housed the old, new and patch directories. Default is @default. In the old directory, place the 6.x module code to be upgraded. The upgraded code is saved to the new directory and patch files are written to the patch directory.', array('@path' => $path, '@default' => DEADWOOD_DIR)),
    '#size' => 30,
    '#maxlength' => 255,
    '#validate' => array('coder_upgrade_validate_dir'),
  );

  $form['coder_upgrade_upgrade_core'] = array(
    '#type' => 'checkbox',
    '#title' => t('Update Drupal core modules'),
    '#default_value' => variable_get('coder_upgrade_upgrade_core', FALSE),
    '#description' => t('If checked, then the list of modules to select for upgrade will be the Drupal core modules. Otherwise, the list will be created from contributed modules.'),
  );

  $form['coder_upgrade_replace_files'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace files'),
    '#default_value' => variable_get('coder_upgrade_replace_files', FALSE),
    '#description' => t('If checked, then the original file will be written to the output directory shown above and then replaced with the upgraded file. Otherwise, the upgraded file will be written to the output directory shown above.'),
  );

  $form['coder_upgrade_preserve_array_format'] = array(
    '#type' => 'checkbox',
    '#title' => t('Preserve array formatting'),
    '#default_value' => variable_get('coder_upgrade_preserve_array_format', FALSE),
    '#description' => t('If checked, then array expressions will be formatted to match the input. If not checked, then array expressions will be formatted per Drupal coding standards. This means array expressions will be inlined in function calls, function parameters, and when a single value. Otherwise, the expression will will be multiline formatted.'),
  );

  $form['coder_upgrade_enable_debug_output'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debug output from coder upgrade'),
    '#default_value' => variable_get('coder_upgrade_enable_debug_output', FALSE),
    '#description' => t('If checked, then coder upgrade debug output will be written to the file @file. WARNING: This option should NOT be enabled except for testing and development purposes, and then only on smaller files containing the code to be debugged.', array('@file' => coder_upgrade_path('debug'))),
  );

  $form['coder_upgrade_enable_parser_debug_output'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debug output from grammar parser'),
    '#default_value' => variable_get('coder_upgrade_enable_parser_debug_output', FALSE),
    '#description' => t('If checked, then grammar parser debug output will be written to the file @file. WARNING: This option should NOT be enabled except for testing and development purposes, and then only on smaller files containing the code to be debugged.', array('@file' => $parser->debugPath())),
  );

  return $form;
}

/**
 * Returns form content for performance settings tab.
 *
 * @return array
 *   Form item.
 */
function coder_upgrade_performance_build() {
  $path = coder_upgrade_path('theme_cache');
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Performance'),
    '#description' => t('To minimize the chance of hitting PHP memory and processing time limits, it is recommended to run Coder Upgrade in a separate process without a Drupal bootstrap. However, because this has been reported to fail on certain combinations of operating system, PHP version, and runtime environment, this option was not set when this module was enabled.'),
    '#tree' => FALSE,
    '#weight' => 1,
  );

  $form['coder_upgrade_use_separate_process'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use separate process'),
    '#default_value' => variable_get('coder_upgrade_use_separate_process', FALSE),
    '#description' => t('If checked, then Coder Upgrade will be run in a separate process without a Drupal bootstrap.'),
  );

  $form['theme_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Cache core theme information'),
    '#prefix' => '<div class="label">' . t('If Drupal core has been updated on this site, then click the button below to refresh the core theme information cache file at @file.', array('@file' => $path)) . '</div>',
  );

  return $form;
}

/**
 * Submit handler for the settings form.
 *
 * Rename module input and output directories based on user settings.
 */
function coder_upgrade_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $op = isset($values['op']) ? $values['op'] : '';

  $cur = variable_get('coder_upgrade_dir', DEADWOOD_DIR);
  $new = $op == t('Reset to defaults') ? DEADWOOD_DIR : $values['coder_upgrade_dir'];
  if ($new != $cur) {
    if (rename(coder_upgrade_directory_path($cur, FALSE), coder_upgrade_directory_path($new, FALSE))) {
      variable_set('coder_upgrade_dir_old', $new . '/old');
      variable_set('coder_upgrade_dir_new', $new . '/new');
      variable_set('coder_upgrade_dir_patch', $new . '/patch');
      drupal_set_message(t('Base directory was renamed to ' . $new . '.'));
    }
    else {
      // Reset the directory variable.
      variable_set('coder_upgrade_dir', $cur);
      drupal_set_message(t('Could not rename base directory'), 'error');
    }
  }
}

/**
 * Submit callback; creates a core theme information cache file.
 *
 * This file is used when the upgrade routines are run in a separate process.
 */
function coder_upgrade_create_theme_cache_submit($form, &$form_state) {
  global $_coder_upgrade_theme_registry;

  module_load_include('inc', 'coder_upgrade', 'includes/conversion');
  module_load_include('inc', 'coder_upgrade', 'conversions/begin');
  // Create a core theme information cache.
  coder_upgrade_cache_theme_registry();
  // Write cache to file.
  $path = coder_upgrade_path('theme_cache');
  if (file_put_contents($path, serialize($_coder_upgrade_theme_registry)) === FALSE) {
    drupal_set_message(t('Could not write to core theme information cache file.'), 'error');
    return;
  }
  drupal_set_message(t('Core theme information cache created at @file.', array('@file' => $path)));
}
