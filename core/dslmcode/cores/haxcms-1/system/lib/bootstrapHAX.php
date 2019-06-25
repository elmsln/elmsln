<?php
// basic global debugging
function hax500Debug()
{
    if ($err = error_get_last()) {
        die('<pre>' . print_r($err, true) . '</pre>');
    }
}
register_shutdown_function('hax500Debug');
// register our global CMS variable for the whole damn thing
global $HAXCMS;
global $config;
// support for config.php to override core capabilities
$config['connection'] = array();
// calculate where we are in the file system, accurately
$here = str_replace('/system/lib/bootstrapHAX.php', '', __FILE__);
// core support for IAM symlinked core which follows a similar pattern at a custom base path
// this is needed because of how PHP resolves paths when in symlinked patterns
if (file_exists($here . '/_config/IAM')) {
  $pieces = explode('/', $_SERVER['REQUEST_URI']);
  array_shift($pieces);
  // leverage BRANCH in order to calculate the correct directory name here
  if ($branch = file_get_contents($here . '/BRANCH.txt')) {
    $here = str_replace('cores/HAXcms-' . $branch, 'users/' . $pieces[0], $here);
  }
}
define('HAXCMS_ROOT', $here);
// the whole CMS as one object
include_once 'HAXCMS.php';
// invoke the CMS
$HAXCMS = new HAXCMS();
// support IAM config now apply these changes
if (file_exists($here . '/_config/IAM')) {
    $HAXCMS->config->iam = true;
    if (file_exists($here . '/../../_iamConfig/HAXcmsConfig.php')) {
        include_once $here . '/../../_iamConfig/HAXcmsConfig.php';
    }
}