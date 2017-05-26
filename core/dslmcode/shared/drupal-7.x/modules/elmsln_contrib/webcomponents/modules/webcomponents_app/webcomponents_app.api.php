<?php
/**
 * @file
 * Code for the wiring up Webcomponent based one page apps.
 */

/**
 * Implements hook_register_webcomponent_apps().
 * This provides a standard way of integrating one page apps
 * into Drupal. It's standardizing the conventions for our
 * development of elements which are going to be at
 * minimum one page apps if not providing full on paging and
 * routing internal to themselves. This helps reduce the
 * amount of work required to get a new app wired up and starts to
 * give us development conventions associated with them!
 */
function hook_register_webcomponent_apps() {
  return array(
    // machine name of the app
    'open-studio' => array(
      // path to the file to actually load
      'path' => 'sites/all/libraries/webcomponents/polymer/apps/my-one-page/src/my-one-page-app/my-one-page-app.html',
      // a human readable title
      'title' => t('Open studio'),
      // optional: module it comes from
      'module' => 'my_custom_module',
      // optional: menu for making this visible in drupal's menu system
      'menu' => array(
        'type' => MENU_NORMAL_ITEM,
        'menu_name' => 'menu-navigation',
        'weight' => -10,
      ),
      // optional: adding a data router for getting information back in
      // a consistent way. This isn't required but will be used almost
      // all of the time unless paths are hard wired into the app itself
      // or the app is a stand alone without pulling data from drupal.
      'data' => array(
        // the callback function to issue
        'callback' => 'my_custom_module_data_callback',
        // the name of the property the element uses to pull data
        'property' => 'source-path',
      ),
      // optional: completely optional but also is hooked in from where ever it comes from
      // this allows you to do any other kind of contextual operation you would need.
      // For example, elmsln uses the 'distro' context value to match against the currently
      // active distribution. This allows us to enable certain one page apps only on certain
      // sites in a multi-site while still managing them in a single location (if needed).
      // @see elmsln_core_register_webcomponent_apps_alter.
      'context' => array(
        'distro' => 'standard'
      ),
    ),
  );
}
