<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    // @todo write back to the correct page
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    $body = $_POST['body'];
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    if ($page = $site->loadPage($HAXCMS->safePost['page'])) {
      // convert web location for loading into file location for writing
      $page->location = str_replace($HAXCMS->basePath . $HAXCMS->sitesDirectory, HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory, $page->location);
      $bytes = $page->writeLocation($body);
      if ($bytes === FALSE) {
        header('Status: 500');
        print 'failed to write';
      }
      else {
        header('Status: 200');
        print json_encode($bytes);
      }
      exit;
    }
  }
?>