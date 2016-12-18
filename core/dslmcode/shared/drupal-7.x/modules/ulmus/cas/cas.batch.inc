<?php

/**
 * @file
 * Provides CAS batch functions.
 */

/**
 * CAS user creation batch callback.
 *
 * @param $cas_name
 *   The name of the CAS user.
 */
function cas_batch_user_add($cas_name, &$context) {
  $options = array(
    'invoke_cas_user_presave' => TRUE,
  );

  // Remove any whitespace around usernames.
  $cas_name = trim($cas_name);

  // Check if the account already exists.
  $existing_account = cas_user_load_by_name($cas_name);

  if ($existing_account == TRUE){
    $uri = entity_uri('user', $existing_account);
    $context['results']['messages']['already_exist'][] = t('<a href="@url">%name</a>', array('@url' => url($uri['path'], $uri['options']), '%name' => $existing_account->name));;
    return;
  }

  $account = cas_user_register($cas_name, $options);

  // Display error if user creation fails.
  if (!$account) {
    $context['results']['messages']['error'][] = t("@cas_name", array('@cas_name' => $cas_name));
  }
  else {
    $uri = entity_uri('user', $account);
    $context['results']['messages']['newly_created'][] = t('<a href="@url">%name</a>', array('@url' => url($uri['path'], $uri['options']), '%name' => $account->name));
    return $account;
  }
}

/**
 * CAS user creation 'finished' callback.
 * Consolidates message output.
 */
function cas_batch_user_finished($success, $results, $operations) {
  if ($success) {
    if (!empty($results['messages']['error'])) {
      drupal_set_message(t('Error occurred during account creation of %count CAS username(s): !usernames', array('%count' => count($results['messages']['error']), '!usernames' => implode(', ', $results['messages']['error']))), 'warning');
    }
    if (!empty($results['messages']['already_exist'])) {
      drupal_set_message(t('The following %count CAS username(s) are already in use on this site: !usernames', array('%count' => count($results['messages']['already_exist']), '!usernames' => implode(', ', $results['messages']['already_exist']))), 'warning');
    }
    if (!empty($results['messages']['newly_created'])) {
      drupal_set_message(t('The following %count CAS usernames were created: !usernames', array('%count' => count($results['messages']['newly_created']), '!usernames' => implode(', ', $results['messages']['newly_created']))));
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
}
