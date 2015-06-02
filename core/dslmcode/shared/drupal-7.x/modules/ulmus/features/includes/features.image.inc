<?php

/**
 * Implements hook_features_api().
 */
function image_features_api() {
  return array(
    'image' => array(
      'name' => t('Image styles'),
      'feature_source' => TRUE,
      'default_hook' => 'image_default_styles',
      'alter_hook' => 'image_styles',
    )
  );
}

/**
 * Implements hook_features_export_options().
 */
function image_features_export_options() {
  $options = array();
  foreach (image_styles() as $name => $style) {
    $options[$name] = $style['name'];
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function image_features_export($data, &$export, $module_name = '') {
  $pipe = array();
  $map = features_get_default_map('image');
  foreach ($data as $style) {
    $export['dependencies']['image'] = 'image';
    // If another module provides this style, add it as a dependency
    if (isset($map[$style]) && $map[$style] != $module_name) {
      $module = $map[$style];
      $export['dependencies'][$module] = $module;
    }
    // Otherwise, export the style
    elseif (image_style_load($style)) {
      $export['features']['image'][$style] = $style;
    }
  }
  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function image_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  $code[] = '  $styles = array();';
  $code[] = '';
  foreach ($data as $name) {
    if ($style = image_style_load($name)) {
      _image_features_style_sanitize($style);
      $style_export = features_var_export($style, '  ');
      $style_identifier = features_var_export($name);
      $code[] = "  // Exported image style: {$name}.";
      $code[] = "  \$styles[{$style_identifier}] = {$style_export};";
      $code[] = "";
    }
  }
  $code[] = '  return $styles;';
  $code = implode("\n", $code);
  return array('image_default_styles' => $code);
}

/**
 * Implements hook_features_revert().
 */
function image_features_revert($module) {
  if ($default_styles = features_get_default('image', $module)) {
    foreach (array_keys($default_styles) as $default_style) {
      if ($style = image_style_load($default_style)) {
        if ($style['storage'] != IMAGE_STORAGE_DEFAULT) {
          image_default_style_revert($style);
        }
      }
    }
  }
}

/**
 * Remove unnecessary keys for export.
 */
function _image_features_style_sanitize(array &$style) {
  // Sanitize style: Don't export numeric IDs and things which get overwritten
  // in image_styles() or are code/storage specific. The name property will be
  // the key of the exported $style array.
  $style = array_diff_key($style, array_flip(array(
    'isid',
    'name',
    'module',
    'storage',
  )));

  // Sanitize effects: all that needs to be kept is name, weight and data,
  // which holds all the style-specific configuration. Other keys are assumed
  // to belong to the definition of the effect itself, so not configuration.
  foreach ($style['effects'] as $id => $effect) {
    $style['effects'][$id] = array_intersect_key($effect, array_flip(array(
      'name',
      'data',
      'weight',
    )));
  }
}
