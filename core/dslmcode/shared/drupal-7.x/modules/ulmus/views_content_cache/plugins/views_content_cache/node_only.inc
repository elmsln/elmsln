<?php
/**
 * @file
 * Provides the Views content cache node only plugin.
 */

class views_content_cache_key_node_only extends views_content_cache_key {
  function options_form($value, &$handler = NULL) {
    return array(
      '#title' => t('Node only'),
      '#description' => t('Allows the node segment to be refined to only include main operations create/update/delete. Be careful about combing with other node related segments.'),
      '#type' => 'checkboxes',
      '#options' => array(
        'node_changed' => t('Nodes updated/created/deleted'),
      ),
      '#default_value' => $value,
    );
  }

  function content_key($object, $object_type) {
    if ($object_type === 'node') {
      return 'node_changed';
    }
  }
}
