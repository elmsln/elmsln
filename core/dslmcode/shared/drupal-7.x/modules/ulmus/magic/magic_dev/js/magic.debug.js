/**
 * @file
 * Debug functions for the magic_dev module.
 */
(function() {

  // Localstorage Test
  function supports_html5_storage() {
    // Please see https://github.com/Modernizr/Modernizr/blob/master/feature-detects/storage/localstorage.js
    // for details.
    var mod = 'magic';
    try {
      localStorage.setItem(mod, mod);
      localStorage.removeItem(mod);
      return true;
    } catch(e) {
      return false;
    }
  }

  // Viewport Width Display
  function viewport_width() {
    var viewportWidth = document.getElementById('magic-viewport-indicator');
    var widthPX = window.innerWidth;
    var widthEM = widthPX / 16;

    if (supports_html5_storage()) {
      var viewportStatus = localStorage.getItem("MagicViewportStorage");

      if (viewportStatus == 'px') {
        viewportWidth.innerHTML = widthPX + 'px';
      }
      else if (viewportStatus == 'em') {
        viewportWidth.innerHTML = widthEM + 'em';
      }
      else {
        viewportWidth.html = widthEM + 'em';
        localStorage.setItem("MagicViewportStorage", 'em');
      }
    }
    else {
      viewportWidth.html = widthEM + 'em';
    }
  }

  function modernizr_debug() {
    var modernizrDebug = document.getElementById('magic-modernizr-debug');

    if (supports_html5_storage()) {
      var modernizrStatus = localStorage.getItem("MagicModernizrStorage");

      if (modernizrStatus == 'open') {
        removeClass(modernizrDebug, 'closed');
        addClass(modernizrDebug, 'open');
      }
      else if (modernizrStatus == 'closed') {
        removeClass(modernizrDebug, 'open');
        addClass(modernizrDebug, 'closed');
      }
    }
  }

  window.onload = function() {
    viewport_width();

    var viewportWidth = document.getElementById('magic-viewport-indicator');
    var modernizrDebug = document.getElementById('magic-modernizr-debug');

    // Viewport Event Listener
    viewportWidth.addEventListener('click', function() {
      if (supports_html5_storage()) {
        var viewportStatus = localStorage.getItem("MagicViewportStorage");

        if (viewportStatus == 'px') {
          localStorage.setItem("MagicViewportStorage", 'em');
        }
        else if (viewportStatus == 'em') {
          localStorage.setItem("MagicViewportStorage", 'px');
        }

        viewport_width();
      }
    });

    // Modernizr Event Listener
    if (modernizrDebug) {
      modernizrDebug.innerHTML = document.getElementsByTagName('html')[0].classList;

      var modernizrStatus = localStorage.getItem("MagicModernizrStorage");

      if (modernizrStatus == 'closed') {
        removeClass(modernizrDebug, 'open');
        addClass(modernizrDebug, 'closed');
      }

      modernizrDebug.addEventListener('click', function() {
        var modernizrStatus = localStorage.getItem("MagicModernizrStorage");

        if (modernizrStatus == 'closed') {
          localStorage.setItem("MagicModernizrStorage", 'open');
        }
        else {
          localStorage.setItem("MagicModernizrStorage", 'closed');
        }

        modernizr_debug();
      });
    }
  };

  window.onresize = debounce(function() {
    viewport_width();
  }, 20);

  // Returns a function, that, as long as it continues to be invoked, will not
  // be triggered. The function will be called after it stops being called for N
  // milliseconds. If `immediate` is passed, trigger the function on the leading
  // edge, instead of the trailing.
  function debounce(func, wait, immediate) {
    var timeout;
    return function() {
      var context = this, args = arguments;
      var later = function() {
        timeout = null;
        if (!immediate) func.apply(context, args);
      }
      var callNow = immediate && !timeout;
      clearTimeout(timeout);
      timeout = setTimeout(later, wait);
      if (callNow) func.apply(context, args);
    }
  }

  // From http://www.avoid.org/?p=78
  function hasClass(el, name) {
   return new RegExp('(\\s|^)'+name+'(\\s|$)').test(el.className);
  }

  // From http://stackoverflow.com/questions/2155737/remove-css-class-from-element-with-javascript-no-jquery
  function removeClass(ele,cls) {
    if (hasClass(ele,cls)) {
      var reg = new RegExp('(\\s|^)'+cls+'(\\s|$)');
      ele.className=ele.className.replace(reg,' ');
    }
  }

  // From http://www.avoid.org/?p=78
  function addClass(el, name) {
   if (!hasClass(el, name)) { el.className += (el.className ? ' ' : '') +name; }
  }

})();
