<?php
/**
 * @file
 * Defines an authcache fragment for rendering menu tabs.
 */

/**
 * Render menu tabs
 *
 * @see menu.inc
 */
class AuthcacheMenuLocalTabsFragment implements AuthcacheP13nFragmentInterface {
  /**
   * Render and return menu tabs.
   */
  public function render($key, $subject, $context) {
    $tabs = menu_local_tabs();
    return render($tabs);
  }
}
