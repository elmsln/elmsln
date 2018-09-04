<?php
  // basic global debugging
  function hax500Debug(){ if(($err=error_get_last())) die('<pre>'.print_r($err,true).'</pre>'); }
  register_shutdown_function('hax500Debug');
  // register our global CMS variable for the whole damn thing
  global $HAXCMS;
  // calculate where we are in the file system, accurately
  $here = __FILE__;
  define('HAXCMS_ROOT', str_replace('/system/lib/bootstrapHAX.php', '', $here));
  // the whole CMS as one object
  include_once 'HAXCMS.php';
  // invoke the CMS
  $HAXCMS = new HAXCMS();  