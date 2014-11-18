<?php
/**
 * @file
 * cis_tokens.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function cis_tokens_defaultconfig_features() {
  return array(
    'cis_tokens' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function cis_tokens_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tipsy';
  $strongarm->value = array(
    'drupal_forms' => array(
      'forms' => 0,
      'options' => array(
        'fade' => 1,
        'gravity' => 'autoWE',
        'delayIn' => '0',
        'delayOut' => '0',
        'trigger' => 'focus',
        'opacity' => '0.8',
        'offset' => '0',
      ),
    ),
    'custom_selectors' => array(
      0 => array(
        'selector' => '.tipsy',
        'options' => array(
          'fade' => 1,
          'gravity' => 'w',
          'trigger' => 'hover',
          'delayIn' => '0',
          'delayOut' => '0',
          'opacity' => '0.8',
          'offset' => '0',
          'html' => 0,
          'tooltip_content' => array(
            'source' => 'attribute',
            'selector' => 'title',
          ),
        ),
      ),
      1 => array(
        'selector' => '.cis_token_dynamic_value',
        'options' => array(
          'fade' => 1,
          'gravity' => 'autoNS',
          'trigger' => 'hover',
          'delayIn' => '0',
          'delayOut' => '0',
          'opacity' => '1',
          'offset' => '5',
          'html' => 1,
          'tooltip_content' => array(
            'source' => 'attribute',
            'selector' => 'data-cis-token',
          ),
        ),
      ),
    ),
  );
  $export['tipsy'] = $strongarm;

  return $export;
}
