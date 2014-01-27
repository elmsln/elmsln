<?php
/**
 * @file
 * wysiwyg plugin hook.
 */

function token_insert_get_tokens() {
  global $user;
  $roles['global'] = 'global';
  if(variable_get('token_insert_use_tokens_per_role', 0)){
    $roles += $user->roles;
  }
  $all_tokens = token_get_info();
  foreach($roles as $rid => $role){
    foreach ($all_tokens['tokens'] as $category => $tokens) {
      $allowed_options = variable_get('token_insert_' . $rid . '_used_tokens_' . $category, array());
      foreach ($tokens as $token => $description) {
        if (!empty ($allowed_options)) {
          if (isset($allowed_options[$token]) && $allowed_options[$token] === $token) {
            $options[$category . ':' . $token] = $category . ' : [' . $token . '] : ' . truncate_utf8($description['description'], 60, TRUE, TRUE);
          }
          else {
            $all_options[$category . ':' . $token] = $category . ' : [' . $token . '] : ' . truncate_utf8($description['description'], 60, TRUE, TRUE);
          }
        }
        else{
          $all_options[$category . ':' . $token] = $category . ' : [' . $token . '] : ' . truncate_utf8($description['description'], 60, TRUE, TRUE);
        }
      }
    }
  }
  if (empty($options)) {
    $options = $all_options;
  }
  return $options;

  
}

