<?php

/**
 * @file
 * Contains implementation of features_override's hooks for other modules.
 */

/**
 * Implements hook_features_override_component_overrides_alter().
 */
function image_features_override_component_overrides_alter(&$default, &$normal, $context) {
  if ($context['component'] == 'image') {
    // Effects have their keys changed on override. This resets them to numeric.
    $normal['effects'] = array_values($normal['effects']);
    $default['effects'] = array_values($default['effects']);
  }
}

/**
 * Implements hook_features_override_export_render_addition() for image.
 */
function image_features_override_export_render_addition($alter, $element) {
  $code = array();
  if (isset($alter['keys']) && isset($alter['value'])) {
    $component_start = "\$data['$element']";
    $code_line = features_override_export_keys($alter['keys']);
    $value_export = features_override_var_export($alter['value'], '    ');
    $code[] = "";
    $code[] = "  if (" . $component_start . "['storage'] == IMAGE_STORAGE_DEFAULT) {";
    $code[] = "    " . $component_start . $code_line . ' = ' . $value_export . ';';
    $code[] = "  }";
  }
  return $code;
}

/**
 * Implements hook_features_override_export_render_addition() for image.
 */
function image_features_override_export_render_deletion($alter, $element) {
  $code = array();
  if (isset($alter['keys'])) {
    $component_start = "\$data['$element']";
    $code_line = features_override_export_keys($alter['keys']);
    $code[] = "";
    $code[] = "  if (" . $component_start . "['storage'] == IMAGE_STORAGE_DEFAULT) {";
    $code[] =  '    unset(' . $component_start . $code_line . ');';
    $code[] = "  }";
  }
  return $code;
}
