// HAXcms specific clean up and platforn integration
// this ties in custom theme files as well as removes DOM nodes related
// to serving a legacy audience in the event this is evergreen (most times)
var def = document.getElementsByTagName('script')[0];
try {
    // if a dynamic import fails, we bail over to the compiled version
    new Function('import("");');
    // remove fallback cause if we passed dynamic import then we are evergreen
    if (document.getElementById("haxcmsoutdatedfallback")) {
      document.body.removeChild(document.getElementById("haxcmsoutdatedfallback"));
    }
    var build2 = document.createElement('script');
    build2.src = './custom/build/custom.es6.js';
    build2.type = 'module';
    def.parentNode.insertBefore(build2, def);
  } catch (err) {
    var ancient=false;
    try {
      if (typeof Symbol == "undefined") { // IE 11, at least try to serve a watered down site
        ancient = true;
      }
      new Function('let a;'); // bizarre but needed for Safari 9 bc of when it was made
    }
    catch (err) {
      ancient = true;
    }
    if (!ancient) {
      if (document.getElementById("haxcmsoutdatedfallbacksuperold")) {
        document.getElementById('haxcmsoutdatedfallbacksuperold').style.display = 'none';
      }
      var defs;
      // FF 6x.x can be given ES6 compliant code safely
      if (/Firefox\/6/.test(navigator.userAgent) || window.customElements) {
        defs = [
          "./custom/build/custom.es6-amd.js"
        ];
      }
      else {
        if (document.documentMode || /Edge/.test(navigator.userAgent)) { // stupid edge
          defs.push(cdn + "build/es5-amd/dist/build-legacy.js");
        }
      }
      define(defs, function () { "use strict" });
    }
    else {
      // we bombed somewhere above, this implies that it's some odd between version
      // most likely Safari 9ish, IE pre 11 and anything uber old. Serve no JS variation
      if (document.getElementById('site')) {
        document.getElementById('site').style.display = 'none';
        document.getElementById('haxcmsoutdatedfallbacksuperold').style.display = 'block';
        var path = window.location.href.substr(window.location.href.lastIndexOf('/') + 1);
        if (path) {
          document.getElementById('content').src = 'pages/' + path + '/index.html';
        }
      }
    }
  }
  // css files load faster when implemented this way
  var link = document.createElement('link');
  link.rel = 'stylesheet';
  link.href = cdn + 'build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/base.css';
  link.type = 'text/css';
  def.parentNode.insertBefore(link, def);
  var link2 = document.createElement('link');
  link2.rel = 'stylesheet';
  link2.href = './theme/theme.css';
  link2.type = 'text/css';
  def.parentNode.insertBefore(link2, def);