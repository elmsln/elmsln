<?php
/**
 * @file
 * Provides the Views content cache node plugin.
 */

class views_content_cache_key_node extends views_content_cache_key {
  function options_form($value, &$handler = NULL) {
    return array(
      '#title' => t('Node types'),
      '#description' => t('Checks for new or updated nodes of any of the selected types.'),
      '#type' => 'checkboxes',
      '#options' => array_merge(node_type_get_names(), $this->additional_options_for_arguments($handler->view)),
      '#default_value' => $value,
      '#weight' => -10,
    );
  }

  function content_key($object, $object_type) {
    if ($object_type === 'node') {
      return $object->type;
    }
    elseif ($object_type === 'comment' && !empty($object->nid) && ($node = node_load($object->nid))) {
      return $node->type;
    }
  }

  /**
   * We support using the node type argument for the view key
   */
  function view_key_from_arguments() {
    return array('views_handler_argument_node_type');
  }
}
