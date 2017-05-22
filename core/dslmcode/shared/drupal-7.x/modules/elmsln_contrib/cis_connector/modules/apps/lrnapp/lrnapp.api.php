<?php
/**
 * @file
 * Code for the wiring up LRN Apps.
 */

/**
 * Implements hook_register_lrnapps().
 * This provides a standard way of integrating one page apps
 * into Drupal. It's standardizing the conventions for our
 * development of lrnapp- elements which are going to be at
 * minimum one page apps if not providing full on paging and
 * routing internal to themselves. This helps reduce the
 * amount of work required to get a new app wired up and starts to
 * give us development conventions associated with them!
 */
function hook_register_lrnapps() {
  return array(
    // machine name of the app
    'open-studio' => array(
      // module it comes from
      'module' => 'cle_open_studio_app',
      // a human readable title
      'title' => t('Open studio'),
      // optional: menu for making this visible in drupal's menu system
      'menu' => array(
        'type' => MENU_NORMAL_ITEM,
        'menu_name' => 'menu-elmsln-navigation',
        'weight' => -10,
      ),
      // optional: adding a data router for getting information back in
      // a consistent way. This isn't required but will be used almost
      // all of the time unless paths are hard wired into the app itself
      // or the app is a stand alone without pulling data from drupal.
      'data' => '_cle_open_studio_app_data',
    ),
  );
}
