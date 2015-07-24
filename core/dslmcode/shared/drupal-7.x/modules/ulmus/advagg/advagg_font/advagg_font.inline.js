/**
 * @file
 * Used to add a class to the top level element based off of cookies.
 */

// Check cookies ASAP and set class.
var fonts = document.cookie.split('advagg');
for (var key in fonts) {
  var font = fonts[key].split('=');
  var pos = font[0].indexOf('font_');
  if (pos !== -1) {
    // Only allow alpha numeric class names.
    window.document.documentElement.className += ' ' + font[0].substr(5).replace(/[^a-zA-Z0-9\-]/g, '');
  }
}
