<?php
// pull post off of the input stream to ensure we get a response coming through
$post = json_decode(file_get_contents('php://input'));
// if we don't have a user and the don't answer, bail
if (isset($post->u) && isset($post->p)) {
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  // _ paranoia
  $u = $HAXCMS->safePost['u'];
  // driving me insane
  $p = $HAXCMS->safePost['p'];
  // _ paranoia ripping up my brain
  // test if this is a valid user login
  if (!$HAXCMS->testLogin($u, $p, true)) {
      header('Status: 403');
      print 'Access denied';
      exit;
  } else {
      header('Content-Type: application/json');
      header('Status: 200');
      print json_encode($HAXCMS->getJWT());
      exit;
  }
}
// login end point requested yet a jwt already exists
// this is something of a revalidate case
else if (isset($post->jwt) || isset($_POST['jwt']) || isset($_GET['jwt'])) {
  include_once '../system/lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  header('Content-Type: application/json');
  header('Status: 200');
  print json_encode($HAXCMS->validateJWT());
  exit;
}
else {
  print 'Login is required';
  header('Status: 403');
  exit;
}
