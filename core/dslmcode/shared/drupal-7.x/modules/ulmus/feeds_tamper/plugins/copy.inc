<?php

/**
 * @file
 * Copy value from one source to another.
 */

$plugin = array(
  'form' => 'feeds_tamper_copy_form',
  'callback' => 'feeds_tamper_copy_callback',
  'name' => 'Copy source value',
  'multi' => 'direct',
);

function feeds_tamper_copy_form($importer, $element_key, $settings) {
  $form = $sources = array();
  $source_configs = $importer->parser->getMappingSources();
  foreach ($importer->processor->config['mappings'] as $mapping) {
    $sources[$mapping['source']] = isset($source_configs[$mapping['source']]) ? $source_configs[$mapping['source']]['name'] : $mapping['source'];
  }

  $form['to_from'] = array(
    '#title' => t('To or from'),
    '#type' => 'radios',
    '#default_value' => isset($settings['to_from']) ? $settings['to_from'] : 'to',
    '#options' => array('to' => t('To'), 'from' => t('From')),
    '#description' => t('Select wheter this source value should be copied <em>to</em> another source, or <em>from</em> another source to this one.'),
  );

  $form['source'] = array(
    '#type' => 'radios',
    '#default_value' => isset($settings['source']) ? $settings['source'] :key($sources),
    '#options' => $sources,
    '#title' => t('Source'),
  );

  return $form;
}

function feeds_tamper_copy_callback($result, $item_key, $element_key, &$field, $settings) {
  switch ($settings['to_from']) {
    case 'to':
      $result->items[$item_key][$settings['source']] = $field;
      return;
    case 'from':
      $field = $result->items[$item_key][$settings['source']];
      return;
  }
}
