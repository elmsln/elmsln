/**
 *
 */
var H5P = H5P || (function () {
  var head = document.getElementsByTagName('head')[0];
  var contentId = 0;
  var contents = {};
  
  /**
   * Wraps multiple content between a prefix and a suffix.
   */
  var wrap = function (prefix, content, suffix) {
    var result = '';
    for (var i = 0; i < content.length; i++) {
      result += prefix + content[i] + suffix;
    }
    return result;
  };
  
  /**
   * 
   */
  var loadContent = function (id, script) {
    var url = script.getAttribute('data-h5p');
    var data, callback = 'H5P' + id;
    
    // Prevent duplicate loading.
    script.removeAttribute('data-h5p');
    
    // Callback for when content data is loaded.
    window[callback] = function (content) {
      contents[id] = content;
      
      var iframe = document.createElement('iframe');
      var parent = script.parentNode;
      parent.insertBefore(iframe, script);
      
      iframe.id = 'h5p-iframe-' + id;
      iframe.style.display = 'block';
      iframe.style.width = '100%';
      iframe.style.height = '1px';
      iframe.style.border = 'none';
      iframe.style.zIndex = 101;
      iframe.style.top = 0;
      iframe.style.left = 0;
      iframe.className = 'h5p-iframe';
      iframe.setAttribute('frameBorder', '0');
      iframe.contentDocument.open();
      iframe.contentDocument.write('\
        <!doctype html><html class="h5p-iframe">\
        <head>\
          <script>\
            var H5PIntegration = window.parent.H5P.getIntegration(' + id + ');\
          </script>\
          ' + wrap('<link rel="stylesheet" href="', content.styles, '">') + '\
          ' + wrap('<script src="', content.scripts, '"></script>') + '\
        </head><body>\
          <div class="h5p-content" data-class="' + content.library + '" data-content-id="' + id + '"/>\
        </body></html>');
      iframe.contentDocument.close();
      iframe.contentDocument.documentElement.style.overflow = 'hidden';
      
      // Clean up
      parent.removeChild(script);
      head.removeChild(data);
      delete window[callback];
    };
    
    // Create data script
    data = document.createElement('script');
    data.src = url + (url.indexOf('?') === -1 ? '?' : '&') + 'callback=' + callback;
    head.appendChild(data);
  };
  
  /**
   * Go throught all script tags with the data-h5p attribute and load content.
   */
  function H5P() {
    var scripts = document.getElementsByTagName('script');
    var h5ps = []; // Use seperate array since scripts grow in size.
    for (var i = 0; i < scripts.length; i++) {
      var script = scripts[i];
      if (script.hasAttribute('data-h5p')) {
        h5ps.push(script);
      }
    }
    for (i = 0; i < h5ps.length; i++) {
      loadContent(contentId, h5ps[i]);
      contentId++;
    }
  };
  
  /**
   * Return integration object
   */
  H5P.getIntegration = function (id) {
    var content = contents[id];
    return {
      getJsonContent: function () {
        return content.params;
      },
      getContentPath: function () {
        return content.path + 'content/' + content.id + '/';
      },
      getFullscreen: function () {
        return content.fullscreen;
      },
      getLibraryPath: function (library) {
        return content.path + 'libraries/' + library;
      },
      getContentData: function () {
        return {
          library: content.library,
          jsonContent: content.params,
          fullScreen: content.fullscreen,
          exportUrl: content.exportUrl,
          embedCode: content.embedCode
        };
      },
      i18n: content.i18n,
      showH5PIconInActionBar: function () {
        // Always show H5P-icon when embedding
        return true;
      }
    };
  };
  
  // Detect if we support fullscreen, and what prefix to use.
  var fullScreenBrowserPrefix, safariBrowser;
  if (document.documentElement.requestFullScreen) {
    fullScreenBrowserPrefix = '';
  }
  else if (document.documentElement.webkitRequestFullScreen
      && navigator.userAgent.indexOf('Android') === -1 // Skip Android
      ) {
    safariBrowser = navigator.userAgent.match(/Version\/(\d)/);
    safariBrowser = (safariBrowser === null ? 0 : parseInt(safariBrowser[1]));

    // Do not allow fullscreen for safari < 7.
    if (safariBrowser === 0 || safariBrowser > 6) {
      fullScreenBrowserPrefix = 'webkit';
    }
  }
  else if (document.documentElement.mozRequestFullScreen) {
    fullScreenBrowserPrefix = 'moz';
  }
  else if (document.documentElement.msRequestFullscreen) {
    fullScreenBrowserPrefix = 'ms';
  }

  /**
   * Enter fullscreen mode.
   */
  H5P.fullScreen = function ($element, instance, exitCallback, body) {
    var iframe = document.getElementById('h5p-iframe-' + $element.parent().data('content-id'));
    var $classes = $element.add(body);
    var $body = $classes.eq(1);
    
    /**
      * Prepare for resize by setting the correct styles.
      * 
      * @param {String} classes CSS
      */
     var before = function (classes) {
       $classes.addClass(classes);
       iframe.style.height = '100%';
     };

     /**
      * Gets called when fullscreen mode has been entered.
      * Resizes and sets focus on content.
      */
     var entered = function () {
       // Do not rely on window resize events.
       instance.$.trigger('resize');
       instance.$.trigger('focus');
     };

     /**
      * Gets called when fullscreen mode has been exited.
      * Resizes and sets focus on content.
      * 
      * @param {String} classes CSS
      */
     var done = function (classes) {
       H5P.isFullscreen = false;
       $classes.removeClass(classes);

       // Do not rely on window resize events.
       instance.$.trigger('resize');
       instance.$.trigger('focus');

       if (exitCallback !== undefined) {
         exitCallback();
       }
     };

    H5P.isFullscreen = true;
    if (fullScreenBrowserPrefix === undefined) {
      // Create semi fullscreen.

      before('h5p-semi-fullscreen');
      iframe.style.position = 'fixed';
      
      var $disable = $element.prepend('<a href="#" class="h5p-disable-fullscreen" title="Disable fullscreen"></a>').children(':first');
      var keyup, disableSemiFullscreen = function () {
        $disable.remove();      
        $body.unbind('keyup', keyup);
        iframe.style.position = 'static';
        done('h5p-semi-fullscreen');
        return false;
      };
      keyup = function (event) {
        if (event.keyCode === 27) {
          disableSemiFullscreen();
        }
      };
      $disable.click(disableSemiFullscreen);
      $body.keyup(keyup); // TODO: Does not work with iframe's $!
      entered();
    }
    else {
      // Create real fullscreen.

      before('h5p-fullscreen');
      var first, eventName = (fullScreenBrowserPrefix === 'ms' ? 'MSFullscreenChange' : fullScreenBrowserPrefix + 'fullscreenchange');
      document.addEventListener(eventName, function () {
        if (first === undefined) {
          // We are entering fullscreen mode
          first = false;
          entered();
          return;
        }

        // We are exiting fullscreen
        done('h5p-fullscreen');
        document.removeEventListener(eventName, arguments.callee, false);
      });

      if (fullScreenBrowserPrefix === '') {
        iframe.requestFullScreen();
      }
      else {
        var method = (fullScreenBrowserPrefix === 'ms' ? 'msRequestFullscreen' : fullScreenBrowserPrefix + 'RequestFullScreen');
        var params = (fullScreenBrowserPrefix === 'webkit' && safariBrowser === 0 ? Element.ALLOW_KEYBOARD_INPUT : undefined);
        iframe[method](params);
      }
    }
  };
  
  return H5P;
})();

new H5P();
