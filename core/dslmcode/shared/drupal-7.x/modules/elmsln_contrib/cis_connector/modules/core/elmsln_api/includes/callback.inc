<?php
/**
 * @file
 * callback.inc
 */

/**
 * Execute a callback.
 *
 * @param array $info
 *   The callback info array, passed by reference.
 *
 * @return mixed
 *   The results of the callback.
 */
function elmsln_api_callback_execute(array $info) {
  // Bootstrap the callback to minimal requirements.
  elmsln_api_callback_bootstrap($info);

  // Process request data and append/replace arguments if necessary.
  elmsln_api_callback_process_request($info);

  // By default, return ELMSLN_MENU_NOT_FOUND. This will be overridden below.
  $callback_result = ELMSLN_MENU_NOT_FOUND;

  // Check callback access.
  if (!empty($info['access callback']) && !call_user_func_array($info['access callback'], $info['access arguments'])) {
    $callback_result = ELMSLN_MENU_ACCESS_DENIED;
  }
  // Ensure callback function exists and can be invoked.
  elseif (!empty($info['callback function']) || function_exists($info['callback function'])) {
    $callback_result = call_user_func_array($info['callback function'], $info['callback arguments']);
  }

  // Enforce sensitization of the result if the "xss" variable is not
  // explicitly set to a boolean of FALSE.
  if ($info['xss'] !== FALSE) {
    $callback_result = elmsln_api_callback_filter_xss($callback_result);
  }

  return $callback_result;
}

/**
 * Bootstraps Drupal to the correct level based on callback info.
 *
 * @param array $info
 *   The callback info array, passed by reference.
 *
 * @throws Exception
 * @see _drupal_bootstrap_full()
 */
function elmsln_api_callback_bootstrap(array &$info) {
  global $_elmsln;

  // Replace integer based arguments with corresponding value from path.
  foreach (array('access', 'callback') as $type) {
    foreach ($info["$type arguments"] as $key => $value) {
      // Numeric argument exists, replace it.
      if (is_int($value) && !empty($_elmsln['args'][$value])) {
        $info["$type arguments"][$key] = check_plain($_elmsln['args'][$value]);
      }
      // Numeric argument does not exist, remove it.
      elseif (is_int($value)) {
        unset($info["$type arguments"][$key]);
      }
    }
  }
  // If the callback function is located in another file, load that file.
  $path = !empty($info['path']) ? $info['path'] : drupal_get_path('module', $info['module']);

  if (isset($info['file']) && ($filepath = $path . '/' . $info['file']) && file_exists($filepath)) {
    require_once $filepath;
  }

  // The following mimics the behavior of _drupal_bootstrap_full().
  // The difference is that not all modules and includes are loaded.
  if (drupal_bootstrap($info['bootstrap']) < DRUPAL_BOOTSTRAP_FULL) {
    // If "access callback" isn't passed, but "access arguments" is,
    // default to using "user_access" and bootstrap Drupal to at least
    // DRUPAL_BOOTSTRAP_SESSION and ensure the user module has loaded.
    if (empty($info['access callback']) && !empty($info['access arguments'])) {
      drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);
      if (!in_array('user', $info['dependencies'])) {
        $info['dependencies'][] = 'user';
      }
      $info['access callback'] = 'user_access';
    }

    // If language is enabled and site is multilingual, bootstrap at least to
    // DRUPAL_BOOTSTRAP_LANGUAGE and ensure the required modules are enabled.
    if (isset($info['lang'])) {
      $_elmsln['lang'] = $info['lang'];
    }
    if ($_elmsln['lang']) {
      if (!in_array('user', $info['dependencies'])) {
        $info['dependencies'][] = 'user';
      }
      if (!in_array('path', $info['includes'])) {
        $info['includes'][] = 'path';
      }
      // Boot at least DRUPAL_BOOTSTRAP_VARIABLES to ensure
      // drupal_multilingual() works.
      drupal_bootstrap(DRUPAL_BOOTSTRAP_VARIABLES);
      if (drupal_multilingual()) {
        drupal_bootstrap(DRUPAL_BOOTSTRAP_LANGUAGE);
      }
    }

    // Load required include files based on the callback.
    if (isset($info['includes']) && is_array($info['includes'])) {
      foreach ($info['includes'] as $include) {
        if (file_exists("./includes/$include.inc")) {
          require_once "./includes/$include.inc";
        }
      }
    }

    // Detect string handling method.
    unicode_check();

    // Undo magic quotes.
    fix_gpc_magic();

    // Create an associative array with weights as values.
    $modules = array($info['module'] => 0);
    foreach ($info['dependencies'] as $dependency) {
      $modules[$dependency] = 0;
    }

    // Reset module list and load them.
    $module_list = module_list(FALSE, TRUE, FALSE, $modules);
    foreach ($module_list as $module) {
      drupal_load('module', $module);
    }

    // Make sure all stream wrappers are registered.
    file_get_stream_wrappers();

    // Ensure the language variable is set, if not it might cause problems
    // (e.g. entity info).
    global $language;
    if (!isset($language)) {
      $language = language_default();

      $types = language_types();
      foreach ($types as $type) {
        $GLOBALS[$type] = $language;
      }
    }

    // Invoke implementations of hook_init() if the callback doesn't indicate it
    // should be skipped.
    if (empty($info['skip init'])) {
      // Do not use module_invoke_all() because it will load DB cached data for
      // modules that implement the hook.
      foreach ($module_list as $module) {
        module_invoke($module, 'init');
      }
    }
  }
}

/**
 * Process request data for callbacks.
 *
 * By default, all callbacks will have request data processed automatically.
 * A callback must explicitly set $info['process request'] to a boolean of
 * FALSE to disable this functionality.
 *
 * It will match against the callback's parameters and default value variable
 * types. These values are always appended to any integer path values already
 * assigned in the arguments array.
 *
 * This allows callbacks to specify explicit path arguments or simply allow
 * request values to match against the callback's parameter names.
 *
 *   $_REQUEST['my_variable'] = 'foo';
 *
 *   function my_callback($my_variable) {
 *     // Outputs: "foo".
 *     print $my_variable;
 *   }
 *
 *   function my_callback($arbitrary_parameter_name) {
 *     // Outputs: "Array".
 *     // The callback's parameter name does not match the key name in the
 *     // request data. See below why the output is an "Array".
 *     print $arbitrary_parameter_name;
 *   }
 *
 * Regardless if this advanced "mapping" functionality is used, you can always
 * access the entire request data. This data is always appended as the last
 * parameter passed to the callback. Parameters that have been previously
 * matched are excluded from this array. Example:
 *
 *   $_REQUEST['my_variable'] = 'foo';
 *   $_REQUEST['my_second_variable'] = 'bar';
 *
 *   function my_callback($my_variable, $data) {
 *     // Outputs: "foo".
 *     print $my_variable;
 *
 *     // Outputs: NULL.
 *     print $data['my_variable'];
 *
 *     // Outputs: "bar".
 *     print $data['my_second_variable'];
 *   }
 *
 * @param array $info
 *   The callback info array, passed by reference.
 */
function elmsln_api_callback_process_request(&$info) {
  if ($info['process request'] === FALSE) {
    return FALSE;
  }
  // Iterate over the raw $_REQUEST array.
  $request_data = array();
  $json_values = array('true', 'false', '1', '0', 'yes', 'no');
  foreach ($_REQUEST as $key => $value) {
    // Convert possible JSON strings into arrays.
    if (is_string($value) && $value !== '' && ($value[0] === '[' || $value[0] === '{') && ($json = drupal_json_decode($value))) {
      $request_data[$key] = $json;
    }
    // Convert certain JSON values into booleans.
    elseif (!is_int($value) && in_array($value, $json_values)) {
      $request_data[$key] = (bool) $value;
    }
    else {
      $request_data[$key] = $value;
    }
  }

  // Retrieve the default parameters of the callback function.
  foreach (array('access', 'callback') as $type) {
    $data = $request_data;
    // Match the callback function's parameter names against the names of keys
    // in the $_REQUEST array. Ensure the values have the correct type as well.
    $parameters = array();
    $function = $info[($type === 'callback' ? 'callback function' : "$type callback")];
    if (function_exists($function)) {
      $f = new ReflectionFunction($function);
      foreach ($f->getParameters() as $param) {
        $default = NULL;
        if ($param->isDefaultValueAvailable()) {
          $default = $param->getDefaultValue();
        }
        $parameters[$param->name] = $default;
      }
    }
    foreach ($parameters as $name => $default_value) {
      // Check to see if the parameter exists.
      if (isset($data[$name])) {
        // Convert the type of variable in the $_REQUEST array to match the
        // same variable type as the parameter's default value.
        if (!is_null($default_value)) {
          settype($data[$name], gettype($default_value));
        }
        // Move the value of the $_REQUEST data into the parameter array.
        $parameters[$name] = $data[$name];
        // Remove the request data since it has been moved.
        unset($data[$name]);
      }
    }

    // Sort the remaining $_REQUEST data based on key name.
    ksort($data);

    // Merge existing arguments, parameters and any remaining request data.
    $info["$type arguments"] = array_merge($info["$type arguments"], $parameters, array($data));
  }
}

/**
 * Filters callback results against XSS vulnerabilities.
 *
 * @param mixed $result
 *   The result to process.
 *
 * @return array
 *   The filtered result.
 */
function elmsln_api_callback_filter_xss($result) {
  static $allowed_tags;
  if (!isset($allowed_tags)) {
    $allowed_tags = array('a', 'abbr', 'acronym', 'address', 'article', 'aside', 'b', 'bdi', 'bdo', 'big', 'blockquote', 'br', 'caption', 'cite', 'code', 'col', 'colgroup', 'command', 'dd', 'del', 'details', 'dfn', 'div', 'dl', 'dt', 'em', 'figcaption', 'figure', 'footer', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'header', 'hgroup', 'hr', 'i', 'img', 'ins', 'kbd', 'li', 'mark', 'menu', 'meter', 'nav', 'ol', 'output', 'p', 'pre', 'progress', 'q', 'rp', 'rt', 'ruby', 's', 'samp', 'section', 'small', 'span', 'strong', 'sub', 'summary', 'sup', 'table', 'tbody', 'td', 'tfoot', 'th', 'thead', 'time', 'tr', 'tt', 'u', 'ul', 'var', 'wbr');
    drupal_alter('elmsln_api_callback_filter_xss', $allowed_tags);
  }
  if (is_string($result)) {
    $result = filter_xss($result, $allowed_tags);
  }
  elseif (is_array($result)) {
    foreach ($result as $key => $value) {
      // Iterate over multi-dimensional arrays.
      if (is_array($value)) {
        $result[$key] = elmsln_api_callback_filter_xss($value);
      }
      // Filter strings against XSS.
      elseif (is_string($value)) {
        $result[$key] = filter_xss($value, $allowed_tags);
      }
    }
  }
  return $result;
}
