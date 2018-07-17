<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
      // @todo write back to the correct page
      $project = $HAXCMS->safePost['project'];
      $outline = $HAXCMS->safePost['outline'];
    }
  }
?>