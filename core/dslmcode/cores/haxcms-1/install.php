<?php
$failed = false;
if (file_exists(__DIR__ . '/VERSION.txt')) {
  $version = filter_var(file_get_contents(__DIR__ . '/VERSION.txt'));
}
// check for core directories existing, redirect if we do
if (is_dir('_sites') && is_dir('_config') && is_dir('_published') && is_dir('_archived')) {
  header("Location: index.php");
  exit();
} else { ?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>HAXcms Installation</title>
    <link rel="preload" href="./build/es6/dist/build-install.js" as="script" crossorigin="anonymous">
    <link rel="preload" href="./build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/core/site-list/haxcms-site-listing.js"
      as="script" crossorigin="anonymous">
    <link rel="preload" href="./build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/base.css" as="style">
    <link rel="preconnect" crossorigin href="https://fonts.googleapis.com">
    <link rel="preconnect" crossorigin href="https://cdnjs.cloudflare.com">   
    <link rel="stylesheet" href="./build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/base.css" />
    <style>
      body {
        color: #222222;
        background-color: var(--haxcms-system-bg, #888888);
        --haxcms-base-styles-list-font-size: 18px;
        font-size: 18px;
      }
      pre {
        background-color: #333333;
        color: yellow;
        padding: 8px;
      }
      paper-button {
        background-color: var(--haxcms-system-action-color, blue);
      }
      paper-button, a {
        color: #FFFFFF;
        text-decoration: none;
      }
      paper-button:focus,
      paper-button:hover,
      a:focus,
      a:hover {
        color: yellow;
      }
      p,ul,li {
        font-size: 18px;
      }
      hax-logo {
        --hax-logo-letter-spacing: 1px;
        text-align: center;
        --hax-logo-font-size: 40px;
      }
      @media screen and (max-width: 600px) {
        hax-logo {
          --hax-logo-font-size: 20px;
        }
      }
      .version {
        float:right;
        font-weight: bold;
      }
      ul li {
        padding: 4px;
      }
      .wrapper {
        margin: 5vh 15vw;
        display: flex;
        justify-content: center;
      }
      paper-card {
        width: 60vw;
        background-color: white;
        padding: 0 16px;
      }
      git-corner {
        right: 0;
        top: 0;
        position: fixed;
      }
      paper-button {
        text-transform: none;
      }
      h1 {
        margin: 0;
        padding: 0;
        font-size: 32px;
      }
    </style>
  </head>
  <body no-js>
    <git-corner alt="Join HAXcms on Github!" source="https://github.com/elmsln/haxcms"></git-corner>
    <div class="wrapper">
      <paper-card elevation="5">
<?php
  include_once 'system/backend/php/lib/Git.php';
  // add git library
  if (!is_dir('_config')) {
    // gotta config some place now don't we
    if (!mkdir('_config')) {
      $failed = true;
    }
    // place for the ssh key chain specific to haxcms if desired
    mkdir('_config/.ssh');
    // tmp directory for uploads and other file management
    mkdir('_config/tmp');
    mkdir('_config/cache');
    mkdir('_config/user');
    mkdir('_config/user/files');
    // node modules for local theme development if desired
    mkdir('_config/node_modules');
    // make config.json boilerplate
    copy(
      'system/boilerplate/systemsetup/config.json',
      '_config/config.json'
    );
    // make a file to do custom theme development in
    copy(
      'system/boilerplate/systemsetup/my-custom-elements.js',
      '_config/my-custom-elements.js'
    );
    // make a file for userData to reside
    copy(
      'system/boilerplate/systemsetup/userData.json',
      '_config/userData.json'
    );
    // make a config.php boilerplate for larger overrides
    copy('system/boilerplate/systemsetup/config.php', '_config/config.php');
    // htaccess files
    copy('system/boilerplate/systemsetup/.htaccess', '_config/.htaccess');
    copy('system/boilerplate/systemsetup/.user-files-htaccess', '_config/user/files/.htaccess');
    // set permissions
    chmod("_config", 0755);
    chmod("_config/tmp", 0777);
    chmod("_config/config.json", 0777);
    chmod("_config/userData.json", 0777);
    // set SALT
    file_put_contents(
      '_config/SALT.txt',
      uniqid() . '-' . uniqid() . '-' . uniqid() . '-' . uniqid()
    );
    // set things in config file from the norm
    $configFile = file_get_contents('_config/config.php');
    // private key
    $configFile = str_replace(
      'HAXTHEWEBPRIVATEKEY',
      uniqid() . '-' . uniqid() . '-' . uniqid() . '-' . uniqid(),
      $configFile
    );
    // refresh private key
    $configFile = str_replace(
      'HAXTHEWEBREFRESHPRIVATEKEY',
      uniqid() . '-' . uniqid() . '-' . uniqid() . '-' . uniqid(),
      $configFile
    );
    // user
    if(isset($_POST['user'])){
      $configFile = str_replace('jeff', $_POST['user'], $configFile);
    }
    else{
      $configFile = str_replace('jeff', 'admin', $configFile);
    }
    // support POST for password in this setup phase
    // this is typial of hosting environments that need
    // to see the login details ahead of time in order
    // to set things up correctly
    if(isset($_POST['pass'])){
      $pass = $_POST['pass'];
    }
    else {
      // pass
      $alphabet =
          'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789';
      $pass = array(); //remember to declare $pass as an array
      $alphaLength = strlen($alphabet) - 1; //put the length -1 in cache
      for ($i = 0; $i < 12; $i++) {
          $n = rand(0, $alphaLength);
          $pass[] = $alphabet[$n];
      }
      $pass = implode($pass);
    }
    $configFile = str_replace('jimmerson', $pass, $configFile);
    // work on base path relative to where this was just launched from
    // super sneaky and locks it to where it's currently installed but required
    // or we don't know where to look for anything
    $basePath = str_replace('install.php', '', $_SERVER['SCRIPT_NAME']); 
    $configFile = str_replace("->basePath = '/'", "->basePath = '$basePath'", $configFile);
    file_put_contents('_config/config.php', $configFile);
    $git = new Git();
    $git->create('_config');
  }
  if (!is_dir('_sites')) {
    // make sites directory
    mkdir('_sites');
    chmod("_sites", 0777);
    // attempt to set the user / group on sites
    // these probaly won't work
    @chown('_sites', get_current_user());
    @chgrp('_sites', get_current_user());
    $git = new Git();
    $git->create('_sites');
  }
  if (!is_dir('_published')) {
    // make published directory so you can have a copy of these files
    mkdir('_published');
    chmod("_published", 0775);
    // attempt to set the user / group on sites
    // these probaly won't work
    @chown('_published', get_current_user());
    @chgrp('_published', get_current_user());
  }
  if (!is_dir('_archived')) {
    // make published directory so you can have a copy of these files
    mkdir('_archived');
    chmod("_archived", 0775);
    // attempt to set the user / group on sites
    // these probaly won't work
    @chown('_archived', get_current_user());
    @chgrp('_archived', get_current_user());
  }
}
if ($failed) { ?>
        <hax-logo hide-hax>install-issue</hax-logo><div class="version">V<?php print $version;?></div>
        <h1>HAXcms folder needs to be writeable</h1>
        <p>
          You can modify permissions in order to achieve this
          <pre>chmod 0777 <?php print __DIR__; ?></pre>
          Or the prefered method is to run:
          <pre><?php print "bash " . __DIR__ . "/scripts/haxtheweb.sh"; ?></pre>
          A complete installation guide can be read on 
          <a href="https://haxtheweb.org/installation" target="_blank"  rel="noopener noreferrer">
          <paper-button raised><iron-icon icon="icons:build"></iron-icon> HAXTheWeb</paper-button></a>.
        </p>
<?php } else { ?>
        <hax-logo hide-hax>HAXcms</hax-logo><div class="version">V<?php print $version;?></div>
        <h1>Install successful!</h1>
        <p>If you don' see any errors then that means HAXcms has been successfully installed!
        Configuration settings were saved to <strong>_config/config.php</strong></p>
        <ul>
          <li>Username: <strong>admin</strong></li>
          <li>Password: <strong><?php print $pass; ?></strong></li>
        </ul>
        <a href="index.php" tabindex="-1"><paper-button raised><iron-icon icon="icons:touch-app"></iron-icon>Access HAXcms!</paper-button></a>
        <p>Ideas to share or experiencing issues? <a href="http://github.com/elmsln/haxcms/issues" target="_blank" rel="noopener noreferrer" tabindex="-1">
        <paper-button raised><iron-icon icon="icons:stars"></iron-icon>Join our open community!</paper-button></a></p>
<?php } ?>
      </paper-card>
    </div>
    <noscript>Enable JavaScript to experience HAXcms.</noscript>
    <script>document.body.removeAttribute('no-js');var cdn="";var old=false;var ancient=false;
      if (typeof Symbol == "undefined") { // IE 11, at least try to serve a watered down site
        ancient = true;
      }
      try {
        new Function('let a;'); // bizarre but needed for Safari 9 bc of when it was made
      }
      catch (err) {
        ancient = true;
      }
      if (!ancient) {
        try { new Function('import("");'); } catch (err) {
          "use strict"; (function () { function a(a, b, c) { var d = a; if (d.state = b, d.stateData = c, 0 < d.onNextStateChange.length) { var e = d.onNextStateChange.slice(); d.onNextStateChange.length = 0; for (var f, g = 0, h = e; g < h.length; g++)f = h[g], f() } return d } function b(b) { function d() { try { document.head.removeChild(f) } catch (a) { } } var e = a(b, "Loading", void 0), f = document.createElement("script"); return f.src = b.url, f.onload = function () { var a, b, f; void 0 === r ? (b = [], f = void 0) : (a = r(), b = a[0], f = a[1]), c(e, b, f), d() }, f.onerror = function () { g(b, new TypeError("Failed to fetch " + b.url)), d() }, document.head.appendChild(f), e } function c(b, c, e) { var f = d(b, c), g = f[0], h = f[1]; return a(b, "WaitingForTurn", { args: g, deps: h, moduleBody: e }) } function d(a, c) { for (var e, f = [], g = [], i = 0, j = c; i < j.length; i++) { if (e = j[i], "exports" === e) { f.push(a.exports); continue } if ("require" === e) { f.push(function (b, c, e) { var f = d(a, b), g = f[0], i = f[1]; h(i, function () { c && c.apply(null, g) }, e) }); continue } if ("meta" === e) { f.push({ url: !0 === a.isTopLevel ? a.url.substring(0, a.url.lastIndexOf("#")) : a.url }); continue } var l = k(n(a.urlBase, e)); f.push(l.exports), g.push(l), "Initialized" === l.state && b(l) } return [f, g] } function e(b) { var c = a(b, "WaitingOnDeps", b.stateData); return h(b.stateData.deps, function () { return f(c) }, function (a) { return g(c, a) }), c } function f(b) { var c = b.stateData; if (null != c.moduleBody) try { c.moduleBody.apply(null, c.args) } catch (a) { return g(b, a) } return a(b, "Executed", void 0) } function g(b, c) { return !0 === b.isTopLevel && setTimeout(function () { throw c }), a(b, "Failed", c) } function h(a, b, c) { var d = a.shift(); return void 0 === d ? void (b && b()) : "WaitingOnDeps" === d.state ? (!1, void h(a, b, c)) : void i(d, function () { h(a, b, c) }, c) } function i(a, b, c) { switch (a.state) { case "WaitingForTurn": return e(a), void i(a, b, c); case "Failed": return void (c && c(a.stateData)); case "Executed": return void b(); case "Loading": case "WaitingOnDeps": return void a.onNextStateChange.push(function () { return i(a, b, c) }); case "Initialized": throw new Error("All dependencies should be loading already before pressureDependencyToExecute is called."); default: throw new Error("Impossible module state: " + a.state); } } function j(a, b) { switch (a.state) { case "Executed": case "Failed": return void b(); default: a.onNextStateChange.push(function () { return j(a, b) }); } } function k(a) { var b = q[a]; return void 0 === b && (b = q[a] = { url: a, urlBase: m(a), exports: Object.create(null), state: "Initialized", stateData: void 0, isTopLevel: !1, onNextStateChange: [] }), b } function l(a) { return v.href = a, v.href } function m(a) { return a = a.split("?")[0], a = a.split("#")[0], a.substring(0, a.lastIndexOf("/") + 1) } function n(a, b) { return -1 === b.indexOf("://") ? l("/" === b[0] ? b : a + b) : b } function o() { return document.baseURI || (document.querySelector("base") || window.location).href } function p() { var b = document.currentScript; if (!b) return u; if (window.HTMLImports) { var c = window.HTMLImports.importForElement(b); return c ? c.href : u } var d = b.ownerDocument.createElement("a"); return d.href = "", d.href } if (!window.define) { var q = Object.create(null), r = void 0, s = 0, t = void 0, u = o(); window.define = function (a, b) { var d = !1; r = function () { return d = !0, r = void 0, [a, b] }; var f = p(); setTimeout(function () { if (!1 == d) { r = void 0; var g = f + "#" + s++, h = k(g); h.isTopLevel = !0; var i = c(h, a, b); void 0 === t ? e(i) : j(k(t), function () { e(i) }), t = g } }, 0) }, window.define._reset = function () { for (var a in q) delete q[a]; r = void 0, s = 0, t = void 0, u = o() }; var v = document.createElement("a") } })();
          var defs;
          // FF 6x.x can be given ES6 compliant code safely
          if (/Firefox\/6/.test(navigator.userAgent) || window.customElements) {
            defs = [
              cdn + "build/es6-amd/node_modules/web-animations-js/web-animations-next-lite.min.js",
              cdn + "assets/babel-top.js",
              cdn + "build/es6-amd/node_modules/@webcomponents/webcomponentsjs/webcomponents-loader.js",
              cdn + "build/es6-amd/dist/build-install.js",
            ];
          }
          else {
            defs = [
              cdn + "build/es5-amd/node_modules/web-animations-js/web-animations-next-lite.min.js",
              cdn + "assets/babel-top.js",
              cdn + "build/es5-amd/node_modules/fetch-ie8/fetch.js",
              cdn + "build/es6/node_modules/@webcomponents/webcomponentsjs/custom-elements-es5-adapter.js",
              cdn + "build/es5-amd/node_modules/@webcomponents/webcomponentsjs/webcomponents-bundle.js",
              cdn + "build/es5-amd/dist/build-install.js"
            ];
          }
          define(defs, function () { "use strict" });
          old=true;
        }
      }
    </script>
    <script>if(old)document.write('<!--');</script>
    <script type="module">
      import "./build/es6/dist/build-install.js";
    </script>
    <script async src="build/es6/node_modules/web-animations-js/web-animations-next-lite.min.js">
    //<!--! do not remove -->
    </script>
  </body>
</html>