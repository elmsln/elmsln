<?php
/**
 * Implementation of image_effects_text.
 */

/**
 * Real implementation of hook_help() called by image_effects_text_help().
 *
 * Experimental diagnostic page to assist locating valid fonts on the system.
 * Only tuned for Ubuntu so far. I've been unable do find ubiquitous tools that
 * provide useful font listings.'
 */
function image_effects_text_help_inc(/*$path, $arg*/) {
  $output = "<p>
    For text rendering to work on a server, we <em>must</em>
    know the system path to the font <em>file</em>, not just the name.
    Font library handling differs too much on different systems and
    the available PHP toolkits are unable to return good diagnostics.
    </p><p>
    On Debian/Ubuntu, you may find your fonts in and under
    <code>/usr/share/fonts/truetype/</code>
    eg <code>'/usr/share/fonts/truetype/ttf-bitstream-vera/VeraMono.ttf'</code>
    </p><p>
    On OSX, they are probably in <code>/Library/Fonts/</code>
    eg <code>'/Library/Fonts/Times New Roman Bold Italic.ttf'</code>
    </p><p>
    On Windows, they are probably in <code>C:\\WINDOWS\Fonts\</code>
    eg <code>'C:\\WINDOWS\\Fonts\\comic.ttf'</code>
    </p><p>
    Of course, this will change if you deploy to a different server!
    so the best approach is to place your own TTF font file inside your private
    or public files directory and use that. Just give the filename with the
    'private://' or 'public://' scheme prefix and it should be found.
    </p>
  ";
  $output .= t("<p>Files directory is !files</p>", array('!files' => variable_get('file_public_path', conf_path() . '/files')));

  return $output;
}

/**
 * Image effect form callback for the text effect.
 *
 * Note that this is not a complete form, it only contains the portion of the
 * form for configuring the effect options. Therefore it does not not need to
 * include metadata about the effect, nor a submit button.
 *
 * @param array $data
 *   The current configuration for this image effect.
 *
 * @return array
 *   The form definition for this effect.
 */
function image_effects_text_form_inc(array $data) {
  // Use of functions imagecache_file_...() creates a dependency on file utility.inc.
  module_load_include('inc', 'imagecache_actions', 'utility');
  // Use of function imagecache_rgb_form() creates a dependency on file utility-color.inc.
  module_load_include('inc', 'imagecache_actions', 'utility-color');

  // Note: we also need to check for the existence of the module: admin has
  //   all rights, so user_access(...) returns TRUE even if the module is not
  //   enabled and the permission does not exist.
  // A user without the 'use PHP for settings' permission (defined by the core
  // PHP filter module) may not:
  // - Select the 'PHP code' text source option if it is currently not selected.
  // - Change the 'PHP code' textarea.
  $allow_php = module_exists('php') && user_access('use PHP for settings');
  $defaults = array(
    'text_source' => 'text',
    'text' => t('Hello World!'),
    'php' => 'if (!$image_context[\'entity\']) {
  return \'' . t('No referring entity') . '\';
}
$entity_type = \'node\';
$field_name = \'my_field\';
$entity = $image_context[\'entity\'];
$field = field_get_items($entity_type, $entity, $field_name);
if ($field) {
  return isset($field[0][\'value\']) ? $field[0][\'value\'] : \'' . t('No field value') . '\';
}
',
    'text_case' => 'none',
    'fontfile' => drupal_get_path('module', 'image_effects_text') . '/Komika_display.ttf',
    'size' => 50,
    'RGB' => array('HEX' => '#000000'),
    'alpha' => 100,
    'xpos' => '0',
    'ypos' => '0',
    'halign' => 'left',
    'valign' => 'top',
    'angle' => 0,
  );
  $data += $defaults;
  $tokens = token_info();
  $tokens = array_keys($tokens['types']);
  $form = array(
    'text_help' => array(
      '#type' => 'item',
      '#title' => t('Text'),
      '#description' => t('<p>Select the source of the text:</p>
<ul>
<li><strong>Image alt</strong>: the alt text of an image field referring to this image is taken.</li>
<li><strong>Image title</strong>: the title text of an image field referring to this image is taken.</li>
<li><strong>Text (with token replacement)</strong>: A text with optional token replacement. Line breaks can be inserted with \n (\\\\n for a literal \n). You can define the text in the text field below the drop down.</li>
<li><strong>PHP code</strong>: a piece of PHP code that returns the text to display. You can define the PHP code in the text area below the drop down. You will need the \'%use_php\' permission, defined by the \'PHP filter\' module.</li>
</ul>
<p>See the help in README.txt for an extensive explanation of the possibilities.</p>',
        array('%use_php' => t('Use PHP for settings'))),
    ),
    'text_source' => array(
      '#type' => 'select',
      '#title' => t('Text source'),
      '#default_value' => $data['text_source'],
      '#options' => array(
        'alt' => t('Image alt'),
        'title' => t('Image title'),
        'text' => t('Text (with token replacement)'),
        'php' => t('PHP code'),
      ),
    ),
    'text' => array(
      '#type' => 'textfield',
      '#title' => t('Text'),
      '#default_value' => $data['text'],
      '#states' => array(
        'visible' => array(':input[name="data[text_source]"]' => array('value' => 'text')),
      ),
    ),
    'token_help' => array(
      '#type' => 'fieldset',
      '#title' => t('Token replacement patterns'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'tree' => array(
        '#theme' => 'token_tree',
        '#token_types' => $tokens,
      ),
      'token_module_notice' => array(
        '#markup' => !module_exists('token') ? t('You might want to enable the token module to view token replacement patterns.') : '',
      ),
      'entity_token_module_notice' => array(
        '#markup' => !module_exists('entity_token') ? t('You might want to enable the entity_token module to get token options for all entities and field properties.') : '',
      ),
      '#states' => array(
        'visible' => array(':input[name="data[text_source]"]' => array('value' => 'text')),
      ),
    ),
    'php' => array(
      '#type' => 'textarea',
      '#rows' => 12,
      '#title' => t('PHP code'),
      '#default_value' => $data['php'],
      '#disabled' => !$allow_php,
      '#states' => array(
        'visible' => array(':input[name="data[text_source]"]' => array('value' => 'php')),
      ),
      '#wysiwyg' => FALSE,
    ),
    'text_case' => array(
      '#title' => t('Capitalization'),
      '#type' => 'select',
      '#options' => array(
        'none' => t('No transform'),
        'upper' => t('Upper case'),
        'lower' => t('Lower case'),
        'ucfirst' => t('Capitalize first letter'),
        'ucwords' => t('Capitalize each word'),
      ),
      '#default_value' => $data['text_case'],
      '#description' => t('Defines if and how to transform the case of the text to render.'),
    ),
    'fontfile' => array(
      '#type' => 'textfield',
      '#title' => t('Font file name'),
      '#default_value' => $data['fontfile'],
      '#description' => imagecache_actions_file_field_description(),
      '#element_validate' => array('image_effects_text_validate_font'),
      '#size' => 80,
    ),
    'size' => array(
      '#type' => 'textfield',
      '#title' => t('Font size'),
      '#default_value' => $data['size'],
      '#description' => t('The font size in points. Only in GD1 this is in pixels.'),
      '#size' => 3,
    ),
    'RGB' => imagecache_rgb_form($data['RGB']),
    'alpha' => array(
      '#type' => 'textfield',
      '#title' => t('Opacity'),
      '#default_value' => $data['alpha'],
      '#size' => 3,
      '#description' => t('Opacity: 1-100.'),
    ),
    'xpos' => array(
      '#type' => 'textfield',
      '#title' => t('X offset'),
      '#default_value' => $data['xpos'],
      '#description' => t('Enter an offset in pixels or use a keyword: <em>left</em>, <em>center</em>, or <em>right</em>. Syntax like <em>right-20</em> is also valid.'),
      '#size' => 10,
    ),
    'ypos' => array(
      '#type' => 'textfield',
      '#title' => t('Y offset'),
      '#default_value' => $data['ypos'],
      '#description' => t('Enter an offset in pixels or use a keyword: <em>top</em>, <em>center</em>, or <em>bottom</em>. Syntax like <em>bottom-20</em> is also valid.'),
      '#size' => 10,
    ),
    'halign' => array(
      '#type' => 'select',
      '#title' => t('Horizontal alignment'),
      '#default_value' => $data['halign'],
      '#description' => t('The horizontal alignment of the text around the given %xpos.', array('%xpos' => t('X offset'))),
      '#options' => array(
        'left' => t('Left'),
        'center' => t('Center'),
        'right' => t('Right')
      ),
    ),
    'valign' => array(
      '#type' => 'select',
      '#title' => t('Vertical alignment'),
      '#default_value' => $data['valign'],
      '#description' => t('The vertical alignment of the text around the given %ypos.', array('%ypos' => t('Y offset'))),
      '#options' => array(
        'top' => t('Top'),
        'center' => t('Center'),
        'bottom' => t('Bottom')
      ),
    ),
    'angle' => array(
      '#type' => 'textfield',
      '#title' => t('Angle'),
      '#default_value' => $data['angle'],
      '#description' => t('Angle: The angle in degrees, with 0 degrees being left-to-right reading text. Higher values represent a counter-clockwise rotation. For example, a value of 90 would result in bottom-to-top reading text.'),
      '#size' => 3,
    ),
  );
  if (!$allow_php && $data['text_source'] !== 'php') {
    unset($form['text_fieldset']['text_source']['#options']['php']);
  }

  $form['#element_validate'][] = 'image_effects_text_form_validate';
  return $form;
}

/**
 * Element validation callback for the effect form.
 * @see http://api.drupal.org/api/drupal/developer--topics--forms_api_reference.html/7#element_validate
 */
function image_effects_text_form_validate(array $element/*, &$form_state, $form*/) {
  if (!is_numeric($element['size']['#value']) || $element['size']['#value'] <= 0) {
    form_error($element['size'], t('%field must be a positive number.', array('%field' => t('Font size'))));
  }
  if (!is_numeric($element['alpha']['#value']) || $element['alpha']['#value'] < 0 || $element['alpha']['#value'] > 100) {
    form_error($element['alpha'], t('%field must be a number between 1 and 100.', array('%field' => t('Opacity'))));
  }
  if (!is_numeric($element['angle']['#value'])) {
    form_error($element['angle'], t('%field must be a number.', array('%field' => t('Angle'))));
  }
}

/**
 * Validates that the file as specified in the element exists and is readable.
 *
 * This is a Form API #element_validate callback.
 *
 * @param array $element
 */
function image_effects_text_validate_font(array &$element/*, &$form_status*/) {
  if (!imagecache_actions_find_file($element['#value'])) {
    drupal_set_message(t("Unable to find the font file '%file'. Please check the path. You can ignore this waning, if the font refers to a system or toolkit font, and the text shows correctly.", array('%file' => $element['#value'])), 'warning');
  }
}

/**
 * Implements theme_hook() for the text effect summary.
 *
 * @param array $variables
 *   An associative array containing:
 *   - data: The current configuration for this image effect.
 *
 * @return string
 *   The HTML for the summary of this image effect.
 * @ingroup themeable
 */
function theme_image_effects_text_summary(array $variables) {
  $data = $variables['data'];
  switch ($data['text_source']) {
    case 'alt':
      $text = 'image alt';
      break;
    case 'title':
      $text = 'image title';
      break;
    case 'text':
      $text = $data['text'];
      break;
    case 'php':
      $text = 'PHP code';
      break;
    default:
      $text = '';
      break;
  }
  return 'Text: ' . $text . '; Position: ' . $data['xpos'] . ',' . $data['ypos'] . '; Alignment: ' . $data['halign'] . ',' . $data['valign'];
}

/**
 * Image effect callback for the text effect.
 *
 * @param stdClass $image
 * @param array $data
 *
 * @return boolean
 *   true on success, false otherwise.
 */
function image_effects_text_effect_inc(stdClass $image, array $data) {
  // Use of imagecache_actions_hex2rgba() ,the imagecache_file_...() functions,
  // and imagecache_actions_get_image_context() create a dependency on
  // file utility.inc.
  module_load_include('inc', 'imagecache_actions', 'utility');

  // Massage the data and pass it on to the toolkit dependent part.
  // Start with a straight copy.
  $params = $data;

  // Get the text to overlay.
  $params['text'] = image_effects_text_get_text($image, $params);
  if (empty($params['text'])) {
    // No text to overlay. This is a situation that can be expected with token
    // replacement, or custom PHP code. Return immediately with success.
    return TRUE;
  }

  // Find out where the font file is located and if it is readable.
  $params['fontpath'] = imagecache_actions_find_file($data['fontfile']);
  if ($params['fontpath'] === FALSE) {
    // Pass the font on and let's hope that the toolkit knows where to find it.
    // We did warn on the effect form.
    $params['fontpath'] = $data['fontfile'];
  }

  // Parse offsets.
  $params['xpos'] = image_effects_text_get_offset($data['xpos'], $image->info['width'], $image->info['height'], $image->info['width']);
  $params['ypos'] = image_effects_text_get_offset($data['ypos'], $image->info['width'], $image->info['height'], $image->info['height']);

  // Convert color from hex (as it is stored in the UI).
  $params['RGB'] = $data['RGB'];
  if ($params['RGB']['HEX'] && $deduced = imagecache_actions_hex2rgba($params['RGB']['HEX'])) {
    $params['RGB'] += $deduced;
  }

  // Make integers of various parameters.
  $params['size'] = (int) $params['size'];
  $params['xpos'] = (int) $params['xpos'];
  $params['ypos'] = (int) $params['ypos'];

  // Hand over to toolkit.
  return image_toolkit_invoke('image_effects_text', $image, array($params));
}

/**
 * GD toolkit specific implementation of the text effect.
 *
 * @param stdClass $image
 * @param array $data
 *   The parameters for this effect.
 *
 * @return bool
 *   true on success, false otherwise.
 */
function image_gd_image_effects_text(stdClass $image, array $data) {
  // Convert color and alpha to GD alpha and color value.
  // GD alpha value: 0 = opaque, 127 = transparent.
  $data['alpha'] = (int) ((1 - ($data['alpha'] / 100)) * 127);
  $color = imagecolorallocatealpha($image->resource, $data['RGB']['red'], $data['RGB']['green'], $data['RGB']['blue'], $data['alpha']);
  if ($color !== FALSE) {
    $bounds = NULL;
    // Adjust Y position for vertical alignment (if different from bottom).
    if ($data['valign'] !== 'bottom') {
      // Get bounding box.
      // PHP Manual: "This function requires both the GD library and the » FreeType library."
      // So it is not more demanding than imagettftext, which we need anyway.
      $bounds = imagettfbbox($data['size'], 0, $data['fontpath'], $data['text']);
      if (!$bounds) {
        drupal_set_message(t('Failed to calculate text dimensions using GD toolkit. Ignoring the alignment settings.'), 'warning');
      }
      else {
        // Get height of bounding box.
        $height = $bounds[1] - $bounds[7];
        // Shift ypos down (full height on bottom, half the height on center).
        $data['ypos'] += $data['valign'] === 'center' ? (int) ($height / 2) : $height;
      }
    }
    // Adjust X position for horizontal alignment (if different from left).
    if ($data['halign'] !== 'left') {
      // Get bounding box. PHP Manual: "This function requires both the GD
      // library and the » FreeType library.", so it is not more demanding than
      // imagettftext(), which we need anyway.
      if ($bounds === NULL) {
        $bounds = imagettfbbox($data['size'], 0, $data['fontpath'], $data['text']);
        if (!$bounds) {
          drupal_set_message(t('Failed to calculate text dimensions using GD toolkit. Ignoring the alignment.'), 'warning');
        }
      }
      if ($bounds !== FALSE) {
        // Get width of bounding box.
        $width = $bounds[2] - $bounds[0];
        // Shift xpos to the left (full width on right, half the width on center).
        $data['xpos'] -= $data['halign'] === 'center' ? (int) ($width / 2) : $width;
      }
    }

    // PHP Manual: "This function requires both the GD library and the » FreeType library."
    $bounds = imagettftext($image->resource, $data['size'], $data['angle'], $data['xpos'], $data['ypos'], $color, $data['fontpath'], $data['text']);
    return $bounds !== FALSE;
  }
  return FALSE;
}

/**
 * Imagemagick toolkit specific implementation of the text effect.
 *
 * Text in Imagemagick:
 * - http://www.imagemagick.org/script/command-line-options.php?#draw
 * - http://www.imagemagick.org/script/command-line-options.php?#annotate
 *
 * UTF-8/non-ascii characters:
 * To prevent problems with non-ASCII characters, the online manual suggests to
 * put the text in a file and use the @{file} syntax. This does not work with
 * the text primitive of the -draw command, so we use -annotate.
 * We put the text in a temporary file which will be deleted by our hook_exit().
 * http://www.imagemagick.org/Usage/windows/#character_encoding
 *
 * Alignment in Imagemagick:
 * This is not directly supported, though a justification option has been
 * proposed: http://www.imagemagick.org/Usage/bugs/future/#justification.
 *
 * What we do have is the gravity option:
 * Gravity is used to position a text, but it also automatically applies a
 * justification based on that placement. So we use gravity here for alignment,
 * but will thus have to rebase our positioning.
 * - http://www.imagemagick.org/Usage/annotating/#gravity
 *
 * Gravity  |halign|valign |hpos change|vpos change
 * ------------------------------------------------
 * NorthWest left   top     0           0
 * North     center top     -width/2    0
 * NorthEast right  top     -width      0
 * West      left   center  0           -height/2
 * Center    center center  -width/2    -height/2
 * East      right  center  -width      -height/2
 * SouthWest left   bottom  0           -height
 * South     center bottom  -width/2    -height
 * SouthEast right  bottom  -width      -height
 *
 * @param stdClass $image
 * @param array $data
 *   The parameters for this effect.
 *
 * @return bool
 *   true on success, false otherwise.

 */
function image_imagemagick_image_effects_text(stdClass $image, array $data) {
  static $alignments2gravity = array(
    'left' => array(
      'top' => array(
        'gravity' => 'NorthWest',
        'tx' => 0,
        'ty' => 0,
      ),
      'center' => array(
        'gravity' => 'West',
        'tx' => 0,
        'ty' => -0.5,
      ),
      'bottom' => array(
        'gravity' => 'SouthWest',
        'tx' => 0,
        'ty' => 1, // reversed translation
      ),
    ),
    'center' => array(
      'top' => array(
        'gravity' => 'North',
        'tx' => -0.5,
        'ty' => 0,
      ),
      'center' => array(
        'gravity' => 'Center',
        'tx' => -0.5,
        'ty' => -0.5,
      ),
      'bottom' => array(
        'gravity' => 'South',
        'tx' => -0.5,
        'ty' => 1, // reversed translation
      ),
    ),
    'right' => array(
      'top' => array(
        'gravity' => 'NorthEast',
        'tx' => 1, // reversed translation
        'ty' => 0,
      ),
      'center' => array(
        'gravity' => 'East',
        'tx' => 1, // reversed translation
        'ty' => -0.5,
      ),
      'bottom' => array(
        'gravity' => 'SouthEast',
        'tx' => 1, // reversed translation
        'ty' => 1, // reversed translation
      ),
    ),
  );

  // Convert color and alpha to Imagemagick rgba color argument.
  $alpha = $data['alpha'] / 100;
  $color = 'rgba(' . $data['RGB']['red'] . ',' . $data['RGB']['green'] . ',' . $data['RGB']['blue'] . ',' . $alpha . ')';

  // Set gravity for the alignment and calculate the translation to the
  // requested x and y offset as starting from the gravity point.
  $alignment_corrections = $alignments2gravity[$data['halign']][$data['valign']];
  $gravity = $alignment_corrections['gravity'];
  if ($alignment_corrections['tx'] > 0) {
    $data['xpos'] = (int) ($alignment_corrections['tx'] * $image->info['width'] - $data['xpos']);
  }
  else {
    $data['xpos'] += (int) ($alignment_corrections['tx'] * $image->info['width']);
  }
  if ($alignment_corrections['ty'] > 0) {
    $data['ypos'] = (int) ($alignment_corrections['ty'] * $image->info['height'] - $data['ypos']);
  }
  else {
    $data['ypos'] += (int) ($alignment_corrections['ty'] * $image->info['height']);
  }

  // Add signs to translation, also when positive or 0.
  if ($data['xpos'] >= 0) {
    $data['xpos'] = '+' . $data['xpos'];
  }
  if ($data['ypos'] >= 0) {
    $data['ypos'] = '+' . $data['ypos'];
  }

  // Angle must be positive.
  if ($data['angle'] < 0) {
    $data['angle'] = $data['angle'] % 360 + 360;
  }

  // Set font file, size and color. fontpath is the real path, not a wrapper.
  $image->ops[] = '-font ' . escapeshellarg($data['fontpath']);
  $image->ops[] = "-pointsize {$data['size']}";
  $image->ops[] = '-fill ' . escapeshellarg($color);

  // Add text to a temporary file,
  $tmp_file_name = drupal_tempnam('temporary://', 'image_effects_text');
  $tmp_file = fopen($tmp_file_name, 'w');
  if ($tmp_file) {
    fwrite($tmp_file, $data['text']);
    fclose($tmp_file);
    // and inform our hook_exit about it.
    image_effects_text_exit($tmp_file_name);
    $tmp_file_name = drupal_realpath($tmp_file_name);
    $text = "@$tmp_file_name";
  }
  else {
    // Fallback to pass the text via the command line, let's hope there are no
    // non-ASCII characters or that it works anyway (OS and locale dependent).
    $text = $data['text'];
  }

  // Add gravity.
  $image->ops[] = "-gravity $gravity";
  // Add text angle, position and text (file) itself.
  $image->ops[] = "-annotate {$data['angle']}x{$data['angle']}{$data['xpos']}{$data['ypos']} " . escapeshellarg($text);

  return TRUE;
}


/**
 * UTILITY
 */

/**
 * Convert a position into an offset in pixels.
 *
 * Position may be a number of additions and/or subtractions of:
 * - An value, positive or negative, in pixels.
 * - A, positive or negative, percentage (%). The given percentage of the
 *   current dimension will be taken.
 * - 1 of the keywords:
 *   * top: 0
 *   * bottom: the height of the current image
 *   * left: 0
 *   * right: the width of the current image
 *   * center: 50% (of the current dimension)
 * Examples:
 * 0, 20, -20, 90%, 33.3% + 10, right, center - 20, 300 - center, bottom - 50.
 * Note:
 * The algorithm will accept many more situations, though the result may be hard
 * to predict.
 *
 * @param string $position
 *   The string defining the position.
 * @param int $width
 *   The length of the horizontal dimension.
 * @param int $height
 *   The length of the vertical dimension.
 * @param int $length
 *   The length of the current dimension (should be either width or height).
 *
 * @return number
 *   The computed offset in pixels.
 */
function image_effects_text_get_offset($position, $width, $height, $length) {
  $value = 0;

  $tokens = preg_split('/ *(-|\+) */', $position, 0, PREG_SPLIT_DELIM_CAPTURE);
  $sign = 1;
  foreach ($tokens as $token) {
    switch ($token) {
      case '+';
        // Ignore, doesn't change the sign
        break;
      case '-';
        // Flip the sign.
        $sign = -$sign;
        break;
      case 'top':
      case 'left':
        // Actually, top and left are a no-op.
        $value += $sign * 0;
        $sign = 1;
        break;
      case 'bottom':
        // Use height of the image, even if this is for the horizontal position.
        $value += $sign * $height;
        $sign = 1;
        break;
      case 'right':
        // Use width of the image, even if this is for the vertical position.
        $value += $sign * $width;
        $sign = 1;
        break;
      case 'center':
        // half the current dimension as provided by $length.
        $value += $sign * $length / 2;
        $sign = 1;
        break;
      default:
        // Value: absolute or percentage
        if (substr($token, -strlen('%')) === '%') {
          $percentage = ((float) substr($token, 0, -strlen('%'))) / 100.0;
          $value += $sign * ($percentage * $length);
        }
        else {
          $value += $sign * (float) $token;
        }
        $sign = 1;
        break;
    }
  }
  return $value;
}

/**
 * Get the text to use for this image.
 *
 * @param stdClass $image
 *   The image the current effect is to be applied to.
 * @param array $data
 *   An array containing the effect data.
 *
 * @return string
 *   Plain text to be placed on the image.
 */
function image_effects_text_get_text(stdClass $image, array $data) {
  // Get context about the image.
  $image_context = imagecache_actions_get_image_context($image, $data);

  if ($data['text_source'] === 'text') {
    // Replace \n with a newline character, except when preceded by a \.
    $text = preg_replace('/([^\\\\])\\\\n/', "$1\n", $data['text']);
    // Replace \\n by \n.
    $text = preg_replace('/\\\\\\\\n/', '\n', $text);

    // Replace tokens.
    $token_data = array();
    foreach ($image_context['referring_entities'] as /*$field_name =>*/ $field_referring_entities) {
      foreach ($field_referring_entities as $entity_type => $entities) {
        // We can pass only 1 entity per given type to token_replace(), we take
        // the first.
        $token_data[$entity_type] = reset($entities);
      }
    }
    if ($image_context['managed_file']) {
      $token_data['file'] = $image_context['managed_file'];
    }
    // We should not sanitize the text as it will not be rendered in the browser
    // but is rendered on the image canvas on the server.
    $text = token_replace($text, $token_data, array('clear' => TRUE, 'sanitize' => FALSE));
  }
  else if ($data['text_source'] === 'alt' || $data['text_source'] === 'title') {
    $text = '';
    // We have 2 possible sources for the alt or title text:
    // - Image field.
    // - Media module (7.x-2.x) with file_entity: the alt and title come as
    // fields of the file entity, stored in 'managed_file'. The names of the
    // fields are field_file_image_alt_text resp. field_file_image_title_text.
    // BTW: these fields are also available in the 'image_field' entry, but as
    // a managed file may be existing without any image field referring to it,
    // we do the lookup in the managed_file entry.
    if (!empty($image_context['image_field'][$data['text_source']])) {
      $text = $image_context['image_field'][$data['text_source']];
    }
    else if (!empty($image_context['managed_file'])) {
      $field = field_get_items('file', $image_context['managed_file'], "field_file_image_{$data['text_source']}_text");
      if ($field) {
        $text = $field[0]['value'];
      }
    }
  }
  else { // $data['text_source'] === 'php'
    // Process the php using php_eval (rather than eval), but with GLOBAL
    // variables, so they can be passed successfully.
    $GLOBALS['image_context'] = $image_context;
    $GLOBALS['image'] = $image;

    // Get (non-alterable) context about the image style and image effect.
    $execution_info = imagecache_actions_get_image_effect_context();
    $GLOBALS['image_style'] = $execution_info['image_style'];
    $GLOBALS['image_effect_id'] = $execution_info['image_effect_id'];

    // We don't need to check_plain() the resulting text, as the text is not
    // rendered in a browser but processed on the server.
    $text = module_exists('php') ? php_eval('<' . '?php global $image, $image_context; ' . $data['php'] . ' ?' . '>') : '';

    unset($GLOBALS['image_effect_id']);
    unset($GLOBALS['image_style']);
    unset($GLOBALS['image']);
    unset($GLOBALS['image_context']);
  }

  // Convert case.
  $text = image_effect_text_case_transform($text, isset($data['text_case']) ? $data['text_case'] : 'none');

  return $text;
}

/**
 * Transform a string by a certain method.
 *
 * Proudly copied from module://views/includes/handlers.inc.
 *
 * @param $string
 *    The input you want to transform.
 * @param $option
 *    How do you want to transform it, possible values:
 *      - upper: Uppercase the string.
 *      - lower: lowercase the string.
 *      - ucfirst: Make the first char uppercase.
 *      - ucwords: Make each word in the string uppercase.
 *
 * @return string
 *    The transformed string.
 */
function image_effect_text_case_transform($string, $option) {
  global $multibyte;

  switch ($option) {
    default:
      return $string;
    case 'upper':
      return drupal_strtoupper($string);
    case 'lower':
      return drupal_strtolower($string);
    case 'ucfirst':
      return drupal_strtoupper(drupal_substr($string, 0, 1)) . drupal_substr($string, 1);
    case 'ucwords':
      if ($multibyte == UNICODE_MULTIBYTE) {
        return mb_convert_case($string, MB_CASE_TITLE);
      }
      else {
        return ucwords($string);
      }
  }
}

