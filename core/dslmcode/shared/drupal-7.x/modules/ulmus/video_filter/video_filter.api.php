<?php

/**
 * @file
 * Hooks provided by the Video Filter module.
 */

/**
 * Defines video codecs and callbacks.
 *
 * @return array
 *   A video codec described as an associative array that may contain the
 *   following key-value pairs:
 *   - name: Required. A name for the codec.
 *   - sample_url: Required. An example of a URL the codec can handle.
 *   - callback: The function to call to generate embed code for the codec.
 *     Either this or html5_callback must be specified.
 *   - html5_callback: The function to call to generate device agnostic, HTML5
 *     embed code for the codec. Either this or callback must be specified.
 *   - instructions: Instructions for using the codec, to be displayed on the
 *     "Compse tips" page at filter/tips.
 *   - regexp: Required. A regular expression describing URLs the codec can
 *     handle. Multiple regular expressions may be supplied as an array.
 *     $video['codec']['delta'] will be set to the key of the match.
 *   - ratio: Required. A ratio for resizing the video within the dimensions
 *     optionally supplied in the token, expressed as height / width.
 *   - control_bar_height: The pixel height of the video player control bar, if
 *     applicable.
 */
function hook_codec_info() {
  $codecs = array();

  $codecs['minimal_example'] = array(
    'name' => t('Minimal Example'),
    'sample_url' => 'http://minimal.example.com/uN1qUeId',
    'callback' => 'MODULE_minimal_example',
    'regexp' => '/minimal\.example\.com\/([a-z0-9\-_]+)/i',
    'ratio' => 4 / 3,
  );

  $codecs['complete_example'] = array(
    'name' => t('Complete Example'),
    'sample_url' => 'http://complete.example.com/username/uN1qUeId',
    'callback' => 'MODULE_complete_example',
    'html5_callback' => 'MODULE_complete_example_html5',
    'instructions' => t('Your Complete Example username can be the first URL argument or a sub-subdomain.'),
    'regexp' => array(
      '/complete\.example\.com\/([a-z0-9\-_]+)\/([a-z0-9\-_]+)/i',
      '/([a-z0-9\-_]+)\.complete\.example\.com\/([a-z0-9\-_]+)/i',
    ),
    'ratio' => 4 / 3,
    'control_bar_height' => 25,
  );

  return $codecs;
}

/**
 * Alters the codecs available to Video Filter.
 *
 * @param array $codecs
 */
function hook_video_filter_codec_info_alter(&$codecs) {}

/**
 * Alters a video's attributes previous to rendering.
 *
 * @param array $video
 */
function hook_video_filter_video_alter(&$video) {}
