<?php

/**
 * @file
 * Implements a generic entity delete action. Uses Entity API if available.
 */

function views_bulk_operations_delete_action_info() {
  return array(
    'views_bulk_operations_delete_item' => array(
      'type' => 'entity',
      'label' => t('Delete item'),
      'configurable' => FALSE,
      'behavior' => array('deletes_property'),
      'triggers' => array('any'),
    ),
    'views_bulk_operations_delete_revision' => array(
      'type' => 'entity',
      'label' => t('Delete revision'),
      'configurable' => FALSE,
      'behavior' => array('deletes_property'),
      'triggers' => array('any'),
    ),
  );
}

function views_bulk_operations_delete_item_views_bulk_operations_form($settings) {
  $form = array();
  $form['log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log individual deletions'),
    '#description' => t('Note: Deleting large amounts of entities will generate large amounts of log messages.'),
    '#default_value' => !empty($settings['log']),
  );

  return $form;
}

function views_bulk_operations_delete_item($entity, $context) {
  $info = entity_get_info($context['entity_type']);
  $entity_id = $entity->{$info['entity keys']['id']};

  entity_delete($context['entity_type'], $entity_id);

  // Add a message to the watchdog if we've been configured to do so.
  if (!empty($context['settings']['log'])) {
    // Log an appropriate message for this entity type, using the format from
    // the node, taxonomy and user module for their entity types.
    switch ($context['entity_type']) {
      case 'node':
        watchdog('content', '@type: deleted %title.', array('@type' => $entity->type, '%title' => $entity->title));
        break;

      case 'taxonomy_term':
        watchdog('taxonomy', 'Deleted term %name.', array('%name' => $entity->name), WATCHDOG_NOTICE);
        break;

      case 'user':
        watchdog('user', 'Deleted user: %name %email.', array('%name' => $entity->name, '%email' => '<' . $entity->mail . '>'), WATCHDOG_NOTICE);
        break;

      default:
        watchdog('entity', 'Deleted @type %label.', array('@type' => $context['entity_type'], '%label' => entity_label($context['entity_type'], $entity)));
        break;
    }
  }
}

function views_bulk_operations_delete_revision($entity, $context) {
  $info = entity_get_info($context['entity_type']);
  $revision_id = $entity->{$info['entity keys']['revision']};
  entity_revision_delete($context['entity_type'], $revision_id);
}
