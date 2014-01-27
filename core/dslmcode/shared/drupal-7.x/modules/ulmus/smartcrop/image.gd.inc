<?php
// $Id: image.gd.inc,v 1.1.2.4 2010/12/07 19:35:18 grendzy Exp $

/**
 * @file
 * libgd implementation of smartcrop action.
 *
 * Cropping algorithm is derived from http://code.google.com/p/sorl-thumbnail/
 * by Mikko Hellsing, Chris Beaven.
 * Adapted to ImageCache and GD by Dylan Tack (grendzy).
 */

/**
 * Scale and crop an image to the specified size using GD.
 *
 * @param $image_data An image object.
 * @param $requested_x The requested image width.
 * @param $requested_y The requested image height.
 * @param $upscale TRUE if upscaling is allowed.
 * @return TRUE if successful.
 */
function image_gd_smartcrop_scale(stdClass $image_data, $requested_x, $requested_y, $upscale) {
  $ratio = max($requested_x / $image_data->info['width'], $requested_y / $image_data->info['height']);
  if ($ratio <= 1 || $upscale) {
    if (!image_gd_resize($image_data, round($ratio * $image_data->info['width']), round($ratio * $image_data->info['height']))) {
      return FALSE;
    }
  }
  return image_gd_smartcrop_crop($image_data, $requested_x, $requested_y);
}

/**
 * Crop an image, removing the lowest entropy areas.
 *
 * @param array $image_data
 * @param int $requested_x
 * @param int $requested_y
 * @return booleon TRUE if successful
 */
function image_gd_smartcrop_crop(stdClass $image_data, $requested_x, $requested_y) {
  $image = $image_data->resource;
  $dx = imagesx($image) - min(imagesx($image), $requested_x);
  $dy = imagesy($image) - min(imagesy($image), $requested_y);
  $left = $top = 0;
  $left_entropy = $right_entropy = $top_entropy = $bottom_entropy = 0;
  $right = imagesx($image);
  $bottom = imagesy($image);

  // Slice from left and right edges until the correct width is reached.
  while ($dx) {
    $slice = min($dx, 10);

    // Calculate the entropy of the new slice.
    if (!$left_entropy) {
      $left_entropy = _smartcrop_gd_entropy_slice($image_data, $left, $top, $slice, imagesy($image));
    }
    if (!$right_entropy) {
      $right_entropy = _smartcrop_gd_entropy_slice($image_data, $right - $slice, $top, $slice, imagesy($image));
    }

    // Remove the lowest entropy slice.
    if ($left_entropy >= $right_entropy) {
      $right -= $slice;
      $right_entropy = 0;
    }
    else {
      $left += $slice;
      $left_entropy = 0;
    }
    $dx -= $slice;
  }

  // Slice from the top and bottom edges until the correct width is reached.
  while ($dy) {
    $slice = min($dy, 10);

    // Calculate the entropy of the new slice.
    if (!$top_entropy) {
      $top_entropy = _smartcrop_gd_entropy_slice($image_data, $left, $top, $requested_x, $slice);
    }
    if (!$bottom_entropy) {
      $bottom_entropy = _smartcrop_gd_entropy_slice($image_data, $left, $bottom - $slice, $requested_x, $slice);
    }

    // Remove the lowest entropy slice.
    if ($top_entropy >= $bottom_entropy) {
      $bottom -= $slice;
      $bottom_entropy = 0;
    }
    else {
      $top += $slice;
      $top_entropy = 0;
    }
    $dy -= $slice;
  }

  // Finally, crop the image using the coordinates found above.
  $cropped_image = image_gd_create_tmp($image_data, $right - $left, $bottom - $top);
  imagecopy($cropped_image, $image, 0, 0, $left, $top, $right - $left, $bottom - $top);
  imagedestroy($image_data->resource);
  $image_data->resource = $cropped_image;
  $image_data->info['width'] = $requested_x;
  $image_data->info['height'] = $requested_y;
  return TRUE;
}

/**
 * Compute the entropy of an image slice.
 *
 * @param $image_data An image object
 * @param $x Starting X coordinate.
 * @param $y Starting Y coordinate.
 * @param $width The width of the slice.
 * @param $height The height of the slice.
 * @return
 */
function _smartcrop_gd_entropy_slice($image_data, $x, $y, $width, $height) {
  $slice = image_gd_create_tmp($image_data, $width, $height);
  imagecopy($slice, $image_data->resource, 0, 0, $x, $y, $width, $height);
  $entropy = _smartcrop_gd_entropy($slice);
  imagedestroy($slice);
  return $entropy;
}

/**
 * Compute the entropy of an image, defined as -sum(p.*log2(p)).
 * @param resource $img GD image resource.
 * @return float The entropy of the image.
 */
function _smartcrop_gd_entropy($img) {
  $histogram = _smartcrop_gd_histogram($img);
  $histogram_size = array_sum($histogram);
  $entropy = 0;
  foreach ($histogram as $p) {
    if ($p == 0) {
      continue;
    }
    $p = $p / $histogram_size;
    $entropy += $p * log($p, 2);
  }
  return $entropy * -1;
}

/**
 * Compute a histogram of an image.
 * @param resource $img GD image resource.
 * @return array histogram as an array.
 */
function _smartcrop_gd_histogram($img) {
  $histogram = array_fill(0, 768, 0);
  for ($i = 0; $i < imagesx($img); $i++) {
    for ($j = 0; $j < imagesy($img); $j++) {
      $rgb = imagecolorat($img, $i, $j);
      $r = ($rgb >> 16) & 0xFF;
      $g = ($rgb >> 8) & 0xFF;
      $b = $rgb & 0xFF;
      $histogram[$r]++;
      $histogram[$g + 256]++;
      $histogram[$b + 512]++;
    }
  }
  return $histogram;
}
