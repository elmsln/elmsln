<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT() && isset($_FILES['file-upload'])) {
    header('Content-Type: application/json');
    $site = $HAXCMS->loadSite($HAXCMS->safeGet['siteName']);
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    if ($page = $site->loadPage($HAXCMS->safeGet['page'])) {
      $status = 403;
      $upload = $_FILES['file-upload'];
      $file = new HAXCMSFile();
      print $file->save($upload, $site, $page);
      exit;
    }
  }
?>