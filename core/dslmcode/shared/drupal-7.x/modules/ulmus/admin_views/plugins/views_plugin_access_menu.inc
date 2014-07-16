<?php

/**
 * @file
 * Contains views_plugin_access_menu.
 */

/**
 * Access plugin that provides router item-based access control.
 *
 * @ingroup views_access_plugins
 */
class views_plugin_access_menu extends views_plugin_access {
  /**
   * Checks access to the view in case the current path is not the router path defined for the view.
   *
   * When accessing/rendering a view on a different page than the original menu
   * router path, then the menu system will not have checked access to the view.
   * In that case, we need to check access to the router path manually.
   */
  function access($account) {
    // If we are on the original router path, the menu system has checked access already.
    $item = menu_get_item();
    if ($item['href'] == $_GET['q']) {
      return TRUE;
    }
    // Retrieve the original router path for this view, and check access to it.
    $path = $this->view->display_handler->get_option('path');
    $item = menu_get_item($path);

    return $item['access'];
  }
}
