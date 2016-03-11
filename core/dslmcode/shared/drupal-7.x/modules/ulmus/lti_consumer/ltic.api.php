<?php

/**
 * @file
 * Hooks provided by the ltic module.
 */
/**
 * @addtogroup hooks
 * @{
 */

/**
 * Change mentored users array.
 *
 * @param $mentored_users array
 *   Add list of user ids that this user can mentor.
 */
function hook_lti_mentored_users_alter(&$mentored_users) {

  $mentored_users[] = 23;
  $mentored_users[] = 24;
}

/**
 * Add a users lis_person_sourcedid.
 * This will be per user and could be extracted from users profile or user 
 * account fields.
 *
 * @param $mentored_users array
 *   Add list of user ids that this user can mentor.
 */
function hook_lti_lis_person_sourcedid_alter(&$lis_source_ID) {
// see 6 Using Learning Information Services with LTI of
// 1.2 IMS Global Learning Tools Interoperability® Implementation Guide 
  $lis_source_ID = 'school.edu:SI182-F08';
}

/**
 * This prevents the outcomes api from displaying a unsupported
 * massage and handles the message appropriatly.
 *
 * @param $handled boolian
 * @param $message_type string
 * @param $this Outcomes Instance
 * 
 */
function hook_ltic_outcomes_request(&$handled, $message_type, $outcomesObject) {
  if ($message_type == 'doThis') {
    $handled = TRUE;
    $response = new OutcomesResponse('success', 'found do this', uniqid(), 'doThis');
    $responsexml = $response->getResponse();
    echo $responsexml->asXML();
  }
}
