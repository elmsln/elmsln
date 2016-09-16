<?php
/**
 * @file
 * Provides the base Views content cache plugin.
 */


/**
 * Base class for the views content cache plugins.
 */
class views_content_cache_key {

  /**
   * Optionally provides a option form for the user to use this segment.
   *
   * Typical uses of this will include returning a checkboxes FormAPI element
   * that will allow the user to indicate which keys in the cache segement
   * they are interested in for the view that they are building.
   * Eg. Checkboxes for each node type or each organic group.
   *
   * @param $value
   *   The default value that has been previously set.
   * @param $handler
   *   The handler that this options for is for.
   * @return
   *   A FormAPI element that will appear as part of the views content cache
   *   options form when building a view.
   */
  function options_form($value, &$handler = NULL) {
    return array();
  }

  /**
   * Builds an array of keys for the cache segment.
   *
   * When an 'event' happens, e.g. a node is saved, views content cache will
   * consult this plugin for the keys it wishes to store in its cache segments.
   * Views content cache will then handle the storage.
   *
   * @param $object
   *   The object that is being changed.
   * @param $object_type
   *   The type of the object that is being changed.
   * @return
   *   Either a scalar value or an array of scalars. These should be the
   *   different keys that are effected by the event in this cache segment.
   */
  function content_key($object, $object_type) {
    return NULL;
  }


  /**
   * An array of keys to check in this cache segment when viewing the view.
   *
   * As a user views a view, we are asked for the keys that views content cache
   * should consider in our segment. Normally we'd just return the values as set
   * by the user from our options_form().
   *
   * @param $values
   *   An array of values that was stored from our form element in options_form().
   * @return
   *   An array of keys in our cache segment.
   */
  function view_key($values, &$handler) {
    $values = array_filter($values);

    // Find any values that are for arguments and replace with real values.
    if (count($this->view_key_from_arguments())) {
      $values = $this->view_key_replace_arguments($values, $handler);
    }

    return $values;
  }

  /**
   * Replaces values corresponding to argument values set dynamically.
   */
  function view_key_replace_arguments($values, &$handler) {
    foreach ($values as $value) {
      if (strpos($value, '__arg:') === 0) {
        // Get the argument and make sure its actually on the view still.
        $arg_id = drupal_substr($value, drupal_strlen('__arg:'));
        if (isset($handler->view->argument[$arg_id]) && $handler->view->argument[$arg_id]->argument_validated) {
          // Argument is there and ready to go!
          $argument = clone($handler->view->argument[$arg_id]);
          $arg_value = $argument->get_value();
          // Might need to split this up.
          if (!empty($argument->options['break_phrase'])) {
            views_break_phrase($argument->get_value(), $argument);
            foreach ($argument->value as $new_val) {
              $values[$new_val] = $new_val;
            }
          }
          else {
            $new_val = $argument->get_value();
            $values[$new_val] = $new_val;
          }
        }
        // Always remove the dummy argument value.
        unset($values[$value]);
      }
    }

    return $values;
  }

  /**
   * Returns an array of views arguments that can supply valid key values.
   *
   * Plugins can define types of arguments that can optionally be checked for
   * key values when looking up cache segments.
   *
   * @return
   *   An array of argument handler classes that this plugin supports.
   */
  function view_key_from_arguments() {
    return array();
  }

  /**
   * Handy helper method that scans the given view looking for arguments.
   */
  function additional_options_for_arguments(&$view) {
    $options = array();

    $arguments = $view->display_handler->get_handlers('argument');

    if (is_array($arguments)) {
      foreach ($arguments as $arg_id => $argument) {
        foreach ($this->view_key_from_arguments() as $class) {
          if (is_a($argument, $class)) {
            // This argument can provide us with keys.
            $options['__arg:' . $arg_id] = t('Value from argument: %title', array('%title' => $argument->ui_name()));
          }
        }
      }
    }

    return $options;
  }

  /**
   * The method by which this plugin's where clause will be combined with others.
   *
   * Can either be 'AND' or 'OR' at the moment.
   */
  function clause_mode() {
    return 'AND';
  }
}
