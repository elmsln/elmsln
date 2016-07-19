<?php

/**
 * @file
 * Scheduler functions to provide default rules and components.
 */

/**
 * Implements hook_default_rules_configuration().
 *
 * @return
 *   An array of rules configurations with the configuration names as keys.
 */
function scheduler_default_rules_configuration() {
  // Define two reaction rules which will be displayed on the 'Rules' tab. These
  // are initially inactive, but the user can enable them, and then modify the
  // values and/or add more conditions and actions.

  // 1. Reaction rule to send an email when Scheduler publishes content.
  $rule = rules_reaction_rule();
  $rule->label = t('Send e-mail when content is published by Scheduler');
  $rule->active = FALSE;
  $rule->event('scheduler_node_has_been_published_event')
    ->condition(rules_condition('data_is_empty', array('data:select' => 'node:author:mail', 'value' => TRUE))->negate())
    ->action('mail', array(
      'to' => '[node:author:mail]',
      'subject' => t("'[node:title]' has been published on [site:name]"),
      // Needs double quotes for the newlines to be evaluated.
      'message' => t("Dear [node:author:name],\r\nYour [node:type] '[node:title]' has been published on [site:name].\r\nThe link is [node:url]\r\n"),
    ));
  $rule->tags = array('Scheduler');
  $configs['scheduler_send_email_after_publishing_node'] = $rule;

  // 2. Reaction rule to send an email when Scheduler unpublishes content.
  $rule = rules_reaction_rule();
  $rule->label = t('Send e-mail when content is unpublished by Scheduler');
  $rule->active = FALSE;
  $rule->event('scheduler_node_has_been_unpublished_event')
    ->condition(rules_condition('data_is_empty', array('data:select' => 'node:author:mail', 'value' => TRUE))->negate())
    ->action('mail', array(
      'to' => '[node:author:mail]',
      'subject' => t("'[node:title]' has been unpublished on [site:name]"),
      'message' => t("Dear [node:author:name],\r\nYour [node:type] '[node:title]' has been unpublished on [site:name].\r\nThe link is [node:url]\r\n"),
    ));
  $rule->tags = array('Scheduler');
  $configs['scheduler_send_email_after_unpublishing_node'] = $rule;

  // Define four components which will be available in the 'Components' tab in
  // Rules admin. These are also available in Views Bulk Operations, to allow
  // a user to set or remove scheduling dates in bulk.

  // 1. Component to set the publishing date on a node.
  $rule = rule(array(
    'scheduler_node' => array(
      'type' => 'node',
      'label' => t('Node'),
      'description' => t('The node for publishing via Scheduler.'),
    ),
    'scheduler_publish_on_date' => array(
      'type' => 'date',
      'label' => t('Publish-on Date'),
      'description' => t('The publishing date to be used by Scheduler.'),
    ),
  ));
  $rule->label = t('Set scheduled publishing date');
  $rule
    ->condition('scheduler_condition_publishing_is_enabled', array(
      'node:select' => 'scheduler-node',
    ))
    // The keys required below are 'node:select' and 'date:select'. This is made
    // up of the key names defined in scheduler_rules_action_info() followed by
    // :select to specify data selection instead of plain text values.
    ->action('scheduler_set_publish_date_action', array(
      'node:select' => 'scheduler-node',
      'date:select' => 'scheduler-publish-on-date',
    ));
  $rule->tags = array('Scheduler');
  $configs['scheduler_set_publish_date_component'] = $rule;

  // 2. Component to set the unpublishing date on a node.
  $rule = rule(array(
    'scheduler_node' => array(
      'type' => 'node',
      'label' => t('Node'),
      'description' => t('The node for unpublishing via Scheduler.'),
    ),
    'scheduler_unpublish_on_date' => array(
      'type' => 'date',
      'label' => t('Unpublish-on Date'),
      'description' => t('The unpublishing date to be used by Scheduler.'),
    ),
  ));
  $rule->label = t('Set scheduled unpublishing date');
  $rule
    ->condition('scheduler_condition_unpublishing_is_enabled', array(
      'node:select' => 'scheduler-node',
    ))
    ->action('scheduler_set_unpublish_date_action', array(
      'node:select' => 'scheduler-node',
      'date:select' => 'scheduler-unpublish-on-date',
    ));
  $rule->tags = array('Scheduler');
  $configs['scheduler_set_unpublish_date_component'] = $rule;

  // 3. Component to remove the publishing date from a node.
  $rule = rule(array(
    'scheduler_node' => array(
      'type' => 'node',
      'label' => t('The scheduled node'),
      'description' => t('The node scheduled for publishing via Scheduler.'),
    ),
  ));
  $rule->label = t('Remove scheduled publishing date');
  $rule
    ->condition('scheduler_condition_node_is_scheduled_for_publishing', array(
      'node:select' => 'scheduler-node',
    ))
    ->action('scheduler_remove_publish_date_action', array(
      'node:select' => 'scheduler-node',
    ));
  $rule->tags = array('Scheduler');
  $configs['scheduler_remove_publish_date_component'] = $rule;

  // 4. Component to remove the unpublishing date from a node.
  $rule = rule(array(
    'scheduler_node' => array(
      'type' => 'node',
      'label' => t('The scheduled node'),
      'description' => t('The node scheduled for unpublishing via Scheduler.'),
    ),
  ));
  $rule->label = t('Remove scheduled unpublishing date');
  $rule
    ->condition('scheduler_condition_node_is_scheduled_for_unpublishing', array(
      'node:select' => 'scheduler-node',
    ))
    ->action('scheduler_remove_unpublish_date_action', array(
      'node:select' => 'scheduler-node',
    ));
  $rule->tags = array('Scheduler');
  $configs['scheduler_remove_unpublish_date_component'] = $rule;

  return $configs;
}
