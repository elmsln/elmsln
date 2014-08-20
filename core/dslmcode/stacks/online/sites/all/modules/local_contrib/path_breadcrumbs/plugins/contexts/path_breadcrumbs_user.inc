<?php

/**
 * @file
 * Plugin to provide a user context with more flexible convert callback.
 */

$plugin = array(
  'title' => t("User"),
  'description' => t('A single user object.'),
  'context' => 'ctools_context_create_user',
  'edit form' => 'ctools_context_user_settings_form',
  'defaults' => array('type' => 'select', 'uid' => ''),
  'keyword' => 'user',
  'context name' => 'path_breadcrumbs_user',
  'convert list' => 'ctools_context_user_convert_list',
  'convert' => 'path_breadcrumbs_ctools_context_user_convert',
  'convert default' => 'name',

  // This context is deprecated and should not be usable in the UI.
  'no ui' => TRUE,
  'no required context ui' => TRUE,
);

/**
 * Convert a context into a string.
 */
function path_breadcrumbs_ctools_context_user_convert($context, $type) {
  $values = token_generate('user', array($type => $type), array('user' => $context->data));
  if (isset($values[$type])) {
    return $values[$type];
  }
}
