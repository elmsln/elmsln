<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    $body = $_POST['body'];
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    if ($page = $site->loadPage($HAXCMS->safePost['page'])) {
      // convert web location for loading into file location for writing
      $bytes = $page->writeLocation($body, HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $site->name . '/');
      if ($bytes === FALSE) {
        header('Status: 500');
        print 'failed to write';
      }
      else {
        // update the updated timestamp
        $page->metadata->updated = time();
        // auto generate a text only description from first 200 chars
        $clean = strip_tags($body);
        $page->description = substr($clean, 0, 200);
        // update the item in the metadata to indicate when content was last set
        $site->manifest->updateItem($page, TRUE);
        header('Status: 200');
        print json_encode($bytes);
      }
      exit;
    }
  }
?>