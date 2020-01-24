<?php
// This is all the PHP / JS code we need in order to make HAX CMS work with PHP
// The variable below is global and then elements look for it for it's configuration
// and unpack from there
include_once dirname(__FILE__) . '/system/backend/php/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
$appSettings = $HAXCMS->appJWTConnectionSettings();
header('Content-Type: application/javascript');
?>
window.appSettings = <?php print json_encode($appSettings); ?>;