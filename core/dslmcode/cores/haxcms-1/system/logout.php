<?php
// @todo need to run some kind of shut down routine for logging out
include_once '../system/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
header('Content-Type: application/json');
header('Status: 200');
print json_encode('loggedout');
exit();
?>
