<?php

/**
 * @file
 * Definition of views_plugin_access.
 */

/**
 * @defgroup views_access_plugins Views access plugins
 * @{
 * @todo.
 *
 * @see hook_views_plugins()
 */

/**
 * The base plugin to handle access control.
 */
class views_plugin_access extends views_plugin {

  /**
   * Initialize the plugin.
   *
   * @param view $view
   *   The view object.
   * @param object $display
   *   The display handler.
   */
  public function init(&$view, &$display) {
    $this->view = &$view;
    $this->display = &$display;

    if (is_object($display->handler)) {
      $options = $display->handler->get_option('access');
      // Overlay incoming options on top of defaults.
      $this->unpack_options($this->options, $options);
    }
  }

  /**
   * Retrieve the options when this is a new access control plugin.
   */
  public function option_definition() {
    return array();
  }

  /**
   * Provide the default form for setting options.
   */
  public function options_form(&$form, &$form_state) {
  }

  /**
   * Provide the default form form for validating options.
   */
  public function options_validate(&$form, &$form_state) {
  }

  /**
   * Provide the default form form for submitting options.
   */
  public function options_submit(&$form, &$form_state) {
  }

  /**
   * Return a string to display as the clickable title for the access control.
   */
  public function summary_title() {
    return t('Unknown');
  }

  /**
   * Determine if the current user has access or not.
   */
  public function access($account) {
    // Default to no access control.
    return TRUE;
  }

  /**
   * Determine the access callback and arguments.
   *
   * This information will be embedded in the menu in order to reduce
   * performance hits during menu item access testing, which happens
   * a lot.
   *
   * @return array
   *   The first item should be the function to call, and the second item should
   *   be an array of arguments. The first item may also be TRUE (bool only)
   *   which will indicate no access control.
   */
  public function get_access_callback() {
    // Default to no access control.
    return TRUE;
  }

}

/**
 * @}
 */
