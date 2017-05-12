<?php
/**
 * @file
 * Functions needed to execute image effects provided by the tokencrop module.
 */

/**
 * Implements hook_image_effect_info().
 */
function tokencrop_image_effect_info() {
  $effects = array(
    'tokencrop_scale_and_crop' => array(
      'label' => t('Scale and Token Crop'),
      'help' => t('Similar to "Scale And Crop", but uses a token to select where it takes it from.'),
      'effect callback' => 'tokencrop_scale_effect',
      'form callback' => 'tokencrop_scale_form',
      'summary theme' => 'image_scale_summary',
    ),
    'tokencrop_crop' => array(
      'label' => t('Token Crop'),
      'help' => t('Similar to "Crop", but uses a token to select where it takes it from.'),
      'effect callback' => 'tokencrop_crop_effect',
      'form callback' => 'tokencrop_resize_form',
      'summary theme' => 'image_resize_summary',
    ),
  );
  return $effects;
}

function tokencrop_resize_form($data) {
  $form = image_resize_form($data);
  return $form;
}

function tokencrop_scale_form($data) {
  $form = image_scale_form($data);
  return $form;
}

/**
 * Image effect callback; Scale and Smart Crop an image resource.
 *
 * @param $image
 *   An image object returned by image_load().
 * @param $data
 *   An array of attributes to use when performing the scale effect with the
 *   following items:
 *   - "width": An integer representing the desired width in pixels.
 *   - "height": An integer representing the desired height in pixels.
 *   - "upscale": A Boolean indicating that the image should be upscalled if
 *     the dimensions are larger than the original image.
 *
 * @return
 *   TRUE on success. FALSE on failure to scale image.
 */
function tokencrop_scale_effect(&$image, $data) {

  // Set sane default values.
  $data += array(
    'upscale' => FALSE,
  );

  // Set impossibly large values if the width and height aren't set.
  $data['width'] = empty($data['width']) ? PHP_INT_MAX : $data['width'];
  $data['height'] = empty($data['height']) ? PHP_INT_MAX : $data['height'];

  if (!image_toolkit_invoke('tokencrop_scale', $image, $data)) {
    watchdog('image', 'Image scale failed using the %toolkit toolkit on %path (%mimetype, %dimensions)', array('%toolkit' => $image->toolkit, '%path' => $image->source, '%mimetype' => $image->info['mime_type'], '%dimensions' => $image->info['height'] . 'x' . $image->info['height']), WATCHDOG_ERROR);
    return FALSE;
  }
  return TRUE;
}

/**
 * Image effect callback; Smart Crop an image resource.
 *
 * @param $image
 *   An image object returned by image_load().
 * @param $data
 *   An array of attributes to use when performing the resize effect with the
 *   following items:
 *   - "width": An integer representing the desired width in pixels.
 *   - "height": An integer representing the desired height in pixels.
 *
 * @return
 *   TRUE on success. FALSE on failure to resize image.
 */
function tokencrop_crop_effect(&$image, $data) {
  if (!image_toolkit_invoke('tokencrop_crop', $image, $data)) {
    watchdog('image', 'Smart crop failed using the %toolkit toolkit on %path (%mimetype, %dimensions)', array('%toolkit' => $image->toolkit, '%path' => $image->source, '%mimetype' => $image->info['mime_type'], '%dimensions' => $image->info['height'] . 'x' . $image->info['height']), WATCHDOG_ERROR);
    return FALSE;
  }
  return TRUE;
}
