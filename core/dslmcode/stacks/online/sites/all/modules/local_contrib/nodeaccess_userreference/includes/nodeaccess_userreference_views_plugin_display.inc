<?php
// $Id$

/**
 * @file
 * Handler for nodeaccess_userreference_views_plugin_display.
 */
class nodeaccess_userreference_views_plugin_display extends views_plugin_display {
  function execute() {
    return $this->view->render($this->display->id);
  }

  function render() {
    return !empty($this->view->result) || !empty($this->view->style_plugin->definition['even empty']) ? $this->view->style_plugin->render($this->view->result) : '';
  }

  function uses_exposed() {
    return FALSE;
  }

  function query() {
    $options = $this->get_option('nodeaccess_userreference_options');

    // Restrict by supplied entity id.
    $alias = $this->view->query->ensure_table($options['table']);
    $this->view->query->add_where(NULL, "$alias.$options[field_id]", $options['ids'], 'IN');

  }
}