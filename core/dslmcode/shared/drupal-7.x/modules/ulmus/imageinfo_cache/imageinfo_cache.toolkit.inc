<?php

/**
 * @file
 * Imageinfo Cache module. Pseudo image toolkit functions.
 */

/**
 * Get details about an image.
 *
 * @param object $image
 *   An image object.
 *
 * @return mixed
 *   FALSE, if the file could not be found or is not an image. Otherwise, a
 *   keyed array containing information about the image:
 *   - width: Width in pixels.
 *   - height: Height in pixels.
 *   - extension: Commonly used file extension for the image.
 *   - mime_type: MIME type ('image/jpeg', 'image/gif', 'image/png').
 *   - file_size: Image size in bytes.
 *
 * @see image_get_info()
 */
function image_imageinfo_cache_get_info($image) {
  // If not using the cache, bypass it.
  if (!variable_get('imageinfo_cache_getimagesize', IMAGEINFO_CACHE_GETIMAGESIZE)) {
    return _image_imageinfo_cache_get_details($image);
  }

  if (strpos($image->source, '/styles/') === FALSE) {
    $cid = 'ORIGINAL-FILE:';
  }
  else {
    $matches = array();
    preg_match('/.*\/styles\/(.+?)\/.*/', $image->source, $matches);
    $cid = $matches[1] . ':';
  }

  $details = array();
  $cid .= drupal_hash_base64($image->source);

  // Try the static cache first.
  $static_cache = &drupal_static(__FUNCTION__);
  if (isset($static_cache[$cid])) {
    return $static_cache[$cid];
  }

  // Try the cache back end.
  $cache = cache_get($cid, 'cache_imageinfo');
  if (!empty($cache) && !empty($cache->data)) {
    return $cache->data;
  }

  // Try the database next.
  if (db_table_exists('file_metadata')) {
    $results = db_query("
      SELECT
        file_metadata_width.value AS width,
        file_metadata_height.value AS height,
        SUBSTRING_INDEX(file_managed.uri, '.', -1) AS extension,
        file_managed.filemime AS mime_type,
        file_managed.filesize AS file_size
      FROM {file_managed} AS file_managed
      INNER JOIN {file_metadata} AS file_metadata_width
        ON file_metadata_width.fid = file_managed.fid
        AND file_metadata_width.name = 'width'
      INNER JOIN {file_metadata} AS file_metadata_height
        ON file_metadata_height.fid = file_managed.fid
        AND file_metadata_height.name = 'height'
      WHERE file_managed.uri = :uri
    ", array(':uri' => $image->source))->fetchAll();
    if (!empty($results) && !empty($results[0])) {
      $details['width'] = unserialize($results[0]->width);
      $details['height'] = unserialize($results[0]->height);
      $details += (array) $results[0];
    }
  }

  // Change toolkit back to the original value and get the info from the file
  // system.
  if (empty($details)) {
    $details = _image_imageinfo_cache_get_details($image);
  }

  // Write to the cache.
  if (!empty($details) && empty($cache->data)) {
    // Write to the static cache first.
    $static_cache[$cid] = $details;

    // CACHE_PERMANENT isn't good here. Use 2 weeks from now + 0-45 days.
    // The random 0 to 45 day addition is to prevent a cache stampede.
    cache_set($cid, $details, 'cache_imageinfo', round(REQUEST_TIME + 1209600 + mt_rand(0, 3888000), -3));
  }

  return $details;
}

/**
 * Get details about an image.
 *
 * @param object $image
 *   An image object.
 *
 * @return mixed
 *   FALSE, if the file could not be found or is not an image. Otherwise, a
 *   keyed array containing information about the image:
 *   - width: Width in pixels.
 *   - height: Height in pixels.
 *   - extension: Commonly used file extension for the image.
 *   - mime_type: MIME type ('image/jpeg', 'image/gif', 'image/png').
 *   - file_size: Image size in bytes.
 *
 * @see image_get_info()
 */
function _image_imageinfo_cache_get_details($image) {
  // Change toolkit back to the original value.
  $image->toolkit = variable_get('image_toolkit_original', 'gd');
  $details = image_toolkit_invoke('get_info', $image);
  // Change toolkit to the pseudo value again.
  $image->toolkit = variable_get('image_toolkit', 'gd');

  if (isset($details) && is_array($details)) {
    $details['file_size'] = filesize($image->source);
  }
  return $details;
}

/**
 * Crops an image to the given coordinates.
 *
 * @param object $image
 *   An image object. The $image->resource, $image->info['width'], and
 *   $image->info['height'] values will be modified by this call.
 * @param int $x
 *   The starting x offset at which to start the crop, in pixels.
 * @param int $y
 *   The starting y offset at which to start the crop, in pixels.
 * @param int $width
 *   The width of the cropped area, in pixels.
 * @param int $height
 *   The height of the cropped area, in pixels.
 *
 * @return bool
 *   TRUE or FALSE, based on success.
 *
 * @see image_crop()
 */
function image_imageinfo_cache_crop($image, $x, $y, $width, $height) {
  // Change toolkit back to the original value.
  $image->toolkit = variable_get('image_toolkit_original', 'gd');
  $return = image_toolkit_invoke('crop', $image, array($x, $y, $width, $height));
  // Change toolkit to the pseudo value again.
  $image->toolkit = variable_get('image_toolkit', 'gd');
  return $return;
}

/**
 * Converts an image into grayscale.
 *
 * @param object $image
 *   An image object. The $image->resource value will be modified by this call.
 *
 * @return bool
 *   TRUE or FALSE, based on success.
 *
 * @see image_desaturate()
 */
function image_imageinfo_cache_desaturate($image) {
  // Change toolkit back to the original value.
  $image->toolkit = variable_get('image_toolkit_original', 'gd');
  $return = image_toolkit_invoke('desaturate', $image);
  // Change toolkit to the pseudo value again.
  $image->toolkit = variable_get('image_toolkit', 'gd');
  return $return;
}

/**
 * Creates an image resource from a file.
 *
 * @param object $image
 *   An image object. The $image->resource value will populated by this call.
 *
 * @return bool
 *   TRUE or FALSE, based on success.
 *
 * @see image_load()
 */
function image_imageinfo_cache_load($image) {
  // Change toolkit back to the original value.
  $image->toolkit = variable_get('image_toolkit_original', 'gd');
  $return = image_toolkit_invoke('load', $image);
  // Change toolkit to the pseudo value again.
  $image->toolkit = variable_get('image_toolkit', 'gd');
  return $return;
}

/**
 * Scales an image to the specified size.
 *
 * @param object $image
 *   An image object. The $image->resource, $image->info['width'], and
 *   $image->info['height'] values will be modified by this call.
 * @param int $width
 *   The new width of the resized image, in pixels.
 * @param int $height
 *   The new height of the resized image, in pixels.
 *
 * @return bool
 *   TRUE or FALSE, based on success.
 *
 * @see image_resize()
 */
function image_imageinfo_cache_resize($image, $width, $height) {
  // Change toolkit back to the original value.
  $image->toolkit = variable_get('image_toolkit_original', 'gd');
  $return = image_toolkit_invoke('resize', $image, array($width, $height));
  // Change toolkit to the pseudo value again.
  $image->toolkit = variable_get('image_toolkit', 'gd');
  return $return;
}

/**
 * Rotates an image the given number of degrees.
 *
 * @param object $image
 *   An image object. The $image->resource, $image->info['width'], and
 *   $image->info['height'] values will be modified by this call.
 * @param float $degrees
 *   The number of (clockwise) degrees to rotate the image.
 * @param string $background
 *   An hexadecimal integer specifying the background color to use for the
 *   uncovered area of the image after the rotation. E.g. 0x000000 for black,
 *   0xff00ff for magenta, and 0xffffff for white. For images that support
 *   transparency, this will default to transparent. Otherwise it will
 *   be white.
 *
 * @return bool
 *   TRUE or FALSE, based on success.
 *
 * @see image_rotate()
 */
function image_imageinfo_cache_rotate($image, $degrees, $background = NULL) {
  // Change toolkit back to the original value.
  $image->toolkit = variable_get('image_toolkit_original', 'gd');
  $return = image_toolkit_invoke('rotate', $image, array($degrees, $background));
  // Change toolkit to the pseudo value again.
  $image->toolkit = variable_get('image_toolkit', 'gd');
  return $return;
}

/**
 * Writes an image resource to a destination file.
 *
 * @param object $image
 *   An image object.
 * @param string $destination
 *   A string file URI or path where the image should be saved.
 *
 * @return bool
 *   TRUE or FALSE, based on success.
 *
 * @see image_save()
 */
function image_imageinfo_cache_save($image, $destination) {
  // Change toolkit back to the original value.
  $image->toolkit = variable_get('image_toolkit_original', 'gd');
  $return = image_toolkit_invoke('save', $image, array($destination));
  // Call hook_image_imageinfo_cache_save($image, $destination, $return);
  module_invoke_all('image_imageinfo_cache_save', $image, $destination, $return);

  // Change toolkit to the pseudo value again.
  $image->toolkit = variable_get('image_toolkit', 'gd');
  return $return;
}

/**
 * Retrieve settings for the original toolkit.
 *
 * @return mixed
 *   FALSE on failure; form array on success.
 */
function image_imageinfo_cache_settings() {
  $toolkit = variable_get('image_toolkit_original', 'gd');
  $function = 'image_' . variable_get('image_toolkit_original', 'gd') . '_settings';
  if (function_exists($function)) {
    return $function();
  }
  watchdog('image', 'The selected image handling toolkit %toolkit can not correctly process %function.', array('%toolkit' => $toolkit, '%function' => $function), WATCHDOG_ERROR);
  return FALSE;
}
