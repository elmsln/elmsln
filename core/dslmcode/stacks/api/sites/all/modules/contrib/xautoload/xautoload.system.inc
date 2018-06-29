<?php

use Drupal\xautoload\Discovery\WildcardFileFinder;

/**
 * Implements hook_modules_enabled()
 *
 * @param string[] $modules
 */
function xautoload_modules_enabled($modules) {
  xautoload()->phaseControl->modulesEnabled($modules);
}

/**
 * Implements hook_registry_files_alter()
 *
 * Support wildcard syntax in the files[] setting in your module's info file.
 * See https://drupal.org/node/1976198
 *
 * This function will remove entries like foo/inc/**, and instead add all the
 * individual class files found in the foo/inc/ folder.
 *
 * @param array[] &$files
 *   List of files specified in files[] array in module info files.
 *   Format:
 *
 *     $files['modules/field/field.attach.inc'] = array(
 *       'module' => 'field',
 *       'weight' => 0,
 *     );
 *     // Wildcard syntax.
 *     $files['sites/all/modules/foo/inc/**'] = array(
 *       'module' => 'foo',
 *       'weight' => 0,
 *     );
 */
function xautoload_registry_files_alter(&$files) {
  $file_finder = new WildcardFileFinder();
  $file_finder->addDrupalPaths($files);
  $files = $file_finder->getDrupalFiles();
}
