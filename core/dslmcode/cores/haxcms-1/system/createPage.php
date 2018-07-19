<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
      header('Status: 200');
      $params = $HAXCMS->safeGet;
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
?>