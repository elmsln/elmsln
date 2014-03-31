<?php
/**
 * @file
 * Views integration to allow CIS querying via UI.
 */
/**
 * Implements hook_views_post_build().
 */
function cis_connector_views_post_build(&$view) {
  // only enable this for views XML backend calls
  if (
    $view->base_table == 'xml' &&
    // ensure the cis bucket is set and not empty
    isset($view->query->options['cis_bucket']) &&
    $view->query->options['cis_bucket'] != '' &&
    // make sure the registry bucket exists
    $settings = _cis_connector_build_registry($view->query->options['cis_bucket'])
  ) {
    // make sure the call is to the correct xml data source
    $path = '/';
    if ($view->query->options['cis_instance']) {
      $path = base_path();
    }
    $address = _cis_connector_format_address($settings, $path);
    $view->query->options['xml_file'] = $address . $view->query->options['xml_file'];
  }
}

/**
 * Implements hook_views_plugins().
 */
function cis_connector_views_plugins() {
  $path = drupal_get_path('module', 'cis_connector');
  $plugins = array();
  $plugins['display_extender']['cis_connector'] = array(
    'title' => t('CIS connector'),
    'help' => t('CIS settings'),
    'path' => $path,
    'handler' => 'cis_connector_views_plugin_display_extender',
  );
  return $plugins;
}