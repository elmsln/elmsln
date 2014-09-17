<?php


/**
 * Implements hook_drush_exit().
 */
function apc_drush_exit() {
  if (class_exists('DrupalAPCCache')){
    DrupalAPCCache::remoteFlush();
  }
}
