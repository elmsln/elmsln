<?php

/**
 * @file
 * Default views.
 */

/**
 * Implements hook_views_default_views().
 */
function admin_views_views_default_views() {
  // @todo This static might need to re-evaluate whether the originating module
  //   of an default admin view exists when invoked more than once (potentially
  //   during or after drupal_flush_all_caches()).
  $views = &drupal_static(__FUNCTION__);

  if (isset($views)) {
    return $views;
  }

  // Collect all modules providing admin_views_default.
  $modules = module_list();
  foreach ($modules as $module) {
    $dir = DRUPAL_ROOT . '/' . drupal_get_path('module', $module) . '/admin_views_default';
    if (is_dir($dir)) {
      // Scan each admin_views_default directory for provided default views.
      foreach (file_scan_directory($dir, '/\.inc$/') as $filepath => $file) {
        // Extract the primary module dependency of the default admin view, which
        // is the filename prefix delimited by a period/dot; e.g.,
        // 'taxonomy.foo-bar.inc', and only include it if that module is enabled.
        $dependency = strtok($file->filename, '.');
        if (isset($modules[$dependency])) {
          include $filepath;
          if (isset($view)) {
            $views[$view->name] = $view;
          }
        }
      }
    }
  }
  return $views;
}

