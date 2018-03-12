/**
 * @file
 * Used to toggle the AdvAgg Bypass Cookie client side.
 */

/* global Drupal:false */
/* eslint-disable no-unused-vars */

/**
 * Test to see if the given string contains unicode.
 *
 * @param {int} interval
 *   String to test.
 * @param {int} granularity
 *   String to test.
 * @param {string} langcode
 *   Language used in translation.
 *
 * @return {bool}
 *   true if string contains non ASCII characters.
 *   false if string only contains ASCII characters.
 */
Drupal.formatInterval = function (interval, granularity, langcode) {
  'use strict';
  granularity = typeof granularity !== 'undefined' ? granularity : 2;
  langcode = typeof langcode !== 'undefined' ? langcode : null;
  var output = '';

  /* eslint-disable key-spacing */
  while (granularity > 0) {
    var value = 0;
    if (interval >= 31536000) {
      value = 31536000;
      output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), '1 year', '@count years', {langcode : langcode});
    }
    else if (interval >= 2592000) {
      value = 2592000;
      output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), '1 month', '@count months', {langcode : langcode});
    }
    else if (interval >= 604800) {
      value = 604800;
      output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), '1 week', '@count weeks', {langcode : langcode});
    }
    else if (interval >= 86400) {
      value = 86400;
      output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), '1 day', '@count days', {langcode : langcode});
    }
    else if (interval >= 3600) {
      value = 3600;
      output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), '1 hour', '@count hours', {langcode : langcode});
    }
    else if (interval >= 60) {
      value = 60;
      output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), '1 min', '@count min', {langcode : langcode});
    }
    else if (interval >= 1) {
      value = 1;
      output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), '1 sec', '@count sec', {langcode : langcode});
    }

    interval %= value;
    granularity--;
  }

  return output.length ? output : Drupal.t('0 sec', {}, {langcode : langcode});
  /* eslint-enable key-spacing */
};

/**
 * Test to see if the given string contains unicode.
 *
 * @param {string} str
 *   String to test.
 *
 * @return {bool}
 *   true if string contains non ASCII characters.
 *   false if string only contains ASCII characters.
 */
function advagg_is_unicode(str) {
  'use strict';
  for (var i = 0, n = str.length; i < n; i++) {
    if (str.charCodeAt(i) > 255) {
      return true;
    }
  }
  return false;
}

/**
 * Toggle the advagg cookie.
 *
 * @return {bool}
 *   true if hostname contains unicode.
 *   false so the form does not get submitted.
 */
function advagg_toggle_cookie() {
  'use strict';
  // Fallback to submitting the form for Unicode domains like ".рф".
  if (advagg_is_unicode(document.location.hostname)) {
    return true;
  }

  var cookie_name = 'AdvAggDisabled';

  // See if the cookie exists.
  var cookie_pos = document.cookie.indexOf(cookie_name + '=' + Drupal.settings.advagg.key);

  // If the cookie does exist then remove it.
  if (cookie_pos !== -1) {
    document.cookie =
      cookie_name + '='
      + '; expires=Thu, 01 Jan 1970 00:00:00 GMT'
      + '; path=' + Drupal.settings.basePath
      + '; domain=.' + document.location.hostname + ';';
    alert(Drupal.t('AdvAgg Bypass Cookie Removed'));
  }
  // If the cookie does not exist then set it.
  else {
    var bypass_length = document.getElementById('edit-timespan').value;
    var expire_date = new Date(new Date().getTime() + bypass_length * 1000);

    document.cookie =
      cookie_name + '=' + Drupal.settings.advagg.key
      + '; expires=' + expire_date.toGMTString()
      + '; path=' + Drupal.settings.basePath
      + '; domain=.' + document.location.hostname + ';';
    alert(Drupal.t('AdvAgg Bypass Cookie Set for @time.', {'@time': Drupal.formatInterval(bypass_length)}));
  }

  // Must return false, if returning true then form gets submitted.
  return false;
}
