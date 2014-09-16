<?php
// $Id$

/**
 * @file
 * Provides Rules integration for the Voting API module
 */

/**
 * Implementation of hook_rules_data_type_info().
 */
function voting_rules_rules_data_info() {
  // Default properties common to vote and vote results.
  $defaults = array(
    'entity_type' => array(
      'label' => t('Entity type'),
      'description' => t('The type of the entity.'),
      'type' => 'token', // Unrelated with token module! Means machine name.
    ),
    'entity_id' => array(
      'label' => t('Entity ID'),
      'description' => t('The entity ID.'),
      'type' => 'integer',
    ),
    'entity' => array(
      'label' => t('Entity'),
      'description' => t('The entity being voted on.'),
      'type' => 'entity',
      'getter callback' => 'voting_rules_get_property',
    ),
    'value_type' => array(
      'label' => t('Value type'),
      'description' => t('The value type.'),
      'type' => 'token',
    ),
    'value' => array(
      'label' => t('Value'),
      'description' => t('The value of the vote.'),
      'type' => 'decimal',
    ),
    'timestamp' => array(
      'label' => t('Date'),
      'description' => t('The date of the vote.'),
      'type' => 'date',
    ),
    'tag' => array(
      'label' => t('Tag'),
      'description' => t('The tag.'),
      'type' => 'token',
    ),
  );
  
  // Data info for vote and vote results.
  $data_info = array(
    'vote' => array(
      'label' => t('Vote'),
      'description' => t('A vote.'),
      'group' => t('Voting API'),
      'wrap' => TRUE,
      'property info' => array(
        'uid' => array(
          'label' => t("User ID"),
          'description' => t('The user ID.'),
          'type' => 'integer',
          'description' => t("The unique ID of the user account."),
        ),
        'user' => array(
          'label' => t("User"),
          'description' => t('The user account.'),
          'type' => 'user',
          'getter callback' => 'voting_rules_get_property',
        ),
        'vote_source' => array(
          'label' => t('Vote source'),
          'description' => t('The source of the vote.'),
          'type' => 'text',
        ),
        'prepped' => array(
          'label' => t('Prepped'),
          'description' => t('Whether the vote was prepopulated or not.'),
          'type' => 'boolean',
        ),
        'vote_id' => array(
          'label' => t('Vote ID'),
          'description' => t('The vote ID.'),
          'type' => 'integer',
        ),
      ) + $defaults,
    ),
    'vote_results' => array(
      'label' => t('Vote Results'),
      'description' => t('The vote results.'),
      'group' => t('Voting API'),
      'property info' => array(),
      'wrap' => TRUE,
    ),
  );
  
  // Format vote result data info for each defined calculation function (count,
  // sum, average...).
  $votingapi_metadata = votingapi_metadata();
  
  foreach ($votingapi_metadata['functions'] as $function => $info) {
    $data_info['vote_results']['property info'][$function] = array(
      'label' => $info['name'],
      'description' => $info['description'],
      'type' => 'vote_result',
      'wrap' => TRUE,
      'property info' => array(
        'vote_cache_id' => array(
          'label' => t("Cache ID"),
          'type' => 'integer',
        ),
        'function' => array(
          'label' => t("Function"),
          'type' => 'text',
        ),
      ) + $defaults,
    );
  }

  return $data_info;
}

/**
 * Implementation of hook_rules_data_info_alter().
 */
function voting_rules_rules_data_info_alter(&$data_info) {
  $entity_types = voting_rules_get_types();
  
  foreach ($entity_types as $entity_type => $label) {
    $data_info[$entity_type]['property info']['votes'] = array(
      'label' => t('Vote'),
      'description' => t('The vote.'),
      'type' => 'list<vote>',
      'getter callback' => 'voting_rules_get_votes',
    );
    $data_info[$entity_type]['property info']['vote_results'] = array(
      'label' => t('Vote results'),
      'description' => t('The vote results.'),
      'type' => 'vote_results',
      'wrap' => TRUE,
      'getter callback' => 'voting_rules_get_vote_results',
    );
  }
}

/**
 * Implementation of hook_rules_event_info().
 */
function voting_rules_rules_event_info() {
  $entity_types = voting_rules_get_types();
  $events = array();

  foreach ($entity_types as $entity_type => $label) {
    $events['voting_rules_insert_' . $entity_type] = array(
      'label' => t('User votes on a @label', array('@label' => $label)),
      'variables' => array(
        'vote' => array(
      		'label' => t('Vote'),
      		'description' => t('The vote.'),
          'type' => 'vote',
          'label' => t('The vote'),
        ),
        $entity_type => array(
        	'label' => $label,
        	'description' => t("The @label being voted on", array('@label' => $label)),
          'type' => $entity_type,
        ),
      ),
      'group' => t('Voting API'),
    );

    $events['voting_rules_delete_' . $entity_type] = array(
      'label' => t('User deletes a vote on a @label', array('@label' => $label)),
      'variables' => array(
        'vote' => array(
      		'label' => t('Vote'),
      		'description' => t('The vote.'),
          'type' => 'vote',
        ),
        $entity_type => array(
        	'label' => $label,
        	'description' => t("The @label being voted on", array('@label' => $label)),
          'type' => $entity_type,
        ),
      ),
      'group' => t('Voting API'),
    );

    $events['voting_rules_results_' . $entity_type] = array(
      'label' => t('Votes are calculated for a @label', array('@label' => $label)),
      'variables' => array(
        'vote_results' => array(
      		'label' => t('Vote results'),
      		'description' => t('The vote results.'),
          'type' => 'vote_results',
        ),
        $entity_type => array(
        	'label' => $label,
        	'description' => t("The @label being voted on", array('@label' => $label)),
          'type' => $entity_type,
        ),
      ),
      'group' => t('Voting API'),
    );
  }

  return $events;
}

/**
 * Implementation of hook_rules_condition_info().
 */
function voting_rules_rules_condition_info() {
  return array(
    'voting_rules_condition_check_vote_value' => array(
      'label' => t('Check the value of the vote'),
      'named parameter' => TRUE,
      'parameter' => array(
        'vote' => array(
      		'label' => t('Vote'),
      		'description' => t('The vote.'),
          'type' => 'vote',
        ),
        'operator' => array(
          'type' => 'text',
          'label' => t('Operator'),
          'description' => t('The comparison operator.'),
          'optional' => TRUE,
          'default value' => '==',
          'options list' => 'voting_rules_condition_operator_options',
          'restriction' => 'input',
        ),
        'value' => array(
          'type' => 'text',
          'label' => t('Data value'),
          'description' => t('The value to compare the data with.'),
        ),
      ),
      'group' => t('Voting API'),
    ),
    'voting_rules_condition_check_results' => array(
      'label' => t('Evaluate the results of a vote'),
      'named parameter' => TRUE,
      'parameter' => array(
        'vote_results' => array(
      		'label' => t('Vote results'),
      		'description' => t('The vote results.'),
          'type' => 'vote_results',
        ),
        'function' => array(
          'type' => 'text',
          'label' => t('Function'),
          'description' => t('The function used to compute the value.'),
          'default value' => 'sum',
          'options list' => 'voting_rules_condition_function_options',
          'restriction' => 'input',
        ),
        'operator' => array(
          'type' => 'text',
          'label' => t('Operator'),
          'description' => t('The comparison operator.'),
          'default value' => '==',
          'options list' => 'voting_rules_condition_operator_options',
          'restriction' => 'input',
        ),
        'value' => array(
          'type' => 'text',
          'label' => t('Data value'),
          'description' => t('The value to compare the data with.'),
        ),
      ),
      'group' => t('Voting API'),
    ),
  );
}

/**
 * Options list: Operators.
 */
function voting_rules_condition_operator_options() {
  return array(
    '==' => t('equals'),
    '<' => t('is lower than'),
    '<=' => t('is lower than or equal to'),
    '>' => t('is greather than'),
    '>=' => t('is greather than or equal to'),
  );
}

/**
 * Options list: Supported calculation functions.
 */
function voting_rules_condition_function_options() {
	$functions = array();
  $votingapi_metadata = votingapi_metadata();
  
  foreach ($votingapi_metadata['functions'] as $function => $info) {
  	$functions[$function] = $info['name'];
  }
  
  return $functions;
}

/**
 * Condition: Evaluate the results of the vote.
 */
function voting_rules_condition_check_results($args, RulesCondition $condition, $op) {
  foreach ($args['vote_results'] as $vote_result) {
    if ($vote_result['function'] == $args['function']) {
      return eval('return ' . (float) $vote_result['value'] . $args['operator'] . (float) $args['value'] . ';');
    }
  }
}

/**
 * Condition: Check the value of an individual vote.
 */
function voting_rules_condition_check_vote_value($args, RulesCondition $condition, $op) {
	if (in_array($args['operator'], array_keys(voting_rules_condition_operator_options()))) {
  	return eval('return ' . (float) $args['vote']['value'] . $args['operator'] . (float) $args['value'] . ';');
  }
}
