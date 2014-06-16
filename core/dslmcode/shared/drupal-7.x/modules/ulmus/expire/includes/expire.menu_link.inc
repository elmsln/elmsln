<?php

/**
 * @file
 * Provides class that expires menulinks.
 */

class ExpireMenuLink implements ExpireInterface {

  /**
   * Executes expiration actions for menu link.
   *
   * @param $menu_link
   *   Array with settings of menu links like from menu_link_load().
   *
   * @param $action
   *   Action that has been executed.
   *
   * @param $skip_action_check
   *   Shows whether should we check executed action or just expire menu items.
   */
  function expire($menu_link, $action, $skip_action_check = FALSE) {

    // Stop further expiration if executed action is not selected by admin.
    if (!$skip_action_check && !in_array($action, array_filter(variable_get('expire_menu_link_actions', array())))) {
      return;
    }

    // Ensure that this menu is expirable.
    $settings = array_filter(variable_get('expire_menu_link_override_menus', array()));
    if (empty($menu_link['mlid']) || !array_key_exists($menu_link['menu_name'], $settings)) {
      return;
    }

    // Ensure that current menu item level is not higher than required.
    $depth = $settings[$menu_link['menu_name']];
    if (!empty($menu_link['depth']) && $menu_link['depth'] > $depth) {
      return;
    }

    // Collect menu items' urls.
    $expire_urls = array();
    if ($links =  _menu_build_tree($menu_link['menu_name'], array('max_depth' =>  $depth))) {
      $expire_urls = $this->get_urls_from_menu_tree($links['tree']);
    }

    // Flush page cache for expired urls.
    ExpireAPI::executeExpiration(array_unique($expire_urls), 'menu_link', $menu_link);
  }

  /**
   * Fetches an internal urls from a menu items tree.
   */
  private function get_urls_from_menu_tree($tree) {
    $links = array();
    foreach ($tree as $item) {
      if (empty($item['link']['external']) || $item['link']['link_path'] == '<front>') {
        $links[] = $item['link']['link_path'];
      }
      if (!empty($item['below'])) {
        $links = array_merge($links, $this->get_urls_from_menu_tree($item['below']));
      }
    }
    return $links;
  }

}
