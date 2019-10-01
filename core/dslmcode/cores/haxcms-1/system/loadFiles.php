<?php
include_once dirname(__FILE__) . '/lib/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
// this will broker the request off of the op parameter
// this is required because of the way that HAX editor formulates
// the app store end point requests
$HAXCMS->executeRequest('loadFiles');