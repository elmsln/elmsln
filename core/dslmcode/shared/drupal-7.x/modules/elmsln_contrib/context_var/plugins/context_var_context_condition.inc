<?php

/**
 * @file
 * This class extends the context_condition
 */
class context_var_context_condition extends context_condition {
  /**
   * Omit condition values. We will provide a custom input form for our conditions.
   */
  function condition_values() {
    return array();
  }

  /**
   * Condition form.
   */
  function condition_form($context) {
    $form = parent::condition_form($context);
    unset($form['#options']);
    $form['#type'] = 'textarea';
    $form['#description'] = 'Map values as database variable|value. This will also accept variable|index:value in the case of arrays that are stored in the drupal variable table. %theme can be used to replace it with the current theme in use, accounting for og_theme';
    $form['#default_value'] = implode("\n", $this->fetch_from_context($context, 'values'));
    return $form;
  }

  /**
   * Condition form submit handler.
   */
  function condition_form_submit($values) {
    $parsed = array();
    $items = explode("\n", $values);
    // pull together the values that are of the form name|value and store them in an array
    if (!empty($items)) {
      foreach ($items as $v) {
        $v = trim($v);
        if (!empty($v)) {
          $parsed[$v] = $v;
        }
      }
    }
    return $parsed;
  }

  /**
   * Execute.
   */
  function execute() {
    foreach (context_enabled_contexts() as $context) {
      if ($vars = $this->fetch_from_context($context, 'values')) {
        // scan for the %theme value for replacement as a custom token
        if (module_exists('og_context')) {
          $group = og_context();
          // we are in the context of a group, grab theme from there
          if (isset($group->type)) {
            $theme = $group->og_theme;
          }
          else {
            $theme = variable_get('default_theme', 'garland');
          }
        }
        else {
          $theme = variable_get('default_theme', 'garland');
        }
        $vars = str_replace('%theme', $theme, $vars);
        // split all values that we recieve
        $all_conditions_met = TRUE;
        foreach ($vars as $var) {
          // split based on | safely
          $values = explode('|', filter_xss($var));
          // blow the array up based on | and convert it back into a key => value pair
          $sys_array = array(); // reset the sys_array so that variables don't carry over from other contexts
          for ($i = 0; $i < count($values) -1; ) {
            $sys_array[$values[$i]] = $values[$i + 1];
            $i = $i + 2;
          }
          // go through each value pair and compare to drupal's current values
          // because we use variable_get this will take into account strongarm / spaces
          foreach ($sys_array as $key => $value) {
            if (module_exists('variable')) {
              $sys_var = variable_get_value($key);
            }
            else {
              $sys_var = variable_get($key, array());
            }
            // check to see if this is an even deeper array
            if (strpos($value, ':') === FALSE) {
              // if the database value doesn't equal the context value, return FALSE
              if ($sys_var != $value) {
                $all_conditions_met = FALSE;
              }
            }
            else {
              // drupal values can store arrays, we need to check for an array value
              $tmp_val = explode(':', $value);
              // if the database value doesn't equal the context value, return FALSE
              if (!isset($sys_var[$tmp_val[0]]) || $sys_var[$tmp_val[0]] != $tmp_val[1]) {
                $all_conditions_met = FALSE;
              }
            }
          }
        }
        // if all the conditions are met, pass ahead that they are met
        if ($all_conditions_met) {
          $this->condition_met($context);
        }
      }
    }
  }
}
