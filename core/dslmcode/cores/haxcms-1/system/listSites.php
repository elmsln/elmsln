<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
  header('Content-Type: application/json');
  header('Status: 200');
  $return = array(
    "id" => "123-123-123-123",
    "title" => "My sites",
    "author" => "me",
    "description" => "All of my micro sites I know and love.",
    "license" => "by-sa",
    "metadata" => array(),
    "items" => array()
  );
  // loop through files directory so we can cache those things too
  if ($handle = opendir(HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory)) {
    while (false !== ($item = readdir($handle))) {
      if ($item != "." && $item != ".." && is_dir(HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $item) && file_exists(HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $item . '/site.json')) {
        $json = file_get_contents(HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $item . '/site.json');
        $site = json_decode($json);
        $site->location = $HAXCMS->basePath . $HAXCMS->sitesDirectory . '/' . $item . '/';
        $site->metadata->pageCount = count($site->items);
        unset($site->items);
        $return['items'][] = $site;
      }
    }
    closedir($handle);
  }
  print json_encode($return);
  exit();
?>
