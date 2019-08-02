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
  	'#default_value' => image_styles_admin_style_to_string($style),
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
 * Converts image style data into a json string so it can be exported.
 *
 * @param array $style
 *   An image style array.
 *
 * @return string
 *   The image style converted to a string. Keys that are not needed for import
 *   are not serialized.
 */
function image_styles_admin_style_to_string($style) {
  $style = array_intersect_key($style, array('name' => 0, 'label' => 0, 'effects' => 0));
  foreach ($style['effects'] as &$effect) {
    $effect = array_intersect_key($effect, array('weight' => 0, 'name' => 0, 'data' => 0));
  }

  array_walk_recursive($style, function(&$value) {
    if (is_string($value)) {
      $value = image_styles_admin_unify_newlines($value);
    }
  });
  return json_encode($style);
}

/**
 * Unifies newlines in the string to the Unix newline standard.
 *
 * #2636314: textareas may convert newlines to the underlying OS style: convert
 * all new lines to Unix style before stringifying an image style.
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
 * Decodes and validates a json string into image style data.
 *
 * Some notes on any security implications for creating styles like this:
 * - json_decode() is considered safe regardless of the contents give to it.
 * - Not expected array entries are subsequently removed (array_intersect_key)
 *   thus the return will not contain unexpected array entries
 * - Values with known types are checked.
 * - Effect data array is not checked as it cannot be checked. Possibly unsafe
 *   but:
 *   - Proper checking and/or converting to int/float/bool while processing an
 *     image derivative is the responsibility of the image effect.
 *   - Effect data is only shown to a user on the edit form and in the image
 *     effect summary theme. Proper escaping and/or converting to int/float/bool
 *     in the theme before rendering it is again the responsibility of the image
 *     effect. On the form it is the form api that will do so.
 * - Effect data may contain PHP code and if the image effect is allowing this
 *   it may get [php_]eval()'ed. The image effects themselves should check for
 *   the 'use PHP for settings' permission on the create/edit form and check
 *   that the PHP module is enabled on execution (that is: during image
 *   derivative creation).
 *   However, we cannot do so on importing as we cannot know if the imported
 *   image style contains image effects that allow PHP code. Therefore, we use a
 *   separate access right for importing styles that is to be considered having
 *   the same security implications as the 'use PHP for settings' right (from
 *   the PHP module) and thus should only be given to highly trusted users.
 *
 * @param string $import
 *   The json representation of an image style array.
 *
 * @return array|false
 *   An image style array or false if the string could not be decoded into
 *   image style data.
 */
function image_styles_admin_import_extract_style($import) {
  $style = json_decode($import, TRUE);

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

  return $style;
}
