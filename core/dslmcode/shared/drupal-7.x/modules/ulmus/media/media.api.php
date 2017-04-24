<?php

/**
 * @file
 * Hooks provided by the Media module.
 */

/**
 * Parses a url or embedded code into a unique URI.
 *
 * @param string $url
 *   The original URL or embed code to parse.
 *
 * @return array
 *   The unique URI for the file, based on its stream wrapper, or NULL.
 *
 * @see hook_media_parse_alter()
 * @see media_parse_to_file()
 * @see media_add_from_url_validate()
 */
function hook_media_parse($url) {
  // Only parse URLs from our website of choice: examplevideo.com
  if (substr($url, 0, 27) == 'http://www.examplevideo.com') {
    // Each video has a 5 digit ID, i.e. http://www.examplevideo.com/12345
    // Grab the ID and use it in our URI.
    $id = substr($url, 28, 33);
    return file_stream_wrapper_uri_normalize('examplevideo://video/' . $id);
  }
}

/**
 * Alters the parsing of urls and embedded codes into unique URIs.
 *
 * @param string $success
 *   The unique URI for the file, based on its stream wrapper, or NULL.
 * @param array $context
 *   A nested array of contextual information containing the following keys:
 *   - url: The original URL or embed code to parse.
 *   - module: The name of the module which is attempting to parse the url or
 *     embedded code into a unique URI.
 *
 * @see hook_media_parse()
 * @see hook_media_browser_plugin_info()
 * @see media_get_browser_plugin_info()
 */
function hook_media_parse_alter(&$success, $context) {
  $url = $context['url'];
  $url_info = parse_url($url);

  // Restrict users to only embedding secure links.
  if ($url_info['scheme'] != 'https') {
    $success = NULL;
  }

  // Use a custom handler for detecting YouTube videos.
  if ($context['module' == 'media_youtube']) {
    $handler = new CustomYouTubeHandler($url);
    $success = $handler->parse($url);
  }
}

/**
 * Returns a list of plugins for the media browser.
 *
 * @return array
 *   A nested array of plugin information, keyed by plugin name. Each plugin
 *   info array may have the following keys:
 *   - title: (required) A name for the tab in the media browser.
 *   - class: (required) The class name of the handler. This class must
 *     implement a view() method, and may (should) extend the
 *     @link MediaBrowserPlugin MediaBrowserPlugin @endlink class.
 *   - weight: (optional) Integer to determine the tab order. Defaults to 0.
 *   - access callback: (optional) A callback for user access checks.
 *   - access arguments: (optional) An array of arguments for the user access
 *   check.
 *
 * Additional custom keys may be provided for use by the handler.
 *
 * @see hook_media_browser_plugin_info_alter()
 * @see media_get_browser_plugin_info()
 */
function hook_media_browser_plugin_info() {
  $info['media_upload'] = array(
    'title' => t('Upload'),
    'class' => 'MediaBrowserUpload',
    'weight' => -10,
    'access callback' => 'user_access',
    'access arguments' => array('create files'),
  );

  return $info;
}

/**
 * Alter the list of plugins for the media browser.
 *
 * @param array $info
 *   The associative array of media browser plugin definitions from
 *   hook_media_browser_plugin_info().
 *
 * @see hook_media_browser_plugin_info()
 * @see media_get_browser_plugin_info()
 */
function hook_media_browser_plugin_info_alter(&$info) {
  $info['media_upload']['title'] = t('Upload 2.0');
  $info['media_upload']['class'] = 'MediaBrowserUploadImproved';
}

/**
 * Alter the plugins before they are rendered.
 *
 * @param array $plugin_output
 *   The associative array of media browser plugin information from
 *   media_get_browser_plugin_info().
 *
 * @see hook_media_browser_plugin_info()
 * @see media_get_browser_plugin_info()
 */
function hook_media_browser_plugins_alter(&$plugin_output) {
  $plugin_output['upload']['form']['upload']['#title'] = t('Upload 2.0');
  $plugin_output['media_internet']['form']['embed_code']['#size'] = 100;
}

/**
 * Alter a singleton of the params passed to the media browser.
 *
 * @param array $stored_params
 *   An array of parameters provided when a media_browser is launched.
 *
 * @see media_browser()
 * @see media_set_browser_params()
 */
function hook_media_browser_params_alter(&$stored_params) {
  $stored_params['view_mode'] = 'custom';
  $stored_params['types'][] = 'document';
  unset($stored_params['enabledPlugins'][0]);
}
