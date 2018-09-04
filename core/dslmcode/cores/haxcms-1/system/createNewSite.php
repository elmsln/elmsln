<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
      header('Status: 200');
      $params = $HAXCMS->safePost;
      // woohoo we can edit this thing!
      $site = $HAXCMS->loadSite(strtolower($params['siteName']), TRUE, $params['domain']);
      // now get a new item to reference this into the top level sites listing
      $schema = $HAXCMS->outlineSchema->newItem();
      $schema->id = $site->manifest->id;
      $schema->title = $params['siteName'];
      $schema->location = $HAXCMS->basePath . $HAXCMS->sitesDirectory . '/' . $site->manifest->metadata->siteName . '/index.html';
      $schema->metadata->siteName = $site->manifest->metadata->siteName;
      // description for an overview if desired
      $schema->description = $params['description'];
      // background image / banner
      $schema->metadata->image = $params['image'];
      // theme to make it easier to swap out later on
      $schema->metadata->theme = $params['theme'];
      // icon to express the concept / visually identify site
      $schema->metadata->icon = $params['icon'];
      // domain for publishing
      $schema->metadata->domain = $params['domain'];
      // slightly style the site based on css vars and hexcode
      if (isset($params['hexCode'])) {
        $hex = $params['hexCode'];
      }
      else {
        $hex = '#aeff00';
      }
      $schema->metadata->hexCode = $hex;
      if (isset($params['cssVariable'])) {
        $cssvar = $params['cssVariable'];
      }
      else {
        $cssvar = '--simple-colors-lime-background5';
      }
      $schema->metadata->created = time();
      $schema->metadata->updated = time();
      $schema->metadata->cssVariable = $cssvar;
      // add the item back into the outline schema
      $HAXCMS->outlineSchema->addItem($schema);
      $HAXCMS->outlineSchema->save();
      // mirror the metadata information into the site's info
      // this means that this info is available to the full site listing
      // as well as this individual site. saves on performance / calls
      // later on if we only need to hit 1 file each time to get all the
      // data we need.
      $site->manifest->metadata = $schema->metadata;
      $site->manifest->description = $schema->description;
      $site->manifest->save();
      print json_encode($schema);      
    }
    else {
      header('Status: 403');
    }
    exit;
  }
?>