<?php
  // if we don't have a user and the don't answer, bail
  if (!isset($_SERVER['PHP_AUTH_USER'])) {
    header('WWW-Authenticate: Basic realm="Private"');
    header('HTTP/1.0 401 Unauthorized');
    print 'Login is required';
    header('Status: 403');
    exit;
  }
  else {
    include_once '../system/lib/bootstrapHAX.php';
    include_once $HAXCMS->configDirectory . '/config.php';
    // test if this is a valid user login
    if (!$HAXCMS->testLogin(TRUE)) {
      print 'Access denied';
      header('Status: 403');
      exit;
    }
    else {
      header('Content-Type: application/json');
      header('Status: 200');
      print json_encode($HAXCMS->getJWT());
      exit;
    }
  }