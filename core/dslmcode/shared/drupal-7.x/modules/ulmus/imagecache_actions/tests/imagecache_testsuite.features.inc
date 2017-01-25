<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function imagecache_testsuite_imagecache_default_presets() {
  $filepath = drupal_get_path('module', 'imagecache_testsuite');
  // Each of these presets is stored in its own file.
  // Scan each of these files and return the list.
  return imagecache_testsuite_get_tests();
}
