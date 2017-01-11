<?php

/**
 * @file
 * Rules integration for the Flag module.
 */

/**
 * Implements hook_rules_data_info().
 * @ingroup rules
 */
function flag_rules_data_info() {
  return array(
    'flag' => array(
      'label' => t('flag'),
      'ui class' => 'FlagRulesUIClass',
      'wrapper class' => 'FlagRulesDataWrapper',
      'wrap' => TRUE,
    ),
    'flagging' => array(
      'label' => t('flagging'),
      'parent' => 'entity',
      'group' => t('flag'),
    ),
  );
}

/**
 * A custom wrapper class for flags to be used with Rules.
 * @ingroup rules
 */
class FlagRulesDataWrapper extends RulesIdentifiableDataWrapper implements RulesDataWrapperSavableInterface {

  protected function extractIdentifier($flag) {
    return $flag->name;
  }

  protected function load($name) {
    return flag_get_flag($name);
  }

  public function save() {
    $flag = $this->value();
    $flag->save();
  }

  public function validate($value) {
    if (isset($value) && is_string($value)) {
      return TRUE;
    }
    elseif (isset($value) && is_object($value) && $value instanceof flag_flag) {
      return TRUE;
    }
    return parent::validate($value);
  }
}

/**
 * UI for inputing flags.
 * @ingroup rules
 */
class FlagRulesUIClass extends RulesDataUI implements RulesDataDirectInputFormInterface {

  public static function getDefaultMode() {
    return 'input';
  }

  public static function inputForm($name, $info, $settings, RulesPlugin $element) {
    $options = _flag_rules_flags_options(isset($info['flag_type']) ? $info['flag_type'] : NULL);
    $header  = array(
      'title' => t('Flag:'),
      'type' => t('The flag type'),
      'global' => t('Is the flag global?'),
    );
    $settings += array($name => isset($info['default value']) ? $info['default value'] : '');

    $form[$name] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#required' => empty($info['optional']),
      '#multiple' => FALSE,
      '#default_value' => $settings[$name],
      '#empty' => t('There is no suiting flag available.'),
    );
    return $form;
  }

  public static function render($value) {
    $flag = flag_get_flag($value);

    if ($flag === FALSE) {
      return array();
    }

    return array(
      'content' => array('#markup' => check_plain($flag->get_title())),
      '#attributes' => array('class' => array('rules-parameter-flag')),
    );
  }
}

function _flag_rules_flags_options($flag_type = NULL) {
  $flags = flag_get_flags();
  $options = array();
  foreach ($flags as $flag) {
    if (!isset($flag_type) || $flag->entity_type == $flag_type) {
      $options[$flag->name] = array(
        'title' => $flag->get_title(),
        'type' => $flag->entity_type,
        'global' => $flag->global ? t('Yes') : t('No'),
      );
    }
  }
  return $options;
}

/**
 * Implements hook_rules_event_info().
 */
function flag_rules_event_info() {
  $items = array();

  $flags = flag_get_flags();
  foreach ($flags as $flag) {
    // We only support flags on entities.
    if ($info = entity_get_info($flag->entity_type)) {
      $variables = array(
        'flag' => array(
          'type' => 'flag',
          'label' => t('flag'),
          'flag_type' => $flag->entity_type,
        ),
        'flagged_' . $flag->entity_type => array(
          'type' => $flag->entity_type,
          'label' => $info['label'],
        ),
        'flagging_user' => array(
          'type' => 'user',
          'label' => t('flagging user'),
        ),
        'flagging' => array(
          'type' => 'flagging',
          'label' => t('flagging'),
        ),
      );

      // For each flag we define two events.
      $items['flag_flagged_' . $flag->name] = array(
        'group' => t('Flag'),
        'label' => t('A @flag-type has been flagged, under "@flag-title"', array('@flag-title' => $flag->get_title(), '@flag-type' => t($flag->entity_type))),
        'variables' => $variables,
        'access callback' => 'flag_rules_integration_access',
      );
      $items['flag_unflagged_' . $flag->name] = array(
        'group' => t('Flag'),
        'label' => t('A @flag-type has been unflagged, under "@flag-title"', array('@flag-title' => $flag->get_title(), '@flag-type' => t($flag->entity_type))),
        'variables' => $variables,
        'access callback' => 'flag_rules_integration_access',
      );
    }
  }
  return $items;
}

/**
 * Implements hook_rules_action_info().
 */
function flag_rules_action_info() {
  $param_defaults = array(
    'flagging_user' => array(
      'type' => 'user',
      'label' => t('User on whose behalf to flag'),
      'description' => t('For non-global flags, this is the user on whose behalf to flag the object. In addition, if checked below, the access permissions to the flag are checked against this user.'),
    ),
    'permission_check' => array(
      'type' => 'boolean',
      'label' => t('Skip permission check'),
      'description' => t('Whether to ignore permissions of the user on whose behalf to flag.'),
      'restriction' => 'input',
    ),
  );
  $items = array(
    'flag_trim' => array(
      'label' => t('Trim a flag'),
      'base' => 'flag_rules_action_trim',
      'parameter' => array(
        'flag' => array(
          'type' => 'flag',
          'label' => t('Flag'),
        ),
        'flagging_user' => array(
          'type' => 'user',
          'label' => t('User whose flag to trim'),
          'description' => t('For non-global flags, this is the user whose flag to trim. (For global flags, this argument is ignored.)'),
        ),
        'cutoff_size' => array(
          'type' => 'integer',
          'label' => t('Flag queue size'),
          'description' => t('The maximum number of objects to keep in the queue. Newly flagged objects will be kept; older ones will be removed. Tip: by typing "1" here you implement a singleton.'),
        ),
        'trim_newest' => array(
          'type' => 'boolean',
          'label' => t('Trim newest flags'),
          'description' => t('Checking this will trim the newest flags.  This will prevent new flags once a limit is reached.'),
        ),
        'permission_check' => $param_defaults['permission_check'],
      ),
      'group' => t('Flag'),
      'access callback' => 'flag_rules_integration_access',
    ),
    'fetch_overall_flag_count' => array(
      'label' => t('Fetch overall flag count'),
      'base' => 'flag_rules_action_fetch_overall_flag_count',
      'parameter' => array(
        'flag' => array(
          'type' => 'flag',
          'label' => t('Flag'),
        ),
      ),
      'provides' => array(
        'overall_flag_count' => array(
          'label' => t('Overall flag count'),
          'description' => t('During a flagging/unflagging event the count
            will take into account the current flagging/unflagging procedure.'),
          'type' => 'integer',
        ),
      ),
      'group' => t('Flag'),
      'access callback' => 'flag_rules_integration_access',
    ),
    'fetch_entity_flag_count' => array(
      'label' => t('Fetch entity flag count'),
      'base' => 'flag_rules_action_fetch_entity_flag_count',
      'parameter' => array(
        'flag' => array(
          'type' => 'flag',
          'label' => t('Flag'),
        ),
        'entity_type' => array(
          'type' => 'text',
          'label' => t('Entity type'),
          'options list' => 'flag_rules_get_flag_types',
          'restriction' => 'input',
        ),
      ),
      'provides' => array(
        'entity_flag_count' => array(
          'label' => t('Entity flag count'),
          'description' => t('During a flagging event, the count
            will take into account the current flagging procedure. For
            an unflagging event, the count will NOT yet be decreased for the
            current unflagging procedure.'),
          'type' => 'integer',
        ),
      ),
      'group' => t('Flag'),
      'access callback' => 'flag_rules_integration_access',
    ),
    'fetch_user_flag_count' => array(
      'label' => t('Fetch user flag count'),
      'base' => 'flag_rules_action_fetch_user_flag_count',
      'parameter' => array(
        'flag' => array(
          'type' => 'flag',
          'label' => t('Flag'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
      'provides' => array(
        'user_flag_count' => array(
          'label' => t('User flag count'),
          'description' => t('During a flagging event, the count
            will take into account the current flagging procedure. For
            an unflagging event, the count will NOT yet be decreased for the
            current unflagging procedure.'),
          'type' => 'integer',
        ),
      ),
      'group' => t('Flag'),
      'access callback' => 'flag_rules_integration_access',
    ),
  );
  foreach (flag_get_types() as $type) {
    $entity_info = entity_get_info($type);
    $label = $entity_info['label'];
    $items += array(
      'flag_fetch_' . $type . '_by_user' => array(
        'label' => t('Fetch @label flagged by user', array('@label' => $label)),
        'base' => 'flag_rules_action_fetch_entity_by_user',
        'parameter' => array(
          'flag' => array(
            'type' => 'flag',
            'label' => t('Flag'),
            'flag_type' => $type,
            'description' => t('The flag to check for.'),
          ),
          'flagging_user' => array(
            'type' => 'user',
            'label' => t('User who flagged the @label', array('@label' => $label)),
            'description' => t('For non-global flags, this is the user who flagged the @label. (For global flags, this argument is ignored.)', array('@label' => $label)),
          ),
        ),
        'provides' => array(
          'content_flagged_by_user' => array(
            'label' => t('Content flagged by user'),
            'type' => 'list<' . $type . '>',
          ),
        ),
        'group' => t('Flag'),
        'access callback' => 'flag_rules_integration_access',
      ),
      'flag_flag' . $type => array(
        'label' => t('Flag a @label', array('@label' => $label)),
        'base' => 'flag_rules_action_flag',
        'parameter' => array(
          'flag' => array(
            'type' => 'flag',
            'label' => t('Flag'),
            'flag_type' => $type,
            'description' => t('The flag to check for.'),
          ),
          $type => array(
            'type' => $type,
            'label' => $label,
          ),
        ) + $param_defaults,
        'group' => t('Flag'),
        'access callback' => 'flag_rules_integration_access',
      ),
      'flag_unflag' . $type => array(
        'label' => t('Unflag a @label', array('@label' => $label)),
        'base' => 'flag_rules_action_unflag',
        'parameter' => array(
          'flag' => array(
            'type' => 'flag',
            'label' => t('Flag'),
            'flag_type' => $type,
            'description' => t('The flag to check for.'),
          ),
          $type => array(
            'type' => $type,
            'label' => $label,
          ),
        ) + $param_defaults,
        'group' => t('Flag'),
        'access callback' => 'flag_rules_integration_access',
      ),
    );
    $items['flag_fetch_users_' . $type] = array(
      'label' => t('Fetch users who have flagged a @label', array('@label' => $label)),
      'base' => 'flag_rules_action_fetch_users',
      'parameter' => array(
        'flag' => array(
          'type' => 'flag',
          'label' => t('Flag'),
          'flag_type' => $type,
          'description' => t('Choose the flag for which to fetch the users.'),
        ),
        $type => array(
          'type' => $type,
          'label' => $label,
        ),
      ),
      'provides' => array(
        'users' => array(
          'label' => t('Users who flagged'),
          'type' => 'list<user>',
        ),
      ),
      'group' => t('Flag'),
      'access callback' => 'flag_rules_integration_access',
    );
  }
  // For backward compatibility sake. This was the original name of the
  // 'fetch node by user'.
  $items['flag_fetch_entity_by_user'] = $items['flag_fetch_node_by_user'];
  $items['flag_fetch_entity_by_user']['label'] .= ' ' . t('(Legacy)');
  return $items;
}

/**
 * Base action implementation: Flag.
 */
function flag_rules_action_flag($flag, $entity, $flagging_user, $permissions_check) {
  $flag->flag('flag', $flag->get_entity_id($entity), $flagging_user, $permissions_check);
}

/**
 * Base action implementation: Unflag.
 */
function flag_rules_action_unflag($flag, $entity, $flagging_user, $permissions_check) {
  $flag->flag('unflag', $flag->get_entity_id($entity), $flagging_user, $permissions_check);
}

/**
 * Base action implementation: Trim flag.
 */
function flag_rules_action_trim($flag, $flagging_user, $cutoff_size, $trim_newest, $permissions_check) {
  // For some reason, when this action fires in response to a flagging event,
  // as an anonymous user, then the $flagging_user is sent through as FALSE.
  // Not sure why. This workaround fixes the problem in this specific case.
  if ($flagging_user === FALSE) {
    $flagging_user = $GLOBALS['user'];
  }
  flag_trim_flag($flag, $flagging_user, $cutoff_size, $trim_newest, $permissions_check);
}

/**
 * Base action implementation: Fetch users who flagged an entity.
 */
function flag_rules_action_fetch_users($flag, $entity) {
  $result = db_select('flagging', 'fc')
    ->fields('fc', array('uid'))
    ->condition('entity_type', $flag->entity_type)
    ->condition('entity_id', $flag->get_entity_id($entity))
    ->condition('fid', $flag->fid)
    ->execute();
  $uids = $result->fetchCol();
  // Filter out anonymous users.
  return array('users' => array_filter($uids));
}

/**
 * Base action implementation: Fetch entities flagged by a user.
 */
function flag_rules_action_fetch_entity_by_user($flag, $entity) {
  $query = db_select('flagging', 'fc')
    ->fields('fc', array('entity_id'))
    ->condition('entity_type', $flag->entity_type)
    ->condition('fid', $flag->fid);
  // For global flags the user parameter is ignored, so we add the
  // extra 'uid' condition when the flag is NOT global.
  if (!$flag->global) {
    $user = entity_metadata_wrapper('user', $entity);
    $sid = $user->flag_sid->value();
    $query = $query->condition('uid', $user->uid->value());
    // Filter out any bad session ids and any users that aren't anonymous.
    if (!empty($sid) && $sid != -1) {
      $query->condition('sid', $sid);
    }
  }
  $result = $query->execute();
  $flagged = $result->fetchCol();
  return array('content_flagged_by_user' => $flagged);
}

/**
 * Base action implementation: Fetch overall count for a particular flag.
 *
 * The count that is returned during a flagging or an unflagging will take into
 * account the current flag/unflag process.
 */
function flag_rules_action_fetch_overall_flag_count($flag) {
  $count = flag_get_flag_counts($flag->name);
  return array('overall_flag_count' => $count);
}

/**
 * Helper function which will return all the available flag types.
 *
 *  @return
 *  An array of flag type names keyed by the type name.
 */
function flag_rules_get_flag_types() {
  $types = array();
  foreach (flag_get_types() as $type) {
    $types[$type] = $type;
  }
  return $types;
}

/**
 * Base action implementation: Fetch count of flags for a particular entity
 * type.
 *
 * During a flagging, the current flagging will be included in the count.
 * During an unflagging, the current flagging being removed will not yet have
 * been removed from the count.
 */
function flag_rules_action_fetch_entity_flag_count($flag, $entity_type) {
  $count = flag_get_entity_flag_counts($flag, $entity_type);
  return array('entity_flag_count' => $count);
}

/**
 * Base action implementation: Fetch user's flag count.
 *
 * During a flagging, the current flagging will be included in the count.
 * During an unflagging, the current flagging will not yet have been removed
 * from the count.
 */
function flag_rules_action_fetch_user_flag_count($flag, $user) {
  $count = flag_get_user_flag_counts($flag, $user);
  return array('user_flag_count' => $count);
}

/**
 * Implements hook_rules_condition_info().
 */
function flag_rules_condition_info() {
  $items = array();
  foreach (flag_get_types() as $type) {
    $entity_info = entity_get_info($type);
    $label = isset($entity_info[$type]['label']) ? $entity_info[$type]['label'] : $type;
    $items += array(
      'flag_threshold_' . $type => array(
        'label' => drupal_ucfirst(t('@type has flagging count', array('@type' => $label))),
        'base' => 'flag_rules_condition_threshold',
        'parameter' => array(
          'flag' => array(
            'type' => 'flag',
            'label' => t('Flag'),
            'flag_type' => $type,
            'description' => t('The flag to check for.'),
          ),
          $type => array(
            'type' => $type,
            'label' => $label,
          ),
          'number' => array(
            'type' => 'integer',
            'label' => t('Number'),
            'description' => t('The number against which to test the number of
              times the object is flagged. For example, if you type "3" here,
              and choose "Greater than" for the operator, then this condition
              will return TRUE if the object is flagged more than three times.
              During a flagging or an unflagging event the count will take into
              account the current flag/unflag process.'),
          ),
          'operator' => array(
            'type' => 'text',
            'label' => t('Comparison operator'),
            'options list' => 'flag_rules_condition_threshold_operator_options',
            'restriction' => 'input',
            'default value' => '=',
            'optional' => TRUE,
          ),
        ),
        'group' => t('Flag'),
        'access callback' => 'flag_rules_integration_access',
      ),
      'flag_flagged_' . $type => array(
        'label' => drupal_ucfirst(t('@type is flagged', array('@type' => $label))),
        'base' => 'flag_rules_condition_flagged',
        'parameter' => array(
          'flag' => array(
            'type' => 'flag',
            'label' => t('Flag'),
            'flag_type' => $type,
            'description' => t('The flag to check for.'),
          ),
          $type => array(
            'type' => $type,
            'label' => $label,
          ),
          'flagging_user' => array(
            'type' => 'user',
            'label' => t('User on whose behalf to check'),
            'description' => t('For non-global flags, this is the user on whose behalf the flag is checked.'),
          ),
        ),
        'group' => t('Flag'),
        'access callback' => 'flag_rules_integration_access',
      ),
    );
  }
  return $items;
}

/**
 * Options list callback for the operator parameter of the flagging threshold
 * condition.
 */
function flag_rules_condition_threshold_operator_options() {
  return array(
    '>'  => t('Greater than'),
    '>=' => t('Greater than or equal'),
    '='  => t('Equal to'),
    '<=' => t('Less than or equal'),
    '<'  => t('Less than'),
  );
}

/**
 * Condition: Check flagging count.
 *
 * The count that is returned during a flagging or an unflagging will take into
 * acount the current flag/unflag process.
 */
function flag_rules_condition_threshold($flag, $entity, $number, $operator = '=') {
  $count = $flag->get_count($flag->get_entity_id($entity));

  switch ($operator) {
    case '>': return $count > $number;
    case '>=': return $count >= $number;
    case '=': return $count == $number;
    case '<': return $count < $number;
    case '<=': return $count <= $number;
  }
}

/**
 * Condition: Flag is flagged.
 */
function flag_rules_condition_flagged($flag, $entity, $account) {
  return $flag->is_flagged($flag->get_entity_id($entity), $account->uid);
}

/**
 * Rules integration access callback.
 */
function flag_rules_integration_access($type, $name) {
  return user_access('administer flags');
}
