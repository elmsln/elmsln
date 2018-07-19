<?php
  // clear login data
  if(isset($_SERVER['PHP_AUTH_USER']))
    unset($_SERVER['PHP_AUTH_USER']);       
  if (isset($_SERVER['PHP_AUTH_PW']))
    unset($_SERVER['PHP_AUTH_PW']);
  header('Content-Type: application/json');
  header('Status: 200');
  print json_encode('loggedout');
  exit;
?>