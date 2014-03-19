<?php
/**
 * @file
 * Implements a generic entity delete action. Uses Entity API if available.
 */

/**
 * Implements hook_action_info().
 */
function replicate_ui_replicate_action_info() {
  return array(
    'replicate_ui_replicate_item' => array(
      'type' => 'entity',
      'label' => t('Replicate item'),
      'configurable' => FALSE,
      'behavior' => array('replicates_property'),
    ),
  );
}

/**
 * Callback for replicate_action_info().
 */
function replicate_ui_replicate_item($entity, $context) {
  // account for context params so they can be passed for VBO processing
  if (isset($context['params'])) {
    $entity->action_params = $context['params'];
  }

  // Duplicate the entity and save the replica.
  replicate_entity($context['entity_type'], $entity);
}
