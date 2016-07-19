<?php

/**
 * Implements hook_features_api().
 */
function menu_features_api() {
  return array(
    'menu_custom' => array(
      'name' => t('Menus'),
      'default_hook' => 'menu_default_menu_custom',
      'feature_source' => TRUE,
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
    ),
    'menu_links' => array(
      'name' => t('Menu links'),
      'default_hook' => 'menu_default_menu_links',
      'feature_source' => TRUE,
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
    ),
    // DEPRECATED
    'menu' => array(
      'name' => t('Menu items'),
      'default_hook' => 'menu_default_items',
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
      'feature_source' => FALSE,
    ),
  );
}

/**
 * Implements hook_features_export().
 * DEPRECATED: This implementation simply migrates deprecated `menu` items
 * to the `menu_links` type.
 */
function menu_features_export($data, &$export, $module_name = '') {
  $pipe = array();
  foreach ($data as $path) {
    $pipe['menu_links'][] = "features:{$path}";
  }
  return $pipe;
}

/**
 * Implements hook_features_export_options().
 */
function menu_custom_features_export_options() {
  $options = array();
  $result = db_query("SELECT * FROM {menu_custom} ORDER BY title", array(), array('fetch' => PDO::FETCH_ASSOC));
  foreach ($result as $menu) {
    $options[$menu['menu_name']] = $menu['title'];
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function menu_custom_features_export($data, &$export, $module_name = '') {
  // Default hooks are provided by the feature module so we need to add
  // it as a dependency.
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['menu'] = 'menu';

  // Collect a menu to module map
  $pipe = array();
  $map = features_get_default_map('menu_custom', 'menu_name');
  foreach ($data as $menu_name) {
    // If this menu is provided by a different module, add it as a dependency.
    if (isset($map[$menu_name]) && $map[$menu_name] != $module_name) {
      $export['dependencies'][$map[$menu_name]] = $map[$menu_name];
    }
    else {
      $export['features']['menu_custom'][$menu_name] = $menu_name;
    }
  }
  return $pipe;
}

/**
 * Implements hook_features_export_render()
 */
function menu_custom_features_export_render($module, $data) {
  $code = array();
  $code[] = '  $menus = array();';
  $code[] = '';

  $translatables = array();
  foreach ($data as $menu_name) {
    $row = db_select('menu_custom')
      ->fields('menu_custom')
      ->condition('menu_name', $menu_name)
      ->execute()
      ->fetchAssoc();
    if ($row) {
      $export = features_var_export($row, '  ');
      $code[] = "  // Exported menu: {$menu_name}.";
      $code[] = "  \$menus['{$menu_name}'] = {$export};";
      $translatables[] = $row['title'];
      $translatables[] = $row['description'];
    }
  }
  if (!empty($translatables)) {
    $code[] = features_translatables_export($translatables, '  ');
  }

  $code[] = '  return $menus;';
  $code = implode("\n", $code);
  return array('menu_default_menu_custom' => $code);
}

/**
 * Implements hook_features_revert().
 */
function menu_custom_features_revert($module) {
  menu_custom_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function menu_custom_features_rebuild($module) {
  if ($defaults = features_get_default('menu_custom', $module)) {
    foreach ($defaults as $menu) {
      menu_save($menu);
    }
  }
}

/**
 * Implements hook_features_export_options().
 */
function menu_links_features_export_options() {
  global $menu_admin;
  // Need to set this to TRUE in order to get menu links that the
  // current user may not have access to (i.e. user/login)
  $menu_admin = TRUE;
  $use_menus = array_intersect_key(menu_get_menus(), array_flip(array_filter(variable_get('features_admin_menu_links_menus', array_keys(menu_get_menus())))));
  $menu_links = menu_parent_options($use_menus, array('mlid' => 0));
  $options = array();
  foreach ($menu_links as $key => $name) {
    list($menu_name, $mlid) = explode(':', $key, 2);
    if ($mlid != 0) {
      $link = menu_link_load($mlid);
      $identifier = menu_links_features_identifier($link, TRUE);
      $options[$identifier] = "{$menu_name}: {$name}";
    }
  }
  $menu_admin = FALSE;
  return $options;
}

/**
 * Callback for generating the menu link exportable identifier.
 */
function menu_links_features_identifier($link, $old = FALSE) {
  // Add some uniqueness to these identifiers, allowing multiple links with the same path, but different titles.
  $clean_title = features_clean_title(isset($link['title']) ? $link['title'] : $link['link_title']);

  // The old identifier is requested.
  if ($old) {
    // if identifier already exists
    if (isset($link['options']['identifier'])) {
      return $link['options']['identifier'];
    }
    // providing backward compatibility and allowing/enabling multiple links with same paths
    else {
      $identifier = isset($link['menu_name'], $link['link_path']) ? "{$link['menu_name']}:{$link['link_path']}" : FALSE;
      // Checking if there are multiples of this identifier
      if (features_menu_link_load($identifier) !== FALSE) {
        // this is where we return the upgrade posibility for links.
        return $identifier;
      }
    }
  }

  return isset($link['menu_name'], $link['link_path']) ? "{$link['menu_name']}_{$clean_title}:{$link['link_path']}" : FALSE;
}

/**
 * Implements hook_features_export().
 */
function menu_links_features_export($data, &$export, $module_name = '') {
  // Default hooks are provided by the feature module so we need to add
  // it as a dependency.
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['menu'] = 'menu';

  // Collect a link to module map
  $pipe = array();
  $map = features_get_default_map('menu_links', 'menu_links_features_identifier');
  foreach ($data as $key => $identifier) {
    if ($link = features_menu_link_load($identifier)) {
      // If this link is provided by a different module, add it as a dependency.
      $new_identifier = menu_links_features_identifier($link, empty($export));
      if (isset($map[$identifier]) && $map[$identifier] != $module_name) {
        $export['dependencies'][$map[$identifier]] = $map[$identifier];
      }
      else {
        $export['features']['menu_links'][$new_identifier] = $new_identifier;
      }
      // For now, exclude a variety of common menus from automatic export.
      // They may still be explicitly included in a Feature if the builder
      // chooses to do so.
      if (!in_array($link['menu_name'], array('features', 'primary-links', 'secondary-links', 'navigation', 'admin', 'devel'))) {
        $pipe['menu_custom'][] = $link['menu_name'];
      }
    }
  }
  return $pipe;
}

/**
 * Implements hook_features_export_render()
 */
function menu_links_features_export_render($module, $data, $export = NULL) {
  $code = array();
  $code[] = '  $menu_links = array();';
  $code[] = '';

  $translatables = array();
  foreach ($data as $identifier) {

    if ($link = features_menu_link_load($identifier)) {
      $new_identifier = menu_links_features_identifier($link, empty($export));

      // Replace plid with a parent path.
      if (!empty($link['plid']) && $parent = menu_link_load($link['plid'])) {
        // If the new identifier is different than the old, maintain
        // 'parent_path' for backwards compatibility.
        if ($new_identifier != menu_links_features_identifier($link)) {
          $link['parent_path'] = $parent['link_path'];
        }
        else {
          $clean_title = features_clean_title($parent['title']);
          $link['parent_identifier'] = "{$parent['menu_name']}_{$clean_title}:{$parent['link_path']}";
        }
      }

      if (isset($export)) {
        // Don't show new identifier unless we are actually exporting.
        $link['options']['identifier'] = $new_identifier;
        // identifiers are renewed, => that means we need to update them in the db
        $temp = $link;
        menu_link_save($temp);
      }

       unset($link['plid']);
       unset($link['mlid']);

      $code[] = "  // Exported menu link: {$new_identifier}.";
      $code[] = "  \$menu_links['{$new_identifier}'] = ". features_var_export($link, '  ') .";";
      $translatables[] = $link['link_title'];
    }
  }
  $code[] = '';
  if (!empty($translatables)) {
    $code[] = features_translatables_export($translatables, '  ');
  }

  $code[] = '  return $menu_links;';
  $code = implode("\n", $code);
  return array('menu_default_menu_links' => $code);
}

/**
 * Implements hook_features_revert().
 */
function menu_links_features_revert($module) {
  menu_links_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function menu_links_features_rebuild($module) {
  if ($menu_links = features_get_default('menu_links', $module)) {
    menu_links_features_rebuild_ordered($menu_links);
  }
}

/**
 * Generate a depth tree of all menu links.
 */
function menu_links_features_rebuild_ordered($menu_links, $reset = FALSE) {
  static $ordered;
  static $all_links;
  if (!isset($ordered) || $reset) {
    $ordered = array();
    $unordered = features_get_default('menu_links');

    // Order all links by depth.
    if ($unordered) {
      do {
        $current = count($unordered);
        foreach ($unordered as $key => $link) {
          $identifier = menu_links_features_identifier($link);
          $parent = isset($link['parent_identifier']) ? $link['parent_identifier'] : '';
          $weight = 0;
          // Parent has been seen, so weigh this above parent.
          if (isset($ordered[$parent])) {
            $weight = $ordered[$parent] + 1;
          }
          // Next loop will try to find parent weight instead.
          elseif ($parent) {
            continue;
          }
          $ordered[$identifier] = $weight;
          $all_links[$identifier] = $link;
          unset($unordered[$key]);
        }
      // Exit out when the above does no changes this loop.
      } while (count($unordered) < $current);
    }
    // Add all remaining unordered items to the ordered list.
    foreach ($unordered as $link) {
      $identifier = menu_links_features_identifier($link);
      $ordered[$identifier] = 0;
      $all_links[$identifier] = $link;
    }
    asort($ordered);
  }

  // Ensure any default menu items that do not exist are created.
  foreach (array_keys($ordered) as $identifier) {
    $link = $all_links[$identifier];

    $existing = features_menu_link_load($identifier);
    if (!$existing || in_array($link, $menu_links)) {
      // Retrieve the mlid if this is an existing item.
      if ($existing) {
        $link['mlid'] = $existing['mlid'];
      }
      // Retrieve the plid for a parent link.
      if (!empty($link['parent_identifier']) && $parent = features_menu_link_load($link['parent_identifier'])) {
        $link['plid'] = $parent['mlid'];
      }
      // This if for backwards compatibility.
      elseif (!empty($link['parent_path']) && $parent = features_menu_link_load("{$link['menu_name']}:{$link['parent_path']}")) {
         $link['plid'] = $parent['mlid'];
       }
      else {
        $link['plid'] = 0;
      }
      menu_link_save($link);
    }
  }
}

/**
 * Load a menu link by its menu_name_cleantitle:link_path identifier.
 * Also matches links with unique menu_name:link_path
 */
function features_menu_link_load($identifier) {
  $menu_name = '';
  $link_path = '';
  // This gets variables for menu_name_cleantitle:link_path format.
  if (strstr($identifier, "_")) {
    $link_path = substr($identifier, strpos($identifier, ":") + 1);
    list($menu_name) = explode('_', $identifier, 2);
    $clean_title = substr($identifier, strpos($identifier, "_")  + 1, strpos($identifier, ":") - strpos($identifier, "_") - 1);
  }
  // This gets variables for traditional identifier format.
  else {
    $clean_title = '';
    list($menu_name, $link_path) = explode(':', $identifier, 2);
  }
  $links = db_select('menu_links')
    ->fields('menu_links', array('menu_name', 'mlid', 'plid', 'link_path', 'router_path', 'link_title', 'options', 'module', 'hidden', 'external', 'has_children', 'expanded', 'weight', 'customized'))
    ->condition('menu_name', $menu_name)
    ->condition('link_path', $link_path)
    ->addTag('features_menu_link')
    ->execute()
    ->fetchAllAssoc('mlid');

  foreach($links as $link) {
    $link->options = unserialize($link->options);

    // Title or previous identifier matches.
    if ((isset($link->options['identifier']) && strcmp($link->options['identifier'], $identifier) == 0)
        || (isset($clean_title) && strcmp(features_clean_title($link->link_title), $clean_title) == 0)) {

      return (array)$link;
    }
  }

  // Only one link with the requested menu_name and link_path does exists,
  // -- providing an upgrade possibility for links saved in a feature before the
  // new identifier-pattern was added.
  if (count($links) == 1 && empty($clean_title)) {
    $link = reset($links); // get the first item
    return (array)$link;
  }
  // If link_path was changed on an existing link, we need to find it by
  // searching for link_title.
  else if (isset($clean_title)) {
    $links = db_select('menu_links')
    ->fields('menu_links', array('menu_name', 'mlid', 'plid', 'link_path', 'router_path', 'link_title', 'options', 'module', 'hidden', 'external', 'has_children', 'expanded', 'weight'))
    ->condition('menu_name', $menu_name)
    ->execute()
    ->fetchAllAssoc('mlid');

    foreach($links as $link) {
      $link->options = unserialize($link->options);
      // Links with a stored identifier must only be matched on that identifier,
      // to prevent cross over assumptions.
      if (isset($link->options['identifier'])) {
        if (strcmp($link->options['identifier'], $identifier) == 0) {
          return (array)$link;
        }
      }
      elseif ((strcmp(features_clean_title($link->link_title), $clean_title) == 0)) {
        return (array)$link;
      }
    }
  }
  return FALSE;
}

/**
 * Returns a lowercase clean string with only letters, numbers and dashes
 */
function features_clean_title($str) {
  return strtolower(preg_replace_callback('/(\s)|([^a-zA-Z\-0-9])/i', create_function(
          '$matches',
          'return $matches[1]?"-":"";'
      ), $str));
}
