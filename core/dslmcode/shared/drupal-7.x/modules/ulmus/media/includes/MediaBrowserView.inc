<?php

/**
 * @file
 * Definition of MediaBrowserView.
 */

/**
 * Media browser plugin for displaying a specific view and display.
 */
class MediaBrowserView extends MediaBrowserPlugin {
  /**
   * The view object from views_get_view() for this plugin.
   *
   * @var view
   */
  protected $view;

  /**
   * Implements MediaBrowserPluginInterface::__construct().
   */
  public function __construct($info, $params) {
    parent::__construct($info, $params);

    // Set up the view object with the proper display.
    if ($view = views_get_view($info['view_name'])) {
      $display_id = !empty($info['view_display_id']) ? $info['view_display_id'] : NULL;
      if ($view->set_display($display_id)) {
        $this->view = $view;
      }
    }
  }

  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    return !empty($this->view) && $this->view->access($this->view->current_display, $account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    if (!empty($this->view)) {
      $build['#markup'] = $this->view->preview();

      // Allow the View title to override the plugin title.
      if ($title = $this->view->get_title()) {
        $build['#title'] = $title;
      }

      return $build;
    }
  }
}
