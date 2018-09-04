<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    // ensure we have something we can load and ship back out the door
    if ($site = $HAXCMS->loadSite($HAXCMS->safePost['siteName'])) {
      $path = HAXCMS_ROOT . '/scripts/surgepublish.sh';
      $name = escapeshellarg($site->manifest->metadata->siteName);
      // attempt to publish
      $output = shell_exec("bash $path $name");
      // load the site from name
      $site->manifest->metadata->lastPublished = time();
      $site->manifest->save();
      header('Status: 200');
      $return = array(
        'status' => 200,
        'url' => $site->manifest->metadata->domain,
        'label' => 'Click to access ' . $site->manifest->title,
        'response' => 'Site published!',
        'output' => $output,
      );
    }
    else {
      header('Status: 500');
      $return = array(
        'status' => 500,
        'url' => NULL,
        'label' => NULL,
        'response' => 'Unable to load site',
        'output' => '',
      ); 
    }
    print json_encode($return);
    exit;
  }
?>