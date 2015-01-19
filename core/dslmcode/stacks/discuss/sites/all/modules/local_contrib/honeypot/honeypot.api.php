<?php

/**
 * @file
 * API Functionality for Honeypot module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the honeypot protections added to a particular form.
 *
 * @param array $options
 *   Protections that will be applied to the form. May be empty, or may include
 *   'honeypot' and/or 'time_restriction'.
 * @param array $form
 *   The Form API form to which protections will be added.
 */
function hook_honeypot_form_protections_alter(&$options, $form) {
  // Add 'time_restriction' protection to 'mymodule-form' if it's not set.
  if ($form['form_id']['#value'] == 'mymodule_form' && !in_array('time_restriction', $options)) {
    $options[] = 'time_restriction';
  }
}

/**
 * React to an addition of honeypot form protections for a given form_id.
 *
 * After honeypot has added its protections to a form, this hook will be called.
 * You can use this hook to track when and how many times certain protected
 * forms are displayed to certain users, or for other tracking purposes.
 *
 * @param array $options
 *   Protections that were applied to the form. Includes 'honeypot' and/or
 *   'time_restriction'.
 * @param array $form
 *   The Form API form to which protections were added.
 */
function hook_honeypot_add_form_protection($options, $form) {
  if ($form['form_id']['#value'] == 'mymodule_form') {
    // Do something...
  }
}

/**
 * React to the rejection of a form submission.
 *
 * When honeypot rejects a form submission, it calls this hook with the form ID,
 * the user ID (0 if anonymous) of the user that was disallowed from submitting
 * the form, and the reason (type) for the rejection of the form submission.
 *
 * @param string $form_id
 *   Form ID of the form the user was disallowed from submitting.
 * @param int $uid
 *   0 for anonymous users, otherwise the user ID of the user.
 * @param string $type
 *   String indicating the reason the submission was blocked. Allowed values:
 *     - honeypot: If honeypot field was filled in.
 *     - honeypot_time: If form was completed before the configured time limit.
 */
function hook_honeypot_reject($form_id, $uid, $type) {
  if ($form_id == 'mymodule_form') {
    // Do something...
  }
}

/**
 * Add time to the Honeypot time limit.
 *
 * In certain circumstances (for example, on forms routinely targeted by
 * spammers), you may want to add an additional time delay. You can use this
 * hook to return additional time (in seconds) to honeypot when it is calculates
 * the time limit for a particular form.
 *
 * @param int $honeypot_time_limit
 *   The current honeypot time limit (in seconds), to which any additions you
 *   return will be added.
 * @param array $form_values
 *   Array of form values (may be empty).
 * @param int $number
 *   Number of times the current user has already fallen into the honeypot trap.
 *
 * @return int
 *   Additional time to add to the honeypot_time_limit, in seconds (integer).
 */
function hook_honeypot_time_limit($honeypot_time_limit, $form_values, $number) {
  $additions = 0;
  // If 'some_interesting_value' is set in your form, add 10 seconds to limit.
  if (!empty($form_values['some_interesting_value']) && $form_values['some_interesting_value']) {
    $additions = 10;
  }
  return $additions;
}

/**
 * @} End of "addtogroup hooks".
 */
