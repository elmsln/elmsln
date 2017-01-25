<?php
/**
 * @file Helper functions for the alpha effect.
 *
 * @author dan http://coders.co.nz
 */

/**
 * Image effect form callback for the alpha effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function coloractions_alpha_form(array $data) {
  $defaults = array(
    'flatten' => FALSE,
    'RGB' => array('HEX' => '#000000'),
    'opacity' => 0.5,
  );
  $data = array_merge($defaults, (array) $data);

  $form = array();
  $form['help'] = array(
    '#markup' => t("
      <p>You can <em>either</em> set the alpha values of the image to a fixed
      amount by defining opacity, <em>or</em> choose a color and let the
      darkness of the image pixels define an opacity.
      These are different effects. Don't do both
      or you will just get a plain block of color of a certain opacity.
    ")
  );

  $form['opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Opacity'),
    '#default_value' => $data['opacity'],
    '#size' => 3,
    '#description' => t("
      A decimal between 0 and 1.
      You can define the amount of transparency to apply, eg 0.8 (80%) opacity
      will make the image slightly transparent.
      Use this with <em>no</em> fill color defined for normal results.
      If you follow up by flattening the image onto white or grey,
      this will have the effect of partial desaturation.
    "),
  );

  $form['description'] = array(
    '#value' => t(
      "<p>Alpha toning is an advanced method of greyscaling or colorizing.
      It works using transparency, not colour matching.
      The results of this filter are excellent for using as watermarks,
      and for 'sepia' type imprints on coloured or textured backgrounds.
      It converts dark areas of the image to opaque, light to transparent.</p>
      <p>Note that if you are working with JPEGs, this alpha effect will not last into the final image
      <em>unless</em> you either <strong>flatten</strong> this image against a background color
      or image in a later process or <strong>convert</strong> it to a PNG before saving
      using available imagecache actions.</p>"
    )
  );

  $form['RGB'] = imagecache_rgb_form($data['RGB']);
  $form['RGB']['#type'] = 'fieldset';
  $form['RGB']['#title'] = t('Fill Color');
  $form['RGB']['HEX']['#description'] = t("
    Although this image will end up as an alpha transparency mask,
    it still has to have some colour to be visible.
    Black is safe. Dark Sepia #704214 is good too.
    Set it to nothing to not perform any color shift.
    ");

  $form['flatten'] = array(
    '#type' => 'checkbox',
    '#title' => t('Flatten Transparency'),
    '#default_value' => $data['flatten'],
    '#return_value' => TRUE,
    '#description' => t("The opposite of adding alpha transparency, 'flatten' will place the given colour solidly behind the image. Use this if you can't trust IE, or you really do want the image filled in with a solid colour."),
  );

  return $form;
}

/**
 * Implements theme_hook() for the alpha effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 *
 * @ingroup themeable
 */
function theme_coloractions_alpha_summary(array $variables) {
  $data = $variables['data'];
  return ($data['flatten'] ? t("Flatten") : t("Transparent"))
    . ($data['opacity'] ? " : " . ($data['opacity'] * 100) . '%' : '')
    . " : " . theme_imagecacheactions_rgb($data['RGB']);
}

/**
 * Image effect callback for the alpha effect.
 *
 * Either convert light parts of an image to see-through, or place a solid
 * colour behind areas that would otherwise be see-though
 *
 * To save a partially transparent image, the image resource must be switched to
 * PNG. REMEMBER TO SWITCH IT BACK if needed.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return bool
 *   true on success, false otherwise.
 */
function coloractions_alpha_effect(stdClass $image, array $data) {
  // @todo: Extract to GD specific function.
  if (!$data['flatten']) {
    // Given an image, convert dark areas to opaque, light to transparent.
    return png_color2alpha($image, $data['RGB']['HEX'], $data['opacity']);
  }
  else {
    // Do the opposite, flatten the transparency ONTO the given color.
    $info = $image->info;

    if (!$info) {
      watchdog('imagecache_actions', "Problem converting image to fill behind. Source image returned no info");
      return FALSE;
    }

    $base_image = imagecreatetruecolor($info['width'], $info['height']);
    imagesavealpha($base_image, TRUE);
    imagealphablending($base_image, FALSE);

    // Start with a solid color.
    $background_rgb = imagecache_actions_hex2rgba($data['RGB']['HEX']);

    // Setting the background color here solid is what flattens the image.
    // But what I really want to do is set it colored rgb AND 100% transparent,
    // in the hope that a failure to render transparency would instead render
    // THAT colour.
    $background_color = @imagecolorallocatealpha($base_image, $background_rgb['red'], $background_rgb['green'], $background_rgb['blue'], 0);
    // But that still doesn't work. Yet somehow I've seen transparent images
    // that fallback to white, not silver.

    imagefill($base_image, 0, 0, $background_color);

    // And set the overlay behavior back again.
    imagealphablending($base_image, TRUE);

    // Place the current image over it.
    if ($result = imagecopy($base_image, $image->resource, 0, 0, 0, 0, $info['width'], $info['height'])) {
      imagedestroy($image->resource);
      $image->resource = $base_image;
    }

    return $result;
  }
}

/**
 * This achieves a tonal effect by converting the images combined tone and
 * existing transparency into one shade value. This is then used as the ALPHA
 * transparency for that pixel, while the whole thing is coloured the same
 * shade. Images 'grey toned' in this manner should sit smoothly on any
 * background.
 *
 * With no color set, use the existing hue.
 *
 * To save a partially transparent image, the image resource must be switched to
 * PNG. ... or maybe not. Just flatten it yourself, or switch the format
 * yourself. This hack would produce side effects otherwise.
 *
 * This algorithm runs maths per-pixel, and therefore is incredibly much more
 * inefficient than any native routine. Will kill the server on large images.
 *
 * @param stdClass $image
 * @param string $color
 * @param float $opacity
 *   between 0 transparent and 1 solid.
 *
 * @return bool
 *   true on success, false otherwise.
 */
function png_color2alpha(stdClass $image, $color, $opacity = NULL) {
  $info = $image->info;
  if (!$info) {
    return FALSE;
  }
  $im1 = $image->resource;

  imagesavealpha($im1, TRUE);
  imagealphablending($im1, FALSE);

  if ($color) {
    $background = imagecache_actions_hex2rgba($color);
  }
  $width = imagesx($im1);
  $height = imagesy($im1);

  if (($width * $height) > (1200 * 1200)) {
    watchdog('imagecache_actions', __FUNCTION__ . " on {$image->source}. Image is TOO BIG to run the per-pixel algorithm. Aborting.");
    return FALSE;
  }
  for ($i = 0; $i < $height; $i++) {
    //this loop traverses each row in the image
    for ($j = 0; $j < $width; $j++) {
      //this loop traverses each pixel of each row
      // Get the color & alpha info of the current pixel.
      $retrieved_color = imagecolorat($im1, $j, $i); // an index
      $rgba_array = imagecolorsforindex($im1, $retrieved_color);
      $alpha = 127;

      // Calculate the total shade value of this pixel.

      // If the rule sets a color, then the darkness of the existing
      // pixel will define the desired alpha value.
      if ($color) {
        $lightness = ($rgba_array['red'] + $rgba_array['green'] + $rgba_array['blue']) / 3;
        // Need to flip the numbers around before doing maths.
        //$opacity = 1-($rgba_array['alpha']/127);
        //$darkness = 1-($lightness/256); // 0 is white, 1 is black
        //$visibility = $darkness * $opacity;
        //$alpha = (1-$visibility) * 127;
        $alpha = (1 - ((1 - ($lightness / 256)) * (1 - ($rgba_array['alpha'] / 127)))) * 127;
      }
      // If color is NOT set, then the existing color is passed though, only
      // made somewhat transparent.
      if (!$color) {
        $background = $rgba_array;
      }
      if ($opacity) {
        // It's a user-defined alpha value.
        $alpha = $alpha * $opacity;
      }

      // Paint the pixel.
      /** @noinspection PhpUndefinedVariableInspection */
      $color_to_paint = imagecolorallocatealpha($image->resource, $background['red'], $background['green'], $background['blue'], $alpha);
      imagesetpixel($image->resource, $j, $i, $color_to_paint);
    }
  }
  return TRUE;
}
