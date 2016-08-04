<?php

/**
 * @file
 * Settings form.
 */

/**
 * Config form shown at admin/config/services/puzzler
 */
function puzzler_admin($form, &$form_state) {

  $intervals = array(
    'z' => 'No cache',
    60 => '1 minute',
    3*60 => '3 minutes',
    5*60 => '5 minutes',
    15*60 => '15 minutes',
    30*60 => '30 minutes',
    60*60 => '1 hour',
    3*60*60 => '3 hours',
    5*60*60 => '5 hours',
    15*60*60 => '15 hours',
    24*60*60 => '1 day',
    3*24*60*60 => '3 days',
    7*24*60*60 => '1 week',
    30*24*60*60 => '1 month',
    4*30*24*60*60 => '3 months',
    6*30*24*60*60 => '6 months',
    365*24*60*60 => '1 year',
  );
  //dpm($intervals);
  $form['puzzler_cache'] = array(
    '#type' => 'select',
    '#title' => t('Time before fetching new data'),
    '#default_value' => variable_get('puzzler_cache', PUZZLER_CACHE_DURATION),
    '#description' => t('Duration to keep the fetched data in cache. Can be overridden when using PHP snippets. Default: %defaultcache.', array('%defaultcache' => check_plain('1 day'))),
    '#options' => $intervals,
    '#required' => TRUE,
  );

  $form['puzzler_fallback_language'] = array(
    '#type' => 'textfield',
    '#title' => t('Fallback language'),
    '#default_value' => variable_get('puzzler_fallback_language', PUZZLER_FALLBACK_LANGUAGE),
    '#size' => 3,
    '#maxlength' => 2,
    '#description' => t('If there is no language defined in the node, use this value as a fallback. Can be overridden when using PHP snippets. Default: %puzzler_fallback_language.', array('%puzzler_fallback_language' => PUZZLER_FALLBACK_LANGUAGE)),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
