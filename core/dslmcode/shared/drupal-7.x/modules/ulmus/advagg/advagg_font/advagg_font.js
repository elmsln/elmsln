/**
 * @file
 * Used to add a class to the top level element when an external font is ready.
 */

/* global Drupal:false */

/**
 * Run the check.
 *
 * @param string key
 *   The class name to add to the html tag.
 * @param string value
 *   The font name.
 */
function advagg_run_check(key, value) {
  // Only run if window.FontFaceObserver is defined.
  if (window.FontFaceObserver) {
    new window.FontFaceObserver(value).check().then(function () {
      // Only alpha numeric value.
      key = key.replace(/[^a-zA-Z0-9\-]/g, '');

      // Set Class.
      if (Drupal.settings.advagg_font_no_fout != 1) {
        window.document.documentElement.className += ' ' + key;
      }

      // Set Cookie for a day.
      if (Drupal.settings.advagg_font_cookie == 1) {
        expire_date = new Date(new Date().getTime() + 86400 * 1000);
        document.cookie = 'advaggfont_' + key + '=' + value + ';'
          + ' expires=' + expire_date.toGMTString() + ';'
          + ' path=/;'
          + ' domain=.' + document.location.hostname + ';';
      }
    }, function() {});
  }
  else {
    // Try again in 100 ms.
    window.setTimeout(function() {
      advagg_run_check(key, value);
    }, 100);
  }
}

/**
 * Get the list of fonts to check for.
 */
function advagg_font_add_font_classes_on_load() {
  for (var key in Drupal.settings.advagg_font) {
    var html_class = (' ' + window.document.documentElement.className + ' ').indexOf(' ' + key + ' ');
    // If the class already exists in the html element do nothing.
    if (html_class === -1) {
      // Wait till the font is downloaded, then set cookie & class.
      advagg_run_check(key, Drupal.settings.advagg_font[key]);
    }
  }
}

/**
 * Make sure jQuery and Drupal.settings are defined before running.
 */
function advagg_font_check() {
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
