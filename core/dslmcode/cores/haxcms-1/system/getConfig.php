<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Status: 200');
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
        $response = new stdClass();
        $response->schema = $HAXCMS->getConfigSchema();
        $response->values = $HAXCMS->config;
        foreach ($response->values->appStore as $key => $val) {
            if ($key !== 'apiKeys') {
                unset($response->values->appStore->{$key});
            }
        }
        print json_encode($response);
    } else {
        header('Status: 403');
    }
    exit();
}
?>
