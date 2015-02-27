<?php

/**
 * @file Node clone rules functions
 */

/**
 * Implementation of hook_rules_event_info.
 */
function clone_rules_event_info() {
  // Let rules know about the node clone event.
  $items = array(
    'clone_node' => array(
      'label' => t('After cloning a node'),
      'group' => t('Node'),
      'variables' => array(
        'cloned_node' => array('type' => 'node', 'label' => t('The cloned node')),
        'original_node' => array('type' => 'node', 'label' => t('The original node')),
      ),
    ),
  );
  return $items;
}
