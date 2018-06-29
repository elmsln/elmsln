<?php
  // Start the session
  session_start();
  define('HAXCMS_ROOT', getcwd());
  // service library
  include_once 'lib/HAXService.php';
  // the whole CMS as one object
  include_once 'lib/HAXCMS.php';
  // invoke the CMS
  $GLOBALS['HAXCMS'] = new HAXCMS();
  // configure it
  include_once 'config.php';
  // Set session variables
  //$_SESSION["favcolor"] = "green";
  //$project = $GLOBALS['HAXCMS']->loadProject('current', TRUE);
  //$project->addPage();
  //$project->addPage();
?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, minimum-scale=1, initial-scale=1, user-scalable=yes">
    <title>hax-body demo</title>
    <script src="webcomponents/bower_components/webcomponentsjs/webcomponents.min.js"></script>
    <script>
      /* this script must run before Polymer is imported */
      window.Polymer = {
        dom: 'shady',
        lazyRegister: true
      };
    </script>
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-store.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-body.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-autoloader.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-manager.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-app-picker.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-app.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-panel.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-export-dialog.html">
    <link rel="import" href="webcomponents/bower_components/hax-body/hax-toolbar.html">
    <!-- Adding Favicon -->
    <link rel="apple-touch-icon" sizes="57x57" href="assets/favicon/apple-icon-57x57.png">
    <link rel="apple-touch-icon" sizes="60x60" href="assets/favicon/apple-icon-60x60.png">
    <link rel="apple-touch-icon" sizes="72x72" href="assets/favicon/apple-icon-72x72.png">
    <link rel="apple-touch-icon" sizes="76x76" href="assets/favicon/apple-icon-76x76.png">
    <link rel="apple-touch-icon" sizes="114x114" href="assets/favicon/apple-icon-114x114.png">
    <link rel="apple-touch-icon" sizes="120x120" href="assets/favicon/apple-icon-120x120.png">
    <link rel="apple-touch-icon" sizes="144x144" href="assets/favicon/apple-icon-144x144.png">
    <link rel="apple-touch-icon" sizes="152x152" href="assets/favicon/apple-icon-152x152.png">
    <link rel="apple-touch-icon" sizes="180x180" href="assets/favicon/apple-icon-180x180.png">
    <link rel="icon" type="image/png" sizes="192x192"  href="assets/favicon/android-icon-192x192.png">
    <link rel="icon" type="image/png" sizes="32x32" href="assets/favicon/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="96x96" href="assets/favicon/favicon-96x96.png">
    <link rel="icon" type="image/png" sizes="16x16" href="assets/favicon/favicon-16x16.png">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="msapplication-TileImage" content="assets/favicon/ms-icon-144x144.png">
    <meta name="theme-color" content="#ffffff">
    <link rel="stylesheet" href="assets/styles.css">
</head>
<body>
  <hax-store app-store='<?php print json_encode($GLOBALS['HAXCMS']->appStoreConnection);?>'></hax-store>
  <hax-body></hax-body>
  <hax-autoloader hidden></hax-autoloader>
  <hax-panel align="left"></hax-panel>
  <hax-manager></hax-manager>
  <hax-export-dialog></hax-export-dialog>
  <hax-app-picker></hax-app-picker>
</body>
</html>