/**
 * @file
 * Used to add a class to the top level element when an external font is ready.
 */

/* global Drupal:false */

/**
 * Run the check.
 *
 * @param {string} key
 *   The class name to add to the html tag.
 * @param {string} value
 *   The font name.
 */
function advagg_run_check(key, value) {
  'use strict';
  // Only run if window.FontFaceObserver is defined.
  if (window.FontFaceObserver) {
    // Only alpha numeric value.
    key = key.replace(/[^a-zA-Z0-9\-]/g, '');

    if (typeof window.FontFaceObserver.prototype.load === 'function') {
      new window.FontFaceObserver(value).load().then(function () {
        advagg_run_check_inner(key, value);
      }, function () {});
    }
    else {
      new window.FontFaceObserver(value).check().then(function () {
        advagg_run_check_inner(key, value);
      }, function () {});
    }
  }
  else {
    // Try again in 100 ms.
    window.setTimeout(function () {
      advagg_run_check(key, value);
    }, 100);
  }
}

/**
 * Run the check.
 *
 * @param {string} key
 *   The class name to add to the html tag.
 * @param {string} value
 *   The font name.
 */
function advagg_run_check_inner(key, value) {
  'use strict';
  // Set Class.
  if (Drupal.settings.advagg_font_no_fout != 1) {
    window.document.documentElement.className += ' ' + key;
  }

  // Set Cookie for a day.
  if (Drupal.settings.advagg_font_cookie == 1) {
    var expire_date = new Date(new Date().getTime() + 86400 * 1000);
    document.cookie = 'advaggfont_' + key + '=' + value
      + '; expires=' + expire_date.toUTCString()
      + '; domain=.' + document.location.hostname
      + '; path=/';
  }
}

/**
 * Get the list of fonts to check for.
 */
function advagg_font_add_font_classes_on_load() {
  'use strict';
  for (var key in Drupal.settings.advagg_font) {
    if (Drupal.settings.advagg_font.hasOwnProperty(key)) {
      var html_class = (' ' + window.document.documentElement.className + ' ').indexOf(' ' + key + ' ');
      // If the class already exists in the html element do nothing.
      if (html_class === -1) {
        // Wait till the font is downloaded, then set cookie & class.
        advagg_run_check(key, Drupal.settings.advagg_font[key]);
      }
    }
  }
}

/**
 * Make sure jQuery and Drupal.settings are defined before running.
 */
function advagg_font_check() {
  'use strict';
  if (window.jQuery && window.Drupal && window.Drupal.settings) {
    advagg_font_add_font_classes_on_load();
  }
  else {
    // Try again in 20 ms.
    window.setTimeout(advagg_font_check, 20);
  }
}

// Start the process.
advagg_font_check();
