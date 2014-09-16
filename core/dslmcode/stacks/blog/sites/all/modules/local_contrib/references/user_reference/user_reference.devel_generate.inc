<?php

function user_reference_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_user_reference_devel_generate', $object, $field);
  }
  else {
    return _user_reference_devel_generate($object, $field);
  }
}

function _user_reference_devel_generate($object, $field) {
  $object_field = array();
  $allowed_values = user_reference_potential_references($field);
  if (isset($allowed_values[0])) {
    unset($allowed_values[0]);
  }
  if (!empty($allowed_values)) {
    // Just pick one of the specified allowed values.
    $object_field['uid'] = array_rand($allowed_values);
  }
  return $object_field;
}
