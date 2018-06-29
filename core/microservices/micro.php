<?php
/**
 * @file
 * Simple router for getting calls to run different docker commands
 */
// ensure we have a thing
if (!isset($_GET['data'])) {
  return FALSE;
}
else {
  $data = json_decode($_GET['data']);
  if (!isset($data->token) || !isset($data->ops) || !isset($data->service)) {
    return FALSE;
  }
  else {
    // load configuration off the file system
    define('MICRO_ROOT', getcwd());
    include_once MICRO_ROOT . '/../dslmcode/elmsln_environment/elmsln_environment.php';
    // build sha1 hash for a public / private key pair effectively
    $obj = array(
      $elmslncfg['salt'],
      $data->service
    );
    $hash = sha1(serialize($obj));
    // ensure that the key matches the hash against the SALT
    if ($hash === $data->token) {
      print 'Call for ' . $data->service;
      print "\n<br/>\n";
      // @todo this is where we should do this
      print_r($data->ops);
      return TRUE;
    }
  }
}

return FALSE;