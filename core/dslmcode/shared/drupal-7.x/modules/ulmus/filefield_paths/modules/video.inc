<?php

/**
 * @file
 * Video module integration.
 */

/**
 * Implements hook_filefield_paths_field_type_info() on behalf of video.module.
 *
 * @return array
 */
function video_filefield_paths_field_type_info() {
  return array('video');
}
