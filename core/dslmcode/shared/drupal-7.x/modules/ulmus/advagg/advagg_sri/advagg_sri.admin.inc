<?php

/**
 * @file
 * Admin page callbacks for the advagg sri module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup advagg_forms
 *
 * @see system_settings_form()
 */
function advagg_sri_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Subresource Integrity'));
  advagg_display_message_if_requirements_not_met();

  $form = array();
  $form['advagg_sri'] = array(
    '#type' => 'radios',
    '#title' => t('Subresource Integrity Level'),
    '#default_value' => variable_get('advagg_sri', ADVAGG_SRI),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('SHA-256'),
      2 => t('SHA-384'),
      3 => t('SHA-512'),
    ),
  );

  if (module_exists('httprl')) {
    $form['advagg_sri_file_generation'] = array(
      '#type' => 'checkbox',
      '#title' => t('Always output the page with the subresource integrity attribute.'),
      '#default_value' => variable_get('advagg_sri_file_generation', ADVAGG_SRI_FILE_GENERATION),
      '#description' => t('If checked - background processes will not usually be used when generating aggregated files; sometimes resulting in a slower page load. Noted though that the page cache is disabled if the all the aggregates do not have the integrity attribute.'),
    );
  }

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_sri_admin_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Submit callback, clears out the advagg cache bin.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_sri_admin_settings_form_submit($form, &$form_state) {
  // Clear caches.
  advagg_cache_clear_admin_submit();
}
