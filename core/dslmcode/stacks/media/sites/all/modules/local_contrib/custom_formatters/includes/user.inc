<?php
/**
 * @file
 * User module integration.
 */

/**
 * Implements hook_custom_formatters_devel_generate_info() on behalf of
 * user.module.
 */
function user_custom_formatters_devel_generate_info() {
  return array(
    'user' => array(
      'process callback' => 'custom_formatters_user_devel_generate_process',
    ),
  );
}

/**
 * Process callback for User Devel Generate integration.
 */
function custom_formatters_user_devel_generate_process($form_state) {
  module_load_include('inc', 'devel_generate', 'devel_generate');

  $url = parse_url($GLOBALS['base_url']);

  $object = new stdClass();
  $object->uid = mt_rand(3, 100);
  $object->name = devel_generate_word(mt_rand(6, 12));
  $object->pass = user_password();
  $object->mail = "{$object->name}@{$url['host']}";
  $object->status = 1;
  $object->created = 1;
  $object->roles = drupal_map_assoc(array(DRUPAL_AUTHENTICATED_RID));
  $object->language = LANGUAGE_NONE;

  // Populate all core fields on behalf of field.module
  module_load_include('inc', 'devel_generate', 'devel_generate.fields');
  devel_generate_fields($object, 'user', 'user');

  return $object;
}
