<?php

/**
 * @file
 * Handler for dynamic_select_plugin_display.
 */
class dynamic_select_plugin_display extends views_plugin_display {

  function option_definition() {
    $options = parent::option_definition();

    // Force the default style plugin to 'dynamic_select_style' and the default row plugin to
    // 'dynamic_select_fields'.
    $options['style_plugin']['default'] = 'dynamic_select_style';
    $options['defaults']['default']['style_plugin'] = FALSE;
    $options['defaults']['default']['style_options'] = FALSE;

    $options['row_plugin']['default'] = 'dynamic_select_fields';
    $options['defaults']['default']['row_plugin'] = FALSE;
    $options['defaults']['default']['row_options'] = FALSE;

    // Set the display title to an empty string (not used in this display type).
    $options['title']['default'] = '';
    $options['defaults']['default']['title'] = FALSE;

    return $options;
  }

  function get_style_type() {
    return 'dynamic_select_style'; // force the use of this style
  }

  function execute() {

    // The base class cannot be executed.
    return $this->view->render($this->display->id);
  }

  function render() {
    if (!empty($this->view->result) || !empty($this->view->style_plugin->definition['even empty'])) {
      return $this->view->style_plugin->render($this->view->result);
    }
    return '';
  }

  function uses_exposed() {
    return FALSE;
  }
}
