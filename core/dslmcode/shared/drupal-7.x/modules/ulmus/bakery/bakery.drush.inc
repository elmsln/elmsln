<?php

/**
 * @file
 * Drush integration for Bakery.
 */

/**
 * Implementation of hook_drush_help().
 */
function bakery_drush_help($section) {
  switch ($section) {
    case 'drush:bakery-add-slave':
      return dt('Update the Bakery configuration to add a slave site.');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function bakery_drush_command() {
  $items['bakery-add-slave'] = array(
    'description' => 'Add a Bakery slave site.',
    'arguments' => array(
      'slave' => 'Slave site URL, starts with http and ending with /.',
    ),
  );
  return $items;
}

function drush_bakery_add_slave($slave) {
  $slaves = variable_get('bakery_slaves', array());
  $slaves[] = $slave;
  variable_set('bakery_slaves', $slaves);
}
