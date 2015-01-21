<?php

/**
 * @file
 * Rules integration for the Typo module.
 */

/**
 * Implements hook_rules_data_info().
 * @ingroup rules
 */
function typo_rules_data_info() {
  return array(
    'typo' => array(
      'label' => t('Typo'),
      'wrapper class' => 'TypoRulesDataWrapper',
     'wrap' => TRUE,
    ),
  );
}

/**
 * A custom wrapper class for flags to be used with Rules.
 * @ingroup rules
 */
class TypoRulesDataWrapper extends RulesIdentifiableDataWrapper {

  protected function extractIdentifier($typo) {
    return $typo->typo_id;
  }

  protected function load($typo) {
    return db_select('typo', 't')->fields('t', array('typo_id', 'url', 'created', 'status', 'uid', 'moderator_uid', 'text', 'comment'))->condition('t.typo_id', $typo->typo_id)->execute();
  }
}

/**
 * Implements hook_rules_event_info().
 */
function typo_rules_event_info() {
  $defaults = array(
    'group' => t('Typo'),
    'module' => 'typo',
    'access callback' => 'rules_typo_integration_access',
  );
  return array(
    'typo_report_added' => $defaults + array(
      'label' => t('After saving a new typo report'),
      'variables' => array(
        'typo' => array(
          'type' => 'typo',
          'label' => t('Created typo report'),
        ),
      ),
    ),
  );
}

/**
 * Typo integration access callback.
 */
function rules_typo_integration_access($type, $name) {
  return user_access('may send typo reports');
}
