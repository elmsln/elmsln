// TODO: Why can't h5pintegration.js just hook into the H5P namespace instead of creating its own?
var H5PIntegration = H5PIntegration || {};
var H5P = H5P || {};

// If run in an iframe, use parent version of globals.
if (window.parent !== window) {
  Drupal = window.parent.Drupal;
  jQuery = window.parent.jQuery;
}

jQuery(document).ready(function () {
  H5P.loadedJs = Drupal.settings.h5p !== undefined && Drupal.settings.h5p.loadedJs !== undefined ? Drupal.settings.h5p.loadedJs : [];
  H5P.loadedCss = Drupal.settings.h5p !== undefined && Drupal.settings.h5p.loadedCss !== undefined ? Drupal.settings.h5p.loadedCss : [];
});

H5PIntegration.getJsonContent = function (contentId) {
  return Drupal.settings.h5p.content['cid-' + contentId].jsonContent;
};

// Window parent is always available.
var locationOrigin = window.parent.location.protocol + "//" + window.parent.location.host;
H5PIntegration.getContentPath = function (contentId) {
  if (Drupal.settings.h5p !== undefined && contentId !== undefined) {
    return locationOrigin + Drupal.settings.h5p.jsonContentPath + contentId + '/';
  }
  else if (Drupal.settings.h5peditor !== undefined)  {
    return Drupal.settings.h5peditor.filesPath + '/h5peditor/';
  }
};

/**
 * Get the path to the library
 *
 * TODO: Make this use machineName instead of machineName-majorVersion-minorVersion
 *
 * @param {string} library
 *  The library identifier as string, for instance 'downloadify-1.0'
 * @returns {string} The full path to the library
 */
H5PIntegration.getLibraryPath = function (library) {
  // TODO: This is silly and needs to be changed, why does the h5peditor
  // have its own namespace for these things?
  var libraryPath = Drupal.settings.h5p !== undefined ? Drupal.settings.h5p.libraryPath : Drupal.settings.h5peditor.libraryPath

  return Drupal.settings.basePath + libraryPath + library;
};

/**
 * Get Fullscreenability setting.
 */
H5PIntegration.getFullscreen = function (contentId) {
  return Drupal.settings.h5p.content['cid-' + contentId].fullScreen === '1';
};

/**
 * Loop trough styles and create a set of tags for head.
 * TODO: Cache base tags or something to improve performance.
 *
 * @param {Array} styles List of stylesheets
 * @returns {String} HTML
 */
H5PIntegration.getHeadTags = function (contentId) {
  var basePath = window.location.protocol + '//' + window.location.host + Drupal.settings.basePath;

  var createUrl = function (path) {
    if (path.substring(0,7) !== 'http://') {
      // Not external, add base path and cache buster.
      path = basePath + path + '?' + Drupal.settings.h5p.cacheBuster;
    }
    return path;
  }

  var createStyleTags = function (styles) {
    var tags = '';
    for (var i = 0; i < styles.length; i++) {
      tags += '<link rel="stylesheet" href="' + createUrl(styles[i]) + '">';
    }
    return tags;
  };

  var createScriptTags = function (scripts) {
    var tags = '';
    for (var i = 0; i < scripts.length; i++) {
      tags += '<script src="' + createUrl(scripts[i]) + '"></script>';
    }
    return tags;
  };

  return createStyleTags(Drupal.settings.h5p.core.styles)
       + createStyleTags(Drupal.settings.h5p['cid-' + contentId].styles)
       + createScriptTags(Drupal.settings.h5p.core.scripts)
       + createScriptTags(Drupal.settings.h5p['cid-' + contentId].scripts);
};

H5PIntegration.fullscreenText = Drupal.t('Fullscreen');
