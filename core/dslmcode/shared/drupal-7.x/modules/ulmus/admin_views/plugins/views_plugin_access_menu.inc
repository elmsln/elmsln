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
    // Retrieve the original router path for this view, and check access to it.
    // Get this based on the display property of this access plugin, not the
    // view itself. The 'current display' could be set to something else, like
    // default.
    $path = $this->display->handler->get_option('path');
    $item = menu_get_item($path);

    // If we are on the original router path, the menu system has checked access already.
    if ($item['href'] == $_GET['q']) {
      return TRUE;
    }

    return $item['access'];
  }
}
