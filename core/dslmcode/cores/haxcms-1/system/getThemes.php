<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Status: 200');
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
        $response = new stdClass();
        $response->themes = $HAXCMS->getThemes();
        print json_encode($response);
    } else {
        header('Status: 403');
    }
    exit();
}
?>
