<?php
if (!is_dir('_config') || !is_dir('_sites') || !is_dir('_archived') || !is_dir('_published')) {
    header("Location: install.php");
}
include_once 'system/lib/bootstrapHAX.php';
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
    <script type="text/javascript">
      document.write("<base href='" + document.location.pathname.replace('index.html', '') + "' />");
    </script>
    <meta name="generator" content="HAXCMS">
    <meta name="viewport" content="width=device-width, minimum-scale=1, initial-scale=1, user-scalable=yes">
    <title>HAXCMS site list</title>
    <meta name="description" content="My HAXCMS site description">
    
    <link rel="icon" href="assets/favicon.ico">

    <link rel="manifest" href="manifest.json">

    <meta name="theme-color" content="#3f51b5">

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
    <meta name="msapplication-TileColor" content="#3f51b5">
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
      haxcms-site-listing {
        transition: all 1s linear;
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
    <noscript>Please enable JavaScript to view this website.</noscript>
    <script>document.body.removeAttribute('no-js');var cdn="";var old=false;
      try { new Function('import("")'); } catch (err) {
        "use strict"; (function () { function a(a, b, c) { var d = a; if (d.state = b, d.stateData = c, 0 < d.onNextStateChange.length) { var e = d.onNextStateChange.slice(); d.onNextStateChange.length = 0; for (var f, g = 0, h = e; g < h.length; g++)f = h[g], f() } return d } function b(b) { function d() { try { document.head.removeChild(f) } catch (a) { } } var e = a(b, "Loading", void 0), f = document.createElement("script"); return f.src = b.url, f.onload = function () { var a, b, f; void 0 === r ? (b = [], f = void 0) : (a = r(), b = a[0], f = a[1]), c(e, b, f), d() }, f.onerror = function () { g(b, new TypeError("Failed to fetch " + b.url)), d() }, document.head.appendChild(f), e } function c(b, c, e) { var f = d(b, c), g = f[0], h = f[1]; return a(b, "WaitingForTurn", { args: g, deps: h, moduleBody: e }) } function d(a, c) { for (var e, f = [], g = [], i = 0, j = c; i < j.length; i++) { if (e = j[i], "exports" === e) { f.push(a.exports); continue } if ("require" === e) { f.push(function (b, c, e) { var f = d(a, b), g = f[0], i = f[1]; h(i, function () { c && c.apply(null, g) }, e) }); continue } if ("meta" === e) { f.push({ url: !0 === a.isTopLevel ? a.url.substring(0, a.url.lastIndexOf("#")) : a.url }); continue } var l = k(n(a.urlBase, e)); f.push(l.exports), g.push(l), "Initialized" === l.state && b(l) } return [f, g] } function e(b) { var c = a(b, "WaitingOnDeps", b.stateData); return h(b.stateData.deps, function () { return f(c) }, function (a) { return g(c, a) }), c } function f(b) { var c = b.stateData; if (null != c.moduleBody) try { c.moduleBody.apply(null, c.args) } catch (a) { return g(b, a) } return a(b, "Executed", void 0) } function g(b, c) { return !0 === b.isTopLevel && setTimeout(function () { throw c }), a(b, "Failed", c) } function h(a, b, c) { var d = a.shift(); return void 0 === d ? void (b && b()) : "WaitingOnDeps" === d.state ? (!1, void h(a, b, c)) : void i(d, function () { h(a, b, c) }, c) } function i(a, b, c) { switch (a.state) { case "WaitingForTurn": return e(a), void i(a, b, c); case "Failed": return void (c && c(a.stateData)); case "Executed": return void b(); case "Loading": case "WaitingOnDeps": return void a.onNextStateChange.push(function () { return i(a, b, c) }); case "Initialized": throw new Error("All dependencies should be loading already before pressureDependencyToExecute is called."); default: throw new Error("Impossible module state: " + a.state); } } function j(a, b) { switch (a.state) { case "Executed": case "Failed": return void b(); default: a.onNextStateChange.push(function () { return j(a, b) }); } } function k(a) { var b = q[a]; return void 0 === b && (b = q[a] = { url: a, urlBase: m(a), exports: Object.create(null), state: "Initialized", stateData: void 0, isTopLevel: !1, onNextStateChange: [] }), b } function l(a) { return v.href = a, v.href } function m(a) { return a = a.split("?")[0], a = a.split("#")[0], a.substring(0, a.lastIndexOf("/") + 1) } function n(a, b) { return -1 === b.indexOf("://") ? l("/" === b[0] ? b : a + b) : b } function o() { return document.baseURI || (document.querySelector("base") || window.location).href } function p() { var b = document.currentScript; if (!b) return u; if (window.HTMLImports) { var c = window.HTMLImports.importForElement(b); return c ? c.href : u } var d = b.ownerDocument.createElement("a"); return d.href = "", d.href } if (!window.define) { var q = Object.create(null), r = void 0, s = 0, t = void 0, u = o(); window.define = function (a, b) { var d = !1; r = function () { return d = !0, r = void 0, [a, b] }; var f = p(); setTimeout(function () { if (!1 == d) { r = void 0; var g = f + "#" + s++, h = k(g); h.isTopLevel = !0; var i = c(h, a, b); void 0 === t ? e(i) : j(k(t), function () { e(i) }), t = g } }, 0) }, window.define._reset = function () { for (var a in q) delete q[a]; r = void 0, s = 0, t = void 0, u = o() }; var v = document.createElement("a") } })();
        var defs = [
          cdn + "build/es6-amd/node_modules/web-animations-js/web-animations-next-lite.min.js",
          cdn + "assets/babel-top.js"
        ];
        if (window.customElements) { // certain FF / Safari versions
          defs.push(cdn + "build/es6-amd/node_modules/@webcomponents/webcomponentsjs/webcomponents-loader.js");
        }
        else { // Edge prior to evergreen
          defs.push(cdn + "build/es6-amd/node_modules/promise-polyfill/dist/polyfill.min.js");
          defs.push(cdn + "build/es6-amd/node_modules/fetch-ie8/fetch.js");
          defs.push(cdn + "build/es6-amd/node_modules/@webcomponents/webcomponentsjs/webcomponents-bundle.js");
        }
        defs.push(cdn + "build/es6-amd/dist/build-home.js");
        define(defs, function () { "use strict" });
        old=true;
      }
      var link = document.createElement('link');
      link.rel = 'stylesheet';
      link.href = 'build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/base.css';
      link.type = 'text/css';
      var def = document.getElementsByTagName('link')[0];
      def.parentNode.insertBefore(link, def);
    </script>
    <script>if(old)document.write('<!--');</script>
    <script type="module">
      import "./build/es6/dist/build-home.js";
    </script>
    <script async src="build/es6/node_modules/web-animations-js/web-animations-next-lite.min.js">
    //<!--! do not remove -->
    </script>
  </body>
</html>