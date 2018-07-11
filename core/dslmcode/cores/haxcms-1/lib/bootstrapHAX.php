<?php
  function hax500Debug(){ if(($err=error_get_last())) die('<pre>'.print_r($err,true).'</pre>'); }
  register_shutdown_function('hax500Debug');
  // Start the session
  session_start();
  // register our global CMS variable for the whole damn thing
  global $HAXCMS;
  // configure it
  // service library
  include_once 'HAXService.php';
  // the whole CMS as one object
  include_once 'HAXCMS.php';
  // invoke the CMS
  $HAXCMS = new HAXCMS();