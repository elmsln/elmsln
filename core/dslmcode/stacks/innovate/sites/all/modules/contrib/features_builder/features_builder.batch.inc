<?php

/**
 * @file
 * Batch operations for Features Builder.
 */

/**
 * Batch operation to create Features.
 */
function features_builder_build_batch($manifest, $options, &$context) {
  module_load_include('inc', 'features_builder', 'features_builder.build');

  if (empty($context['sandbox'])) {
    $context['sandbox']['manifest'] = $manifest;
    $context['sandbox']['total'] = count($context['sandbox']['manifest']);
  }

  $keys = array_keys($context['sandbox']['manifest']);
  $built = array();
  $count = 0;

  while ($count++ < 10 && count($keys)) {
    // Pluck the next feature from the list to create.
    $feature = array_shift($keys);
    $built[] = variable_get('features_builder_prefix_name') . '_' . $feature;

    // Build it.
    features_builder_build($feature, $context['sandbox']['manifest'][$feature]);
    unset($context['sandbox']['manifest'][$feature]);
  }

  if (!empty($options['enable'])) {
    system_list_reset();
    module_enable($built);
  }

  $context['message'] = t('Building feature @feature', array('@feature' =>  $feature));
  $context['finished'] = 1 - (count($context['sandbox']['manifest']) / $context['sandbox']['total']);
}

function features_builder_batch_finalize($success, $results, $operations) {

  if (module_exists('fxx')) {
    module_load_include('inc', 'fxx', 'fxx.explode');
    fxx_export_explode();
  }

  drupal_flush_all_caches();
  drupal_set_message(t('Features build complete.'));
}
