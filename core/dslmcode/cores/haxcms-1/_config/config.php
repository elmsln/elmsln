<?php
// a private key to do an additional hash via
$HAXCMS->privateKey = 'hax-the-web-key';
// super admin account
$HAXCMS->superUser->name = 'jeff';
// super admin password, you must set this in order for HAX to work
$HAXCMS->superUser->password = 'jimmerson';
// set basePath to be the haxCMS location we've got this placed at
$HAXCMS->basePath = '/haxcms/';