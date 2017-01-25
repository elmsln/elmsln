<?php

/**
 * @file Routines for rounded corners
 */

/**
 * Set radius for corner rounding
 *
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_roundedcorners_form($action) {
  if (image_get_toolkit() != 'gd') {
    drupal_set_message('Rounded corners are not currently supported on all versions of imagemagick. This effect works best with GD image toolkit only.', 'warning');
  }
  drupal_add_js(drupal_get_path('module', 'imagecache_actions') . '/imagecache_actions.jquery.js');
  $defaults = array(
    'radius' => '16',
    #'antialias' => TRUE,
    'independent_corners_set' => array(
      'independent_corners' => FALSE,
      'radii' => array(
        'tl' => 0,
        'tr' => 0,
        'bl' => 0,
        'br' => 0,
      ),
    ),
  );
  $action = array_merge($defaults, (array) $action);

  $form['radius'] = array(
    '#type' => 'textfield',
    '#title' => t('radius'),
    '#default_value' => $action['radius'],
    '#size' => 2,
  );

  $form['independent_corners_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Individual Corner Values'),
    '#collapsible' => TRUE,
    '#collapsed' => (! $action['independent_corners_set']['independent_corners']),
  );
  $form['independent_corners_set']['independent_corners'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set Corners Independently'),
    '#default_value' => $action['independent_corners_set']['independent_corners'],
  );
  $corners = array(
    'tl' => t("Top Left Radius"),
    'tr' => t("Top Right Radius"),
    'bl' => t("Bottom Left Radius"),
    'br' => t("Bottom Right Radius"),
  );
  // Loop over the four corners and create field elements for them.
  $form['independent_corners_set']['radii'] = array(
    '#type' => 'item',
    '#id' => 'independent-corners-set',
    '#states' => array(
      'visible' => array(
        ':input[name="data[independent_corners_set][independent_corners]"]' => array('checked' => TRUE),
      ),
    ),
  );
  foreach ($corners as $attribute => $label) {
    $form['independent_corners_set']['radii'][$attribute] = array(
      '#type' => 'textfield',
      '#title' => $label,
      '#default_value' => 0 + $action['independent_corners_set']['radii'][$attribute],
      '#size' => 2,
    );
  }
  /*
   $form['antialias'] = array(
   '#type' => 'checkbox',
   '#title' => t('antialias'),
   '#return_value' => TRUE,
   '#default_value' => $action['antialias'],
   '#description' => t('Attempt antialias smoothing when drawing the corners'),
   );
   */
  $form['notes'] = array(
    '#markup' => t('
        Note: the rounded corners effect uses true alpha transparency masking.
        This means that this effect <b>will fail to be saved</b> on jpegs
        <em>unless</em> you either <ul>
        <li>convert the image to PNG (using the coloractions filter for that),</li>
        <li>define a canvas underneath it (using canvasactions-define-canvas) or</li>
        <li>underlay a solid color (using coloractions-alpha-flatten) or</li>
        <li>underlay a background image (canvasactions-underlay)</li>
        </ul>
        as a later part of this imagecache pipeline.
        <br/>
      '),
  );

  return $form;
}

function canvasactions_roundedcorners_effect($image, $action) {
  $independent_corners = !empty($action['independent_corners_set']['independent_corners']);
  if (!$independent_corners) {
    // set the independant corners to all be the same.
    $corners = array('tl', 'tr', 'bl', 'br');
    foreach ($corners as $key) {
      // Use the all-the-same radius setting.
      $action['independent_corners_set']['radii'][$key] = $action['radius'];
    }
  }

  return image_toolkit_invoke('roundedcorners', $image, array($action));
}

/**
 * Trim rounded corners off an image, using an anti-aliasing algorithm.
 *
 * Implementation of hook_image()
 *
 * Note, this is not image toolkit-agnostic yet! It just assumes GD.
 * We can abstract it out once we have something else to abstract to.
 * In the meantime just don't.
 *
 * 'handcoded' rounded corners logic contributed by donquixote 2009-08-31
 *
 * @param $image
 * @param $action
 */
function image_gd_roundedcorners($image, $action) {
  // Read settings.
  $width = $image->info['width'];
  $height = $image->info['height'];
  $radius = $action['radius'];
  $independent_corners = !empty($action['independent_corners_set']['independent_corners']);
  $corners = array('tl', 'tr', 'bl', 'br');

  $im = &$image->resource;
  // Prepare drawing on the alpha channel.
  imagesavealpha($im, TRUE);
  imagealphablending($im, FALSE);

  foreach ($corners as $key) {
    if ($independent_corners && isset($action['independent_corners_set']['radii'][$key])) {
      $r = $action['independent_corners_set']['radii'][$key];
    }
    else {
      // Use the all-the-same radius setting.
      $r = $radius;
    }

    // key can be 'tl', 'tr', 'bl', 'br'.
    $is_bottom = ($key{0} == 'b');
    $is_right = ($key{1} == 'r');

    // dx and dy are in "continuous coordinates",
    // and mark the distance of the pixel middle to the image border.
    for ($dx = .5; $dx < $r; ++$dx) {
      for ($dy = .5; $dy < $r; ++$dy) {

        // ix and iy are in discrete pixel indices,
        // counting from the top left
        $ix = floor($is_right ? $width -$dx : $dx);
        $iy = floor($is_bottom ? $height -$dy : $dy);

        // Color lookup at ($ix, $iy).
        $color_ix = imagecolorat($im, $ix, $iy);
        $color = imagecolorsforindex($im, $color_ix);


        // Do not process opacity if transparency is 100%. Just jump...
        // Opacity is always 0 on a transparent source pixel.
        if ($color['alpha'] != 127) {
          $opacity = _canvasactions_roundedcorners_pixel_opacity($dx, $dy, $r);
          if ($opacity >= 1) {
            // we can finish this row,
            // all following pixels will be fully opaque.
            break;
          }


          if (isset($color['alpha'])) {
            $color['alpha'] = 127 - round($opacity * (127 - $color['alpha']));
          }
          else {
            $color['alpha'] = 127 - round($opacity * 127);
          }
          // Value should not be more than 127, and not less than 0.
          $color['alpha'] = ($color['alpha'] > 127) ? 127 : (($color['alpha'] < 0) ? 0 : $color['alpha']);
        }

        $color_ix = imagecolorallocatealpha($im, $color['red'], $color['green'], $color['blue'], $color['alpha']);
        imagesetpixel($im, $ix, $iy, $color_ix);
      }
    }
  }
  return TRUE;
}

/**
 * Calculate the transparency value for a rounded corner pixel
 *
 * @param $x
 *   distance from pixel center to image border (left or right)
 *   should be an integer + 0.5
 *
 * @param $y
 *   distance from pixel center to image border (top or bottom)
 *   should be an integer + 0.5
 *
 * @param $r
 *   radius of the rounded corner
 *   should be an integer
 *
 * @return float
 *   opacity value between 0 (fully transparent) and 1 (fully opaque).
 *
 * OPTIMIZE HERE! This is a really tight loop, potentially getting called
 * thousands of times
 */
function _canvasactions_roundedcorners_pixel_opacity($x, $y, $r) {
  if ($x < 0 || $y < 0) {
    return 0;
  }
  else if ($x > $r || $y > $r) {
    return 1;
  }
  $dist_2 = ($r -$x) * ($r -$x) + ($r -$y) * ($r -$y);
  $r_2 = $r * $r;
  if ($dist_2 > ($r + 0.8) * ($r + 0.8)) {
    return 0;
  }
  else if ($dist_2 < ($r -0.8) * ($r -0.8)) {
    return 1;
  }
  else {
    // this pixel needs special analysis.
    // thanks to a quite efficient algorithm, we can afford 10x antialiasing :)
    $opacity = 0.5;
    if ($x > $y) {
      // cut the pixel into 10 vertical "stripes"
      for ($dx = -0.45; $dx < 0.5; $dx += 0.1) {
        // find out where the rounded corner edge intersects with the stripe
        // this is plain triangle geometry.
        $dy = $r - $y - sqrt($r_2 - ($r -$x -$dx) * ($r -$x -$dx));
        $dy = ($dy > 0.5) ? 0.5 : (($dy < -0.5) ? -0.5 : $dy);
        // count the opaque part of the stripe.
        $opacity -= 0.1 * $dy;
      }
    }
    else {
      // cut the pixel into 10 horizontal "stripes"
      for ($dy = -0.45; $dy < 0.5; $dy += 0.1) {
        // this is the math:
        //   ($r-$x-$dx)^2 + ($r-$y-$dy)^2 = $r^2
        //   $dx = $r - $x - sqrt($r^2 - ($r-$y-$dy)^2)
        $dx = $r - $x - sqrt($r_2 - ($r -$y -$dy) * ($r -$y -$dy));
        $dx = ($dx > 0.5) ? 0.5 : (($dx < -0.5) ? -0.5 : $dx);
        $opacity -= 0.1 * $dx;
      }
    }
    return ($opacity < 0) ? 0 : (($opacity > 1) ? 1 : $opacity);
  }
}



/**
 * imageapi_roundedcorners
 */
function image_imagemagick_roundedcorners($image, $action) {
  // Based on the imagemagick documentation.
  // http://www.imagemagick.org/Usage/thumbnails/#rounded
  // Create arc cut-outs, then mask them.
  // Draw black triangles and white circles.
  // draw circle is center: x,y, and a point on the perimeter
  $corners = array('tl', 'tr', 'bl', 'br');
  $radii = $action['independent_corners_set']['radii'];
  $width = $image->info['width'];
  $height = $image->info['height'];
  $tl = $radii['tl'];
  $tr = $radii['tr'];
  $bl = $radii['bl'];
  $br = $radii['br'];

  $drawmask = '';
  if ($tl) {
    $drawmask .= " fill black polygon 0,0 0,{$tl} {$tl},0";
    $drawmask .= " fill white circle {$tl},{$tl} {$tl},0";
  }
  if ($tr) {
    $right = $width -$tr;
    $drawmask .= " fill black polygon {$right},0 {$width},0 {$width},{$tr}";
    $drawmask .= " fill white circle {$right},{$tr} {$right},0";
  }
  if ($bl) {
    $bottom = $height -$bl;
    $drawmask .= " fill black polygon 0,{$bottom} 0,{$height} {$bl},{$height}";
    $drawmask .= " fill white circle {$bl},{$bottom} 0,{$bottom}";
  }
  if ($br) {
    $bottom = $height -$br;
    $right = $width -$br;
    $drawmask .= " fill black polygon {$right},{$height} {$width},{$bottom} {$width},{$height}";
    $drawmask .= " fill white circle {$right},{$bottom} {$width},{$bottom}";
  }
  $draw = ' -draw ' . escapeshellarg($drawmask);

  $compose = ' ' . escapeshellcmd('(') . " +clone  -threshold -1 $draw " . escapeshellcmd(')') . ' +matte -compose CopyOpacity -composite ';
  $image->ops[] = $compose;
  return TRUE;
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_roundedcorners($variables) {
  $element = $variables['element'];
  $data = $element['#value'];
  if (!empty($data['independent_corners_set']['independent_corners'])) {
    $dimens = join('px | ', $data['independent_corners_set']['radii']) . 'px';
  }
  else {
    $dimens = "Radius: {$data['radius']}px";
  }
  return $dimens;
}
