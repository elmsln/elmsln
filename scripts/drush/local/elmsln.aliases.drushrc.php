<?php
/**
 * Self building aliases by reading them from removes
 */

// @todo THIS NEEDS TO BE CACHED OR IT WILL TAKE FOREVER TO LOAD

// execute a remote command via SSH
// this helps improve performance when dealing with lots of alias files
include_once('ExecuteRemote.php');

// read off the .elmsln/elmsln-hosts manifest
$pulledaliases = array();
$file = getcwd() . '/../.elmsln/elmsln-hosts';
$hosts = file_get_contents($file);
$lines = explode("\n", $hosts);
// read each line of the config file
foreach ($lines as $key => $line) {
  // make sure this line isn't a comment and has a=
  if (strpos($line, 'ssh') === 0) {
    $server = array();
    $line = str_replace('ssh ', '', $line);
    $tmp = explode(' ', $line);
    foreach ($tmp as $item) {
      if (strpos($item, '@')) {
        $tmp2 = explode('@', $item);
        if (count($tmp2) == 2) {
          $server['remote-user'] = $tmp2[0];
          $server['remote-host'] = $tmp2[1];
        }
      }
      else {
        $server['ssh-options'] .= $item . ' ';
      }
    }
    // ensure we have 2 settings before doing this
    if (count($server) == 3) {
      // try for a nice name
      if ($key > 0 && strpos($lines[$key-1], '#') === 0) {
        $aliaskey = _elmsln_alias_server_name($lines[$key-1]);
      }
      else {
        $aliaskey = _elmsln_alias_server_name($server['remote-host']);
      }
      $pulledaliases[$aliaskey] = _elmsln_alias_build_aliases($aliaskey, $server);
    }
  }
}
$aliases['elmsln-all'] = array('site-list' => array());
// now convert these to aliases style
foreach ($pulledaliases as $system => $onsystem) {
  $aliases[$system] = array('site-list' => array());
  array_push($aliases['elmsln-all']['site-list'], '@' . $system);
  foreach ($onsystem as $alias => $settings) {
    array_push($aliases[$system]['site-list'], '@' . $system . '.' . $alias);
    $aliases[$system . '.' . $alias] = $settings;
  }
  sort($aliases[$system]['site-list']);
}
