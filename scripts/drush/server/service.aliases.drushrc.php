<?php
/**
 * Self building aliases for service groups in ELMSLN deployments
 */

// to execute ANY command
include_once('generate_aliases.php');
// abstracted to avoid multiple calls against this file due to
// an issue in drush where it's processing this file many many times
// this also makes it easy to static / pervasively cache the calls
$config = _elmsln_alises_build_server($aliases);

/**
 * Magic to auto produce additional alias sub-groups
 */
$services = array();
$modifier = '-all';
foreach ($aliases as $key => $values) {
  $parts = explode('.', $key);
  if (count($parts) == 2) {
    // make sure we have the sub-group before targeting
    if (!isset($services[$parts[0] . $modifier]['site-list'])) {
      $services[$parts[0] . $modifier]['site-list'] = array();
    }
    // add this item to this sub-grouping, accounting for authorities
    // that will only have 1 system in them
    if ($parts[1] == $config['host']) {
      $services[$parts[0] . $modifier]['site-list'][] = '@' . $parts[0];
    }
    else {
      $services[$parts[0] . $modifier]['site-list'][] = '@' . $key;
    }
  }
}

$aliases = $services;