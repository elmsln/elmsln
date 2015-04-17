<?php
/**
 * @file
 * Personalized fragment for CSRF tokens.
 */

/**
 * Retrieve CSRF-form token for the logged in user.
 *
 * @see form.inc
 */
class AuthcacheFormTokenFragment implements AuthcacheP13nFragmentInterface {
  /**
   * Render hidden field for CSRF token.
   */
  public function render($form_token_id, $ignored, $context) {
    include_once DRUPAL_ROOT . '/includes/common.inc';

    $form_token = drupal_get_token($form_token_id);
    return format_string('<input type="hidden" name="form_token" value="@form_token"></input>',
      array('@form_token' => $form_token));
  }
}
