<?php

/**
 * @file
 * Definition of views_plugin_display_extender.
 */

/**
 * @todo.
 *
 * @ingroup views_display_plugins
 */
class views_plugin_display_extender extends views_plugin {

  /**
   * {@inheritdoc}
   */
  public function init(&$view, &$display) {
    $this->view = $view;
    $this->display = $display;
  }

  /**
   * Provide a form to edit options for this plugin.
   */
  public function options_definition_alter(&$options) {
  }

  /**
   * Provide a form to edit options for this plugin.
   */
  public function options_form(&$form, &$form_state) {
  }

  /**
   * Validate the options form.
   */
  public function options_validate(&$form, &$form_state) {
  }

  /**
   * Handle any special handling on the validate form.
   */
  public function options_submit(&$form, &$form_state) {
  }

  /**
   * Set up any variables on the view prior to execution.
   */
  public function pre_execute() {
  }

  /**
   * Inject anything into the query that the display_extender handler needs.
   */
  public function query() {
  }

  /**
   * Provide the default summary for options in the views UI.
   *
   * This output is returned as an array.
   */
  public function options_summary(&$categories, &$options) {
  }

  /**
   * Static member function to list which sections are defaultable
   * and what items each section contains.
   */
  public function defaultable_sections(&$sections, $section = NULL) {
  }

}
