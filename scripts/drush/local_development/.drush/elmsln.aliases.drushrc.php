<?php
/**
 * Server config for everything
 */
// grouping you are targetting
$group = 'ex';
$server = array(
  'remote-user' => 'example',
  'ssh-options' => '-p 1234',
  'remote-host' => 'example.com',
);
// execute a remote command via SSH
// this helps improve performance when dealing with lots of alias files
include_once('ExecuteRemote.php');
$aliases = _build_aliases($group, $server);
