<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    // load the site from name
    $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
    // update these parts of the manifest to match POST
    $site->manifest->title = filter_var($_POST['manifest']->title, FILTER_SANITIZE_STRING);
    $site->manifest->description = filter_var($_POST['manifest']->description, FILTER_SANITIZE_STRING);
    $site->manifest->metadata->icon = filter_var($_POST['manifest']->metadata->icon, FILTER_SANITIZE_STRING);
    $domain = filter_var($_POST['manifest']->metadata->domain, FILTER_SANITIZE_STRING);
    // support updating the domain CNAME value
    if ($site->manifest->metadata->domain != $domain) {
      $site->manifest->metadata->domain = $domain;
      @file_put_contents($site->directory . '/' . $site->manifest->metadata->siteName . '/CNAME', $domain);
    }
    $site->manifest->metadata->theme = filter_var($_POST['manifest']->metadata->theme, FILTER_SANITIZE_STRING);
    $site->manifest->metadata->image = filter_var($_POST['manifest']->metadata->image, FILTER_SANITIZE_STRING);
    $site->manifest->metadata->hexCode = filter_var($_POST['manifest']->metadata->hexCode, FILTER_SANITIZE_STRING);
    $site->manifest->metadata->cssVariable = filter_var($_POST['manifest']->metadata->cssVariable, FILTER_SANITIZE_STRING);
    $site->manifest->metadata->updated = time();
    $site->manifest->save();
    // now work on HAXCMS layer to match the saved / sanitized data
    $item = $site->manifest;
    // remove items list as we only need the item itself not the nesting
    unset($item->items);
    $HAXCMS->outlineSchema->updateItem($item, TRUE);
    header('Status: 200');
    print json_encode($site->manifest);
    exit;
  }
?>