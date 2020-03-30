<?php
  include_once __DIR__ . '/../../system/backend/php/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
  $site = $HAXCMS->loadSite(basename(__DIR__));
  $page = $site->loadNodeByLocation();
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <?php print $site->getBaseTag(); ?>
  <?php print $site->getSiteMetadata($page); ?>
  <?php print $site->getServiceWorkerScript(null, FALSE, $site->getServiceWorkerStatus()); ?>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
    }
    haxcms-site-builder {
      display: block;
    }
    haxcms-site-builder:not(:defined) div.loading {
      width: 100vw;
      display: block;
      position: initial;
      height: 100vh;
      background: orange;
    }
    haxcms-site-builder:not(:defined) div {
      font-size: 6vw;
      line-height: 1;
      margin: 0 auto;
      top: calc(50vh - 8vw);
      width: 100%;
      justify-content: center;
      display: grid;
      text-align: center;
      padding: 0;
      position: relative;
      font-family: "Courier New", Courier, monospace;
      color: black;
    }
    body[no-js] haxcms-site-builder {
      display: none !important;
    }
  </style>
</head>
<body no-js <?php print $site->getSitePageAttributes();?>>
  <haxcms-site-builder id="site" file="site.json<?php print $HAXCMS->cacheBusterHash();?>">
    <div class="loading">
      <div><?php print $site->name; ?></div>
      <div>loading</div>
    </div>
    <?php print $site->getPageContent($page); ?>
  </haxcms-site-builder>
  <div id="haxcmsoutdatedfallback">
    <haxcms-legacy-player file="site.json<?php print $HAXCMS->cacheBusterHash();?>"></haxcms-legacy-player>
    <div id="haxcmsoutdatedfallbacksuperold"> 
      <iframe id="outline" style="width:18%;float:left;height:500px;padding:0;margin:0;" name="outline" id="frame1"
        src="legacy-outline.html"></iframe>
      <iframe id="content" style="width:80%;float:left;height:500px;padding:0;margin:0;" name="content" id="frame2" src=""></iframe>
      <div style="float:left;padding:16px 0;font-size:32px;text-align: center;width:100%;">Please use a modern browser to
        view our website correctly. <a href="http://outdatedbrowser.com/">Update my browser now</a></div>
    </div>
  </div>
  <script>document.body.removeAttribute('no-js');window.__appCDN="<?php print $HAXCMS->getCDNForDynamic();?>";window.__appForceUpgrade=<?php print $site->getForceUpgrade();?>;</script>
  <script src="./build.js<?php print $HAXCMS->cacheBusterHash();?>"></script>
  <script src="./build-haxcms.js<?php print $HAXCMS->cacheBusterHash();?>"></script>
</body>
</html>