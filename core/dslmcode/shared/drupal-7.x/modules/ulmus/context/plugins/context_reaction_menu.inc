<?php

/**
 * Expose menu items as context reactions.
 */
class context_reaction_menu extends context_reaction {
  /**
   * Provide a form element that allow the admin to chose a menu item.
   */
  function options_form($context) {
    $options = array("-- " . t('None') . " --");
    if (module_exists('menu')) {
      $menus = menu_parent_options(menu_get_menus(), array('mlid' => 0));
      $menu_names = array();
      foreach ($menus as $id => $title) {
        list($menu_name, $mlid) = explode(':', $id);
        // Store the title each menu for reference.
        if ($mlid == '0') {
          $menu_names[$menu_name] = $title;
        }
        else {
          $link = menu_link_load($mlid);
          $identifier = $link['link_path'];
          $root_menu = $menu_names[$menu_name];
          while (isset($options[$root_menu][$identifier])) {
            $identifier .= "'";
          }
          $options[$root_menu][$menu_name . ':' . $identifier] = $title;
        }
      }
    }
    return array(
      '#title' => $this->title,
      '#description' => $this->description,
      '#options' => $options,
      '#type' => 'select',
      '#multiple' => TRUE,
      '#default_value' => $this->fetch_from_context($context),
    );
  }

  /**
   * Override of options_form_submit().
   * Trim any identifier padding for non-unique path menu items.
   */
  function options_form_submit($values) {
    $trimmed = array();
    foreach ($values as $value) {
      $value = trim($value, "'");
      $trimmed[] = $value;
    }
    return $trimmed;
  }

  /**
   * Overrides parent function to include legacy handling for old format of just storing a single path.
   */
  function fetch_from_context($context) {
    $values = parent::fetch_from_context($context);
    // Legacy - convert single string value to an array with a preferred menu
    if (is_string($values)) {
      $menu = menu_link_get_preferred($values);
      if (!$menu) {
        return array();
      }
      return array($menu['menu_name'] . ':' . $menu['link_path']);
    }
    return $values;
  }

  /**
   * Provide active trail in all menus in which our path appears.
   */
  function execute(&$vars = NULL) {
    $menu_names = menu_get_active_menu_names();
    $active_paths = $this->get_active_paths();
    foreach ($menu_names as $menu_name) {
      if (isset($active_paths[$menu_name])) {
        foreach($active_paths[$menu_name] as $path) {
          if ($link = menu_link_get_preferred($path, $menu_name)) {
            $this->set_active_trail_from_link($link);
            return;
          }
        }
      }
    }

    // None of the links can be found in their preferred menus. Instead we just try to find any of the paths in any
    // menu. Note that the preferred menu names list is still used but not always honoured.
    // We hope to not have to fall into this section as we could end up doing rather a lot of lookups.
    foreach ($active_paths as $menu_name => $paths) {
      foreach($paths as $path) {
        if ($link = menu_link_get_preferred($path)) {
          $this->set_active_trail_from_link($link);
          return;
        }
      }
    }
  }

  /**
   * Helper function to build and set the active trail from a menu link.
   *
   * @param $item
   *   A menu link item.
   */
  function set_active_trail_from_link($item) {
    menu_tree_set_path($item['menu_name'], $item['link_path']);
    $trail = array();
    while($item) {
      array_unshift($trail, $item);
      $item = menu_link_load($item['plid']);
    }
    array_unshift($trail, array(
      'title' => t('Home'),
      'href' => '<front>',
      'link_path' => '',
      'localized_options' => array(),
      'type' => 0,
    ));
    menu_set_active_trail($trail);
  }

  /**
   * Helper function to return the list of currently active paths.
   *
   * The paths are grouped by menu name.
   */
  function get_active_paths() {
    $active_paths = array();
    foreach ($this->get_contexts() as $context) {
      $paths = $this->fetch_from_context($context);
      $active_paths = array_merge($active_paths, $paths);
    }

    $by_menu_name = array();
    foreach ($active_paths as $id) {
      list($menu_name, $path) = explode(':', $id);
      $by_menu_name[$menu_name][] = $path;
    }
    return $by_menu_name;
  }
}
