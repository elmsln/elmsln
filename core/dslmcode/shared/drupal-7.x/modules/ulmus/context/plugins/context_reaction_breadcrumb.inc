<?php

/**
 * Set the breadcrumb using a context reaction.
 */
class context_reaction_breadcrumb extends context_reaction_menu {
  /**
   * Overrides set_active_trail_from_link to set the breadcrumb instead of the menu path.
   */
  function set_active_trail_from_link($item) {
    $result = db_select('menu_links')
      ->fields('menu_links', array('p1', 'p2', 'p3', 'p4', 'p5', 'p6', 'p7', 'p8'))
      ->condition('hidden', 0)
      ->condition('link_path', $item['link_path'])
      ->execute();
    while ($parents = $result->fetchAssoc()) {
      $set = FALSE;
      foreach (array_filter($parents) as $plid) {
        $parent = menu_link_load($plid);
        if ($parent && $parent['access'] && empty($parent['hidden']) && !empty($parent['title'])) {
          $set = TRUE;
          $breadcrumb[] = l($parent['title'], $parent['href']);
        }
      }
      // Only set the breadcrumb if one or more links were added to the
      // trail. If not, continue iterating through possible menu links.
      if ($set) {
        drupal_set_breadcrumb($breadcrumb);
        break;
      }
    }
  }
  /**
   * Return the title to be used for the current menu item.
   */
  function get_link_title($item) {
    return module_exists('i18n_menu') ? _i18n_menu_link_title($item) : $item['title'];
  }
}
