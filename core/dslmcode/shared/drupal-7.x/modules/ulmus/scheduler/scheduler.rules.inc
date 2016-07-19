<?php

/**
 * @file
 * Scheduler rules functions.
 */

/**
 * Implements hook_rules_event_info().
 */
function scheduler_rules_event_info() {
  // This hook function defines four Scheduler events which can be used by Rules
  // to trigger other actions.

  // Create an array of variables, as these are the same for each of the events.
  $variables = array(
    'node' => array(
      'type' => 'node',
      'label' => t('Scheduled Content Node'),
      'description' => t('The node object representing the scheduled content'),
    ),
    // Use both dates in all rules to give maximum flexibility for use within a
    // single event. The two dates do exist in the $node object, but will be 0
    // if no date is entered. Including the specific date variables gives more
    // flexibility because any non-entered date will be blank here not zero.
    'publish_on' => array(
      'type' => 'date',
      'label' => t('Scheduler Publish On date'),
      'description' => t('Date and time that the node will be published by Scheduler'),
    ),
    'unpublish_on' => array(
      'type' => 'date',
      'label' => t('Scheduler Unpublish On date'),
      'description' => t('Date and time that the node will be unpublished by Scheduler'),
    ),
  );

  // Define the events.
  $items = array(
    'scheduler_new_node_is_scheduled_for_publishing_event' => array(
      'label' => t('After saving new content that is scheduled for publishing'),
      'group' => t('Scheduler'),
      'variables' => $variables,
    ),
    'scheduler_existing_node_is_scheduled_for_publishing_event' => array(
      'label' => t('After updating existing content that is scheduled for publishing'),
      'group' => t('Scheduler'),
      'variables' => $variables,
    ),
    'scheduler_new_node_is_scheduled_for_unpublishing_event' => array(
      'label' => t('After saving new content that is scheduled for unpublishing'),
      'group' => t('Scheduler'),
      'variables' => $variables,
    ),
    'scheduler_existing_node_is_scheduled_for_unpublishing_event' => array(
      'label' => t('After updating existing content that is scheduled for unpublishing'),
      'group' => t('Scheduler'),
      'variables' => $variables,
    ),
    'scheduler_node_has_been_published_event' => array(
      'label' => t('After a node has been published by Scheduler'),
      'group' => t('Scheduler'),
      'variables' => $variables,
    ),
    'scheduler_node_has_been_unpublished_event' => array(
      'label' => t('After a node has been unpublished by Scheduler'),
      'group' => t('Scheduler'),
      'variables' => $variables,
    ),
  );
  return $items;
}

/**
 * Implements hook_rules_action_info().
 */
function scheduler_rules_action_info() {
  // These actions can be added when building a reaction rule. Use a $defaults
  // array to avoid duplication.
  $defaults = array(
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        // 'label' is shown as fieldset title after adding action.
        'label' => t('The node to be processed by Scheduler'),
        // 'description' is shown beneath the label during add/edit.
        'description' => t('This can be a node object or node id'),
      ),
    ),
    'group' => t('Scheduler'),
  );

  // 1. Action to set the publishing date.
  $actions['scheduler_set_publish_date_action'] = array('label' => t('Set publishing date')) + $defaults;
  $actions['scheduler_set_publish_date_action']['parameter']['date'] = array(
    'type' => 'date',
    'label' => t('The date for publishing'),
    'description' => t('The date when Scheduler will publish the node'),
  );

  // 2. Action to set the unpublishing date.
  $actions['scheduler_set_unpublish_date_action'] = array('label' => t('Set unpublishing date')) + $defaults;
  $actions['scheduler_set_unpublish_date_action']['parameter']['date'] = array(
    'type' => 'date',
    'label' => t('The date for unpublishing'),
    'description' => t('The date when Scheduler will unpublish the node'),
  );

  // 3. Action to remove the publishing date.
  $actions['scheduler_remove_publish_date_action'] = array('label' => t('Remove publishing date')) + $defaults;

  // 4. Action to remove the unpublishing date.
  $actions['scheduler_remove_unpublish_date_action'] = array('label' => t('Remove unpublishing date')) + $defaults;

  return $actions;
}

/**
 * Set the publish_on date for the node.
 *
 * @param $node
 *   The node object to be scheduled for publishing.
 * @param $date
 *   The date for publishing, a unix timestamp integer.
 */
function scheduler_set_publish_date_action($node, $date) {
  // When this action is invoked and it operates on the node being editted then
  // hook_node_presave() and hook_node_update() will be executed anyway. But if
  // this action is being used to schedule a different node then we need to call
  // the functions directly here.
  if (variable_get('scheduler_publish_enable_' . $node->type, 0)) {
    $node->publish_on = $date;
    scheduler_node_presave($node);
    scheduler_node_update($node);
  }
  else {
    $type_name = node_type_get_name($node->type);
    watchdog('scheduler', 'Scheduled publishing is not enabled for %type content. To prevent this message add the condition "Scheduled publishing is enabled" to your Rule, or enable the Scheduler options via the %type content type settings.', array('%type' => $type_name), WATCHDOG_WARNING, l(t('@type settings', array('@type' => $type_name)), 'admin/structure/types/manage/' . $node->type));
  }
}

/**
 * Set the unpublish_on date for the node.
 *
 * @param $node
 *   The node object to be scheduled for unpublishing.
 * @param $date
 *   The date for unpublishing, a unix timestamp integer.
 */
function scheduler_set_unpublish_date_action($node, $date) {
  if (variable_get('scheduler_unpublish_enable_' . $node->type, 0)) {
    $node->unpublish_on = $date;
    scheduler_node_presave($node);
    scheduler_node_update($node);
  }
  else {
    $type_name = node_type_get_name($node->type);
    watchdog('scheduler', 'Scheduled unpublishing is not enabled for %type content. To prevent this message add the condition "Scheduled unpublishing is enabled" to your Rule, or enable the Scheduler options via the %type content type settings.', array('%type' => $type_name), WATCHDOG_WARNING, l(t('@type settings', array('@type' => $type_name)), 'admin/structure/types/manage/' . $node->type));
  }
}

/**
 * Remove the publish_on date for the node.
 *
 * @param $node
 *   The node object from which to remove the publish_on date.
 */
function scheduler_remove_publish_date_action($node) {
  if (variable_get('scheduler_publish_enable_' . $node->type, 0)) {
    $node->publish_on = 0;
    scheduler_node_presave($node);
    scheduler_node_update($node);
  }
  else {
    $type_name = node_type_get_name($node->type);
    watchdog('scheduler', 'Scheduled publishing is not enabled for %type content. To prevent this message add the condition "Scheduled publishing is enabled" to your Rule, or enable the Scheduler options via the %type content type settings.', array('%type' => $type_name), WATCHDOG_WARNING, l(t('@type settings', array('@type' => $type_name)), 'admin/structure/types/manage/' . $node->type));
  }
}

/**
 * Remove the unpublish_on date for the node.
 *
 * @param $node
 *   The node object from which to remove the unpublish_on date.
 */
function scheduler_remove_unpublish_date_action($node) {
  if (variable_get('scheduler_unpublish_enable_' . $node->type, 0)) {
    $node->unpublish_on = 0;
    scheduler_node_presave($node);
    scheduler_node_update($node);
  }
  else {
    $type_name = node_type_get_name($node->type);
    watchdog('scheduler', 'Scheduled unpublishing is not enabled for %type content. To prevent this message add the condition "Scheduled unpublishing is enabled" to your Rule, or enable the Scheduler options via the %type content type settings.', array('%type' => $type_name), WATCHDOG_WARNING, l(t('@type settings', array('@type' => $type_name)), 'admin/structure/types/manage/' . $node->type));
  }
}

/**
 * Implements hook_rules_condition_info().
 */
function scheduler_rules_condition_info() {
  // Create a default, as most of the values are identical for all conditions.
  $default = array(
    'group' => t('Scheduler'),
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('The node to test for scheduling properties'),
        'description' => t('This can be a node object or node id'),
      ),
    ),
  );

  // 1. Condition to check if publishing is enabled for the content type.
  $conditions['scheduler_condition_publishing_is_enabled'] = array(
    'label' => t('Scheduled publishing is enabled for this content type')) + $default;

  // 2. Condition to check if unpublishing is enabled for the content type.
  $conditions['scheduler_condition_unpublishing_is_enabled'] = array(
    'label' => t('Scheduled unpublishing is enabled for this content type')) + $default;

  // 3. Condition to check if the node is scheduled for publishing.
  $conditions['scheduler_condition_node_is_scheduled_for_publishing'] = array(
    'label' => t('The node is scheduled for publishing')) + $default;

  // 4. Condition to check if the node is scheduled for unpublishing.
  $conditions['scheduler_condition_node_is_scheduled_for_unpublishing'] = array(
    'label' => t('The node is scheduled for unpublishing')) + $default;

  return $conditions;
}

/**
 * Determines whether scheduled publishing is enabled for this node type.
 *
 * @param $node
 *   A node object.
 * @return
 *   TRUE if scheduled publishing is enabled for the node type, FALSE if not.
 */
function scheduler_condition_publishing_is_enabled($node) {
  return (variable_get('scheduler_publish_enable_' . $node->type, 0) == 1);
}

/**
 * Determines whether scheduled unpublishing is enabled for this node type.
 *
 * @param $node
 *   A node object.
 * @return
 *   TRUE if scheduled unpublishing is enabled for the node type, FALSE if not.
 */
function scheduler_condition_unpublishing_is_enabled($node) {
  return (variable_get('scheduler_unpublish_enable_' . $node->type, 0) == 1);
}

/**
 * Determines whether a node is scheduled for publishing.
 *
 * @param $node
 *   A node object.
 * @return
 *   TRUE if the node is scheduled for publishing, FALSE if not.
 */
function scheduler_condition_node_is_scheduled_for_publishing($node) {
  return !empty($node->publish_on);
}

/**
 * Determines whether a node is scheduled for unpublishing.
 *
 * @param $node
 *   A node object.
 * @return
 *   TRUE if the node is scheduled for unpublishing, FALSE if not.
 */
function scheduler_condition_node_is_scheduled_for_unpublishing($node) {
  return !empty($node->unpublish_on);
}
