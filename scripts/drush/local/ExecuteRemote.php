<?php

function _elmsln_alias_execute($server, $script) {
  $output = array();
  $error = FALSE;
  // Setup connection string
  $string = $server['ssh-options'] . ' ' . $server['remote-user'] . '@' . $server['remote-host'];
  // Execute script
  $cmd = "ssh $string $script 2>&1";
  $output['command'] = $cmd;
  exec($cmd, $output, $error);
  if ($error) {
    print 'ERROR IN SSH CONNECTION';
  }
  return $output;
}

/**
 * convert a server name into an alias bucket
 * @param  string $key url to a server to remote connect to
 * @return string         cleaned up to avoid grouping issues
 */
function _elmsln_alias_server_name($key) {
  return ereg_replace("[^a-z]", '', strtolower($key));
}

/**
 * build aliases by running the remote alias generator
 * @param  string $key    server/alias group
 * @param  string $server url to a server to remote connect to
 * @return array         list of aliases w/ their connection credentials
 */
function _elmsln_alias_build_aliases($key, $server) {
  // Create an array to hold the cache, this prevents unneeded ssh connections
  static $systems = array();
  if (!empty($systems[$key])) {
    return $systems[$key];
  }
  // change home directory location if not running linux
  $return = _elmsln_alias_execute($server, "php /home/{$server['remote-user']}/.drush/elmsln.remoteconnect.php");
  // unserialize directly into our expected aliases array
  $system = unserialize($return[0]);
  // append remote connection settings
  foreach ($system as &$alias) {
    if (isset($alias['root'])) {
      $alias += $server;
    }
  }
  $systems[$key] = $system;
  return $systems[$key];
}
