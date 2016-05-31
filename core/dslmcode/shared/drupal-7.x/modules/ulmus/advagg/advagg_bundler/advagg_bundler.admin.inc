<?php

/**
 * @file
 * Admin page callbacks for the advagg bundler module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function advagg_bundler_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Bundler'));

  $form = array();
  $form['advagg_bundler_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bundler is Active'),
    '#default_value' => variable_get('advagg_bundler_active', ADVAGG_BUNDLER_ACTIVE),
    '#description' => t('If not checked, the bundler will passively monitor your site, but it will not split up aggregates.'),
  );

  $options = array(
    0 => 0,
    1 => 1,
    2 => 2,
    3 => 3,
    4 => 4,
    5 => 5,
    6 => 6,
    7 => 7,
    8 => 8,
    9 => 9,
    10 => 10,
    11 => 11,
    12 => 12,
    13 => 13,
    14 => 14,
    15 => 15,
  );
  $form['advagg_bundler_max_css'] = array(
    '#type' => 'select',
    '#title' => t('Target Number Of CSS Bundles Per Page'),
    '#default_value' => variable_get('advagg_bundler_max_css', ADVAGG_BUNDLER_MAX_CSS),
    '#options' => $options,
    '#description' => t('If 0 is selected then the bundler is disabled'),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-bundler-active' => array('checked' => FALSE),
      ),
    ),
  );
  $form['advagg_bundler_max_js'] = array(
    '#type' => 'select',
    '#title' => t('Target Number Of JS Bundles Per Page'),
    '#default_value' => variable_get('advagg_bundler_max_js', ADVAGG_BUNDLER_MAX_JS),
    '#options' => $options,
    '#description' => t('If 0 is selected then the bundler is disabled'),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-bundler-active' => array('checked' => FALSE),
      ),
    ),
  );

  $form['advagg_bundler_grouping_logic'] = array(
    '#type' => 'radios',
    '#title' => t('Grouping logic'),
    '#default_value' => variable_get('advagg_bundler_grouping_logic', ADVAGG_BUNDLER_GROUPING_LOGIC),
    '#options' => array(
      0 => t('File count'),
      1 => t('File size'),
    ),
    '#description' => t('If file count is selected then each bundle will try to have a similar number of original files aggregated inside of it. If file size is selected then each bundle will try to have a similar file size.'),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-bundler-active' => array('checked' => FALSE),
      ),
    ),
  );

  $form['info'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Raw Grouping Info'),
  );
  module_load_include('inc', 'advagg', 'advagg.admin');
  $analysis = advagg_bundler_analysis('', TRUE);

  $rawtext = print_r($analysis, TRUE);
  $form['info']['advagg_bundler_info'] = array(
    '#type' => 'textarea',
    '#title' => t('%count different groupings', array('%count' => count($analysis))),
    '#default_value' => $rawtext,
    '#rows' => 30,
  );

  // Clear the cache bins on submit. Also remove advagg_bundler_info so it
  // doesn't get added to the variable table.
  $form['#submit'][] = 'advagg_bundler_admin_settings_form_submit';

  return system_settings_form($form);
}

// Submit callback.
/**
 * Clear out the advagg cache bin when the save configuration button is pressed.
 */
function advagg_bundler_admin_settings_form_submit($form, &$form_state) {
  // Clear caches.
  advagg_cache_clear_admin_submit();

  // Unset advagg_bundler_info.
  if (isset($form_state['values']['advagg_bundler_info'])) {
    unset($form_state['values']['advagg_bundler_info']);
  }
}
