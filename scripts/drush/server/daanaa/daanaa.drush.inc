<?php

/**
 * @file
 * Drush plugin to bulk switch content ownership.
 */

/**
 * Implementats of hook_drush_help().
 */
function daanaa_drush_help($section) {
  switch ($section) {
    case 'drush:daanaa':
      return dt("This command will change ownership of all content from 1 user to another.");
  }
}

/**
 * Implementats hook_drush_command().
 */
function daanaa_drush_command() {
  $items = array();
  $items['daanaa'] = array(
    'description' => 'Pass in a userid to change ownership of all content from that user to another.',
    'aliases' => array('dana'),
    'callback' => 'daanaa_what_r_yinz_doin',
    'arguments' => array(
      'uid1' => dt('username or id to transfer FROM'),
      'uid2' => dt('username or id to transfer TO'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

/**
 * Drush command callback.
 */
function daanaa_what_r_yinz_doin($uid1 = NULL, $uid2 = NULL) {
  // make sure we have any users
  if (empty($uid1) && $uid1 != 0) {
    drush_log(dt("Yinz workin the turnpike this weekend?"), 'warning');
    drush_log(dt("Translation: You need to supply two user accounts."), 'error');
    return FALSE;
  }
  // make sure we have 2 users
  if (empty($uid2) && $uid2 != 0) {
    drush_log(dt("Yinz don't got pop?!"), 'warning');
    drush_log(dt("Translation: You need to supply another user account to transfer ownership to."), 'error');
    return FALSE;
  }
  // we allow for users to be loaded by name as well
  if (!is_numeric($uid1)) {
    $tmp = user_load_by_name($uid1);
    if (isset($tmp->uid)) {
      $uid1 = $tmp->uid;
    }
    else {
      drush_log(dt("Hey @name, yinz warsh'in yer clothes dan by pantz n'at?", array('@name' => $uid1)), 'warning');
      drush_log(dt("Translation: @name does not exist", array('@name' => $uid1)),'error');
      return FALSE;
    }
  }
  // we allow for users to be loaded by name as well
  if (!is_numeric($uid2)) {
    $tmp = user_load_by_name($uid2);
    if (isset($tmp->uid)) {
      $uid2 = $tmp->uid;
    }
    else {
      drush_log(dt("Hey @name, yinz go'an dantan to see the Clarks? We're goin ta Permannies after.", array('@name' => $uid2)), 'warning');
      drush_log(dt("Translation: @name does not exist", array('@name' => $uid2)),'error');
      return FALSE;
    }
  }
  // load both so this message makes sense...
  $u1 = user_load($uid1);
  $u2 = user_load($uid2);
  // account for annonymous
  if ($u1->uid == 0) {
    $u1->name = t('Anonymous');
  }
  if ($u2->uid == 0) {
    $u2->name = t('Anonymous');
  }
  // make sure they really want to do this since it can't be undone
  drush_print(dt("Hold the phone here knuckleheads! @name1, @name2 where yinz goin, Kennywood? We got DVE on the car radio and a bucket of Iron City for the Stillers.", array('@name1' => $u1->name, '@name2' => $u2->name)));
  if (drush_confirm(dt("Translation: Are you sure you want to make all of user @name1's content now be owned by @name2 ? This cannot be undone.", array('@name1' => $u1->name, '@name2' => $u2->name)))) {
    // assemble all nodes requested
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node');
    $query->propertyCondition('uid', $uid1, '=');
    $result = $query->execute();
    // convert to load only keys of items found
    $etids = array_keys($result['node']);
    // load all the entities in the array
    $nodes = entity_load('node', $etids);
    foreach ($nodes as $node) {
      $node->uid = $uid2;
      node_save($node);
    }
    return TRUE;
  }
  else {
    drush_print(dt("Whew, good. Grab yer terrible towls and let's get back to the tailgate!"));
    return FALSE;
  }
}