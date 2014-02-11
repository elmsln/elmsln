<?php

/**
 * @file
 * The media browser style plugin.
 */

/**
 * Media Views style plugin.
 *
 * Style plugin to render media items as an interactive grid for the media
 * browser.
 *
 * @ingroup views_style_plugins
 */
class media_views_plugin_style_media_browser extends views_plugin_style_list {

  // Stores the files loaded with pre_render.
  public $files = array();

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['type'] = array('default' => 'ul');
    $options['class'] = array('default' => 'media-list-thumbnails');
    $options['wrapper_class'] = array('default' => '');

    return $options;
  }

  /**
   * Prevents a problem with views when get_row_class() is not set.
   */
  public function get_row_class($row_index) {
  }

  /**
   * Add the base field (fid) to the query.
   */
  public function query() {
    if (method_exists($this->view->query, 'add_field')) {
      // Normal file_managed based view.
      $this->view->query->add_field($this->view->base_table, $this->view->base_field);
    }
    if (method_exists($this->view->query, 'addField')) {
      // Search API based view.
      $this->view->query->addField('fid');
    }
    parent::query();
  }

}
