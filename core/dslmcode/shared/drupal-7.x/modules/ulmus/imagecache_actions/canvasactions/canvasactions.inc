<?php
/**
 * @file Helper functions for the canvas actions for imagecache
 *
 * @author Dan Morrison http://coders.co.nz
 *
 * Individually configurable rounded corners logic contributed by canaryMason
 * 2009 03 https://drupal.org/node/402112
 *
 * Better algorithm for trimming rounded corners from donquixote
 * 2009 09 https://drupal.org/node/564036
 *
 */

if (!function_exists('image_overlay')) {
  module_load_include('inc', 'imagecache_actions', 'image_overlay');
}
if (!function_exists('imagecache_actions_pos_form')) {
  module_load_include('inc', 'imagecache_actions', 'utility-form');
}
if (!function_exists('imagecache_actions_keyword_filter')) {
  module_load_include('inc', 'imagecache_actions', 'utility');
}

/**
 * Image effect form callback for the image mask effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_imagemask_form(array $data) {
  // @todo: add offset/positioning/scaling support - currently the mask is applied to the supplied image without resizing and positioned at (0,0)
  $form = array();
  $form['effect_help_text'] = array(
    '#type' => 'item',
    '#title' => t('Image mask'),
    '#description' => t('This effect will add (or replace) a transparency channel to your image. The mask file should be a grayscale image where black is fully transparent and white is fully opaque. The referenced mask will be applied to the top left of the image.'),
  );
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Mask file name'),
    '#default_value' => isset($data['path']) ? $data['path'] : '',
    '#description' => imagecache_actions_file_field_description(),
    '#element_validate' => array('imagecache_actions_validate_file'),
  );
  return $form;
}

/**
 * Implements theme_hook() for the image mask effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_imagemask_summary(array $variables) {
  $data = $variables['data'];
  return 'file: ' . $data['path'];
}

/**
 * Image effect callback for the image mask effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return bool
 *   true on success, false otherwise.
 */
function canvasactions_imagemask_effect(stdClass $image, array $data) {
  $mask = imagecache_actions_image_load($data['path'], $image->toolkit);
  if ($mask) {
    // @todo: (sydneyshan) Consider best way to add offset support - I assume we
    // would position the mask somewhere (top/left/offset px etc) and choose if
    // the surrounding area is white or black (opaque or transparent) using an
    // extra form element (radio). Assess existing positioning code first to
    // reduce duplication of code. Pass the results to the following function as
    // array($mask, $data). Perhaps add a 'scale mask to fit image'/'scale image
    // to fit mask'/'no scale' radio group?
    return image_toolkit_invoke('imagemask', $image, array($mask));
  }
  return FALSE;
}

/**
 * GD toolkit specific implementation of the image mask effect.
 *
 * @param stdClass $image
 *   Image object containing the GD image resource to operate on.
 * @param stdClass $mask
 *   An image object containing the image to use as mask.
 *
 * @return bool
 *   true on success, false otherwise.
 */
function image_gd_imagemask(stdClass $image, stdClass $mask) {
  $newPicture = imagecreatetruecolor($image->info['width'], $image->info['height']);
  imagesavealpha($newPicture, TRUE);
  imagealphablending($newPicture, TRUE);
  $transparent = imagecolorallocatealpha($newPicture, 0, 0, 0, 127);
  imagefill($newPicture, 0, 0, $transparent);

  // Perform pixel-based alpha map application.
  for ($x = 0; $x < $image->info['width']; $x++) {
    for ($y = 0; $y < $image->info['height']; $y++) {
      // Deal with images with mismatched sizes
      if ($x >= $mask->info['width'] || $y >= $mask->info['height']) {
        imagesetpixel($newPicture, $x, $y, $transparent);
      }
      else {
        $alpha = imagecolorsforindex($mask->resource, imagecolorat($mask->resource, $x, $y));
        $alpha = 127 - floor($alpha['red'] / 2);
        $color = imagecolorsforindex($image->resource, imagecolorat($image->resource, $x, $y));
        imagesetpixel($newPicture, $x, $y, imagecolorallocatealpha($newPicture, $color['red'], $color['green'], $color['blue'], $alpha));
      }
    }
  }

  // Copy back to original picture.
  imagedestroy($image->resource);
  $image->resource = $newPicture;

  return TRUE;
}


/**
 * Imagemagick toolkit specific implementation of the image mask effect.
 *
 * @param stdClass $image
 *   Image object containing the image resource to operate on.
 * @param stdClass $mask
 *   An image object containing the image to use as mask.
 *
 * @return bool
 *   true on success, false otherwise.
 */
function image_imagemagick_imagemask(stdClass $image, stdClass $mask) {
  $image->ops[] = escapeshellarg($mask->source);
  $image->ops[] = '-alpha Off -compose CopyOpacity -composite';
  return TRUE;
}

/**
 * Image effect form callback for the define canvas effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_definecanvas_form(array $data) {
  module_load_include('inc', 'imagecache_actions', 'utility-color');
  $defaults = array(
    'RGB' => array(
      'HEX' => '#333333',
    ),
    'under' => TRUE,
    'exact' => array(
      'width' => '',
      'height' => '',
      'xpos' => 'center',
      'ypos' => 'center',
    ),
    'relative' => array(
      'leftdiff' => '',
      'rightdiff' => '',
      'topdiff' => '',
      'bottomdiff' => '',
    ),
  );
  $data += $defaults;

  $form = array(
    'RGB' => imagecache_rgb_form($data['RGB']),
    'help' => array(
      '#markup' => t('Enter no color value for transparent. This will have the effect of adding clear margins around the image.'),
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    ),
    'under' => array(
      '#type' => 'checkbox',
      '#title' => t('Resize canvas <em>under</em> image (possibly cropping)'),
      '#default_value' => $data['under'],
      '#description' => t('If <em>not</em> set, this will create a solid flat layer, probably totally obscuring the source image'),
    ),
  );
  $form['info'] = array('#value' => t('Enter values in ONLY ONE of the below options. Either exact or relative. Most values are optional - you can adjust only one dimension as needed. If no useful values are set, the current base image size will be used.'));
  $form['exact'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => 'Exact size',
    'help' => array(
      '#markup' => t('Set the canvas to a precise size, possibly cropping the image. Use to start with a known size.'),
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    ),
    'width' => array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $data['exact']['width'],
      '#description' => t('Enter a value in pixels or percent'),
      '#size' => 5,
    ),
    'height' => array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => $data['exact']['height'],
      '#description' => t('Enter a value in pixels or percent'),
      '#size' => 5,
    ),
  );
  $form['exact'] = array_merge($form['exact'], imagecache_actions_pos_form($data['exact']));
  if (!$data['exact']['width'] && !$data['exact']['height']) {
    $form['exact']['#collapsed'] = TRUE;
  }

  $form['relative'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Relative size'),
    'help' => array(
      '#markup' => t('Set the canvas to a relative size, based on the current image dimensions. Use to add simple borders or expand by a fixed amount. Negative values may crop the image.'),
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    ),
    'leftdiff' => array(
      '#type' => 'textfield',
      '#title' => t('left difference'),
      '#default_value' => $data['relative']['leftdiff'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels.'),
    ),
    'rightdiff' => array(
      '#type' => 'textfield',
      '#title' => t('right difference'),
      '#default_value' => $data['relative']['rightdiff'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels.'),
    ),
    'topdiff' => array(
      '#type' => 'textfield',
      '#title' => t('top difference'),
      '#default_value' => $data['relative']['topdiff'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels.'),
    ),
    'bottomdiff' => array(
      '#type' => 'textfield',
      '#title' => t('bottom difference'),
      '#default_value' => $data['relative']['bottomdiff'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels.'),
    ),
  );
  if (!$data['relative']['leftdiff'] && !$data['relative']['rightdiff'] && !$data['relative']['topdiff'] && !$data['relative']['bottomdiff']) {
    $form['relative']['#collapsed'] = TRUE;
  }

  $form['#submit'][] = 'canvasactions_definecanvas_form_submit';
  return $form;
}

/**
 * Implements theme_hook() for the define canvas effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_definecanvas_summary(array $variables) {
  $data = $variables['data'];
  if ($data['exact']['width'] || $data['exact']['height']) {
    $w = !empty($data['exact']['width']) ? $data['exact']['width'] : '100%';
    $h = !empty($data['exact']['height']) ? $data['exact']['height'] : '100%';
    $x = !empty($data['exact']['xpos']) ? $data['exact']['xpos'] : '0';
    $y = !empty($data['exact']['ypos']) ? $data['exact']['ypos'] : '0';
    $output = "{$w}x{$h} ($x, $y)";
  }
  else {
    $output = ' left:' . $data['relative']['leftdiff'];
    $output .= ' right:' . $data['relative']['rightdiff'];
    $output .= ' top:' . $data['relative']['topdiff'];
    $output .= ' bottom:' . $data['relative']['bottomdiff'];
  }
  $output .= theme('imagecacheactions_rgb', array('RGB' => $data['RGB']));
  $output .= ($data['under']) ? t(" <b>under</b> image ") : t(" <b>over</b> image ");
  return $output;
}

/**
 * Image effect callback for the define canvas effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function canvasactions_definecanvas_effect(stdClass $image, array $data) {
  // May be given either exact or relative dimensions.
  if ($data['exact']['width'] || $data['exact']['height']) {
    // Allows only one dimension to be used if the other is unset.
    if (!$data['exact']['width']) {
      $data['exact']['width'] = $image->info['width'];
    }
    if (!$data['exact']['height']) {
      $data['exact']['height'] = $image->info['height'];
    }

    $targetsize['width'] = imagecache_actions_percent_filter($data['exact']['width'], $image->info['width']);
    $targetsize['height'] = imagecache_actions_percent_filter($data['exact']['height'], $image->info['height']);

    $targetsize['left'] = image_filter_keyword($data['exact']['xpos'], $targetsize['width'], $image->info['width']);
    $targetsize['top'] = image_filter_keyword($data['exact']['ypos'], $targetsize['height'], $image->info['height']);

  }
  else {
    // Calculate relative size.
    $targetsize['width'] = $image->info['width'] + ((int) $data['relative']['leftdiff']) + ((int) $data['relative']['rightdiff']);
    $targetsize['height'] = $image->info['height'] + ((int) $data['relative']['topdiff']) + ((int) $data['relative']['bottomdiff']);
    $targetsize['left'] = (int) $data['relative']['leftdiff'];
    $targetsize['top'] = (int) $data['relative']['topdiff'];
  }

  // Convert from hex (as it is stored in the UI).
  if ($data['RGB']['HEX'] && $deduced = imagecache_actions_hex2rgba($data['RGB']['HEX'])) {
    $data['RGB'] = array_merge($data['RGB'], $deduced);
  }

  // All the math is done, now defer to the toolkit in use.
  $data['targetsize'] = $targetsize;

  $success = image_toolkit_invoke('definecanvas', $image, array($data));
  if ($success) {
    $image->info['width'] = $targetsize['width'];
    $image->info['height'] = $targetsize['height'];
  }
  return $success;
}

/**
 * GD toolkit specific implementation of the define canvas effect.
 *
 * @param stdClass $image
 * @param array $data
 *   The parameters for this effect. $data['targetsize'] is an array expected to
 *   contain a width, height and a left, top.
 *
 * @return bool
 *   true on success, false otherwise.
 */
function image_gd_definecanvas(stdClass $image, array $data) {
  $targetsize = $data['targetsize'];
  $RGB = $data['RGB'];

  $newcanvas = imagecreatetruecolor($targetsize['width'], $targetsize['height']);
  imagesavealpha($newcanvas, TRUE);
  imagealphablending($newcanvas, FALSE);
  imagesavealpha($image->resource, TRUE);
  if ($RGB['HEX']) {
    // Set color, allow it to define transparency, or assume opaque.
    $background = imagecolorallocatealpha($newcanvas, $RGB['red'], $RGB['green'], $RGB['blue'], $RGB['alpha']);
  }
  else {
    // No color, attempt transparency, assume white.
    $background = imagecolorallocatealpha($newcanvas, 255, 255, 255, 127);
  }
  imagefilledrectangle($newcanvas, 0, 0, $targetsize['width'], $targetsize['height'], $background);

  if ($data['under']) {
    $canvas_object = new stdClass();
    $canvas_object->resource = $newcanvas;
    $canvas_object->info = array(
        'width' => $targetsize['width'],
        'height' => $targetsize['height'],
        'mime_type' => $image->info['mime_type'],
        'extension' => $image->info['extension'],
      );
    $canvas_object->toolkit = $image->toolkit;
    image_overlay($image, $canvas_object, $targetsize['left'], $targetsize['top'], 100, TRUE);
  }
  else {
    $image->resource = $newcanvas;
  }
  return TRUE;
}

/**
 * Imagemagick toolkit specific implementation of the define canvas effect.
 *
 * @param stdClass $image
 * @param array $data
 *   The parameters for this effect. $data['targetsize'] is an array expected to
 *   contain a width, height and a left, top.
 *
 * @return bool
 *   true on success, false otherwise.
 *
 * @see http://www.imagemagick.org/script/command-line-options.php#extent
 */
function image_imagemagick_definecanvas(stdClass $image, $data) {
  // Reset any gravity settings from earlier effects.
  $image->ops[] = '-gravity None';

  $backgroundcolor = $data['RGB']['HEX'] != '' ? '#' . ltrim($data['RGB']['HEX'], '#') : 'None';
  $image->ops[] = '-background ' . escapeshellarg($backgroundcolor);

  $compose_operator = $data['under'] ? 'src-over' : 'dst-over';
  $image->ops[] = "-compose $compose_operator";

  $targetsize = $data['targetsize'];
  $geometry = sprintf('%dx%d', $targetsize['width'], $targetsize['height']);
  if ($targetsize['left'] || $targetsize['top']) {
    $geometry .= sprintf('%+d%+d', -$targetsize['left'], -$targetsize['top']);
  }
  $image->ops[] = '-extent ' . escapeshellarg($geometry);

  return TRUE;
}

/**
 * Image dimensions callback for the define canvas effect.
 *
 * @param array $dimensions
 *   Dimensions to be modified - an associative array containing the items
 *   'width' and 'height' (in pixels).
 * @param array $data
 *   An associative array containing the effect data.
 */
function canvasactions_definecanvas_dimensions(array &$dimensions, array $data) {
  // May be given either exact or relative dimensions.
  if ($data['exact']['width'] || $data['exact']['height']) {
    // Allows only one dimension to be used if the other is unset.
    if (!$data['exact']['width']) {
      $data['exact']['width'] = $dimensions['width'];
    }
    if (!$data['exact']['height']) {
      $data['exact']['height'] = $dimensions['height'];
    }

    $dimensions['width'] = imagecache_actions_percent_filter($data['exact']['width'], $dimensions['width']);
    $dimensions['height'] = imagecache_actions_percent_filter($data['exact']['height'], $dimensions['height']);
  }
  else {
    // Calculate relative sizes (only possible if we have the current size).
    if ($dimensions['width'] !== NULL) {
      $dimensions['width'] = $dimensions['width'] + (int) $data['relative']['leftdiff'] + (int) $data['relative']['rightdiff'];
    }
    if ($dimensions['height'] !== NULL) {
      $dimensions['height'] = $dimensions['height'] + (int) $data['relative']['topdiff'] + (int) $data['relative']['bottomdiff'];
    }
  }
}


/**
 * Image effect form callback for the underlay (background) effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_canvas2file_form(array $data) {
  $defaults = array(
    'xpos' => '0',
    'ypos' => '0',
    'alpha' => '100',
    'path' => '',
    'dimensions' => 'original',
  );
  $data = array_merge($defaults, (array) $data);

  $form = imagecache_actions_pos_form($data);
  $form['alpha'] = array(
    '#type' => 'textfield',
    '#title' => t('opacity'),
    '#default_value' => $data['alpha'],
    '#size' => 6,
    '#description' => t('Opacity: 0-100. Be aware that values other than 100% may be slow to process.'),
  );
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('file name'),
    '#default_value' => $data['path'],
    '#description' => imagecache_actions_file_field_description(),
    '#element_validate' => array('imagecache_actions_validate_file'),
  );
  $form['dimensions'] = array(
    '#type' => 'radios',
    '#title' => t('final dimensions'),
    '#default_value' => $data['dimensions'],
    '#options' => array(
      'original' => 'original (dimensions are retained)',
      'background' => 'background (image will be forced to match the size of the background)',
      'minimum' => 'minimum (image may be cropped)',
      'maximum' => 'maximum (image may end up with gaps)',
    ),
    '#description' => t('What to do when the background image is a different size from the source image. Backgrounds are not tiled, but may be arbitrarily large.'),
  );
  return $form;
}

/**
 * Implements theme_hook() for the underlay (background) effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_canvas2file_summary($variables) {
  $data = $variables['data'];
  $file = $data['path'];
  return "xpos:{$data['xpos']} , ypos:{$data['ypos']} alpha:{$data['alpha']}%. file: $file, dimensions:{$data['dimensions']}";
}

/**
 * Image effect callback for the underlay (background) effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function canvasactions_canvas2file_effect(stdClass $image, array $data) {
  $underlay = imagecache_actions_image_load($data['path'], $image->toolkit);
  if ($underlay) {
    // To handle odd sizes, we will resize/crop the background image to the
    // desired dimensions before starting the merge. The built-in
    // imagecopymerge, and the watermark library both do not allow overlays to
    // be bigger than the target.

    // Adjust size.
    $crop_rules = array(
      'xoffset' => 0,
      'yoffset' => 0,
    );
    if (empty($data['dimensions'])) {
      $data['dimensions'] = 'original';
    }
    switch ($data['dimensions']) {
      case 'original':
        // If the underlay is smaller than the target size,
        // then when preparing the underlay by cropping it,
        // the offsets may need to be negative
        // which will produce a 'cropped' image larger than the original.
        // In this case, we need to calculate the position of the bg image
        // in relation to the space it will occupy under the top layer
        //$crop_rules['xoffset'] = $underlay->info['width'] - $image->info['width'] ;

        $crop_rules['width'] = $image->info['width'];
        $crop_rules['height'] = $image->info['height'];
        break;
      case 'background':
        $crop_rules['width'] = $underlay->info['width'];
        $crop_rules['height'] = $underlay->info['height'];
        break;
      case 'minimum':
        $crop_rules['width'] = min($underlay->info['width'], $image->info['width']);
        $crop_rules['height'] = min($underlay->info['height'], $image->info['height']);
        break;
      case 'maximum':
        $crop_rules['width'] = max($underlay->info['width'], $image->info['width']);
        $crop_rules['height'] = max($underlay->info['height'], $image->info['height']);
        break;
    }
    // imageapi crop assumes upsize is legal.

    // Crop both before processing to avoid unwanted processing.
    image_crop_effect($underlay, $crop_rules);
    // @todo: BUG - this doesn't position either
    // Actually this fails because imagecache_crop fills it with solid color when 'cropping' to a larger size.
    //imagecache_crop_image($image, $crop_rules);
    //dpm(get_defined_vars());
    // This func modifies the underlay image by ref, placing the current canvas on it.
    if (image_overlay($image, $underlay, $data['xpos'], $data['ypos'], $data['alpha'], TRUE)) {
      //$image->resource = $underlay->resource;
      $image = $underlay; //@todo: this is a no-op.
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Image dimensions callback for the underlay (background) effect.
 *
 * @param array $dimensions
 *   Dimensions to be modified - an associative array containing the items
 *   'width' and 'height' (in pixels).
 * @param array $data
 *   An associative array containing the effect data.
 */
function canvasactions_canvas2file_dimensions(array &$dimensions, array $data) {
  if ($data['dimensions'] !== 'original') {
    $underlay = imagecache_actions_image_load($data['path']);
    if ($underlay) {
      // If the new dimensions are taken from the background, we don't need to
      // know the original dimensions, we can just set the new dimensions to the
      // dimensions of the background. Otherwise, we need to know the old
      // dimensions. If unknown we have to leave them unknown.
      switch ($data['dimensions']) {
        case 'background':
          $dimensions['width'] = $underlay->info['width'];
          $dimensions['height'] = $underlay->info['height'];
          break;
        case 'minimum':
          if ($dimensions['width'] !== NULL) {
            $dimensions['width'] = min($underlay->info['width'], $dimensions['width']);
          }
          if ($dimensions['height'] !== NULL) {
            $dimensions['height'] = min($underlay->info['height'], $dimensions['height']);
          }
          break;
        case 'maximum':
          if ($dimensions['width'] !== NULL) {
            $dimensions['width'] =  max($underlay->info['width'], $dimensions['width']);
          }
          if ($dimensions['height'] !== NULL) {
            $dimensions['height'] = max($underlay->info['height'], $dimensions['height']);
          }
      break;
      }
    }
  }
}


/**
 * Image effect form callback for the overlay (watermark) effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_file2canvas_form(array $data) {

  $defaults = array(
    'xpos' => '',
    'ypos' => '',
    'alpha' => '100',
    'scale' => '',
    'path' => '',
  );
  $data = array_merge($defaults, (array) $data);

  $form = array(
    'help' => array(
      '#markup' => t('Note that using a non transparent overlay that is larger than the source image may result in unwanted results - a solid background.'),
    ),
  );
  $form += imagecache_actions_pos_form($data);
  $form['alpha'] = array(
    '#type' => 'textfield',
    '#title' => t('opacity'),
    '#default_value' => $data['alpha'],
    '#field_suffix' => t('%'),
    '#size' => 6,
    '#description' => t('Opacity: 0-100. <b>Warning:</b> Due to a limitation in the GD toolkit, using an opacity other than 100% requires the system to use an algorithm that\'s much slower than the built-in functions. If you want partial transparency, you are better to use an already-transparent png as the overlay source image.'),
    '#element_validate' => array('imagecache_actions_validate_number_non_negative'),
  );
  $form['scale'] = array(
    '#type' => 'textfield',
    '#title' => t('scale'),
    '#default_value' => $data['scale'],
    '#field_suffix' => t('%'),
    '#size' => 6,
    '#description' => t('Scales the overlay with respect to the source, thus not its own dimensions. Leave empty to use the original size of overlay image.'),
    '#element_validate' => array('imagecache_actions_validate_number_positive'),
  );
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('file name'),
    '#default_value' => $data['path'],
    '#description' => imagecache_actions_file_field_description(),
    '#element_validate' => array('imagecache_actions_validate_file'),
  );
  return $form;
}

/**
 * Implements theme_hook() for the overlay (watermark) effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_file2canvas_summary(array $variables) {
  $data = $variables['data'];
  return '<strong>' . $data['path'] . '</strong>, x:' . $data['xpos'] . ', y:' . $data['ypos'] . ', alpha:' . (!empty($data['alpha']) ? $data['alpha'] : 100) . '%' . ', scale:' . (!empty($data['scale']) ? $data['scale'].'%' : '-');
}

/**
 * Image effect callback for the overlay (watermark) image effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function canvasactions_file2canvas_effect(stdClass $image, array $data) {
  $overlay = imagecache_actions_image_load($data['path']);
  if ($overlay) {
    if (!empty($data['scale']) && $data['scale'] > 0) {
      // Scale the overlay with respect to the dimensions of the source being
      // overlaid. To maintain the aspect ratio, only the width of the overlay
      // is scaled like that, the height of the overlay follows the aspect
      // ratio (that is why we use image_scale instead of image_resize).
      $overlay_w = $image->info['width'] * $data['scale'] / 100;
      image_scale($overlay, $overlay_w, NULL, TRUE);
    }
    if (!isset($data['alpha'])) {
      $data['alpha'] = 100;
    }
    return image_overlay($image, $overlay, $data['xpos'], $data['ypos'], $data['alpha']);
  }
  return FALSE;
}


/**
 * Image effect form callback for the overlay: source image to canvas effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_source2canvas_form($data) {
  $defaults = array(
    'xpos' => '',
    'ypos' => '',
    'alpha' => '100',
    'path' => '',
  );
  $data = array_merge($defaults, (array) $data);

  $form = imagecache_actions_pos_form($data);
  $form['alpha'] = array(
    '#type' => 'textfield',
    '#title' => t('opacity'),
    '#default_value' => $data['alpha'],
    '#size' => 6,
    '#description' => t('Opacity: 0-100.'),
  );
  return $form;
}

/**
 * Implements theme_hook() for the overlay: source img to canvas effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_source2canvas_summary(array $variables) {
  $data = $variables['data'];
  return 'xpos:' . $data['xpos'] . ', ypos:' . $data['ypos'] . ' alpha:' . $data['alpha'] . '%';
}

/**
 * Image effect callback for the overlay: source image to canvas effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function canvasactions_source2canvas_effect(stdClass $image, array $data) {
  $overlay = image_load($image->source, $image->toolkit);
  return image_overlay($image, $overlay, $data['xpos'], $data['ypos'], $data['alpha']);
}


/**
 * Image effect form callback for the aspect switcher effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_aspect_form(array $data) {
  $defaults = array(
    'ratio_adjustment' => 1,
    'portrait' => '',
    'landscape' => '',
  );
  $data = array_merge($defaults, (array) $data);

  $form = array(
    'help' => array(
      '#markup' => t('You must create the two presets to use <em>before</em> enabling this process.'),
    )
  );

  // The PASS_THROUGH parameter is new as of D7.23, and is added here to prevent
  // image_style_options() from double-encoding the human-readable image style
  // name, since the form API will already sanitize options in a select list.
  $styles = image_style_options(TRUE, PASS_THROUGH);
  // @todo: remove the current style to prevent (immediate) recursion?

  $form['portrait'] = array(
    '#type' => 'select',
    '#title' => t('Style to use if the image is portrait (vertical)'),
    '#default_value' => $data['portrait'],
    '#options' => $styles,
    '#description' => t('If you choose none, no extra processing will be done.'),
  );
  $form['landscape'] = array(
    '#type' => 'select',
    '#title' => t('Style to use if the image is landscape (horizontal)'),
    '#default_value' => $data['landscape'],
    '#options' => $styles,
    '#description' => t('If you choose none, no extra processing will be done.'),
  );

  $form['ratio_adjustment'] = array(
    '#type' => 'textfield',
    '#title' => t('Ratio Adjustment (advanced)'),
    '#size' => 3,
    '#default_value' => $data['ratio_adjustment'],
    '#description' => t("
This allows you to bend the rules for how different the proportions need to be to trigger the switch.
<br/>If the (width/height)*n is greater than 1, use 'landscape', otherwise use 'portrait'.
<br/>When n = 1 (the default) it will switch between portrait and landscape modes.
<br/>If n > 1, images that are slightly wide will still be treated as portraits.
If n < 1 then blunt portraits will be treated as landscape.
    "),
  );
  return $form;
}


/**
 * Implements theme_hook() for the aspect switcher effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_aspect_summary(array $variables) {
  $data = $variables['data'];

  $label = imagecache_actions_get_style_label($data['portrait']);
  $output = t('Portrait size: %label', array('%label' => $label));
  $label = imagecache_actions_get_style_label($data['landscape']);
  $output .= ', ' . t('Landscape size: %label', array('%label' => $label));
  if ($data['ratio_adjustment'] != 1) {
    $output .= ', ' . t("(switch at 1:@ratio_adjustment)", array('@ratio_adjustment' => $data['ratio_adjustment']));
  }
  return trim($output);
}

/**
 * Image effect callback for the aspect switcher effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function canvasactions_aspect_effect(stdClass $image, array $data) {
  $ratio_adjustment = isset($data['ratio_adjustment']) ? floatval( $data['ratio_adjustment']) : 1;
  $aspect = $image->info['width'] / $image->info['height'];

  // width / height * adjustment. If > 1, it's wide.
  $style_name = (($aspect * $ratio_adjustment) > 1) ? $data['landscape'] : $data['portrait'];

  if (empty($style_name)) {
    // Do nothing. just return what we've got.
    return TRUE;
  }

  $style = image_style_load($style_name);

  if (empty($style)) {
    // Required preset has gone missing?
    watchdog('imagecache_actions', "When running 'aspect' action, I was unable to load sub-action %style_name. Either it's been deleted or the DB needs an update", array('%style_name' => $style_name), WATCHDOG_ERROR);
    return FALSE;
  }

  // Run the preset actions ourself.
  foreach ($style['effects'] as $sub_effect) {
    image_effect_apply($image, $sub_effect);
  }
  return TRUE;
}

/**
 * Image dimensions callback for the aspect switcher effect.
 *
 * @param array $dimensions
 *   Dimensions to be modified - an associative array containing the items
 *   'width' and 'height' (in pixels).
 * @param array $data
 *   An associative array containing the effect data.
 */
function canvasactions_aspect_dimensions(array &$dimensions, array $data) {
  if (empty($dimensions['width']) || empty($dimensions['height'])) {
    // We cannot know which preset would be executed and thus cannot know the
    // resulting dimensions, unless both styles return the same dimensions:
    $landscape_dimensions = $portrait_dimensions = $dimensions;
    image_style_transform_dimensions($data['landscape'], $landscape_dimensions);
    image_style_transform_dimensions($data['portrait'], $portrait_dimensions);
    if ($landscape_dimensions == $portrait_dimensions) {
      $dimensions = $landscape_dimensions;
    }
    else {
      $dimensions['width'] = $dimensions['height'] = NULL;
    }
  }
  else {
    $ratio_adjustment = isset($data['ratio_adjustment']) ? floatval( $data['ratio_adjustment']) : 1;
    $aspect = $dimensions['width'] / $dimensions['height'];
    $style_name = (($aspect * $ratio_adjustment) > 1) ? $data['landscape'] : $data['portrait'];
    image_style_transform_dimensions($style_name, $dimensions);
  }
}

/**
 * Image effect form callback for the resize percent effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_resizepercent_form(array $data) {
  $defaults = array(
    'width' => '',
    'height' => '',
  );
  $data = array_merge($defaults, (array) $data);

  $form['#element_validate'] = array('image_effect_scale_validate');

  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => !empty($data['width']) ? (float) $data['width'] : '',
    '#field_suffix' => ' ' . t('percent'),
    '#required' => FALSE,
    '#size' => 10,
    '#element_validate' => array('canvasactions_resizepercent_validate'),
    '#allow_negative' => FALSE,
  );
  $form['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => !empty($data['height']) ? (float) $data['height'] : '',
    '#field_suffix' => ' ' . t('percent'),
    '#required' => FALSE,
    '#size' => 10,
    '#element_validate' => array('canvasactions_resizepercent_validate'),
    '#allow_negative' => FALSE,
  );

  return $form;
}


/**
 * Element validate handler to ensure that a positive number is specified.
 */
function canvasactions_resizepercent_validate($element, &$form_state) {
  element_validate_number($element, $form_state);
  if (!form_get_error($element)) {
    if ($element['#value'] != ''  && (float) $element['#value'] <= 0) {
      form_error($element, t('!name must be a positive number.', array('!name' => $element['#title'])));
    }
  }
}
/**
 * Calculate percent based on input, fallback if only one value is provided.
 *
 * @param array $data
 *
 * @return float[]|FALSE
 */
function _canvasactions_resizepercent_calculate_percent(array $data) {
  // Fallback if only one value is provided.
  if (empty($data['height'])) {
    if (empty($data['width'])) {
      return FALSE;
    }
    $data['height'] = $data['width'];
  }
  else if (empty($data['width'])) {
    $data['width'] = $data['height'];
  }

  // Get percentage values in decimal values.
  $data['width'] = (float) $data['width'] / 100;
  $data['height'] = (float) $data['height'] / 100;

  return $data;
}

/**
 * Implements theme_hook() for the resize percent effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_resizepercent_summary(array $variables) {
  $data = _canvasactions_resizepercent_calculate_percent($variables['data']);
  if (!$data) {
    return t('Invalid effect data');
  }
  if ($data['width'] != $data['height']) {
    return t('@width%x@height%', array('@width' => 100 * $data['width'], '@height' => 100 * $data['height']));
  }
  else {
    return t('scale to @percent%', array('@percent' => (float) 100 * $data['height']));
  }
}

/**
 * Image effect callback for the resize percent effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function canvasactions_resizepercent_effect(stdClass $image, array $data) {
  $data = _canvasactions_resizepercent_calculate_percent($data);

  $data['width'] = (int) round($image->info['width'] * $data['width']);
  $data['height'] = (int) round($image->info['height'] * $data['height']);

  return image_resize_effect($image, $data);
}

/**
 * Image dimensions callback for the resize percent effect.
 *
 * @param array $dimensions
 *   Dimensions to be modified - an associative array containing the items
 *   'width' and 'height' (in pixels).
 * @param array $data
 *   An associative array containing the effect data.
 */
function canvasactions_resizepercent_dimensions(array &$dimensions, array $data) {
  $data = _canvasactions_resizepercent_calculate_percent($data);

  $dimensions['width'] = (int) round($dimensions['width'] * $data['width']);
  $dimensions['height'] = (int) round($dimensions['height'] * $data['height']);
}

/**
 * Image effect form callback for the blur effect.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function canvasactions_blur_form(array $data) {
  $form['intensity'] = array(
    '#type' => 'textfield',
    '#title' => t('Blur intensity'),
    '#description' => t('A higher intensity results in more blur. The larger the image, the larger value you need to get a really blurred image, think 50 to 100 for 600x400 images.'),
    '#size' => 5,
    '#default_value' => isset($data['intensity']) ? (int) $data['intensity'] : 2,
    '#element_validate' => array('element_validate_integer_positive'),
  );
  return $form;
}

/**
 * Implements theme_hook() for the underlay (background) effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_canvasactions_blur_summary($variables) {
  return t('Intensity: @intensity', array('@intensity' => $variables['data']['intensity']));
}

/**
 * Image effect callback for the resize percent effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function canvasactions_blur_effect(stdClass $image, array $data) {
  return image_toolkit_invoke('blur', $image, $data);
}

/**
 * GD toolkit specific implementation of the blur effect.
 *
 * @param stdClass $image
 * @param int $intensity
 *   The number of times to apply the blur filter.
 *
 * @return boolean
 *   True on success, false otherwise.
 */
function image_gd_blur(stdClass $image, $intensity) {
  $intensity = (int) $intensity;
  $result = TRUE;
  $i = 0;
  while ($result && $i++ < $intensity) {
    $result = imagefilter($image->resource, IMG_FILTER_GAUSSIAN_BLUR);
  }
  return $result;
}

/**
 * Imagemagick toolkit specific implementation of the blur effect.
 *
 * See http://www.imagemagick.org/Usage/blur/.
 *
 * @param stdClass $image
 * @param int $intensity
 *   The "intensity" of the blur effect.
 *
 * @return boolean
 *   True on success, false otherwise.
 */
function image_imagemagick_blur(stdClass $image, $intensity) {
  // To get similar results asd with the GD factor, we use a formula to alter
  // the intensity into the sigma value that is passed to IM.
  $sigma = 4.0 + 0.8 * $intensity;
  $image->ops[] = '-blur ' . escapeshellarg(sprintf('0x%f', $sigma));
  return TRUE;
}

/**
 * Builds the interlace form.
 *
 * This effect has no options, only some help text, so the form is displayed
 * anyway.
 */
function canvasactions_interlace_form() {
  $form = array();
  $form['help'] = array(
    '#markup' => '<p><strong>There are no user-configurable options for this process.</strong></p>
      <p>This effect will save the derivative image in an interlace / progressive way
      which might improve perceived performance, especially for large images.
      File size and loading speed will not change, but the user will pretty quickly
      see a "degraded" copy of the entire image instead of a clear copy of the upper
      part of the image.</p>
      <p>Wikipedia: <a href="https://en.wikipedia.org/wiki/Interlacing_(bitmaps)">Interlacing (bitmaps)</a></p>',
  );
  return $form;
}

/**
 * Image effect callback for the Interlace / Progressive effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return bool
 *   true on success, false otherwise.
 */
function canvasactions_interlace_effect(stdClass $image, array $data) {
  return image_toolkit_invoke('interlace', $image, array($data));
}

/**
 * GD toolkit specific implementation of the image interlace effect.
 *
 * @param stdClass $image
 *   Image object containing the GD image resource to operate on.
 * param array $data
 *   The current configuration for this image effect.
 *
 * @return bool
 *   true on success, false otherwise.
 */
function image_gd_interlace($image/*, array $data*/) {
  imageinterlace($image->resource, 1);
  return TRUE;
}

/**
 * Imagemagick toolkit specific implementation of the image interlace effect.
 *
 * @param stdClass $image
 *   Image object containing the image resource to operate on.
 * param array $data
 *   The current configuration for this image effect.
 *
 * @return bool
 *   true on success, false otherwise.
 */
function image_imagemagick_interlace($image/*, array $data*/) {
  $image->ops[] = '-interlace Plane';
  return TRUE;
}
