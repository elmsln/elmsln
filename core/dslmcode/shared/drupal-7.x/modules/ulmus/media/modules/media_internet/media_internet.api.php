<?php

/**
 * @file
 * Hooks provided by the media_internet module.
 */

/**
 * Returns a list of Internet media providers for URL/embed code testing.
 *
 * @return array
 *   A nested array of provider information, keyed by class name. This class
 *   must implement a claim() method and may (should) extend the
 *   @link MediaInternetBaseHandler MediaInternetBaseHandler @endlink class.
 *   Each provider info array may have the following keys:
 *   - title: (required) A name to be used when listing the currently supported
 *     providers on the web tab of the media browser.
 *   - hidden: (optional) Boolean to prevent the provider title from being
 *     listed on the web tab of the media browser.
 *   - weight: (optional) Integer to determine the tab order. Defaults to 0.
 *
 * @see hook_media_internet_providers_alter()
 * @see media_internet_get_providers()
 */
function hook_media_internet_providers() {
  return array(
    'MyModuleYouTubeHandler' => array(
      'title' => t('YouTube'),
      'hidden' => TRUE,
    ),
  );
}

/**
 * Alter the list of Internet media providers.
 *
 * @param array $providers
 *   The associative array of Internet media provider definitions from
 *   hook_media_internet_providers().
 *
 * @see hook_media_internet_providers()
 * @see media_internet_get_providers()
 */
function hook_media_internet_providers_alter(&$providers) {
  $providers['MyModuleYouTubeHandler']['title'] = t('Google video hosting');
  $providers['MyModuleYouTubeHandler']['weight'] = 42;
}
