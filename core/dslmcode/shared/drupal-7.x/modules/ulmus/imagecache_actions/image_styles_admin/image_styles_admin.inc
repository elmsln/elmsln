<?php

/**
 * @file Include file for image_styles_admin routines that do not need to be
 * loaded on each request.
 */

/**
 * Menu callback: Duplicates an image style and redirects to the image styles
 * overview page.
 *
 * @param array $style
 *   An image style array.
 *
 * @see image_style_name_validate()
 */
function image_styles_admin_duplicate_page_callback($style) {
  $duplicate_style = image_styles_admin_duplicate($style);
  drupal_set_message(t('Style %name has been duplicated to %new_name.', array(
    '%name' => isset($style['label']) ? $style['label'] : $style['name'],
    '%new_name' =>  isset($duplicate_style['label']) ? $duplicate_style['label'] : $duplicate_style['name'])));
  drupal_goto('admin/config/media/image-styles');
}

/**
 * Duplicates an image style and saves it.
 *
 * @param array $style
 *   An image style array.
 * @param string|null $new_style_name
 *   The preferred name for the new style. If left empty, the new name will be
 *   based on the name of the style to duplicate. In both cases and when
 *   necessary, the new name will be made unique by adding some suffix to it.
 * @param string|null $new_style_label
 *   The preferred label for the new style. If left empty, the new label will be
 *   based on the label of the style to duplicate. If that one is also empty,
 *   no label will be defined for the new style, so Drupal (>=7.23) will create
 *   one.
 *
 * @return array
 *   An image style array with the newly created copy of the given style.
 *
 * @see image_style_name_validate()
 */
function image_styles_admin_duplicate($style, $new_style_name = NULL, $new_style_label = NULL) {
  // Find a unique name for the copy.
  // Step 1: Find the base: name without things like '-copy' or '-copy-1'
  $style_name_base = empty($new_style_name) ? $style['name'] : $new_style_name;
  if (preg_match('/-copy(-\d+)?$/', $style_name_base)) {
    $style_name_base = substr($style_name_base, 0, strpos($style_name_base, '-copy'));
  }

  // Step 2: Add -copy to it (if the name comes from the current style).
  if (empty($new_style_name)) {
    $style_name_base .= '-copy';
  }

  // Step 3: Ensure the new name will be unique.
  $i = 0;
  $style_name = $style_name_base;
  $styles = image_styles();
  while (isset($styles[$style_name])) {
    $i++;
    $style_name = $style_name_base . '-' . $i;
  }
  $style['name'] = $style_name;

  // Step 4: Find a new label for the copy.
  if (isset($new_style_label) || isset($style['label'])) {
    $style_label = empty($new_style_label) ? $style['label'] : $new_style_label;
    $copy = t('copy');
    if (preg_match("/ $copy( \d+)?$/", $style_label)) {
      $style_label = substr($style_label, 0, strpos($style_label, " $copy"));
    }

    // Step 4a: Add " copy" to it (if the name comes from the current style).
    if (empty($new_style_label)) {
      $style_label .= " $copy";
    }

    // Step 4b: Make "unique" (based on the number added to the name)
    if ($i > 0) {
      $style['label'] .= " $i";
    }
  }

  // Unset isid to save it as a new style.
  unset($style['isid']);
  $style = image_style_save($style);

  // Save copies of each effect with the new image style ID (isid).
  foreach ($style['effects'] as &$effect) {
    // Unset ieid to save it as a new effect.
    unset($effect['ieid']);
    $effect['isid'] = $style['isid'];
    $effect = image_effect_save($effect);
  }

  return $style;
}

/**
 * drupal_get_form callback: form to export an image style.
 *
 * @param array $form
 * @param array $form_state
 * @param array $style
 *   An image style array.
 *
 * @return array
 */
function image_styles_admin_export_form($form, $form_state, $style) {
  drupal_set_title(format_string('%page_name @style_name',
    array('%page_name' => t('Export image style'), '@style_name' => isset($style['label']) ? $style['label'] : $style['name'])),
    PASS_THROUGH);
  $form['serialized_style'] = array(
    '#type' => 'textarea',
  	'#rows' => 5,
  	'#title' => t('Image style export data'),
  	'#default_value' => image_styles_admin_export_serialize($style),
  	'#attributes' => array('readonly' =>'readonly'),
  	'#description' => t('Copy the contents of this field to the clipboard and, on another site, paste it in the textarea of an %page_title page.',
      array('%page_title' => t('Import image style'))),
  );
  return $form;
}

/**
* drupal_get_form callback: form to import an image style.
*/
function image_styles_admin_import_form($form/*, $form_state*/) {
  $form['serialized_style'] = array(
    '#type' => 'textarea',
  	'#rows' => 5,
  	'#title' => t('Image style import data'),
  	'#default_value' => '',
    '#required' => TRUE,
  	'#description' => t('Paste the contents of the textarea of an %page_title page into this field.', array('%page_title' => t('Export image style'))),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Callback to validate the import style form.
 */
function image_styles_admin_import_form_validate($form, &$form_state) {
  $import = image_styles_admin_unify_newlines($form_state['values']['serialized_style']);
  if (image_styles_admin_import_extract_style($import) === FALSE) {
    form_set_error('serialized_style', t('The %field cannot be imported as an image style.', array('%field' => t('Image style import data'))));
  }
}

/**
 * Callback to process form submission of the import style form.
 */
function image_styles_admin_import_form_submit($form, &$form_state) {
  $import = image_styles_admin_unify_newlines($form_state['values']['serialized_style']);
  $style = image_styles_admin_import_extract_style($import);
  // Import the style by "duplicating" it, but prevent adding the -copy suffix
  // by passing the requested name and label as 2nd and 3rd parameter.
  $new_style = image_styles_admin_duplicate($style, $style['name'], isset($style['label']) ? $style['label'] : NULL);
  if ($new_style['name'] === $style['name']) {
    drupal_set_message(t('Style %name has been imported.', array('%name' => $style['name'])));
  }
  else {
    drupal_set_message(t('Style %name has been imported as %new_name.', array(
      '%name' => isset($style['label']) ? $style['label'] : $style['name'],
      '%new_name' => isset($new_style['label']) ? $new_style['label'] : $new_style['name'])));
  }
  drupal_goto('admin/config/media/image-styles');
}

/**
 * Serializes image style data so it can be exported.
 *
 * @param array $style
 *   An image style array.
 *
 * @return string
 *   The serialized image style. Keys that are not needed for import are not
 *   serialized.
 */
function image_styles_admin_export_serialize($style) {
  $style = array_intersect_key($style, array('name' => 0, 'label' => 0, 'effects' => 0));
  foreach ($style['effects'] as &$effect) {
    $effect = array_intersect_key($effect, array('weight' => 0, 'name' => 0, 'data' => 0));
  }

  array_walk_recursive($style, function(&$value) {
    if (is_string($value)) {
      $value = image_styles_admin_unify_newlines($value);
    }
  });
  return serialize($style);
}

/**
 * Unifies newlines in the string to the Unix newline standard.
 *
 * #2636314: textareas may convert newlines to the underlying OS style: convert
 * all new lines to Unix style before unserializing. As string length is in the
 * serialized data, we must ensure that we also do this on each array value
 * before serializing.
 *
 * @param string $str
 *
 * @return string
 */
function image_styles_admin_unify_newlines($str) {
  $str = str_replace("\r\n", "\n", $str);
  $str = str_replace("\r", "\n", $str);
  return $str;
}

/**
 * Unserializes and validates a string into image style data.
 *
 * @param string $import
 *   The string representation of a @see serialize()'d image style array.
 *
 * @return array|false
 *   An image style array or false if the string could not be unserialized into
 *   image style data.
 */
function image_styles_admin_import_extract_style($import) {
  $style = unserialize($import);

  // Check if the contents of the textarea could be unserialized into an array.
  if (!is_array($style)) {
    return FALSE;
  }

  // Filter out keys that we do not process.
  $style = array_intersect_key($style, array('name' => 0, 'label' => 0, 'effects' => 0));

  // 'name' is required and must be "machine name" string.
  if (!isset($style['name']) || !is_string($style['name']) || preg_match('/[0-9a-z_\-]+/', $style['name']) !== 1) {
    return FALSE;
  }

  // Optional 'label' must be a string.
  if (isset($style['label']) && !is_string($style['label'])) {
    return FALSE;
  }

  // 'effects' is required and must be an array.
  if (!isset($style['effects']) || !is_array($style['effects'])) {
    return FALSE;
  }

  // Check effects elements
  foreach ($style['effects'] as &$effect) {
    // an effect must be an array.
    if (!is_array($effect)) {
      return FALSE;
    }
    // Check if the required keys are available, we will ignore the other.
    $effect = array_intersect_key($effect, array('weight' => 0, 'name' => 0, 'data' => 0));
    if (count($effect) !== 3) {
      return FALSE;
    }
    // effect weight must be an integer (data type in table is int, not float).
    if (!is_int($effect['weight']) && $effect['weight'] !== (string) (int) $effect['weight']) {
      return FALSE;
    }
    // effect name must be a string
    if (!is_string($effect['name'])) {
      return FALSE;
    }
    // Check whether the effect data is an array.
    if (!is_array($effect['data'])) {
      return FALSE;
    }
  }

  // @todo: are there any security implications for creating styles like this?
  // - Unserialize() is save in itself: it only creates data (except possibly
  //   for__wakeup(), but that can only be in already existing code: safe
  // - Not expected array entries are removed (array_intersect_key): safe
  // - Basic types are checked: safe
  // - Effect data array is not checked. Possibly unsafe?! The effect data array
  //   contains the effect parameters. Normally these are entered and validated
  //   via a form and subsequently saved in the database (serialized as here).
  //   The form validation is not executed on import and thus the data may
  //   contain invalid values. This is acceptable as it can also be done by
  //   operating directly on the database. In Drupal this is not normally
  //   checked for during processing: error messages will make clear that the
  //   data has been played with. Can incorrect data be abused? It may contain:
  //   - incorrect types: we do not know the data structure of the various
  //     effects, so we cannot check that and have to accept it as it comes.
  //     Effects should check_plain in summary theme and convert to int/float
  //     whenever possible before using it in commands.
  //   - PHP code, but that may be valid content for the text or custom effects:
  //     Effects should check_plain in summary theme and convert to int/float
  //     whenever possible before using it in commands.
  //     @todo: if the style contains an effect that contains PHP code, the user
  //     should need the 'use PHP for settings' permission.
  //   - HTML and or JS code: when used as parameter, this normally won't hurt.
  //     When showing on the screen (summary theme), proper escaping should
  //     suffice and is needed anyway: responsibility of effect.
  return $style;
}
