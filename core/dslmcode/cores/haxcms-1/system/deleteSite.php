<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    // load site
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    if ($site->name) {
      global $fileSystem;
      $fileSystem->remove([
        $site->directory . '/' . $site->manifest->metadata->siteName
      ]);
      header('Status: 200');
      $return = array(
        'name' => $site->name,
        'detail' => 'Site deleted',
      );
    }
    else {
      header('Status: 500');
      $return = array(
        'name' => $HAXCMS->safePost['siteName'],
        'detail' => 'Site does not exist!'
      );
    }
    print json_encode($return);
    exit();
}
?>
