/**
 * @file
 * Used to add a class to the top level element based off of cookies.
 */

/**
 * Check advagg cookie for fonts.
 *
 * Changes the top level class to include the font name found in the cookie.
 */
function advagg_font_inline() {
  'use strict';
  var fonts = document.cookie.split('advaggf');
  for (var i = 0; i < fonts.length; i++) {
    var font = fonts[i].split('=');
    var pos = font[0].indexOf('ont_');
    if (pos !== -1) {
      // Only allow alpha numeric class names.
      window.document.documentElement.className += ' ' + font[0].substr(4).replace(/[^a-zA-Z0-9\-]/g, '');
      alert(font[0].substr(4).replace(/[^a-zA-Z0-9\-]/g, ''));
    }
  }
}

// Check cookies ASAP and set class.
advagg_font_inline();
