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
  $files = file_scan_directory(QUIZ_VIEWS_DIR . '/defaults', '/\.view\.inc/');
  $views = array();
  foreach ($files as $path => $file) {
    require DRUPAL_ROOT . '/' . $path;
    $views[$view->name] = $view;
  }
  return $views;
}
