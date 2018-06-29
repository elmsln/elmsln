<?php
use Drupal\xautoload\Libraries\SerializableClosureWrapper;
use Drupal\xautoload\Libraries\LibrariesPreLoadCallback;

/**
 * Implements hook_libraries_info_alter()
 *
 * Replaces xautoload-related closures in libraries_info(), so the info can be
 * serialized. Allows recovery of the closures on unserialize().
 *
 * @param array[] $info
 */
function xautoload_libraries_info_alter(&$info) {
  xautoload()->librariesInfoAlter->librariesInfoAlter($info);
}
