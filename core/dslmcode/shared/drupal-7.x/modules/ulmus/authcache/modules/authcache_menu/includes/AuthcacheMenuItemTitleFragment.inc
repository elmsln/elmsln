<?php
/**
 * @file
 * Defines an authcache fragment for returning personalized menu titles.
 */

/**
 * Render personalized menu titles.
 *
 * @see menu.inc
 */
class AuthcacheMenuItemTitleFragment implements AuthcacheP13nFragmentInterface, AuthcacheP13nFragmentLoaderInterface, AuthcacheP13nFragmentAccessInterface {
  /**
   * Load requested menu items.
   */
  public function load($paths, $context) {
    $items = array();

    foreach ($paths as $path) {
      $item = menu_link_get_preferred($path);
      if (empty($item)) {
        throw new AuthcacheP13nRequestNotFound();
      }
      $items[$path] = $item;
    }

    return $items;
  }

  /**
   * Check access to menu item.
   */
  public function check($account, $path, $item, $context) {
    return $item['access'];
  }

  /**
   * Return menu item title.
   */
  public function render($path, $item, $context) {
    return $item['title'] ? $item['title'] : $item['link_title'];
  }
}
