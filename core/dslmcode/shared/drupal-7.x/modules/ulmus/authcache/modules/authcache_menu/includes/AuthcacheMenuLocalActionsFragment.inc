<?php
/**
 * @file
 * Defines authcache fragment for rendering local actions.
 */

/**
 * Render local actions.
 *
 * @see menu.inc
 */
class AuthcacheMenuLocalActionsFragment implements AuthcacheP13nFragmentInterface {
  /**
   * Render and return local actions.
   */
  public function render($key, $subject, $context) {
    $actions = menu_local_actions();
    return render($actions);
  }
}
