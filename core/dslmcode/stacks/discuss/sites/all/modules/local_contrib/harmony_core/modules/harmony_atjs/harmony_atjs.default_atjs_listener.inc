<?php
/**
 * @file
 * harmony_atjs.default_atjs_listener.inc
 */

/**
 * Implements hook_default_atjs_listener().
 */
function harmony_atjs_default_atjs_listener() {
  $export = array();

  $listener = new stdClass();
  $listener->disabled = FALSE; /* Edit this to true to make a default listener disabled initially */
  $listener->api_version = 1;
  $listener->name = 'harmony_users';
  $listener->title = 'Users';
  $listener->entity_type = 'user';
  $listener->bundles = array();
  $listener->record_usage = TRUE;
  $listener->at = '@';
  $listener->tpl = '<li data-value="${atwho-at}${name}">${avatar}${name}</li>';
  $listener->insert_tpl = '<span>${atwho-data-value}</span>';
  $listener->search_key = 'property:name';
  $listener->data_to_supply = array(
    'name' => 'name',
    'uid' => 0,
    'pass' => 0,
    'mail' => 0,
    'theme' => 0,
    'signature' => 0,
    'signature_format' => 0,
    'created' => 0,
    'access' => 0,
    'login' => 0,
    'status' => 0,
    'timezone' => 0,
    'language' => 0,
    'picture' => 0,
    'init' => 0,
    'data' => 0,
    'field_harmony_post_count' => 0,
    'field_harmony_thread_count' => 0,
    'og_user_node' => 0,
  );
  $listener->query_limit = 5;
  $listener->max_length = 10;
  $export['harmony_users'] = $listener;

  return $export;
}
