/**
 * @file
 * Used to add a class to the top level element based off of cookies.
 */

/**
 * Get advagg cookies for fonts or localStorage.
 *
 * Changes the top level class to include the font name found in the cookie.
 */
function advagg_font_inline() {
  'use strict';
  // Cookie handler.
  var fonts = document.cookie.split('advaggf');
  for (var i = 0; i < fonts.length; i++) {
    var font = fonts[i].split('=');
    var pos = font[0].indexOf('ont_');
    if (pos !== -1) {
      // Only allow alpha numeric class names.
      window.document.documentElement.className += ' ' + font[0].substr(4).replace(/[^a-zA-Z0-9-]/g, '');
    }
  }

  // Local Storage handler.
  if (Storage !== void 0) {
    fonts = JSON.parse(localStorage.getItem('advagg_fonts'));
    var current_time = new Date().getTime();
    for (var key in fonts) {
      if (fonts[key] >= current_time) {
        // Only allow alpha numeric class names.
        window.document.documentElement.className += ' ' + key.replace(/[^a-zA-Z0-9-]/g, '');
      }
    }
  }
}


// Check cookies ASAP and set class.
advagg_font_inline();
