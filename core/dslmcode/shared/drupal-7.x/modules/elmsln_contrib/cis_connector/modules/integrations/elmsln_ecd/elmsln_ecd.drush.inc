<?php
/**
 * @file
 * ELMSLN Comply integration Drush functions.
 */

/**
 * Implementats hook_drush_command().
 */
function elmsln_ecd_drush_command() {
  $items = array();
  $items['ecd-bulk-send'] = array(
    'description' => dt('Bulk send all nodes to comply'),
    'aliases' => array('ecd-send'),
  );
  return $items;
}

/**
 * Implementats of hook_drush_help().
 */
function elmsln_ecd_drush_help($section) {
  switch ($section) {
    case 'drush:ecd-bulk-send':
      return dt("Send details of all nodes over to the compliance engine.");
  }
}

/**
 * Drush command callback.
 */
function drush_elmsln_ecd_ecd_bulk_send() {
  // issue bulk send command which might take awhile
  $count = _elmsln_ecd_bulk_send();
  drush_print(dt('@count assets have been submitted to the compliance system.', array('@count' => $count)));
}
