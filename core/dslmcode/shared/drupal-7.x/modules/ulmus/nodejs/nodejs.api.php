<?php

/**
 * @file
 * API documentation for the Nodejs integration module.
 */

/**
 * Define handlers for custom messages received from the Node JS Server.
 *
 * @param String $type
 *   The type of message received from the Node JS Server. Serves to identify
 *   the specific extension of the server that sent the message to the drupal
 *   site. This is set by developers when writing their server extensions.
 *
 *   As an example, a module implementing this hook, and returning a function
 *   called "mymodule_message_handler", will have to implement that
 *   function as follows:
 *
 *   function mymodule_message_handler($message, &$response) {
 *     // Do whatever is needed with the message received.
 *     tell_mom_about_the_message($message);
 *
 *     // Tell something back to the Node JS server.
 *     $response = array(
 *       'message' => 'Thanks, I just told my mom about this!';
 *     );
 *   }
 *
 * @return array
 *   An array of function names. These functions will be executed sequentally,
 *   and will receive the original $message from the server, and a $response
 *   variable passed by reference, which they should use as per they needs. This
 *   variable is what will be sent back automatically by the nodejs module to
 *   the Node JS server.
 */
function hook_nodejs_message_callback($type) {
  switch ($type) {
    // Not necessarily camelCase, but since the type is set on javascript, it'll
    // be usually camelCased.
    case 'myMessageType':
      return array('my_message_handler');
  }
}

/**
 * Define a list of socket.io channels the user will be automatically added to,
 * upon being registered / authenticated in the Node JS server.
 *
 * When a user is added to a channel through this function, he will receive then
 * all messages sent to these channels, without having to call manually the
 * nodejs_add_user_to_channel() function to get the user added to the channel.
 *
 * Note that this hook doesn't provide any kind of wildcard capability, so it's
 * not suitable for all scenarios (e.g: when dealing with channels generated
 * dynamically, for example based on the url the user is visiting). In those
 * cases, the user will have to be added through nodejs_add_user_to_channel().
 *
 * @param stdClass $account
 *   The Drupal account of the user for which the allowed channels are being
 *   checked. This may be an anonymous user.
 *
 * @return array
 *   An array of socket.io channels to which the user will be granted access.
 */
function hook_nodejs_user_channels($account) {
  // Create a channel for each authenticated user.
  if ($account->uid > 0) {
    return array('nodejs_user_' . $account->uid);
  }
}

/**
 * Specifies the list of users that can see presence information (whether a user
 * is connected to the Node JS server or not) about a given account.
 *
 * @param stdClass $account
 *   The Drupal account of the user whose presence information access is being
 *   requested. This may be an anonymous user.
 *
 * @return array
 *   An array of User ids, representing the users that can check the presence
 *   on the Node JS server of the user specified in $account.
 */
function hook_nodejs_user_presence_list($account) {
  if ($account->uid > 0) {
    return array(
      array_keys(my_module_get_friends($account)),
    );
  }
}

/**
 * Add javascript files on pages where Nodejs is loaded.
 *
 * Use this when needing more JS assets in *every* page where Nodejs is loaded,
 * but not in cases where the assets might not always be required. For that
 * scenario, it's better to manually load the files when required, through
 * drupal_add_js().
 *
 * @return array
 *   An array of paths to javascript files to be included on the page.
 */
function hook_nodejs_handlers_info() {
  return array(
    drupal_get_path('module', 'my_nodejs_module') . '/my_nodejs_module.js',
  );
}

