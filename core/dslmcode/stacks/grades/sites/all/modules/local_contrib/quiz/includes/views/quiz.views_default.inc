<?php

/*
 * @file
 * Handles default views.
 * Reads views from all the .view.inc files in the views/defaults directory.
 */

/**
 * Implements hook_views_default_views().
 */
function quiz_views_default_views() {
  $views = array();

  $path = drupal_get_path('module', 'quiz') . '/includes/views/defaults';
  $view_files = file_scan_directory($path, '/.*\.view\.inc/');
  foreach ($view_files as $file) {
    include DRUPAL_ROOT . '/' . $path . '/' . $file->filename;
    $views[$view->name] = $view;
  }

  return $views;
}
