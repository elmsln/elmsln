<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Status: 200');
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken()) {
        $values = $_POST['values'];
        $val = new stdClass();
        if (isset($values->apis) && isset($values->appStore->apiKeys)) {
            $val->apis = $values->apis;
        }
        if (isset($values->publishing)) {
            $val->publishing = $values->publishing;
        }
        $response = $HAXCMS->setConfig($val);
        print json_encode($response);
    } else {
        header('Status: 403');
    }
    exit();
}
?>
