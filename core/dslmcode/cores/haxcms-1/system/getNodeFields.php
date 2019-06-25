<?php
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// test if this is a valid user login
if ($HAXCMS->validateJWT()) {
    header('Content-Type: application/json');
    if ($HAXCMS->validateRequestToken($_POST['token'], 'fields')) {
        $site = $HAXCMS->loadSite($HAXCMS->safePost['siteName']);
        if ($page = $site->loadNode($HAXCMS->safePost['nodeId'])) {
            $schema = $site->loadNodeFieldSchema($page);
            header('Status: 200');
            print json_encode($schema);
        }
    } else {
        header('Status: 403');
    }
    exit();
}
?>
