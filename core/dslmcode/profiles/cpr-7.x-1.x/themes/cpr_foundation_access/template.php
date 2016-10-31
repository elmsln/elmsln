<?php

/**
 * User profile template preprocess.
 */
function cpr_foundation_access_preprocess_user_profile(&$vars) {
  $vars['displayname'] = '';
  if (isset($vars['field_first_name'][0]['safe_value'])) {
    $vars['displayname'] .= $vars['field_first_name'][0]['safe_value'] . ' ';
  }
  if (isset($vars['field_last_name'][0]['safe_value'])) {
    $vars['displayname'] .= $vars['field_last_name'][0]['safe_value'];
  }
  if (isset($vars['field_display_name'][0]['safe_value'])) {
    $vars['displayname'] .= ' | ' . $vars['field_display_name'][0]['safe_value'];
  }
}