<?php

/**
 * @file
 * Rules module drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function rules_drush_command() {
  $items = array();

  $items['rules-list'] = array(
    'description' => 'List all the active and inactive rules for your site.',
    'drupal dependencies' => array('rules'),
    'aliases' => array('rules'),
    'outputformat' => array(
      'default' => 'table',
      'pipe-format' => 'list',
      'field-labels' => array(
        'rule' => dt('Rule'),
        'label' => dt('Label'),
        'event' => dt('Event'),
        'active' => dt('Active'),
        'status' => dt('Status'),
      ),
      'output-data-type' => 'format-table',
    ),
  );
  $items['rules-enable'] = array(
    'description' => 'Enable a rule on your site.',
    'arguments' => array(
      'rule' => 'Rule name to enable.',
    ),
    'drupal dependencies' => array('rules'),
    'aliases' => array('re'),
  );
  $items['rules-disable'] = array(
    'description' => 'Disable a rule on your site.',
    'arguments' => array(
      'rule' => 'Rule name to export.',
    ),
    'drupal dependencies' => array('rules'),
    'aliases' => array('rd'),
  );
  $items['rules-revert'] = array(
    'description' => 'Revert a rule to its original state on your site.',
    'arguments' => array(
      'rule' => 'Rule name to revert.',
    ),
    'drupal dependencies' => array('rules'),
  );
  $items['rules-delete'] = array(
    'description' => 'Delete a rule on your site.',
    'arguments' => array(
      'rule' => 'Rules name to delete.',
    ),
    'drupal dependencies' => array('rules'),
  );
  $items['rules-export'] = array(
    'description' => 'Export a rule.',
    'arguments' => array(
      'rule' => 'Rules name to export.',
    ),
    'drupal dependencies' => array('rules'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function rules_drush_help($section) {
  switch ($section) {
    case 'drush:rules-list':
      return dt('List all the rules on your site.');

    case 'drush:rules-enable':
      return dt('Enable/activate a rule on your site.');

    case 'drush:rules-disable':
      return dt('Disable/deactivate a rule on your site.');

    case 'drush:rules-revert':
      return dt('Revert a module-provided rule to its original state on your site.');

    case 'drush:rules-delete':
      return dt('Delete a rule on your site.');

    case 'drush:rules-export':
      return dt('Export a rule.');
  }
}

/**
 * Get a list of all rules.
 */
function drush_rules_list() {
  $rules = rules_config_load_multiple(FALSE);
  $rows = array();
  foreach ($rules as $rule) {
    if (!empty($rule->name) && !empty($rule->label)) {
      $events = array();
      $event_info = rules_fetch_data('event_info');
      if ($rule instanceof RulesTriggerableInterface) {
        foreach ($rule->events() as $event_name) {
          $event_info += array(
            $event_name => array(
              'label' => dt('Unknown event "!event_name"', array('!event_name' => $event_name)),
            ),
          );
          $events[] = check_plain($event_info[$event_name]['label']);
        }
      }
      $rows[$rule->name] = array(
        'rule' => $rule->name,
        'label' => $rule->label,
        'event' => implode(', ', $events),
        'active' => $rule->active ? dt('Enabled') : dt('Disabled'),
        'status' => $rule->status ? theme('entity_status', array('status' => $rule->status, 'html' => FALSE)) : '',
      );
    }
  }
  if (version_compare(DRUSH_VERSION, '6.0', '<')) {
    drush_print_table($rows, TRUE);
  }
  return $rows;
}

/**
 * Enable a rule on the site.
 */
function drush_rules_enable() {
  $args = func_get_args();
  $rule_name = (!empty($args) && is_array($args)) ? array_shift($args) : '';
  if (empty($rule_name)) {
    return drush_set_error('', 'No rule name given.');
  }

  $rule = rules_config_load($rule_name);
  if (empty($rule)) {
    return drush_set_error('', dt('Could not load rule named "!rule-name".', array('!rule-name' => $rule_name)));
  }

  if (empty($rule->active)) {
    $rule->active = TRUE;
    $rule->save();
    drush_log(dt('The rule "!name" has been enabled.', array('!name' => $rule_name)), 'success');
  }
  else {
    drush_log(dt('The rule "!name" is already enabled.', array('!name' => $rule_name)), 'warning');
  }
}

/**
 * Disable a rule on the site.
 */
function drush_rules_disable() {
  $args = func_get_args();
  $rule_name = (!empty($args) && is_array($args)) ? array_shift($args) : '';
  if (empty($rule_name)) {
    return drush_set_error('', 'No rule name given.');
  }

  $rule = rules_config_load($rule_name);
  if (empty($rule)) {
    return drush_set_error('', dt('Could not load rule named "!rule-name".', array('!rule-name' => $rule_name)));
  }

  if (!empty($rule->active)) {
    $rule->active = FALSE;
    $rule->save();
    drush_log(dt('The rule "!name" has been disabled.', array('!name' => $rule_name)), 'success');
  }
  else {
    drush_log(dt('The rule "!name" is already disabled.', array('!name' => $rule_name)), 'warning');
  }
}

/**
 * Reverts a rule on the site.
 */
function drush_rules_revert() {
  $args = func_get_args();
  $rule_name = (!empty($args) && is_array($args)) ? array_shift($args) : '';
  if (empty($rule_name)) {
    return drush_set_error('', 'No rule name given.');
  }

  $rule = rules_config_load($rule_name);
  if (empty($rule)) {
    return drush_set_error('', dt('Could not load rule named "!rule-name".', array('!rule-name' => $rule_name)));
  }

  if (($rule->status & ENTITY_OVERRIDDEN) == ENTITY_OVERRIDDEN) {
    if (drush_confirm(dt('Are you sure you want to revert the rule named "!rule-name"? This action cannot be undone.', array('!rule-name' => $rule_name)))) {
      $rule->delete();
      drush_log(dt('The rule "!name" has been reverted to its default state.', array('!name' => $rule_name)), 'success');
    }
    else {
      drush_user_abort();
    }
  }
  else {
    drush_log(dt('The rule "!name" has not been overridden and can\'t be reverted.', array('!name' => $rule_name)), 'warning');
  }
}

/**
 * Deletes a rule on the site.
 */
function drush_rules_delete() {
  $args = func_get_args();
  $rule_name = (!empty($args) && is_array($args)) ? array_shift($args) : '';
  if (empty($rule_name)) {
    return drush_set_error('', 'No rule name given.');
  }

  $rule = rules_config_load($rule_name);
  if (empty($rule)) {
    return drush_set_error('', dt('Could not load rule named "!rule-name".', array('!rule-name' => $rule_name)));
  }

  if (drush_confirm(dt('Are you sure you want to delete the rule named "!rule-name"? This action cannot be undone.', array('!rule-name' => $rule_name)))) {
    $rule->delete();
    drush_log(dt('The rule "!name" has been deleted.', array('!name' => $rule_name)), 'success');
  }
  else {
    drush_user_abort();
  }
}

/**
 * Exports a single rule.
 */
function drush_rules_export() {
  $args = func_get_args();
  $rule_name = (!empty($args) && is_array($args)) ? array_shift($args) : '';
  if (empty($rule_name)) {
    return drush_set_error('', dt('No rule name given.'));
  }

  $rule = rules_config_load($rule_name);
  if (empty($rule)) {
    return drush_set_error('', dt('Could not load rule named "!rule-name".', array('!rule-name' => $rule_name)));
  }

  drush_print($rule->export());
  drush_log(dt('The rule "!name" has been exported.', array('!name' => $rule_name)), 'success');
}
