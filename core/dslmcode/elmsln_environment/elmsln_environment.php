<?php
// hard coded would be nice if it was variable but difficult to do so
define ('ELMSLN_CFG_PATH', '/var/www/elmsln/config/scripts/drush-create-site/config.cfg');
define ('ELMSLN_ENV_HOST', '/var/www/elmsln/_elmsln_env_config/environment.php');
global $elmslncfg;

if ($cfg = file_get_contents(ELMSLN_CFG_PATH)) {
  $lines = explode("\n", $cfg);
  // read each line of the cfg file
  foreach ($lines as $line) {
  // make sure this line isn't a comment and has a = in it
    if (strpos($line, '#') !== 0 && strpos($line, '=')) {
      $tmp = explode('=', $line);
      // ensure we have 2 settings before doing this
      if (count($tmp) == 2) {
        // never pass around the dbsu
        if (!in_array($tmp[0], array('dbsu', 'dbsupw'))) {
          // strip encapsulation if it exists
          $elmslncfg[$tmp[0]] = str_replace('"', '', str_replace("'", '', $tmp[1]));
        }
      }
    }
  }
  // support the fact that $elmsln is used to reference in many bash vars
  foreach ($elmslncfg as $key => $value) {
    if (strpos($value, '$elmsln') !== FALSE) {
      $elmslncfg[$key] = str_replace('$elmsln', $elmslncfg['elmsln'], $value);
    }
  }
  // generate more values that we will want to know as shortcuts
  // sprinkle in some salt from the file system
  if (file_exists($elmslncfg['elmsln'] . '/config/SALT.txt')) {
    $elmslncfg['salt'] = file_get_contents($elmslncfg['elmsln'] . '/config/SALT.txt');
  }
}
else {
  $elmslncfg = array();
}
// allow for environment specific overrides
if (file_exists(ELMSLN_ENV_HOST)) {
  include_once(ELMSLN_ENV_HOST);
}
