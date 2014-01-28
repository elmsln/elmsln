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
        'account' => array(
          'type' => 'node',
          'label' => t('Node to replicate'),
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