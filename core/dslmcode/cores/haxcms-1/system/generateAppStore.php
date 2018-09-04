<?php
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // test if this is a valid user login
  if (isset($_GET['app-store-token']) && $HAXCMS->validateRequestToken($_GET['app-store-token'], 'appstore')) {
    header('Content-Type: application/json');
    $haxService = new HAXService();
    $apikeys = array();
    $baseApps = $haxService->baseSupportedApps();
    foreach ($baseApps as $key => $app) {
      if (isset($HAXCMS->apiKeys[$key]) && $HAXCMS->apiKeys[$key] != '') {
        $apikeys[$key] = $HAXCMS->apiKeys[$key];
      }
    }
    $appStore = $haxService->loadBaseAppStore($apikeys);
    // pull in the core one we supply, though only upload works currently
    $tmp = json_decode($HAXCMS->siteConnectionJSON());
    array_push($appStore, $tmp);
    $staxList = $haxService->loadBaseStax();
    $bloxList = $haxService->loadBaseBlox();
    $autoloaderList = json_decode('[
      "video-player",
      "lrn-aside",
      "grid-plate",
      "tab-list",
      "magazine-cover",
      "image-compare-slider",
      "simple-concept-network",
      "license-element",
      "self-check",
      "multiple-choice",
      "oer-schema",
      "hero-banner",
      "task-list",
      "lrn-table",
      "media-image",
      "lrndesign-blockquote",
      "meme-maker",
      "a11y-gif-player",
      "paper-audio-player",
      "wikipedia-query",
      "lrn-vocab",
      "lrn-math",
      "person-testimonial",
      "citation-element",
      "code-editor",
      "place-holder",
      "stop-note",
      "wave-player",
      "lrn-calendar",
      "q-r",
      "pdf-element"
    ]');

    $return = array(
      'status' => 200,
      'apps' => $appStore,
      'stax' => $staxList,
      'blox' => $bloxList,
      'autoloader' => $autoloaderList,
    );
    header('Status: 200');
    print json_encode($return);
    exit;
  }
?>