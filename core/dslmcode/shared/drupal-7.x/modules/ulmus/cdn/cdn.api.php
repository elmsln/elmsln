<?php

/**
 * @file
 * Hooks provided by the CDN module.
 */

/**
 * Allow modules to blacklist file URLs.
 *
 * If a module provides files (static assets, or dynamically generated files)
 * that should never be served from a CDN, they must be blacklisted.
 *
 * @return string[]
 *   A set of path patterns.
 *
 * @see drupal_match_path()
 */
function hook_cdn_blacklist() {
  $blacklist = array();

  // Blacklist wysiwyg library files.
  if (module_exists('wysiwyg')) {
    foreach (wysiwyg_get_all_editors() as $editor) {
      if (!$editor['installed']) {
        continue;
      }
      $blacklist[] = $editor['library path'] . '/*';
    }
  }

  // Blacklist Image CAPTCHA' dynamically generated CAPTCHA images.
  $blacklist[] = 'image_captcha*';

  // Blacklist SimpleTest paths
  $blacklist[] = "*simpletest/verbose/*";

  return $blacklist;
}

/**
 * Alter the blacklist.
 *
 * @param string[] &$blacklist
 *   A set of path patterns.
 *
 * @see drupal_match_path()
 */
function hook_cdn_blacklist_alter(&$blacklist) {
  unset($blacklist[1]);
}
