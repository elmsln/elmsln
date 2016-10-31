<?php

/**
 * @file
 * Menu page callbacks for the lti operations launch,
 * return as well as home and info.
 */

/**
 * LTI launch.
 *
 * Implements the [base_url]/lti path which is called to launch the
 * tool from the LMS
 *  - Verifies the request using OAuth and adds the lti context_info
 *    to the session
 *  - Authenticates the user, possibly after provisioning the account
 *  - Authorises the user via global role mapping
 *  - If OG is configured a course may be provisioned from the
 *    context_info and group roles are mapped
 *  - Finally the destination is calculated and user is redirected there.
 *
 * @return string
 *   Page content.
 */
function lti_tool_provider_launch() {
  global $user;
  // If not an LTI launch request, then ignore.
  if (!lti_tool_provider_is_basic_lti_request()) {
    if (isset($_REQUEST['launch_presentation_return_url'])) {
      lti_tool_provider_goto(url($_REQUEST['launch_presentation_return_url'], array('query' => array('lti_errormsg' => t('Error: Not a LTI request.')))));
    }
    else {
      drupal_set_message(t('Error: Not a LTI request.'), 'error');
      return t('Error: Not a LTI request.');
    }
  }
  // Insure we have a valid context.
  if (empty($_REQUEST['oauth_consumer_key'])) {
    unset($_SESSION['lti_tool_provider_context_info']);
    if (isset($_REQUEST['launch_presentation_return_url'])) {
      lti_tool_provider_goto(url($_REQUEST['launch_presentation_return_url'], array('query' => array('lti_errormsg' => t(t('Not a valid LTI context.'))))));
    }
    else {
      drupal_set_message(t('Error: Invalid context. Missing oauth_consumer_key in request.'), 'error');
      return t('Error: Invalid context. Missing oauth_consumer_key in request.');
    }
  }
  // Begin a new session based on this LTI launch request.
  drupal_session_start();
  $oauth_consumer_key = $_REQUEST["oauth_consumer_key"];
  // Verify the message signature.
  $store = new LTIToolProviderOAuthDataStore();
  $server = new OAuthServer($store);
  $method = new OAuthSignatureMethod_HMAC_SHA1();
  $server->add_signature_method($method);
  $request = OAuthRequest::from_request();
  try {
    $server->verify_request($request);
    // This is a LTI launch request.
  } catch (Exception $e) {
    if (isset($_REQUEST['launch_presentation_return_url'])) {
      lti_tool_provider_goto(url($_REQUEST['launch_presentation_return_url'], array('query' => array('lti_errormsg' => t('Error: Invalid context, OAuth failure.')))));
    }
    else {
      drupal_set_message(check_plain($e->getMessage()), 'error');
      return t('Error: Invalid context, OAuth failure.');
    }
  }
  // Collect the launch information for later storage in the session.
  $launch_info = $request->get_parameters();

  /*if (empty($launch_info['context_id'])) {
    if (isset($launch_info['launch_presentation_return_url'])) {
      lti_tool_provider_goto(url($launch_info['launch_presentation_return_url'], array('query' => array('lti_errormsg' => t('Error: Invalid context, No context Id.')))));
    }
    else {
      return t('Error: Invalid context, No context Id.');
    }
  }*/
  $consumer = lti_tool_provider_get_consumer_by_key($oauth_consumer_key);
  $launch_info['consumer_id'] = $consumer->lti_tool_provider_consumer_id;
  $launch_info['consumer_domain'] = $consumer->lti_tool_provider_consumer_domain;

  if(!empty($consumer->lti_tool_provider_consumer_alternative_user_id_field))
  {
    //Here we use the alternate user ID field for the user.
    $lti_user = $launch_info[$consumer->lti_tool_provider_consumer_alternative_user_id_field];
  }
  else if (!empty($launch_info['user_id'])) {
    $lti_user = $launch_info['user_id'] . $launch_info['consumer_domain'];
  }
  else {
    $lti_user = 'lti_user' . $launch_info['consumer_domain'];
  }

  // Revalidate incoming user.
  if ($user->uid > 0 && $user->name != $lti_user) {
    // Log out prior user and clear session, retaining lti session variables.
    watchdog('user', 'Session closed for %name.', array('%name' => $user->name));
    module_invoke_all('user_logout', $user);
    // Destroy the current session, and reset $user to the anonymous user.
    session_destroy();
    drupal_session_start();
    drupal_set_message(t('Logged current user out.'), 'info');
  }
  if ($user->uid == 0) {
    $email = '';
    if(!empty($consumer->lti_tool_provider_consumer_alternative_email_field)){
        $email = $launch_info[$consumer->lti_tool_provider_consumer_alternative_email_field];
    }else{
        $email = $launch_info['lis_person_contact_email_primary'];
    }
    // If no mail address given, Form a dummy mail address.
    if (empty($email)) {
      if ($launch_info['consumer_domain'] == '') {
          $email = $lti_user . '@invalid';
      }
      else {
          $email = $lti_user . '.invalid';
      }
    }
    // Unauthenticated so create user if necessary.
    if (($account = user_load_by_name($lti_user)) || ($account = user_load_by_mail($email))) {
      // User exists by name or mail.
      if ($account->uid == 1) {
        // User 1 must use drupal authentication.
        if (isset($launch_info['launch_presentation_return_url'])) {
          lti_tool_provider_goto(url($launch_info['launch_presentation_return_url'], array('query' => array('lti_errormsg' => t('Admin account must use Drupal authentication.')))));
        }
        else {
          drupal_set_message(t('Admin account must use Drupal authentication.'), 'error');
          return t('Admin account must use Drupal authentication.');
        }
      }
    }
    else {
      if (!$account = lti_tool_provider_create_account($lti_user, $launch_info)) {
        if (isset($launch_info['launch_presentation_return_url'])) {
          lti_tool_provider_goto(url($launch_info['launch_presentation_return_url'], array('query' => array('lti_errormsg' => t('Account creation failed.')))));
        }
        else {
          drupal_set_message(t('Account creation failed.'), 'error');
          return t('Account creation failed.');
        }
      }
    }
    // Log the user in.
    $form_state = array('uid' => $account->uid);
    user_login_submit(array(), $form_state);
  }
  else {
    $account = user_load($user->uid);
  }
  // $account is the $lti_user.
  // Map Drupal global roles based on the user LTI role.
  if (!empty($launch_info['roles'])) {
    lti_tool_provider_assign_global_roles_to_user($launch_info['roles'], $account->uid);
    drupal_static_reset('user_access');
  }
  $launch_info['destination'] = '';
  drupal_alter('lti_tool_provider_launch', $launch_info, $account);
  // Calculate the final destination.
  if (!empty($launch_info['custom_destination'])) {
    $launch_info['destination'] .= '/' . $launch_info['custom_destination'];
  }
  // Save launch information in session.
  $_SESSION['lti_tool_provider_context_info'] = $launch_info;
  // Set language in session.
  if (!empty($launch_info['launch_presentation_locale'])) {
    $_SESSION['language'] = drupal_strtolower($launch_info['launch_presentation_locale']);
  }
  lti_tool_provider_goto($launch_info['destination']);
}

/**
 * Page callback for the lti return menu item.
 */
function lti_tool_provider_return() {
  // Logout the user and redirect to the return url in the context_info.
  global $user;
  if (isset($_SESSION['lti_tool_provider_context_info'])) {
    // Log user out and return to launch presentation.
    module_invoke_all('lti_tool_provider_return');
    $url = isset($_SESSION['lti_tool_provider_context_info']['launch_presentation_return_url']) ? $_SESSION['lti_tool_provider_context_info']['launch_presentation_return_url'] : '';
  }
  watchdog('user', 'Session closed for %name.', array('%name' => $user->name));
  module_invoke_all('user_logout', $user);
  // Destroy the current session, and reset $user to the anonymous user.
  session_destroy();
  lti_tool_provider_goto($url);
}

/**
 * Menu page callback for the LTI Home menu item.
 */
function lti_tool_provider_home() {
  lti_tool_provider_goto($_SESSION['lti_tool_provider_context_info']['destination']);
}

/**
 * Menu page callback for the LTI Info menu items.
 *
 * @return array
 *   The conent for the page.
 */
function lti_tool_provider_info() {
  // Display all the key/value pairs in the ltitp_context_info.
  $content = array();
  $content[] = array(
    '#type' => 'item',
    '#markup' => t('LTI Context Session Variables'),
  );
  $info = $_SESSION['lti_tool_provider_context_info'];
  $rows = array();
  $loop_counter = 0;
  foreach ($info as $key => $value) {
    $rows[$loop_counter]['data']['key'] = $key;
    $rows[$loop_counter]['data']['value'] = $value;
    $loop_counter++;
  }
  $content['table'] = array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array(t('Key'), t('Value')),
    '#empty' => t('There are no LTI Context variables.'),
  );
  return $content;
}
