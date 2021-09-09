<?php
// a private key to do an additional hash via
$HAXCMS->privateKey = 'HAXTHEWEBPRIVATEKEY';
// a private key for the refresh token for added security
$HAXCMS->refreshPrivateKey = 'HAXTHEWEBREFRESHPRIVATEKEY';
// super admin account
$HAXCMS->superUser->name = 'jeff';
// super admin password, you must set this in order for HAX to work
$HAXCMS->superUser->password = 'jimmerson';
// set basePath to be the haxCMS location we've got this placed at
$HAXCMS->basePath = '/';
// force https for load balanced situations where detection is not accurate
//$HAXCMS->protocol = 'https';
// this ensures certain things are disabled in order to more effectively
// do development on the platform itself. Useful for testing output and
// what not. this applies to ALL REQUESTS asking for it.
//$HAXCMS->developerMode = TRUE;
// use this flag for things that want anonymous page loads to work as they should
// but yet be able to debug things as an admin/authenticated user efficiently
//$HAXCMS->developerModeAdminOnly = TRUE;
// see system/backend/php/lib/HAXCMS.php for additional deeper options
// including $HAXCMS->user and $HAXCMS->password which can be used
// to allow for lower permissioned users to login to specific sites
