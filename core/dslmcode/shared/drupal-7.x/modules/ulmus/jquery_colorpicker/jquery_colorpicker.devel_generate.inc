<?php
/**
 * @file
 * Create random data to populate jquery colorpicker fields.
 */

/**
 * Implements hook_devel_generate().
 */
function jquery_colorpicker_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_jquery_colorpicker_devel_generate', $object, $field, $instance, $bundle);
  }
  else {
    return _jquery_colorpicker_devel_generate($object, $field, $instance, $bundle);
  }
}

function _jquery_colorpicker_devel_generate($object, $field, $instance, $bundle) {
  $object_field['jquery_colorpicker'] = dechex(rand(0, pow(255, 3) - 1));
  return $object_field;
}
