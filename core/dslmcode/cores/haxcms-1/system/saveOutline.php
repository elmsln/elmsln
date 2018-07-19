<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    // load the site from name
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    // wipe the manifest items and rebuild them
    $site->manifest->items = array();
    $items = $_POST['items'];
    $itemMap = array();
    // items from the POST
    foreach ($items as $key => $item) {
      // get a fake item
      $page = $HAXCMS->outlineSchema->newItem();
      $itemMap[$item->id] = $page->id;
      // set a crappy default title
      $page->title = $item->title;
      if ($item->parent == NULL) {
        $page->parent = NULL;
        $page->indent = 0;
      }
      else {
        // set to the parent id
        $page->parent = $itemMap[$item->parent];
        // move it one indentation below the parent; this can be changed later if desired
        $page->indent = $item->indent;
      }
      if (isset($item->order)) {
        $page->order = $item->order;
      }
      else {
        $page->order = $key;
      }
      // keep location if we get one already
      if (isset($item->location)) {
        $page->location = $item->location;
      }
      else {
        // build a location and copy the associated boilerplate files there for it
        $page->location = $site->basePath . $site->name . '/' . $page->order . '/index.html';
        $site->recurseCopy(HAXCMS_ROOT . '/system/boilerplate/page', $site->directory . '/' . $site->name . '/' . $page->order);
      }
      $site->manifest->addItem($page);
    }
    $site->manifest->save();
    header('Status: 200');
    print json_encode($site->manifest->items);
    exit;
  }
?>