<?php
/**
 * @file
 * Example hooks for the ELMSMedia H5P feature.
 */

/**
 * Alter the list of allowed tags to put outputed in the h5p questions.
 */
function hook_elmsmedia_h5p_allowed_tags_alter(&$allowed_tags) {
  $allowed_tags[] = 'em';
  $allowed_tags[] = 'video';
  $allowed_tags[] = 'my-custom-tag';
}