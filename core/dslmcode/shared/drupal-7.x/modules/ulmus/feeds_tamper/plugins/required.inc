<?php

/**
 * @file
 * Make field required. If not present, the feed item will be removed.
 */

$plugin = array(
  'form' => 'feeds_tamper_required_form',
  'callback' => 'feeds_tamper_required_callback',
  'name' => 'Required field',
  'multi' => 'direct',
  'category' => 'Filter',
);

function feeds_tamper_required_form($importer, $element_key, $settings) {
  $form = array();
  $form['help'] = array(
    '#markup' => t('Make this field required. If it is empty, the feed item will not be saved.'),
  );
  return $form;
}

function feeds_tamper_required_callback($result, $item_key, $element_key, &$field, $settings) {
  if (empty($field)) {
    unset($result->items[$item_key]);
  }
}
