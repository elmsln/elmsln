<?php

/**
 * @file
 * Drush plugin to perform a quick EntityFieldQuery.
 */

/**
 * Implementats of hook_drush_help().
 */
function drush_efq_drush_help($section) {
  switch ($section) {
    case 'drush:drush-efq':
      return dt("This command will allow you to query the drupal site via an EntityFieldQuery.");
  }
}

/**
 * Implementats hook_drush_command().
 */
function drush_efq_drush_command() {
  $items = array();
  $items['drush-efq'] = array(
    'description' => 'Run an EntityFieldQuery and get its output',
    'aliases' => array('efq'),
    'callback' => 'drush_efq_drush_efq',
    'arguments' => array(
      'entity_type' => dt('Entity type'),
      'entity_bundle' => dt('Entity bundle'),
      'extras' => dt('JSON array of possible values (optional)'),
      'role' => dt('name or RID of a drupal role, only used with user entity since role is not in scope of EFQ. (optional)'),
    ),
    'options' => array(
      'count' => dt('If we should return the resulting data or just a count.'),
      'format' => dt('Output format, options include json, var_export, etc.'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

/**
 * Drush command callback.
 */
function drush_efq_drush_efq($entity_type, $bundle, $extras = '[]', $role = NULL) {
  // pull items based on bundle
  $options = array();
  $extras = json_decode($extras);
  // assemble all entities requested
  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', $entity_type);
  // user entity doesn't respect querying on bundle
  if ($entity_type != 'user') {
    $query->entityCondition('bundle', $bundle);
  }
  foreach ($extras as $extra) {
    $condition_type = $extra->condition;
    $args = $extra->arguments;
    call_user_func_array(array($query,$condition_type), $args);
  }
  // execute
  $result = $query->execute();
  // convert to load only keys of items found
  $etids = array_keys($result[$entity_type]);
  // load all the entities in the array
  $elist = entity_load($entity_type, $etids);
  // account for role as this is outside scope of EFQ because of silliness
  if (!is_null($role) && $entity_type == 'user') {
    if (!$r = user_role_load_by_name($role)) {
      $r = user_role_load($role);
    }
    // make sure we have a fully loaded role
    if ($r) {
      foreach ($elist as $key => $entity) {
        // check that this entity has this role associated
        if (!isset($entity->roles[$r->rid])) {
          unset($elist[$key]);
        }
      }
    }
    else {
      drush_log(dt('Invalid role @role defined, ignoring filter', array('@role' => $role)), 'warning');
    }
  }
  // check for formats
  if (drush_get_option('count', FALSE)) {
    $elist = count($elist);
  }
  return drush_print_format($elist, 'print-r');
}