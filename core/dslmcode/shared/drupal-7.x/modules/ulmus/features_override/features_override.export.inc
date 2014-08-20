<?php

/**
 * @file
 * Helper function to export features overrides.
 */

/**
 * Parses the identifier into indivudal parts.
 *
 * As the keys may have a period in them, cannot use explode or similair ways.
 *
 * @param $identifier
 *   A string in the form  <comonent>.<element>.<keys> or <component>.<element>.
 * @return
 *   An array of component, element, and keys string
 * @see features_override_make_key()
 */
function features_override_parse_identifier($identifier) {
  $first_period = strpos($identifier, '.');
  $component = substr($identifier, 0, $first_period);
  if ($second_period = strpos($identifier, '.', $first_period + 1)) {
    $element = substr($identifier, $first_period + 1, $second_period - $first_period - 1);
    $keys = substr($identifier, $second_period + 1);
  }
  else {
    $element = substr($identifier, $first_period + 1);
    $keys = FALSE;
  }
  return array($component, $element, $keys);
}

/**
 * Makes a distinct string key from an array of keys.
 *
 * @param $keys
 *   An array of keys.
 * @return
 *   A string representation of the keys.
 */
function features_override_make_key($keys) {
  if (is_array($keys)) {
    $return_keys = array();
    foreach ($keys as $key) {
      $return_keys[] = $key['key'];
    }
  return implode('|', $return_keys);
  }
  else {
    return $keys;
  }
}

/**
 * Returns an array of keys to be ignored for various exportables
 * @param $component
 *   The component to retrieve ignore_keys from.
 */
function features_get_ignore_keys($component) {
  static $cache;
  if (!isset($cache[$component])) {
    $cache[$component] = module_invoke_all('features_override_ignore', $component);
  }
  return $cache[$component];
}

/**
 * Calculates what overrides exist for by component/element.
 *
 * @param $component_key
 *   A component key that's defined via hook_features_api.
 * @param $element_key
 *   A key identifieing an element that's been overriden.
 * @param $reset
 *   Reset the internal cache of overrides gathered.
 * @param $all
 *   If TRUE, return all overrides, otherwise only overrides not yet in an override feature
 *  */
function features_override_get_overrides($component_key = FALSE, $element_key = FALSE, $reset = FALSE, $all = TRUE) {
  static $cache;
  if (!isset($cache) || $reset) {
    $cache = array();
    module_load_include('inc', 'features', 'features.export');
    features_include();
    foreach (features_get_components() as $component => $info) {
      if (empty($info['default_hook']) || $component == 'features_override_items' || $component == 'features_overrides'
        || !features_get_default_alter_hook($component) || !features_hook($component, 'features_export_render')) {
        continue;
      }

      features_include_defaults($component);
      foreach (module_implements($info['default_hook']) as $module) {
        if ($differences = array_filter(features_override_module_component_overrides($module, $component, $reset, $all))) {
          $cache[$component] = isset($cache[$component]) ? array_merge($differences, $cache[$component]) : $differences;
        }
      }
      $cache[$component] = isset($cache[$component]) ? array_filter($cache[$component]) : array();
    }
  }

  if ($component_key && $element_key) {
    return !empty($cache[$component_key][$element_key]) ? $cache[$component_key][$element_key] : array();
  }
  elseif ($component_key) {
    return !empty($cache[$component_key]) ? $cache[$component_key] : array();
  }
  return $cache;
}

/**
 * Helper function in determining equality of arrays. Credit to http://stackoverflow.com/a/4263181
 *
 * @see _features_override_remove_recursion()
 *
 * @param $a
 *  object a
 * @param $b
 *  object b
 * @return bool
 *  
 */
function _features_override_is_ref_to(&$a, &$b, $uniqid) {
  if (is_object($a) && is_object($b)) {
    return ($a === $b);
  }

  $temp_a = $a;
  $temp_b = $b;

  $b = $uniqid;

  if ($a === $uniqid) $return = true;
  else $return = false;

  $a = $temp_a;
  $b = $temp_b;
  return $return;
}

/**
 * Get overrides for specific module/component.
 *
 * @param $module
 *   An enabled module to find overrides for it's components.
 * @param $component
 *   A type of component to find overrides for.
 * @param $reset
 *   Reset the internal cache of overrides gathered.
 * @param $all
 *   If TRUE, return all overrides, otherwise only overrides not yet in an override feature
 * @return
 *   An array of overrides found.
 */
function features_override_module_component_overrides($module, $component, $reset = FALSE, $all = TRUE) {
  static $cache = array();

  if (isset($cache[$module][$component])  && !$reset) {
    return $cache[$module][$component];
  }
  module_load_include('inc', 'features_override', 'features_override.hooks');
  features_include();
  features_include_defaults($component);

  // Allows overriding non-feature controlled code.
  $default_hook = features_get_default_hooks($component);
  if ($all) {
    // call hooks directly
    // could also do
    // $default = features_get_default($component, $module, FALSE, $reset);
    // but this is more efficient
    $default = module_invoke($module, $default_hook);
  }
  else {
    $default = features_get_default($component, $module, TRUE, $reset);
  }
  $normal = features_get_normal($component, $module, $reset);

  // This indicates it is likely not controlled by features, so fetch manually.
  if (!$normal && is_array($default)) {
    $export = features_invoke($component, 'features_export_render', $module, array_keys($default), NULL);
    $code = array_pop($export);
    if (!$code) {
      return array();
    }
    else {
      $normal = eval($code);
    }
  }

  $context = array(
    'component' => $component,
    'module' => $module,
  );

  // Can't use _features_sanitize as that resets some keys.
  _features_override_sanitize($normal);
  _features_override_sanitize($default);
  // make a deep copy of data to prevent problems when removing recursion later
  $default_copy = unserialize(serialize($default));
  $normal_copy = unserialize(serialize($normal));

  $ignore_keys = features_get_ignore_keys($component);
  // remove keys to be ignored
  // doing this now allows us to better control which recursive parts are removed
  if (count($ignore_keys)) {
    _features_override_remove_ignores($default_copy, $ignore_keys);
    _features_override_remove_ignores($normal_copy, $ignore_keys);
  }
  // now remove any remaining recursion
  features_override_remove_recursion($default_copy);
  features_override_remove_recursion($normal_copy);

  $component_overrides = array();
  if ($normal && is_array($normal) || is_object($normal)) {
    foreach ($normal as $name => $properties) {
      $component_overrides[$name] = array(
        'additions' => array(),
        'deletions' => array(),
      );
      if (isset($default_copy[$name])) {
        drupal_alter('features_override_component_overrides', $default_copy[$name], $normal_copy[$name], $context);
        _features_override_set_additions($default_copy[$name], $normal_copy[$name], $component_overrides[$name]['additions'], $ignore_keys);
        _features_override_set_deletions($default_copy[$name], $normal_copy[$name], $component_overrides[$name]['deletions'], $ignore_keys);
      }
      if (!array_filter($component_overrides[$name])) {
        $component_overrides[$name] = FALSE;
      }
    }
    // now check for any elements that are in $default but not in $normal that we didn't process yet
    foreach ($default as $name => $properties) {
      if (!isset($normal_copy[$name])) {
        $_keys = array(array('type' => 'array', 'key' => $name));
        $component_overrides[$name]['deletions'][features_override_make_key($name)] = array(
          'keys' => $name,
        );
      }
    }
  }
  $cache[$module][$component] = $component_overrides;
  return $component_overrides;
}

/**
 * Sorts an array by its keys (assoc) or values (non-assoc).
 *
 * @param $array
 *   An array that needs to be sorted.
 */
function _features_override_sanitize(&$array) {
  if (is_array($array)) {
    $is_assoc = (array_keys($array) !== range(0, count($array) - 1));
    if ($is_assoc) {
      ksort($array);
    }
    else {
      sort($array);
    }
    foreach ($array as $k => $v) {
      if (is_array($v)) {
        _features_override_sanitize($array[$k]);
      }
    }
  }
}

/**
 * Helper function to set the additions between default and normal features.
 *
 * @param $default
 *   The default defination of a component.
 * @param $normal
 *   The current defination of a component.
 * @param $additions
 *   An array of currently gathered additions.
 * @param $ignore_keys
 *   Keys to ignore while processing element.
 * @param $level
 *   How many levels deep into object.
 * @param $keys
 *   The keys for this level.
 */
function _features_override_set_additions(&$default, &$normal, &$additions, $ignore_keys = array(), $level = 0, $keys = array()) {
  if (is_object($normal) || is_array($normal)) {
    foreach ($normal as $key => $value) {
      if (isset($ignore_keys[$key]) && ($level == $ignore_keys[$key])) {
        continue;
      }
      if (is_object($normal)) {
        if (!is_object($default) || !property_exists($default, $key) ||
           (is_scalar($value) && (features_var_export($default->$key) !== features_var_export($value)))) {
          $_keys = array_merge($keys, array(array('type' => 'object', 'key' => $key)));
          $additions[features_override_make_key($_keys)] = array(
            'keys' => $_keys,
            'value' => $value,
            'original' => (is_scalar($value) && isset($default->$key)) ? $default->$key : '',
          );
        }
        elseif (property_exists($default, $key) && ($default->$key !== $value)) {
          _features_override_set_additions($default->$key, $value, $additions, $ignore_keys, $level+1, array_merge($keys, array(array('type' => 'object', 'key' => $key))));
        }
      }
      elseif (is_array($normal)) {
        if (!is_array($default) || !array_key_exists($key, $default) ||
           (is_scalar($value) && (features_var_export($default[$key]) !== features_var_export($value)))) {
          $_keys = array_merge($keys, array(array('type' => 'array', 'key' => $key)));
          $additions[features_override_make_key($_keys)] = array(
            'keys' => $_keys,
            'value' => $value,
            'original' => (is_scalar($value) && isset($default[$key])) ? $default[$key] : '',
          );
        }
        elseif (array_key_exists($key, $default) && (!is_null($value) && ($default[$key] !== $value))) {
          _features_override_set_additions($default[$key], $value, $additions, $ignore_keys, $level+1, array_merge($keys, array(array('type' => 'array', 'key' => $key))));
        }
      }
    }
  }
}

/**
 * Helper function to set the deletions between default and normal features.
 *
 * @param $default
 *   The default defination of a component.
 * @param $normal
 *   The current defination of a component.
 * @param $deletions
 *   An array of currently gathered deletions.
 * @param $ignore_keys
 *   Keys to ignore while processing element.
 * @param $level
 *   How many levels deep into object.
 * @param $keys
 *   The keys for this level.
 */
function _features_override_set_deletions(&$default, &$normal, &$deletions, $ignore_keys = array(), $level = 0, $keys = array()) {
  if (is_object($default) || is_array($default)) {
    foreach ($default as $key => $value) {
      if (isset($ignore_keys[$key]) && ($level == $ignore_keys[$key])) {
        continue;
      }

      if (is_object($default) && is_object($normal)) {
        if (!property_exists($normal, $key)) {
          $_keys = array_merge($keys, array(array('type' => 'object', 'key' => $key)));
          $deletions[features_override_make_key($_keys)] = array(
            'keys' => $_keys,
          );
        }
        elseif (property_exists($normal, $key) && (is_array($value) || is_object($value))) {
          _features_override_set_deletions($value, $normal->$key, $deletions, $ignore_keys, $level+1, array_merge($keys, array(array('type' => 'object', 'key' => $key))));
        }
      }
      elseif (is_array($default) && is_array($normal)) {
        if (!array_key_exists($key, $normal)) {
          $_keys = array_merge($keys, array(array('type' => 'array', 'key' => $key)));
          $deletions[features_override_make_key($_keys)] = array(
            'keys' => $_keys,
          );
        }
        elseif (array_key_exists($key, $normal) && (is_array($value) || is_object($value))) {
          _features_override_set_deletions($value, $normal[$key], $deletions, $ignore_keys, $level+1, array_merge($keys, array(array('type' => 'array', 'key' => $key))));
        }
      }
    }
  }
}

/**
 * Creates a string representation of an array of keys.
 *
 * @param $keys
 *   An array of keys with their associate types.
 *
 * @return
 *   A string representation of the keys.
 */
function features_override_export_keys($keys) {
  $line = '';
  if (is_array($keys)) {
    foreach ($keys as $key) {
      $key_value = $key['key'];
      if (is_numeric($key_value)) {
        $line .= '[' . $key_value . ']';
      }
      elseif ($key['type'] == 'object') {
        $line .= '->' . $key_value;
      }
      else {
        $line .= "['{$key['key']}']";
      }
    }
  }
  return $line;
}

/**
 * Removes recursion from an object or array.
 *
 * @param $item
 *   An object or array passed by reference.
 */
function features_override_remove_recursion(&$item) {
  $uniqid = __FUNCTION__ . mt_rand(); // use of uniqid() here impacts performance
  $stack = array();
  _features_override_remove_recursion($item, $stack, $uniqid);
}

/**
 * Helper to removes recursion from an object/array.
 *
 * @param $item
 *   An object or array passed by reference.
 */
function _features_override_remove_recursion(&$object, &$stack = array(), $uniqid) {
  if ((is_object($object) || is_array($object)) && $object) {
    $in_stack = FALSE;
    foreach($stack as &$item) {
      if(_features_override_is_ref_to($object, $item, $uniqid)) {
        $in_stack = TRUE;
        break;
      }
    }
    if(!$in_stack) {
      $stack[] = $object;
      foreach ($object as $key => &$subobject) {
        if (_features_override_remove_recursion($subobject, $stack, $uniqid)) {
          if (is_object($object)) {
            unset($object->$key);
          }
          else {
            unset($object[$key]);
          }
        }
      }
    } else {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Helper to removes a set of keys an object/array.
 *
 * @param $item
 *   An object or array passed by reference.
 * @param $ignore_keys
 *   Array of keys to be ignored. Values are the level of the key.
 * @param $level
 *   Level of key to remove.  Up to 2 levels deep because $item can still be
 *   recursive
 */
function _features_override_remove_ignores(&$item, $ignore_keys, $level = -1) {
  $is_object = is_object($item);
  if (!is_array($item) && !is_object($item)) {
    return;
  }
  foreach ($item as $key => $value) {
    if (isset($ignore_keys[$key]) && ($ignore_keys[$key] == $level)) {
      if ($is_object) {
        unset($item->$key);
      }
      else {
        unset($item[$key]);
      }
    }
    elseif (($level < 2) && (is_array($value) || is_object($value))) {
      _features_override_remove_ignores($value, $ignore_keys, $level+1);
    }
  }
}

/**
 * Drupal-friendly var_export().
 *
 * @param $var
 *   The variable to export.
 * @param $prefix
 *   A prefix that will be added at the beginning of every lines of the output.
 * @return
 *   The variable exported in a way compatible to Drupal's coding standards.
 */
function features_override_var_export($var, $prefix = '') {
  if (is_array($var) || is_object($var)) {
    // Special causing array so calls features_override_var_export instead of
    // features_var_export.
    if (is_array($var)) {
      if (empty($var)) {
        $output = 'array()';
      }
      else {
        $output = "array(\n";
        foreach ($var as $key => $value) {
          // Using normal var_export on the key to ensure correct quoting.
          $output .= "  " . var_export($key, TRUE) . " => " . features_override_var_export($value, '  ', FALSE) . ",\n";
        }
        $output .= ')';
      }
    }
    // Objects do not export cleanily.
    else {
      if (method_exists($var, 'export')) {
        $output = $var->export();
      }
      elseif (get_class($var) === 'stdClass') {
        $output = '(object) ' . features_override_var_export((array) $var, $prefix);
      }
      elseif (!method_exists($var, '__set_state')) {
        // Ugly, but custom object with no clue how to export.without
        // __set_state class and var_export produces unusable code.
        $output = 'unserialize(' . var_export(serialize($var), TRUE) . ')';
      }
      else {
        $output = var_export($var, TRUE);
      }
    }
  }
  else {
    module_load_include('inc', 'features', 'features.export');
    $output = features_var_export($var);
  }

  if ($prefix) {
    $output = str_replace("\n", "\n$prefix", $output);
  }

  return $output;
}

/**
 * Renders the addition/change to an element.
 */
function features_override_features_export_render_addition($alter, $element, $component, $is_change = TRUE) {
  module_load_include('inc', 'features_override', 'features_override.hooks');
  if (features_hook($component, 'features_override_export_render_addition')) {
    return features_invoke($component, 'features_override_export_render_addition', $alter, $element);
  }
  else {
    $code = array();
    $component_start = "\$data['$element']";
    $code_line = features_override_export_keys($alter['keys']);
    $value_export = features_override_var_export($alter['value'], '    ');
    $original_export = '';
    if ($is_change && isset($alter['original'])) {
      $original_export = features_override_var_export($alter['original'], '    ');
      $original_export = str_replace('/*', '\/*', $original_export);
      $original_export = str_replace('*/', '*\/', $original_export);
      $original_export = ' /* WAS: ' . $original_export . ' */';
    }
    $code[] = "    " . $component_start . $code_line . ' = ' . $value_export . ';' . $original_export;
    return $code;
  }
}

/**
 * Renders the deletion to an element.
 */
function features_override_features_export_render_deletion($alter, $element, $component) {
  module_load_include('inc', 'features_override', 'features_override.hooks');
  if (features_hook($component, 'features_override_export_render_deletion')) {
    return features_invoke($component, 'features_override_export_render_deletion', $alter, $element);
  }
  else {
    $code = array();
    $component_start = "\$data['$element']";
    $code_line = features_override_export_keys($alter['keys']);
    $code[] =  '    unset(' . $component_start . $code_line . ');';
    return $code;
  }
}

/**
 * Encodes a string for use as option.

 * @see features_dom_encode_options()
 * @param $string
 *   A string to encode.
 * @return
 *   An encoded string for use as option value.
 */
function features_override_encode_string($string) {
  $replacements = array(
    ':' => '__'. ord(':') .'__',
    '/' => '__'. ord('/') .'__',
    ',' => '__'. ord(',') .'__',
    '.' => '__'. ord('.') .'__',
    '<' => '__'. ord('<') .'__',
    '>' => '__'. ord('>') .'__',
  );
  return strtr($string, $replacements);
}
