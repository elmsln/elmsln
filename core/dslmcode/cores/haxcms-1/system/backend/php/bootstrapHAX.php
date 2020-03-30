<?php
// basic global debugging
function haxGlobalDebug()
{
    if ($err = error_get_last()) {
      if ($err['type'] === E_ERROR) {
        die('<pre>' . print_r($err, true) . '</pre>');
      }
      else if ($err['type'] === E_WARNING) {
        //die('<pre>' . print_r($err, true) . '</pre>');
      }
      else if ($err['type'] === E_PARSE) {
        //die('<pre>' . print_r($err, true) . '</pre>');
      }
      else if ($err['type'] === E_NOTICE) {
        //die('<pre>' . print_r($err, true) . '</pre>');
      }
    }
}
register_shutdown_function('haxGlobalDebug');
// register our global CMS variable for the whole damn thing
global $HAXCMS;
global $config;
// support for config.php to override core capabilities
$config['connection'] = array();
// calculate where we are in the file system, accurately
$here = str_replace('/system/backend/php/bootstrapHAX.php', '', __FILE__);
// core support for IAM symlinked core which follows a similar pattern at a custom base path
// this is needed because of how PHP resolves paths when in symlinked patterns
// @todo need to support HAXiam in the CLI
if (file_exists($here . '/_config/IAM')) {
  if (isset($_SERVER['REQUEST_URI'])) {
    $pieces = explode('/', $_SERVER['REQUEST_URI']);
    array_shift($pieces);
    $userDir = $pieces[0];
  }
  // account for CLI
  else if (!isset($_SERVER['SERVER_SOFTWARE']) && (php_sapi_name() == 'cli' || is_numeric($_SERVER['argc']) && $_SERVER['argc'] > 0)) {
    if (file_exists($here . '/_config/IAM')) {
      $cliOpts = getopt('', array('op:', 'siteName::', 'iamUser::', 'theme:')) + array('args' => $GLOBALS['argv']);
      if (isset($cliOpts['iamUser'])) {
        $userDir = $cliOpts['iamUser'];
      }
    }
  }
  // leverage BRANCH in order to calculate the correct directory name here
  if ($branch = file_get_contents($here . '/BRANCH.txt')) {
    // intenals rewrite for things that are login in nature
    if (!defined('IAM_INTERNALS') && isset($userDir)) {
      $here = str_replace('cores/HAXcms-' . $branch, 'users/' . $userDir, $here);
    }
  }
}
define('HAXCMS_ROOT', $here);
// the whole CMS as one object
include_once 'lib/HAXCMS.php';
// invoke the CMS
$HAXCMS = new HAXCMS();
// support IAM config now apply these changes
if (file_exists($here . '/_config/IAM')) {
    $HAXCMS->config->iam = true;
    if (file_exists($here . '/../../_iamConfig/HAXcmsConfig.php')) {
        include_once $here . '/../../_iamConfig/HAXcmsConfig.php';
    }
}