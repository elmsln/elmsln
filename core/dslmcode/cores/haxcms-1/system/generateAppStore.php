<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if (
    isset($_GET['app-store-token']) &&
    $HAXCMS->validateRequestToken($_GET['app-store-token'], 'appstore')
) {
    header('Content-Type: application/json');
    $haxService = new HAXService();
    $apikeys = array();
    $baseApps = $haxService->baseSupportedApps();
    foreach ($baseApps as $key => $app) {
        if (
            isset($HAXCMS->config->appStore->apiKeys->{$key}) &&
            $HAXCMS->config->appStore->apiKeys->{$key} != ''
        ) {
            $apikeys[$key] = $HAXCMS->config->appStore->apiKeys->{$key};
        }
    }
    $appStore = $haxService->loadBaseAppStore($apikeys);
    // pull in the core one we supply, though only upload works currently
    $tmp = json_decode($HAXCMS->siteConnectionJSON());
    array_push($appStore, $tmp);
    if (isset($HAXCMS->config->appStore->stax)) {
        $staxList = $HAXCMS->config->appStore->stax;
    } else {
        $staxList = $haxService->loadBaseStax();
    }
    if (isset($HAXCMS->config->appStore->blox)) {
        $bloxList = $HAXCMS->config->appStore->blox;
    } else {
        $bloxList = $haxService->loadBaseBlox();
    }
    if (isset($HAXCMS->config->appStore->autoloader)) {
        $autoloaderList = $HAXCMS->config->appStore->autoloader;
    } else {
        $autoloaderList = json_decode('
      [
        "video-player",
        "meme-maker",
        "lrn-aside",
        "grid-plate",
        "tab-list",
        "magazine-cover",
        "image-compare-slider",
        "license-element",
        "self-check",
        "multiple-choice",
        "oer-schema",
        "hero-banner",
        "task-list",
        "lrn-table",
        "media-image",
        "lrndesign-blockquote",
        "a11y-gif-player",
        "paper-audio-player",
        "wikipedia-query",
        "lrn-vocab",
        "full-width-image",
        "person-testimonial",
        "citation-element",
        "stop-note",
        "place-holder",
        "lrn-math",
        "q-r",
        "lrndesign-gallery",
        "lrndesign-timeline"
      ]
      ');
    }
    $return = array(
        'status' => 200,
        'apps' => $appStore,
        'stax' => $staxList,
        'blox' => $bloxList,
        'autoloader' => $autoloaderList
    );
    header('Status: 200');
    print json_encode($return);
    exit();
}
?>
