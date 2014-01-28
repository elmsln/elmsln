<?php
/**
 * @file
 * Admin settings form for vk_openapi module
 */

/**
 * Typo settings form.
 */
function textbook_admin_settings() {
  $styles = _textbook_load_styles();
  foreach ($styles as $key => $style) {
    $textbook_styles[$key] = $style['name'];
  }
  $form['textbook_active'] = array(
    '#type' => 'select',
    '#title' => t('Default textbook style'),
    '#description' => t('The default style to use when no other is provided.'),
    '#default_value' => variable_get('textbook_active', TEXTBOOK_DEFAULT_SET),
    '#options' => $textbook_styles,
  );

  $form['textbook_reset'] = array(
    '#type' => 'checkbox',
    '#title' => t('Load reset styles'),
    '#description' => t('Should textbook apply its reset style? Disable this if you want to strictly dictate spacing in your theme.'),
    '#default_value' => variable_get('textbook_reset', TEXTBOOK_RESET_DEFAULT),
  );

  return system_settings_form($form);
}
