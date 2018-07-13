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
        $site = $HAXCMS->loadSite(strtolower($params['siteName']), TRUE, $params['theme']);
        // now get a new item to reference this into the top level sites listing
        $schema = $HAXCMS->outlineSchema->newItem();
        $schema->id = $site->manifest->id;
        $schema->title = $params['siteName'];
        $schema->location = $HAXCMS->basePath . $HAXCMS->sitesDirectory . '/' . strtolower($params['siteName']) . '/index.html';
        $schema->metadata->siteName = strtolower($params['siteName']);
        // description for an overview if desired
        $schema->description = $params['description'];
        // background image / banner
        $schema->metadata->image = $params['image'];
        // theme to make it easier to swap out later on
        $schema->metadata->theme = $params['theme'];
        // icon to express the concept / visually identify site
        $schema->metadata->icon = $params['icon'];
        // color to slightly style the site
        $schema->metadata->color = $params['color'];
        // add the item back into the outline schema
        $HAXCMS->outlineSchema->addItem($schema);
        $HAXCMS->outlineSchema->save();
        print json_encode($schema);      
      }
      else {
        header('Status: 403');
      }
      exit;
    }
  }
?>