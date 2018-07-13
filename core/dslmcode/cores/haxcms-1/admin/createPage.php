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
      if ($HAXCMS->validateToken($_GET['token'], $HAXCMS->user->name)) {
        header('Status: 200');
        $params = filter_var_array($_GET, FILTER_SANITIZE_STRING,FILTER_FLAG_STRIP_HIGH);
        // woohoo we can edit this thing!
        $site = $HAXCMS->loadSite(strtolower($params['siteName']), TRUE);
        // get a new item prototype
        $site = $HAXCMS->outlineSchema->newItem();
        // set the title
        $site->title = $params['siteName'];
        $site->metadata->siteName = strtolower($params['siteName']);
        $site->metadata->description = $params['description'];
        $site->metadata->image = $params['image'];
        $site->metadata->icon = $params['icon'];
        // add the item back into the outline schema
        $HAXCMS->outlineSchema->addItem($site);
        $HAXCMS->outlineSchema->save();
        print json_encode($site);      
      }
      else {
        header('Status: 403');
      }
      exit;
    }
  }
?>