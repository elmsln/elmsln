/**
 * @file
 * Used to load CSS via JS so css doesn't block the browser.
 */

/* eslint-disable no-unused-vars */

/**
 * Given a css file, load it using JavaScript.
 *
 * @param {string} src
 *   URL of the css file to load.
 */
function advagg_mod_loadStyleSheet(src) {
  'use strict';
  if (document.createStyleSheet) {
    document.createStyleSheet(src);
  }
  else {
    var stylesheet = document.createElement('link');
    stylesheet.href = src;
    stylesheet.rel = 'stylesheet';
    stylesheet.type = 'text/css';
    document.getElementsByTagName('head')[0].appendChild(stylesheet);
  }
}
