<?php

/**
 * @file
 * Replicate Rules code: actions, conditions and events.
 */

/**
 * Implements hook_rules_action_info().
 */
function replicate_ui_rules_action_info() {
  $actions = array(
    'replicate_ui_replicate_user' => array(
      'label' => t('Replicate a User Account'),
      'group' => t('Replicate'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User to replicate'),
        ),
      ),
    ),
    'replicate_ui_replicate_node' => array(
      'label' => t('Replicate a Node'),
      'group' => t('Replicate'),
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node to replicate'),
        ),
      ),
      'provides' => array(
        'replica_node' => array(
          'type' => 'node',
          'label' => t('Replica node'),
        ),
      ),
    ),
    'replicate_ui_replicate_entity' => array(
      'label' => t('Replicate an Entity'),
      'group' => t('Replicate'),
      'parameter' => array(
        'type' => array(
          'type' => 'text',
          'label' => t('Entity type'),
          'options list' => 'rules_entity_action_type_options',
          'description' => t('Specifies the type of the entity that should be created.'),
          'restriction' => 'input',
        ),
        'entity' => array(
          'type' => 'unknown',
          'label' => t('Entity to replicate'),
        ),
      ),
      'provides' => array(
        'replica_entity' => array(
          'type' => 'entity',
          'label' => t('Replica node'),
        ),
      ),
    ),
  );
  if (module_exists('replicate_field_collection')) {
    $actions['replicate_ui_replicate_field_collection'] = array(
      'label' => t('Replicate a Field Collection Item'),
      'group' => t('Replicate'),
      'parameter' => array(
        'account' => array(
          'type' => 'field_collection_item',
          'label' => t('Field Collection Item to replicate'),
        ),
      ),
    );
  }

  return $actions;
}

/**
 * The action function for the 'replicate_ui_replicate_user'.
 */
function replicate_ui_replicate_user($account) {
  $new = replicate_entity('user', $account);
  if ($new) {
    drupal_set_message(t('User @username has been replicated!', array('@username' => $account->name)));
  }
}

/**
 * The action function for the 'replicate_ui_replicate_node'.
 */
function replicate_ui_replicate_node($node) {
  $new = replicate_entity('node', $node);
  if ($new) {
    drupal_set_message(t('Node @title has been replicated!', array('@title' => $node->title)));
    return array('replica_node' => $new);
  }
}

/**
 * The action function for the 'replicate_ui_replicate_entity'.
 */
function replicate_ui_replicate_entity($type, $id) {
  $toclone = entity_load_single($type, $id);
  $toclone->id = null;
  $new = replicate_entity($type, $toclone);
  if ($new) {
    drupal_set_message(t('Entity @title has been replicated!', array('@title' => $toclone->title)));
    return array('replica_entity' => $new);
  }
}

/**
 * The action function for the 'replicate_ui_replicate_field_collection'.
 */
function replicate_ui_replicate_field_collection($field_collection) {
  $new = replicate_entity('field_collection_item', $field_collection);
  if ($new) {
    drupal_set_message(t('Field Collection @id has been replicated!', array('@id' => $field_collection->item_id)));
  }
}

/**
 * Implements of hook_rules_event_info().
 * @ingroup rules
 */

function replicate_ui_rules_event_info() {
  $defaults = array(
    'module' => 'replicate_ui',
    'group' => t('Replicate'),
  );
  return array(
    'replicate_ui_after_replication' => $defaults +
    array(
      'label' => t('After Replication'),
      'variables' => array(
        'replica' => array('type' => 'entity', 'label' => t('Replicate / Clone')),
        'entity_type' => array('type' => 'text', 'label' => t('Entity type')),
        'original' => array('type' => 'entity', 'label' => t('Original')),
      ),
    ),
  );
}