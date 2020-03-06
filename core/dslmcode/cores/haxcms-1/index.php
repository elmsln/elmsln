<?php
if (!is_dir('_config') || !is_dir('_sites') || !is_dir('_archived') || !is_dir('_published')) {
    header("Location: install.php");
}
include_once dirname(__FILE__) . '/system/backend/php/bootstrapHAX.php';
include_once $HAXCMS->configDirectory . '/config.php';
$appSettings = $HAXCMS->appJWTConnectionSettings();
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <link rel="preload" href="./build/es6/dist/build-home.js" as="script" crossorigin="anonymous">
    <link rel="preload" href="./build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/core/site-list/haxcms-site-listing.js"
      as="script" crossorigin="anonymous">
    <link rel="preload" href="./build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/base.css" as="style">
    <link rel="preconnect" crossorigin href="https://fonts.googleapis.com">
    <link rel="preconnect" crossorigin href="https://cdnjs.cloudflare.com">   
    <link rel="stylesheet" href="build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/base.css" /> 
    <script type="text/javascript">
      document.write("<base href='" + document.location.pathname.replace('index.html', '') + "' />");
    </script>
    <meta name="generator" content="HAXCMS">
    <meta name="viewport" content="width=device-width, minimum-scale=1, initial-scale=1, user-scalable=yes">
    <title>HAXCMS site list</title>
    <meta name="description" content="My HAXCMS site description">
    
    <link rel="icon" href="assets/favicon.ico">

    <link rel="manifest" href="manifest.json">

    <meta name="theme-color" content="#37474f">

    <meta name="mobile-web-app-capable" content="yes">
    <meta name="application-name" content="My site">

    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
    <meta name="apple-mobile-web-app-title" content="My App">

    <link rel="apple-touch-icon" href="assets/icon-48x48.png">
    <link rel="apple-touch-icon" sizes="72x72" href="assets/icon-72x72.png">
    <link rel="apple-touch-icon" sizes="96x96" href="assets/icon-96x96.png">
    <link rel="apple-touch-icon" sizes="144x144" href="assets/icon-144x144.png">
    <link rel="apple-touch-icon" sizes="192x192" href="assets/icon-192x192.png">

    <meta name="msapplication-TileImage" content="assets/icon-144x144.png">
    <meta name="msapplication-TileColor" content="#37474f">
    <meta name="msapplication-tap-highlight" content="no">

    <meta name="twitter:card" content="summary">
    <meta name="twitter:site" content="@elmsln">
    <meta property="og:type" content="website">
    <meta property="og:site_name" content="books-app">
    <meta property="og:image" content="assets/icon-144x144.png" />
    <style>
      body {
        margin: 0;
        min-height: 100vh;
      }
      body[data-logged-in] {
        background-color: #EEEEEE;
      }
      body {
        margin: 0;
        min-height: 100vh;
        transition: .6s linear background;
        background-color: var(--haxcms-system-bg);
      }
      haxcms-site-listing {
        transition: all 1s linear;
        --haxcms-site-listing-color-dark: var(--haxcms-system-bg, --simple-colors-default-theme-blue-11);
        --haxcms-site-listing-color-light: #FFFFFF;
        --haxcms-site-listing-color-hover: var(--haxcms-system-action-color);
        outline-color: var(--haxcms-site-listing-color-hover);
      }
      haxcms-site-listing:not(:defined) {
        width: 100vw;
        display: block;
        position: fixed;
        height: 100vh;
        background: #23D5AB;
      }
      haxcms-site-listing:not(:defined) div {
        font-size: 6vw;
        line-height: 1;
        margin: 0 auto;
        top: calc(50vh - 8vw);
        width: 100%;
        justify-content: center;
        display: block;
        text-align: center;
        padding: 0;
        position: relative;
        font-family: "Courier New", Courier, monospace;
        color: black;
      }
      body[no-js] haxcms-site-listing {
        display: none !important;
      }
      .version {
        font-size: 10px;
        padding: 0 2px;
        font-weight: bold;
        color: #FFFFFF;
        position: absolute;
        right: 0;
        top: 0;
        z-index: 2;
      }
    </style>
  </head>
  <body no-js>
    <script>window.appSettings = <?php print json_encode(
        $appSettings
    ); ?>; </script>
    <haxcms-site-listing create-params='{"token":"<?php print $HAXCMS->getRequestToken(); ?>"}' base-path="<?php print $HAXCMS->basePath; ?>" data-source="<?php print $HAXCMS->sitesJSON; ?>" <?php print $HAXCMS->siteListing->attr; ?>>
      <div>HAXcms</div><div>loading</div>
      <?php print $HAXCMS->siteListing->slot; ?>
    </haxcms-site-listing>
    <div class="version">V<?php print $HAXCMS->getHAXCMSVersion();?></div>
    <noscript>Enable JavaScript to use HAXcms.</noscript>
    <script>document.body.removeAttribute('no-js');window.__appCDN="<?php print $HAXCMS->getCDNForDynamic();?>";window.__appForceUpgrade=true;</script>
    <script src="./build-home.js"></script>
  </body>
</html>