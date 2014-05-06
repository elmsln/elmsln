<?php
/**
 * @file
 * CIS Connector Drush functions.
 */

/**
 * Add/edit options to cache-clear command.
 */
function cis_connector_drush_cache_clear(&$types) {
  $types['cis_connector'] = '_cis_connector_cache_clear';
}
