<?php

/**
 * @file
 * Media module integration for the Media internet module.
 */

/**
 * Implements hook_media_browser_plugin_info().
 */
function media_internet_media_browser_plugin_info() {
  $info['media_internet'] = array(
    'title' => t('Web'),
    'class' => 'MediaBrowserInternet',
  );

  return $info;
}

/**
 * Implements hook_media_internet_providers().
 *
 * Provides a very basic handler which copies files from remote sources to the
 * local files directory.
 */
function media_internet_media_internet_providers() {
  return array(
    'MediaInternetFileHandler' => array(
      'title' => 'Files',
      'hidden' => TRUE,
      // Make it go last.
      'weight' => 10000,
    ),
  );
}
