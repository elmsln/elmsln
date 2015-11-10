<?php

/**
 * @file
 * File module integration.
 */

/**
 * Implements hook_filefield_paths_field_type_info() on behalf of file.module.
 *
 * @return array
 */
function file_filefield_paths_field_type_info() {
  return array('file');
}
