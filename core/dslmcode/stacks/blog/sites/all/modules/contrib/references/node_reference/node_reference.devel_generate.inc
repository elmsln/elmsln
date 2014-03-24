<?php
// $Id: nodereference.devel_generate.inc,v 1.1 2010/01/28 21:06:42 weitzman Exp $

function node_reference_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_node_reference_devel_generate', $object, $field, $instance, $bundle);
  }
  else {
    return _node_reference_devel_generate($object, $field, $instance, $bundle);
  }
}

function _node_reference_devel_generate($object, $field, $instance, $bundle) {
  $object_field = array();
  $allowed_values = node_reference_potential_references($field);
  // unset($allowed_values[0]);
  if (!empty($allowed_values)) {
    // Just pick one of the specified allowed values.
    $object_field['nid'] = array_rand($allowed_values);
  }
  return $object_field;
}
