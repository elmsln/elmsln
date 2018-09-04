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
      $item = $HAXCMS->outlineSchema->newItem();
      // set the title
      $item->title = $params['siteName'];
      $item->metadata->siteName = strtolower($params['siteName']);
      $item->description = $params['description'];
      $item->metadata->image = $params['image'];
      $item->metadata->created = time();
      $item->metadata->updated = time();
      // add the item back into the outline schema
      $site->manifest->addItem($item);
      $site->manifest->save();
      print json_encode($item);      
    }
    else {
      header('Status: 403');
    }
    exit;
  }
?>