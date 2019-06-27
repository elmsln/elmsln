<?php
// a private key to do an additional hash via
$HAXCMS->privateKey = 'HAXTHEWEBPRIVATEKEY';
// super admin account
$HAXCMS->superUser->name = 'jeff';
// super admin password, you must set this in order for HAX to work
$HAXCMS->superUser->password = 'jimmerson';
// set basePath to be the haxCMS location we've got this placed at
$HAXCMS->basePath = '/';
// see system/lib/HAXCMS.php for additional deeper options
// including $HAXCMS->user and $HAXCMS->password which can be used
// to allow for lower permissioned users to login to specific sites
