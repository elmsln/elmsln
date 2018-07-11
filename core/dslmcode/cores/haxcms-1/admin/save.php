<?php
  // if we don't have a user and the don't answer, bail
  if (!isset($_SERVER['PHP_AUTH_USER'])) {
    header('WWW-Authenticate: Basic realm="Private"');
    header('HTTP/1.0 401 Unauthorized');
    print 'Login is required';
    exit;
  }
  else {
    include_once '../system/lib/bootstrapHAX.php';
    include_once $HAXCMS->configDirectory . '/config.php';
    // test if this is a valid user login
    if (!$HAXCMS->testLogin(TRUE)) {
      print 'Access denied';
      exit;
    }
    else {
      // woohoo we can edit this thing!
      $site = $HAXCMS->loadSite('current', TRUE);
      // @todo figure out the active page we were modifying
      // @todo get the data off the wire, validate it, save it
    }
  }