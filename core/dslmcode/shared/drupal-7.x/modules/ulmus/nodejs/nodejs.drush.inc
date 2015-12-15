<?php

/**
 * Implements hook_drush_help().
 */
function nodejs_drush_help($section) {
  switch ($section) {
    case 'drush:broadcast-message':
      return dt('Broadcast a message to all connected cliets.');
    case 'drush:channel-message':
      return dt('Send a message to all users subscribed to a given channel.');
    case 'drush:user-message':
      return dt('Send a message to a given user.');
    case 'drush:user-message-multiple':
      return dt('Send a message to a the given list of users.');
    case 'drush:role-message':
      return dt('Send a message to all user with the given role.');
    case 'drush:kick-user':
      return dt('Kick the given user off the node.js server.');
  }
}

/**
 * Implements hook_drush_command().
 */
function nodejs_drush_command() {
  $items['broadcast-message'] = array(
    'callback' => 'nodejs_broadcast_message',
    'description' => 'Broadcast a message to all connected cliets.',
    'arguments' => array(
      'subject' => 'The subject of the message to broadcast.',
      'body' => 'The body of message to broadcast.',
    ),
  );
  $items['channel-message'] = array(
    'callback' => 'nodejs_send_channel_message',
    'description' => 'Send a message to all users subscribed to a given channel.',
    'arguments' => array(
      'channel' => 'The channel to send the message to send.',
      'subject' => 'The subject of the message to send.',
      'body' => 'The body of message to send.',
    ),
  );
  $items['user-message'] = array(
    'callback' => 'nodejs_send_user_message',
    'description' => 'Send a message to a given user.',
    'arguments' => array(
      'uid' => 'The user id of the message recipient.',
      'subject' => 'The subject of the message.',
      'body' => 'The body of message.',
    ),
  );
  $items['user-message-multiple'] = array(
    'callback' => 'nodejs_send_user_message_multiple',
    'description' => 'Send a message to multiple users.',
    'arguments' => array(
      'uids' => 'The user ids of the message recipients, seperated by comma(,)',
      'subject' => 'The subject of the message.',
      'body' => 'The body of message.',
    ),
  );
  $items['role-message'] = array(
    'callback' => 'nodejs_send_role_message',
    'description' => 'Send a message to users in a role.',
    'arguments' => array(
      'role' => 'The role name',
      'subject' => 'The subject of the message.',
      'body' => 'The body of message.',
    ),
  );
  $items['kick-user'] = array(
    'callback' => 'nodejs_kick_user',
    'description' => 'Kick the given user off the node.js server.',
    'arguments' => array(
      'uid' => 'The user id of the person to be kicked off.',
    ),
  );
  return $items;
}

