var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Construct the editor.
 *
 * @param {String} library
 * @param {Object} defaultParams
 * @returns {H5peditor}
 */
ns.Editor = function (library, defaultParams, replace) {
  var self = this;

  // Create iframe and replace the given element with it
  var height = 1;
  var iframe = ns.$('<iframe/>', {
    css: {
      display: 'block',
      width: '100%',
      height: height + 'px',
      border: 'none',
      zIndex: 101,
      top: 0,
      left: 0
    },
    'class': 'h5p-editor-iframe',
    frameBorder: '0'
  }).replaceAll(replace).load(function () {
    var $ = this.contentWindow.H5P.jQuery;
    var LibrarySelector = this.contentWindow.H5PEditor.LibrarySelector;
    this.contentWindow.H5P.$body = $(this.contentDocument.body);

    var $container = $('body > .h5p-editor');

    // Load libraries list
    $.ajax({
      dataType: 'json',
      url: ns.getAjaxUrl('libraries')
    }).fail(function () {
      $container.html('Error, unable to load libraries.');
    }).done(function (data) {
      self.selector = new LibrarySelector(data, library, defaultParams);
      self.selector.appendTo($container.html(''));
      if (library) {
        self.selector.$selector.change();
      }
    });
    
    // Start resizing the iframe
    if (iframe.contentWindow.MutationObserver !== undefined) {
      // If supported look for changes to DOM elements. This saves resources.
      var running;
      var limitedResize = function (mutations) {
        if (!running) {
          running = setTimeout(function () {
            resize();
            running = null;
          }, 40); // 25 fps cap
        }
      };
      
      new iframe.contentWindow.MutationObserver(limitedResize).observe(iframe.contentWindow.document.body, {
        childList: true,
        attributes: true,
        characterData: true,
        subtree: true,
        attributeOldValue: false,
        characterDataOldValue: false
      });
      H5P.$window.resize(limitedResize);
    }
    else {
      // Use an interval for resizing the iframe
      (function resizeInterval() {
        resize();
        setTimeout(resizeInterval, 40); // No more than 25 times per second
      })();
    }
  }).get(0);
  
  iframe.contentDocument.open();
  iframe.contentDocument.write('\
    <!doctype html><html>\
    <head>\
      ' + ns.wrap('<link rel="stylesheet" href="' + ns.baseUrl, ns.assets.css, '">') + '\
      ' + ns.wrap('<script src="' + ns.baseUrl, ns.assets.js, '"></script>') + '\
    </head><body>\
      <div class="h5p-editor">' + ns.t('core', 'loading', {':type': 'libraries'}) + '</div>\
    </body></html>');
  iframe.contentDocument.close();
  iframe.contentDocument.documentElement.style.overflow = 'hidden';
  
  /**
   * Private. Checks if iframe needs resizing, and then resize it.
   */
  var resize = function () {
    if (iframe.contentWindow.document.body.clientHeight === height) {
      return; // Prevent resize if we're the same size
    }
    
    // Use clientHeight to keep track of the actual body height since scrollHeight doesn't decrease
    height = iframe.contentWindow.document.body.clientHeight;

    // Retain parent size to avoid jumping/scrolling
    var parentHeight = iframe.parentElement.style.height;
    iframe.parentElement.style.height = iframe.parentElement.clientHeight + 'px'; 

    // Reset iframe height, in case content has shrinked.
    iframe.style.height = '1px';

    // Resize iframe so all content is visible. Use scrollHeight to make sure we get everything
    iframe.style.height = (iframe.contentDocument.body.scrollHeight) + 'px';

    // Free parent
    iframe.parentElement.style.height = parentHeight;
  };
};

/**
 * Return library used.
 */
ns.Editor.prototype.getLibrary = function () {
  if (this.selector !== undefined) {
    return this.selector.$selector.val();
  }
};

/**
 * Return params needed to start library.
 */
ns.Editor.prototype.getParams = function () {
  if (this.selector !== undefined) {
    return this.selector.getParams();
  }
};

ns.language = {};

/**
 * Translate text strings.
 *
 * @param {String} library
 *  library machineName, or "core"
 * @param {String} key
 * @param {Object} vars
 * @returns {String|@exp;H5peditor@call;t}
 */
ns.t = function (library, key, vars) {
  if (ns.language[library] === undefined) {
    return 'Missing translations for library ' + library;
  }

  if (library === 'core') {
    if (ns.language[library][key] === undefined) {
      return 'Missing translation for ' + key;
    }
    var translation = ns.language[library][key];
  }
  else {
    if (ns.language[library]['libraryStrings'] === undefined || ns.language[library]['libraryStrings'][key] === undefined) {
      return ns.t('core', 'missingTranslation', {':key': key});
    }
    var translation = ns.language[library]['libraryStrings'][key];
  }

  // Replace placeholder with variables.
  for (var placeholder in vars) {
    translation = translation.replace(placeholder, vars[placeholder]);
  }

  return translation;
};

/**
 * Wraps multiple content between a prefix and a suffix.
 */
ns.wrap = function (prefix, content, suffix) {
  var result = '';
  for (var i = 0; i < content.length; i++) {
    result += prefix + content[i] + suffix;
  }
  return result;
};