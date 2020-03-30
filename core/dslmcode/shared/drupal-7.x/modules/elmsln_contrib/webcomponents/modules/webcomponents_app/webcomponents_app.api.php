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
      // optional: menu for making this visible in drupal's menu system
      'menu' => array(
        'type' => MENU_NORMAL_ITEM,
        'menu_name' => 'menu-navigation',
        'weight' => -10,
      ),
      // optional: support for automatically generating a block that theme's the web component
      'block' => TRUE,
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
      // optional: allow for defining properties that need to be added automatically
      'properties' => array(
        'name' => 'Dana',
        'age' => array(
          'callback' => '_get_user_age',
        )
      ),
      // optional: allow for defining slots that get added to the contents of the tag
      // this compiles prior to rendering through the theme layer so that this would look
      // like <span slot="title">Page 1</span><span slot="content"></span> and etc
      'slots' => array(
        'title' => 'Page 1',
        'content' => array(
          'callback' => '_get_active_content',
        )
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

/**
 * Implements hook_register_webcomponent_apps_alter().
 * @param  array $apps loaded app definitions
 */
function hook_register_webcomponent_apps_alter($apps) {
  $apps['my-app']['title'] = t('Cool stuff');
}

/**
 * Implements hook_webcomponents_app_data_alter().
 * @param  array $return  response from the server after data callback processed
 * @param  array $app     loaded app definition
 */
function hook_webcomponents_app_data_alter($return, $app) {
  if ($app['name'] == 'my-app' && isset($return['data']['file']) && $return['status'] == 200) {
    // do something extra with images uploaded successfully
    // via our app
    if ($return['data']['file']->type == 'image') {

    }
  }
}

/**
 * Implements hook_webcomponents_app_deliver_output_alter().
 * @param  array $return  response from the server just before printing out
 */
function hook_webcomponents_app_deliver_output_alter(&$return, $app) {
  if ($app->machine_name == 'cool-stuff') {
    $return .= "\n" . '<add-on-some-custom-element-too></add-on-some-custom-element-too>';
  }
}

/**
 * Implements hook_webcomponents_app_deliver_data_alter().
 * @param  array $return  response from the server just before returning data as a json blob
 */
function hook_webcomponents_app_deliver_data_alter(&$return, $app) {
  // prevent 404s for no reason
  if ($return['status'] == 404) {
    // I'm a teapot short and stout
    $return['status'] = 418;
    $return['detail'] = t('I\'m a little tea pot short and stout');
  }
}

/**
 * Implements hook_webcomponents_app_element_import_alter().
 * @param  array  $link_element   an array to be added via drupal_add_html_head
 * @param  array  $app            app manifest as loaded by drupal
 * @param  string $machine_name   the name of the app
 * @param  string $hash           hash value based on filesize for easy cache busting
 * @see  drupal_add_html_head()
 */
function hook_webcomponents_app_element_import_alter(&$link_element, $app, $machine_name, $hash) {
  // we don't store our apps in the app path, we only use it for registration
  $link_element['#attributes']['href'] = libraries_get_path('webcomponents', TRUE) . '/polymer/apps-src/' . $machine_name . '/' . $machine_name . '.html?h' . $hash;
}
