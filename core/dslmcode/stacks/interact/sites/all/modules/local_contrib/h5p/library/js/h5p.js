// TODO: Should we split up the generic parts needed by the editor(and others), and the parts needed to "run" H5Ps?
var H5P = H5P || {};

// Determine if we're inside an iframe.
H5P.isFramed = (window.self !== window.top);

// Useful jQuery object.
H5P.$window = H5P.jQuery(window);

// Detect if we support fullscreen, and what prefix to use.
if (document.documentElement.requestFullScreen) {
  H5P.fullScreenBrowserPrefix = '';
}
else if (document.documentElement.webkitRequestFullScreen
    && navigator.userAgent.indexOf('Android') === -1 // Skip Android
    ) {
  H5P.safariBrowser = navigator.userAgent.match(/Version\/(\d)/);
  H5P.safariBrowser = (H5P.safariBrowser === null ? 0 : parseInt(H5P.safariBrowser[1]));
  
  // Do not allow fullscreen for safari < 7.
  if (H5P.safariBrowser === 0 || H5P.safariBrowser > 6) {
    H5P.fullScreenBrowserPrefix = 'webkit';
  }
}
else if (document.documentElement.mozRequestFullScreen) {
  H5P.fullScreenBrowserPrefix = 'moz';
}
else if (document.documentElement.msRequestFullscreen) {
  H5P.fullScreenBrowserPrefix = 'ms';
}

/**
 * Initialize H5P content.
 * Scans for ".h5p-content" in the document and initializes H5P instances where found.
 */
H5P.init = function () {
  // Useful jQuery object.
  H5P.$body = H5P.jQuery(document.body);

  // Prepare internal resizer for content.
  var $window = H5P.jQuery(window.parent);

  // H5Ps added in normal DIV.
  var $containers = H5P.jQuery(".h5p-content").each(function () {
    var $element = H5P.jQuery(this);
    var $container = H5P.jQuery('<div class="h5p-container"></div>').appendTo($element);
    var contentId = $element.data('content-id');
    var contentData = H5PIntegration.getContentData(contentId);
    if (contentData === undefined) {
      return H5P.error('No data for content id ' + contentId + '. Perhaps the library is gone?');
    }
    var library = {
      library: contentData.library,
      params: JSON.parse(contentData.jsonContent)
    };

    // Create new instance.
    var instance = H5P.newRunnable(library, contentId, $container, true);
    
    // Check if we should add and display a fullscreen button for this H5P.
    if (contentData.fullScreen == 1) {
      H5P.jQuery('<div class="h5p-content-controls"><div role="button" tabindex="1" class="h5p-enable-fullscreen" title="' + H5P.t('fullscreen') + '"></div></div>').prependTo($container).children().click(function () {
        H5P.fullScreen($container, instance);
      });
    };
    
    var $actions = H5P.jQuery('<ul class="h5p-actions"></ul>');
    if (contentData.exportUrl !== '') {
      // Display export button
      H5P.jQuery('<li class="h5p-button h5p-export" role="button" tabindex="1" title="' + H5P.t('downloadDescription') + '">' + H5P.t('download') + '</li>').appendTo($actions).click(function () {
        window.location.href = contentData.exportUrl;
      });
    }
    if (instance.getCopyrights !== undefined) {
      // Display copyrights button
      H5P.jQuery('<li class="h5p-button h5p-copyrights" role="button" tabindex="1" title="' + H5P.t('copyrightsDescription') + '">' + H5P.t('copyrights') + '</li>').appendTo($actions).click(function () {
        H5P.openCopyrightsDialog($actions, instance);
      });
    }
    if (contentData.embedCode !== undefined) {
      // Display embed button
      H5P.jQuery('<li class="h5p-button h5p-embed" role="button" tabindex="1" title="' + H5P.t('embedDescription') + '">' + H5P.t('embed') + '</li>').appendTo($actions).click(function () {
        H5P.openEmbedDialog($actions, contentData.embedCode);
      });
    }
    if (H5PIntegration.showH5PIconInActionBar()) {
      H5P.jQuery('<li><a class="h5p-link" href="http://h5p.org" target="_blank" title="' + H5P.t('h5pDescription') + '"></a></li>').appendTo($actions);
    }
    $actions.insertAfter($container);
    
    if (H5P.isFramed) {
      // Make it possible to resize the iframe when the content changes size. This way we get no scrollbars.
      var iframe = window.parent.document.getElementById('h5p-iframe-' + contentId);
      var resizeIframe = function () {
        if (window.parent.H5P.isFullscreen) {
          return; // Skip if full screen.
        }
        
        // Retain parent size to avoid jumping/scrolling
        var parentHeight = iframe.parentElement.style.height;
        iframe.parentElement.style.height = iframe.parentElement.clientHeight + 'px'; 

        // Reset iframe height, in case content has shrinked.
        iframe.style.height = '1px';

        // Resize iframe so all content is visible.
        iframe.style.height = (iframe.contentDocument.body.scrollHeight) + 'px';

        // Free parent
        iframe.parentElement.style.height = parentHeight;
      };
      
      var resizeDelay;
      instance.$.on('resize', function () {
        // Use a delay to make sure iframe is resized to the correct size.
        clearTimeout(resizeDelay);
        resizeDelay = setTimeout(function () {
          resizeIframe();
        }, 1);
      });
    }
    
    // Resize everything when window is resized.
    $window.resize(function () {
      if (window.parent.H5P.isFullscreen) {
        // Use timeout to avoid bug in certain browsers when exiting fullscreen. Some browser will trigger resize before the fullscreenchange event.
          instance.$.trigger('resize');
      }
      else {
        instance.$.trigger('resize');
      }
    });
    
    // Resize content.
    instance.$.trigger('resize');
  });

  // Insert H5Ps that should be in iframes.
  H5P.jQuery("iframe.h5p-iframe").each(function () {
    var contentId = H5P.jQuery(this).data('content-id');
    this.contentDocument.open();
    this.contentDocument.write('<!doctype html><html class="h5p-iframe"><head>' + H5PIntegration.getHeadTags(contentId) + '</head><body><div class="h5p-content" data-content-id="' + contentId + '"/></body></html>');
    this.contentDocument.close();
  });
};

/**
 * Enable full screen for the given h5p.
 *
 * @param {jQuery} $element Content container.
 * @param {object} instance
 * @param {function} exitCallback Callback function called when user exits fullscreen.
 * @param {jQuery} $body For internal use. Gives the body of the iframe.
 * @returns {undefined}
 */
H5P.fullScreen = function ($element, instance, exitCallback, body) {
  if (H5P.isFramed) {
    // Trigger resize on wrapper in parent window.
    window.parent.H5P.fullScreen($element, instance, exitCallback, H5P.$body.get());
    return;
  }
  
  var $container = $element;
  var $classes, $iframe;
  if (body === undefined)  {
    $body = H5P.$body;
  }
  else {
    // We're called from an iframe.
    $body = H5P.jQuery(body);
    $classes = $body.add($element.get());
    var iframeSelector = '#h5p-iframe-' + $element.parent().data('content-id');
    $iframe = H5P.jQuery(iframeSelector);
    $element = $iframe.parent(); // Put iframe wrapper in fullscreen, not container.
  }
  
  $classes = $element.add(H5P.$body).add($classes);
  
  /**
   * Prepare for resize by setting the correct styles.
   * 
   * @param {String} classes CSS
   */
  var before = function (classes) {
    $classes.addClass(classes);
    
    if ($iframe !== undefined) {
      // Set iframe to its default size(100%).
      $iframe.css('height', '');
    }
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
  if (H5P.fullScreenBrowserPrefix === undefined) {
    // Create semi fullscreen.
    
    before('h5p-semi-fullscreen');
    var $disable = H5P.jQuery('<div role="button" tabindex="1" class="h5p-disable-fullscreen" title="' + H5P.t('disableFullscreen') + '"></div>').appendTo($container.find('.h5p-content-controls'));
    var keyup, disableSemiFullscreen = function () {
      $disable.remove();      
      $body.unbind('keyup', keyup);
      done('h5p-semi-fullscreen');
    };
    keyup = function (event) {
      if (event.keyCode === 27) {
        disableSemiFullscreen();
      }
    };
    $disable.click(disableSemiFullscreen);
    $body.keyup(keyup);
    entered();
  }
  else {
    // Create real fullscreen.
    
    before('h5p-fullscreen');
    var first, eventName = (H5P.fullScreenBrowserPrefix === 'ms' ? 'MSFullscreenChange' : H5P.fullScreenBrowserPrefix + 'fullscreenchange');
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

    if (H5P.fullScreenBrowserPrefix === '') {
      $element[0].requestFullScreen();
    }
    else {
      var method = (H5P.fullScreenBrowserPrefix === 'ms' ? 'msRequestFullscreen' : H5P.fullScreenBrowserPrefix + 'RequestFullScreen');
      var params = (H5P.fullScreenBrowserPrefix === 'webkit' && H5P.safariBrowser === 0 ? Element.ALLOW_KEYBOARD_INPUT : undefined);
      $element[0][method](params);
    }
  }
};

/**
 * Find the path to the content files based on the id of the content
 *
 * Also identifies and returns absolute paths
 *
 * @param string path
 *  Absolute path to a file, or relative path to a file in the content folder
 * @param contentId
 *  Id of the content requesting a path
 */
H5P.getPath = function (path, contentId) {
  var hasProtocol = function (path) {
    return path.match(/^[a-z0-9]+:\/\//i);
  };
  
  if (hasProtocol(path)) {
    return path;
  }
  
  if (contentId !== undefined) {
    prefix = H5PIntegration.getContentPath(contentId);
  }
  else if (window['H5PEditor'] !== undefined) {
    prefix = H5PEditor.filesPath;
  }
  else {
    return;
  }
  
  if (!hasProtocol(prefix)) {
    prefix = window.parent.location.protocol + "//" + window.parent.location.host + prefix;
  }
  
  return prefix + '/' + path; 
};

/**
 * THIS FUNCTION IS DEPRECATED, USE getPath INSTEAD
 *
 *  Find the path to the content files folder based on the id of the content
 *
 *  @param contentId
 *  Id of the content requesting a path
 */
H5P.getContentPath = function (contentId) {
  return H5PIntegration.getContentPath(contentId);
};

/**
 * Get library class constructor from H5P by classname.
 * Note that this class will only work for resolve "H5P.NameWithoutDot". 
 * Also check out: H5P.newRunnable
 *
 * Used from libraries to construct instances of other libraries' objects by name.
 *
 * @param {string} name Name of library
 * @returns Class constructor
 */
H5P.classFromName = function (name) {
  var arr = name.split(".");
  return this[arr[arr.length-1]];
};

/**
 * A safe way of creating a new instance of a runnable H5P.
 *
 * TODO: Should we check if version matches the library?
 * TODO: Dynamically try to load libraries currently not loaded? That will require a callback.
 * 
 * @param {Object} library Library/action object form params.
 * @param {Number} contentId 
 * @param {jQuery} $attachTo An optional element to attach the instance to.
 * @param {Boolean} skipResize Optionally skip triggering of the resize event after attaching.
 * @return {Object} Instance.
 */
H5P.newRunnable = function (library, contentId, $attachTo, skipResize) {
  try {
    var nameSplit = library.library.split(' ', 2);
    var versionSplit = nameSplit[1].split('.', 2);
  }
  catch (err) {
    return H5P.error('Invalid library string: ' + library.library);
  }
  
  if ((library.params instanceof Object) !== true || (library.params instanceof Array) === true) {
    H5P.error('Invalid library params for: ' + library.library);
    return H5P.error(library.params);
  }
  
  // Find constructor function
  try {
    nameSplit = nameSplit[0].split('.');
    var constructor = window;
    for (var i = 0; i < nameSplit.length; i++) { 
      constructor = constructor[nameSplit[i]];
    };
    if (typeof constructor !== 'function') {
      throw null;
    }
  }
  catch (err) {
    return H5P.error('Unable to find constructor for: ' + library.library);
  }
  
  var instance = new constructor(library.params, contentId);
  
  if (instance.$ === undefined) {
    instance.$ = H5P.jQuery(instance);
  }
  
  if ($attachTo !== undefined) {
    instance.attach($attachTo);
    
    if (skipResize === undefined || !skipResize) {
      // Resize content.
      instance.$.trigger('resize');
    }
  }
  return instance;
};

/**
 * Used to print useful error messages.
 *
 * @param {mixed} err Error to print.
 * @returns {undefined}
 */
H5P.error = function (err) {
  if (window['console'] !== undefined && console.error !== undefined) {
    console.error(err);
  }
};

/**
 * Translate text strings.
 *
 * @param {String} key Translation identifier, may only contain a-zA-Z0-9. No spaces or special chars.
 * @param {Object} vars Data for placeholders.
 * @param {String} ns Translation namespace. Defaults to H5P.
 * @returns {String} Text
 */
H5P.t = function (key, vars, ns) {
  if (ns === undefined) {
    ns = 'H5P';
  }

  if (H5PIntegration.i18n[ns] === undefined) {
    return '[Missing translation namespace "' + ns + '"]';
  }
  
  if (H5PIntegration.i18n[ns][key] === undefined) {
    return '[Missing translation "' + key + '" in "' + ns + '"]';
  }

  var translation = H5PIntegration.i18n[ns][key];
  
  if (vars !== undefined) {
    // Replace placeholder with variables.
    for (var placeholder in vars) {
      translation = translation.replace(placeholder, vars[placeholder]);
    }  
  }

  return translation;
};

H5P.Dialog = function (name, title, content, $element) {
  var self = this;
  var $dialog = H5P.jQuery('<div class="h5p-popup-dialog h5p-' + name + '-dialog">\
                              <div class="h5p-inner">\
                                <h2>' + title + '</h2>\
                                <div class="h5p-scroll-content">' + content + '</div>\
                                <div class="h5p-close" role="button" tabindex="1" title="' + H5P.t('close') + '">\
                              </div>\
                            </div>')
    .insertAfter($element)
    .click(function () {
      self.close();
    })
    .children('.h5p-inner')
      .click(function () {
        return false;
      })
      .find('.h5p-close')
        .click(function () {
          self.close();
        })
        .end()
      .end();
    
  this.open = function () {
    setTimeout(function () {
      $dialog.addClass('h5p-open'); // Fade in
      // Triggering an event, in case something has to be done after dialog has been opened.
      H5P.jQuery(self).trigger('dialog-opened', [$dialog]);
    }, 1);
  };
  
  this.close = function () {
    $dialog.removeClass('h5p-open'); // Fade out
    setTimeout(function () {
      $dialog.remove();
    }, 200);
  };
};

/**
 * Gather copyright information and display in a dialog over the content.
 *
 * @param {jQuery} $element to insert dialog after.
 * @param {object} instance to get copyright information from.
 * @returns {undefined}
 */
H5P.openCopyrightsDialog = function ($element, instance) {
  var copyrights = instance.getCopyrights();
  if (copyrights !== undefined) {
    copyrights = copyrights.toString();
  }
  if (copyrights === undefined || copyrights === '') {
    copyrights = H5P.t('noCopyrights');
  }
  
  var dialog = new H5P.Dialog('copyrights', H5P.t('copyrightInformation'), copyrights, $element);
  dialog.open();
};

/**
 * Display a dialog containing the embed code.
 *
 * @param {jQuery} $element to insert dialog after.
 * @param {string} embed code.
 * @returns {undefined}
 */
H5P.openEmbedDialog = function ($element, embedCode) {
  var dialog = new H5P.Dialog('embed', H5P.t('embed'), '<textarea class="h5p-embed-code-container">' + embedCode + '</textarea>', $element);
  
  // Selecting embed code when dialog is opened
  H5P.jQuery(dialog).on('dialog-opened', function (event, $dialog) {
    $dialog.find('.h5p-embed-code-container').select();
  });
  
  dialog.open();
};

/**
 * Copyrights for a H5P Content Library.
 */
H5P.ContentCopyrights = function () {
  var label;
  var media = [];
  var content = [];
  
  /**
   * Public. Set label.
   *
   * @param {String} newLabel
   */
  this.setLabel = function (newLabel) {
    label = newLabel;
  };
  
  /**
   * Public. Add sub content.
   *
   * @param {H5P.MediaCopyright} newMedia
   */
  this.addMedia = function (newMedia) {
    if (newMedia !== undefined) {
      media.push(newMedia);
    }
  };
  
  /**
   * Public. Add sub content.
   *
   * @param {H5P.ContentCopyrights} newContent
   */
  this.addContent = function (newContent) {
    if (newContent !== undefined) {
      content.push(newContent);
    }
  };
  
  /**
   * Public. Print content copyright.
   *
   * @returns {String} HTML.
   */
  this.toString = function () {
    var html = '';
  
    // Add media rights
    for (var i = 0; i < media.length; i++) {
      html += media[i];
    }
    
    // Add sub content rights
    for (var i = 0; i < content.length; i++) {
      html += content[i];
    }
    
    
    if (html !== '') {
      // Add a label to this info
      if (label !== undefined) {
        html = '<h3>' + label + '</h3>' + html;
      }
      
      // Add wrapper
      html = '<div class="h5p-content-copyrights">' + html + '</div>';
    }
    
    return html;
  };
};

/**
 * A ordered list of copyright fields for media.
 *
 * @param {Object} copyright information fields.
 * @param {Object} labels translation.  Optional.
 * @param {Array} order of fields. Optional.
 * @param {Object} extraFields for copyright. Optional.
 */
H5P.MediaCopyright = function (copyright, labels, order, extraFields) {
  var thumbnail;
  var list = new H5P.DefinitionList();
  
  /**
   * Private. Get translated label for field.
   *
   * @param {String} fieldName
   * @return {String} 
   */
  var getLabel = function (fieldName) {
    if (labels === undefined || labels[fieldName] === undefined) {
      return H5P.t(fieldName);
    }
    
    return labels[fieldName];
  };
  
  /**
   * Private. Get humanized value for field.
   *
   * @param {String} fieldName
   * @return {String} 
   */
  var humanizeValue = function (fieldName, value) {
    if (fieldName === 'license') {
      return H5P.copyrightLicenses[value];
    }
    
    return value;
  };
  
  if (copyright !== undefined) {
    // Add the extra fields
    for (var field in extraFields) {
      if (extraFields.hasOwnProperty(field)) {
        copyright[field] = extraFields[field];
      }
    }
    
    if (order === undefined) {
      // Set default order
      order = ['title', 'author', 'year', 'source', 'license'];
    }
    
    for (var i = 0; i < order.length; i++) {
      var fieldName = order[i];
      if (copyright[fieldName] !== undefined) {
        list.add(new H5P.Field(getLabel(fieldName), humanizeValue(fieldName, copyright[fieldName])));
      }
    }
  }
  
  /**
   * Public. Set thumbnail.
   *
   * @param {H5P.Thumbnail} newThumbnail
   */
  this.setThumbnail = function (newThumbnail) {
    thumbnail = newThumbnail;
  };
  
  /**
   * Public. Checks if this copyright is undisclosed.
   * I.e. only has the license attribute set, and it's undisclosed.
   *
   * @returns {Boolean}
   */
  this.undisclosed = function () {
    if (list.size() === 1) {
      var field = list.get(0);
      if (field.getLabel() === getLabel('license') && field.getValue() === humanizeValue('license', 'U')) {
        return true;
      }
    }
    return false;
  };
  
  /**
   * Public. Print media copyright.
   *
   * @returns {String} HTML.
   */
  this.toString = function () {
    var html = '';
    
    if (this.undisclosed()) {
      return html; // No need to print a copyright with a single undisclosed license.
    }
    
    if (thumbnail !== undefined) {
      html += thumbnail;
    }
    html += list;
    
    if (html !== '') {
      html = '<div class="h5p-media-copyright">' + html + '</div>';
    }
    
    return html;
  };
};

// Translate table for copyright license codes.
H5P.copyrightLicenses = {
  'U': 'Undisclosed',
  'CC BY': 'Attribution',
  'CC BY-SA': 'Attribution-ShareAlike',
  'CC BY-ND': 'Attribution-NoDerivs',
  'CC BY-NC': 'Attribution-NonCommercial',
  'CC BY-NC-SA': 'Attribution-NonCommercial-ShareAlike',
  'CC BY-NC-ND': 'Attribution-NonCommercial-NoDerivs',
  'GNU GPL': 'General Public License',
  'PD': 'Public Domain',
  'ODC PDDL': 'Public Domain Dedication and Licence',
  'CC PDM': 'Public Domain Mark',
  'C': 'Copyright'
};

/**
 * Simple class for creating thumbnails for images.
 *
 * @param {String} source
 * @param {Number} width
 * @param {Number} height
 */
H5P.Thumbnail = function (source, width, height) {
  var thumbWidth, thumbHeight = 100;
  if (width !== undefined) {
    thumbWidth = Math.round(thumbHeight * (width / height));
  }

  /**
   * Public. Print thumbnail.
   *
   * @returns {String} HTML.
   */
  this.toString = function () {
    return '<img src="' + source + '" alt="' + H5P.t('thumbnail') + '" class="h5p-thumbnail" height="' + thumbHeight + '"' + (thumbWidth === undefined ? '' : ' width="' + thumbWidth + '"') + '/>';
  };
};

/**
 * Simple data class for storing a single field.
 */
H5P.Field = function (label, value) {
  /**
   * Public. Get field label.
   *
   * @returns {String}
   */ 
  this.getLabel = function () {
    return label;
  };
  
  /**
   * Public. Get field value.
   *
   * @returns {String}
   */ 
  this.getValue = function () {
    return value;
  };
};

/**
 * Simple class for creating a definition list.
 */
H5P.DefinitionList = function () {
  var fields = [];
  
  /**
   * Public. Add field to list.
   *
   * @param {H5P.Field} field
   */
  this.add = function (field) {
    fields.push(field);
  };
  
  /**
   * Public. Get Number of fields.
   *
   * @returns {Number}
   */
  this.size = function () {
    return fields.length;
  };
  
  /**
   * Public. Get field at given index.
   *
   * @param {Number} index
   * @returns {Object}
   */
  this.get = function (index) {
    return fields[index];
  };
  
  /**
   * Public. Print definition list.
   *
   * @returns {String} HTML.
   */
  this.toString = function () {
    var html = '';
    for (var i = 0; i < fields.length; i++) {
      var field = fields[i];
      html += '<dt>' + field.getLabel() + '</dt><dd>' + field.getValue() + '</dd>';
    }
    return (html === '' ? html : '<dl class="h5p-definition-list">' + html + '</dl>');
  };
};

/**
 * THIS FUNCTION/CLASS IS DEPRECATED AND WILL BE REMOVED.
 *
 * Helper object for keeping coordinates in the same format all over.
 */
H5P.Coords = function (x, y, w, h) {
  if ( !(this instanceof H5P.Coords) )
    return new H5P.Coords(x, y, w, h);

  this.x = 0;
  this.y = 0;
  this.w = 1;
  this.h = 1;

  if (typeof(x) === 'object') {
    this.x = x.x;
    this.y = x.y;
    this.w = x.w;
    this.h = x.h;
  } else {
    if (x !== undefined) {
      this.x = x;
    }
    if (y !== undefined) {
      this.y = y;
    }
    if (w !== undefined) {
      this.w = w;
    }
    if (h !== undefined) {
      this.h = h;
    }
  }
  return this;
};

/**
 * Parse library string into values.
 *
 * @param {string} library
 *  library in the format "machineName majorVersion.minorVersion"
 * @returns
 *  library as an object with machineName, majorVersion and minorVersion properties
 *  return false if the library parameter is invalid
 */
H5P.libraryFromString = function (library) {
  var regExp = /(.+)\s(\d)+\.(\d)$/g;
  var res = regExp.exec(library);
  if (res !== null) {
    return {
      'machineName': res[1],
      'majorVersion': res[2],
      'minorVersion': res[3]
    };
  }
  else {
    return false;
  }
};

/**
 * Get the path to the library
 *
 * @param {String} library
 *   The library identifier in the format "machineName-majorVersion.minorVersion".
 * @returns {String} The full path to the library.
 */
H5P.getLibraryPath = function (library) {
  return H5PIntegration.getLibraryPath(library);
};

/**
 * Recursivly clone the given object.
 * TODO: Consider if this needs to be in core. Doesn't $.extend do the same? 
 *
 * @param {object} object Object to clone.
 * @param {type} recursive
 * @returns {object} A clone of object.
 */
H5P.cloneObject = function (object, recursive) {
  var clone = object instanceof Array ? [] : {};

  for (var i in object) {
    if (object.hasOwnProperty(i)) {
      if (recursive !== undefined && recursive && typeof object[i] === 'object') {
        clone[i] = H5P.cloneObject(object[i], recursive);
      }
      else {
        clone[i] = object[i];
      }
    }
  }

  return clone;
};

/**
 * Remove all empty spaces before and after the value.
 * TODO: Only include this or String.trim(). What is best?
 * I'm leaning towards implementing the missing ones: http://kangax.github.io/compat-table/es5/
 * So should we make this function deprecated?
 *
 * @param {String} value
 * @returns {@exp;value@call;replace}
 */
H5P.trim = function (value) {
  return value.replace(/^\s+|\s+$/g, '');
};

/**
 * Check if javascript path/key is loaded.
 *
 * @param {String} path
 * @returns {Boolean}
 */
H5P.jsLoaded = function (path) {
  H5P.loadedJs = H5P.loadedJs || [];
  return H5P.jQuery.inArray(path, H5P.loadedJs) !== -1;
};

/**
 * Check if styles path/key is loaded.
 *
 * @param {String} path
 * @returns {Boolean}
 */
H5P.cssLoaded = function (path) {
  H5P.loadedCss = H5P.loadedCss || [];
  return H5P.jQuery.inArray(path, H5P.loadedCss) !== -1;
};

/**
 * Shuffle an array in place.
 * TODO: Consider if this should be a part of core. I'm guessing very few libraries are going to use it.
 *
 * @param {array} array Array to shuffle
 * @returns {array} The passed array is returned for chaining.
 */
H5P.shuffleArray = function (array) {
  if (! array instanceof Array) {
    return;
  }

  var i = array.length, j, tempi, tempj;
  if ( i === 0 ) return false;
  while ( --i ) {
    j       = Math.floor( Math.random() * ( i + 1 ) );
    tempi   = array[i];
    tempj   = array[j];
    array[i] = tempj;
    array[j] = tempi;
  }
  return array;
};

/**
 * Post finished results for user.
 * TODO: Should we use events instead? That way the parent can handle the results of the child.
 *
 * @param {Number} contentId
 * @param {Number} points
 * @param {Number} maxPoints
 */
H5P.setFinished = function (contentId, points, maxPoints) {
  if (H5P.postUserStatistics === true) {
    H5P.jQuery.post(H5P.ajaxPath + 'setFinished', {contentId: contentId, points: points, maxPoints: maxPoints});
  }
};

// Add indexOf to browsers that lack them. (IEs)
if (!Array.prototype.indexOf) {
  Array.prototype.indexOf = function (needle) {
    for (var i = 0; i < this.length; i++) {
      if (this[i] === needle) {
        return i;
      }
    }
    return -1;
  };
}

// Need to define trim() since this is not available on older IEs,
// and trim is used in several libs
if (String.prototype.trim === undefined) {
  String.prototype.trim = function () {
    return H5P.trim(this);
  };
}

// Finally, we want to run init when document is ready.
// TODO: Move to integration. Systems like Moodle using YUI cannot get its translations set before this starts!
if (H5P.jQuery) {
  H5P.jQuery(document).ready(function () {
    if (!H5P.initialized) {
      H5P.initialized = true;
      H5P.init();
    }
  });
}
