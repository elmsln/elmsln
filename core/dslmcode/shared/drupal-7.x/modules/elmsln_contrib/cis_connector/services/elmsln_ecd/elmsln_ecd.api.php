<?php
/**
 * @file
 * Comply integration API.
 */

/**
 * Implements hook_ecd_ignored_types_alter().
 *
 * This hook can be used to add content types that you DO NOT
 * want to ship a reference over to the compliance system.
 * While it would seem to make more sense to have the reverse
 * of defining type TO sync, this module is only to be enabled
 * when it is desired to track assets / content / etc for compliance
 * and quality. So, this won't be enabled on systems that don't want
 * to be tracking this and systems that don't want to track everything
 * can then use this alter hook to ensure their types are not affected.
 * The ELMSLN core types of section, cis_course, and course are all
 * automatically ignored as they are to help keep the data-model alive.
 *
 * @param  array &$ignore array of node types to ignore syncing.
 */
function hook_ecd_ignored_types_alter(&$ignore) {
  // don't send details about the cle_submission type
  // as we don't audit the accessibility of student submissions
  $ignore[] = 'cle_submission';
}


/**
 * Implements hook_ecd_asset_type_alter().
 *
 * Modify the asset type from its default of media to
 * either content or link based on content type / properties
 * of the node that's passed in.
 *
 * @param  string &$type asset type
 * @param  object $node  associated node to evaluate
 */
function hook_ecd_asset_type_alter(&$type, $node) {
  // check if we have a page type and modify to
  // content from media. This is useful for filtering
  // data in comply.
  if ($node->type == 'page') {
    $type = 'content';
  }
}