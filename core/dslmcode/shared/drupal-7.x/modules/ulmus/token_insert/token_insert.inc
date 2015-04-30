<?php
/**
 * @file
 * Helper functions for token_insert.module.
 */

function token_insert_get_tokens() {
  global $user;
  $roles['global'] = 'global';
  if (variable_get('token_insert_use_tokens_per_role', 0)) {
    $roles += $user->roles;
  }
  $all_tokens = token_get_info();
  foreach ($roles as $rid => $role) {
    foreach ($all_tokens['tokens'] as $category => $tokens) {
      // Check to see if all tokens are enabled for this category.
      $allow_all = variable_get('token_insert_' . $rid . '_all_tokens_' . $category, FALSE);
      if (!$allow_all) {
        $allowed_options = variable_get('token_insert_' . $rid . '_used_tokens_' . $category, array());
      }
      foreach ($tokens as $token => $description) {
        $full_token = '[' . $category . ':' . $token . ']';
        if ($allow_all) {
          $options[$full_token] = $category . ' : [' . $token . '] : ' . truncate_utf8($description['description'], 60, TRUE, TRUE);
        }
        else {
          if (!empty ($allowed_options)) {
            if (isset($allowed_options[$full_token]) && $allowed_options[$full_token]) {
              $options[$full_token] = $category . ' : [' . $token . '] : ' . truncate_utf8($description['description'], 60, TRUE, TRUE);
            }
            else {
              $all_options[$full_token] = $category . ' : [' . $token . '] : ' . truncate_utf8($description['description'], 60, TRUE, TRUE);
            }
          }
          else {
            $all_options[$full_token] = $category . ' : [' . $token . '] : ' . truncate_utf8($description['description'], 60, TRUE, TRUE);
          }
        }
      }
    }
  }
  if (empty($options)) {
    $options = $all_options;
  }
  return $options;
}

function token_insert_get_allowed_token_types() {
  global $user;
  $roles['global'] = 'global';
  if (variable_get('token_insert_use_tokens_per_role', 0)) {
    $roles += $user->roles;
  }
  $all_tokens = token_get_info();
  foreach ($roles as $rid => $role) {
    foreach ($all_tokens['tokens'] as $category => $tokens) {
      // Check to see if all tokens are enabled for this category.
      $allow_all = variable_get('token_insert_' . $rid . '_all_tokens_' . $category, FALSE);
      if (!$allow_all) {
        $allowed_options = variable_get('token_insert_' . $rid . '_used_tokens_' . $category, array());
      }
      foreach ($tokens as $token => $description) {
        $full_token = '[' . $category . ':' . $token . ']';
        if ($allow_all) {
          $options[$category] = $category;
          break;
        }
        else {
          if (!empty ($allowed_options)) {
            if (isset($allowed_options[$full_token]) && $allowed_options[$full_token]) {
              $options[$category] = $category;
              break;
            }
            else {
              $all_options[$category] = $category;
              break;
            }
          }
          else {
            $all_options[$category] = $category;
              break;
          }
        }
      }
    }
  }
  if (empty($options)) {
    $options = $all_options;
  }
  return $options;
}
