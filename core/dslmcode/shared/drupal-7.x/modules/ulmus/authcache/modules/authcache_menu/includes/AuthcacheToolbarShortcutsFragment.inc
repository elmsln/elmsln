<?php
/**
 * @file
 * Defines authcache fragment for rendering shortcuts.
 */

/**
 * Render shortcuts.
 *
 * @see shortcut.module
 */
class AuthcacheToolbarShortcutsFragment implements AuthcacheP13nFragmentInterface {
  /**
   * Render and return local actions.
   */
  public function render($key, $subject, $context) {
    $element = shortcut_toolbar_pre_render(array());
    return render($element);
  }
}
