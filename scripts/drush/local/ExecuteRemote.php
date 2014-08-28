<?php
/**
 * Class for remote execution over SSH
 */
class ExecuteRemote {
  private static $host;
  private static $options;
  private static $username;
  private static $error;
  private static $output;
  // password is not allowed, use SSH key gens for secure bind
  public static function setup($host, $options, $username) {
    self::$host = $host;
    self::$options = $options;
    self::$username = $username;
  }

  public static function executeScriptSSH($script) {
    // Setup connection string
    $connectionString = self::$options . ' ' . self::$username. '@' . self::$host;
    // Execute script
    $cmd = "ssh $connectionString $script 2>&1";
    self::$output['command'] = $cmd;
    exec($cmd, self::$output, self::$error);
    if (self::$error) {
      //throw new Exception ("\nError sshing: ".print_r(self::$output, true));
    }
    return self::$output;
  }
}

function _build_aliases($group, $server) {
  // Create an array to hold the cache, this prevents unneeded ssh connections
  static $aliases = array();

  if (!empty($aliases)) {
    return $aliases;
  }
  // build remote connection object
  $connection = new ExecuteRemote();
  // pass same settings we're append for connection
  $connection->setup($server['remote-host'], $server['ssh-options'], $server['remote-user']);
  // return output of the remote execution of our script, serialized
  // change home directory location if not running linux
  $return = $connection->executeScriptSSH("php /home/{$server['remote-user']}/.drush/$group.remoteconnect.php");
  // unserialize directly into our expected aliases array
  $aliases = unserialize($return[0]);
  // append remote connection settings
  foreach ($aliases as &$alias) {
    if (isset($alias['root'])) {
      $alias += $server;
    }
  }
  return $aliases;
}
