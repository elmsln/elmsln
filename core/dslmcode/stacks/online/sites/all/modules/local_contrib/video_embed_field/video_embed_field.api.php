<?php

/**
 * API Info for video_embed_field module
 */

/**
 * @function hook_video_embed_handler_info
 * Can be used to add more handlers for video_embed_field
 * @return an array of handlers, each handler is an array with the following
 * keys:
 * 'title' : required, the untranslated title of the provider, to show to the
 *   admin user.
 * 'function' : required, the function used to generate the embed code.
 * 'thumbnail_function' : optional, the function used to provide the thumbnail
 *   for a video.
 * 'thumbnail_default : optional, the default thumbnail image to display in case
 *   thumbnail_function does not exist or has no results.
 * 'data_function' : optional, the function to return an array of video data.
 * 'form' : required, the function that returns the settings form for your
 *   provider.
 * 'form_validate: optional the function that validates the settings form for
 *   your provider.
 * 'domains' : required, an array of domains to match against, this is used to
 *   know which provider to use.
 * 'defaults' : default values for each setting made configurable in your form
 *   function.
 *
 * @see hook_video_embed_handler_info_alter()
 * @see below for function definitions
 */
function hook_video_embed_handler_info() {
  $handlers = array();

  $handlers['ustream'] = array(
    'title' => 'UStream',
    'function' => 'your_module_handle_ustream',
    'thumbnail_function' => 'your_module_handle_ustream_thumbnail',
    'thumbnail_default' => drupal_get_path('module', 'your_module') . '/img/ustream.jpg',
    'data_function' => 'your_module_handler_ustream_data',
    'form' => 'your_module_handler_ustream_form',
    'form_validate' => 'your_module_handler_ustream_form_validate',
    'domains' => array(
      'ustream.com',
    ),
    'defaults' => array(
      'width' => 640,
      'height' => 360,
    ),
  );

  return $handlers;
}

/**
 * Performs alterations on video_embed_field handlers.
 *
 * @param $info
 *   Array of information on video handlers exposed by
 *   hook_video_embed_handler_info() implementations.
 */
function hook_video_embed_handler_info_alter(&$info) {
  // Change the thumbnail function for 'ustream' provider.
  if (isset($info['ustream'])) {
    $info['ustream']['thumbnail_function'] = 'your_module_handle_ustream_thumbnail_alter';
  }
}

/**
 * Example callbacks for a provider (in this case for ustream).
 * Obviously, these functions are only for example purposes.
 */

/**
 * Generate the embed code for a video
 * @param $url - the video url as entered by the user
 * @param $settings - the settings for this provider as defined in the form function,
 *                      defaulting to your provider's defaults
 * @return the embed code as a renderable array
 */
function your_module_handle_ustream($url, $settings) {
  return array(
    //this should be the full embed code for your provider, including each of the settings
    '#markup' => '<iframe src="ustream"></iframe>',
  );
}

/**
 * Retrieve information about the thumbnail for a given url
 * @param $url - the url of the video as entered by the user
 * @return an array with the keys:
 *   'id' => an id for the video which is unique to your provider, used for naming the cached thumbnail file
 *   'url' => the url to retrieve the thumbnail from
 */
function your_module_handle_ustream_thumbnail($url) {
  return array(
    'id' => '12332243242', //generally the id that the provider uses for the video
    'url' => 'http://something/thumbnail/somthing.jpg', //the url of the thumbnail
  );
}

/**
 * A forms api callback, returns the settings form for the provider
 * @param $defaults - default/current values for your provider, the currently saved settings
 *                       with empty values filled with the defaults provided in info hook
 * @return a form as defined by forms api
 *
 * @see http://api.drupal.org/api/drupal/developer!topics!forms_api_reference.html/7
 */
function your_module_handler_ustream_form($defaults) {
  $form = array();

  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Player Width'),
    '#description' => t('The width of the player in pixels'),
    '#default_value' => $defaults['width'],
  );

  return $form;
}

/**
 * Return an array of extra data to be stored with the video, this data will be available for theming
 * @return an array
 */
function your_module_handler_ustream_data($url) {
  return array();
}
