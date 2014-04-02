<?php

/**
 * @file
 * Administrative page callbacks for the Style Guide Swatch module.
 */

/**
 * Page callback: Displays color swatches.
 *
 * @param string|null $theme
 *   (optional) The theme to display palettes for. Defaults to NULL, which will
 *   fallback to the default theme.
 */
function styleguide_palette_page($theme = NULL) {
  $theme = $theme ?: variable_get('theme_default', 'bartik');
  return array(
    '#theme' => 'styleguide_palette',
    '#swatches' => styleguide_palette($theme),
  );
}

/**
 * Form constructor for the style guide swatch form.
 *
 * @param string|null $theme
 *   (optional) The theme to display palettes for. Defaults to NULL, which will
 *   fallback to the default theme.
 *
 * @see styleguide_palette_form_validate()
 * @see styleguide_palette_form_submit()
 */
function styleguide_palette_form($form, &$form_state, $theme = NULL) {
  $form['colorpicker'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'styleguide-palette-colorpicker',
      'class' => array(
        'element-hidden',
      ),
    ),
    '#attached' => array(
      'library' => array(
        array('system', 'farbtastic'),
      ),
      'js' => array(
        drupal_get_path('module', 'styleguide_palette') . '/js/styleguide_palette.js',
      ),
    ),
  );

  $theme = $theme ?: variable_get('theme_default', 'bartik');
  $swatches = array();
  $results = styleguide_palette_swatch_load_multiple($theme);
  foreach ($results as $swatch) {
    $name = check_plain($swatch->name);
    $swatches[$name]['theme'] = array(
      '#type' => 'value',
      '#value' => $theme,
    );
    $swatches[$name]['id'] = array(
      '#type' => 'value',
      '#value' => $swatch->id,
    );
    $swatches[$name]['description'] = array(
      '#type' => 'value',
      '#value' => $swatch->description,
    );
    $swatches[$name]['hex'] = array(
      '#type' => 'textfield',
      '#title' => $name,
      '#default_value' => check_plain($swatch->hex),
      '#description' => check_plain($swatch->description),
      '#element_validate' => array('styleguide_palette_swatch_validate_hex'),
      '#size' => 7,
      '#attributes' => array('class' => array('colorpicker-input')),
    );
    $swatches[$name]['delete'] = array(
      '#type' => 'link',
      '#title' => t('Delete'),
      '#href' => "admin/config/user-interface/styleguide-palette/delete/$swatch->id",
    );
  }
  if (!empty($swatches)) {
    $form['palette'] = array(
      '#type' => 'fieldset',
      '#title' => t('Color palette'),
      '#tree' => TRUE,
    );
    $form['palette'] += $swatches;
  }

  $form['add_swatch'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add a swatch'),
  );
  $form['add_swatch']['theme'] = array(
    '#type' => 'value',
    '#value' => $theme,
  );
  $form['add_swatch']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Swatch name'),
  );
  $form['add_swatch']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Swatch description'),
  );
  $form['add_swatch']['hex'] = array(
    '#type' => 'textfield',
    '#title' => t('Hex value'),
    '#element_validate' => array('styleguide_palette_swatch_validate_hex'),
    '#attributes' => array('class' => array('colorpicker-input')),
    '#size' => 7,
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save palette'),
  );

  return $form;
}

/**
 * Form element validation handler for hex elements.
 */
function styleguide_palette_swatch_validate_hex($element, &$form_state) {
  $value = strtolower($element['#value']);
  if ($value !== '' && !preg_match('/^#([a-f0-9]{3}){1,2}$/iD', $value)) {
    form_error($element, t('%name must be a valid hexadecimal CSS color value.', array('%name' => $element['#title'])));
  }
}

/**
 * Form validation handler for styleguide_palette_form().
 *
 * @see styleguide_palette_form_submit()
 */
function styleguide_palette_form_validate($form, &$form_state) {
  if (!empty($form_state['values']['name']) && empty($form_state['values']['hex'])) {
    form_error($form['add_swatch']['hex'], t('Missing swatch hex value.'));
  }
  if (empty($form_state['values']['name']) && !empty($form_state['values']['hex'])) {
    form_error($form['add_swatch']['name'], t('Missing swatch name.'));
  }
}

/**
 * Form submission handler for styleguide_palette_form().
 *
 * @see styleguide_palette_form_validate()
 */
function styleguide_palette_form_submit($form, &$form_state) {
  $form_state['values'] += array('palette' => array());
  foreach ($form_state['values']['palette'] as $name => $swatch) {
    $swatch['name'] = $name;
    drupal_write_record('styleguide_palette_swatch', $swatch, 'id');
  }

  $new_swatch = array_intersect_key(array_filter($form_state['values']), array_flip(array('name', 'description', 'hex', 'theme')));
  // The 'theme' key will always be present, so ensure that a new swatch was
  // actually added.
  $swatch_updated = array_intersect_key($new_swatch, array_flip(array('name', 'hex')));
  if (!empty($swatch_updated)) {
    drupal_write_record('styleguide_palette_swatch', $new_swatch);
    drupal_set_message(t('Style guide swatches added.'));
  }
  elseif (!empty($form_state['values']['palette'])) {
    drupal_set_message(t('Style guide palette updated.'));
  }
}

/**
 * Form constructor for the swatch deletion confirmation form.
 *
 * @param array $swatch
 *   The swatch to be deleted.
 *
 * @see styleguide_palette_swatch_delete_form_submit()
 */
function styleguide_palette_swatch_delete_form($form, &$form_state, array $swatch) {
  $form['swatch_id'] = array(
    '#type' => 'value',
    '#value' => $swatch['id'],
  );
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $swatch['name'])),
    'admin/config/user-interface/styleguide-palette/edit',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submission handler for styleguide_palette_swatch_delete_form().
 */
function styleguide_palette_swatch_delete_form_submit($form, &$form_state) {
  $swatch = styleguide_palette_swatch_load($form_state['values']['swatch_id']);
  styleguide_palette_swatch_delete($form_state['values']['swatch_id']);
  watchdog('styleguid_palette', 'Deleted %title.', array('%title' => $swatch['name']));
  drupal_set_message(t('%title has been deleted.', array('%title' => $swatch['name'])));
  $form_state['redirect'] = 'admin/config/user-interface/styleguide-palette/edit/' . $swatch['theme'];
}
