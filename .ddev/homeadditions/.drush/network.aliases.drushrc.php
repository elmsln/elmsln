<?php
/**
 * Self building aliases for on ELMSLN deployments
 */

// to execute ANY command
include_once('generate_aliases.php');
// abstracted to avoid multiple calls against this file due to
// an issue in drush where it's processing this file many many times
// this also makes it easy to static / pervasively cache the calls
_elmsln_alises_build_server($aliases);

// allow for network centric call structures as well
$network = array();
foreach ($aliases as $key => $alias) {
  // see if we have a course
  $tmp = explode('.', $key);
  // ensure we have two pieces here
  if (count($tmp) == 2) {
    // group as networks
    $name = $tmp[1];
    // ensure we have a site-list since this is just an alternate form of
    // what we already know about in the alias arrays
    if (isset($network[$name]['site-list'])) {
      $network[$name]['site-list'][] = '@' . $key;
    }
    else {
      $network[$name]['site-list'] = array('@' . $key);
    }
  }
}
// add in our network centric aliases
$aliases = $network;