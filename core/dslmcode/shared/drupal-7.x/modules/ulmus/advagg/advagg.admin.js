/* global Drupal:false */

/**
 * @file
 * Used to toggle the AdvAgg Bypass Cookie client side.
 */

/**
 * Test to see if the given string contains unicode.
 *
 * @param str
 *   String to test.
 * @return
 *   true if string contains non ASCII characters.
 *   false if string only contains ASCII characters.
 */
function advagg_is_unicode(str){
  "use strict";
  for (var i = 0, n = str.length; i < n; i++) {
    if (str.charCodeAt( i ) > 255) {
      return true;
    }
  }
  return false;
}

/**
 * Toggle the advagg cookie
 *
 * @return
 *   true if hostname contains unicode.
 *   false so the form does not get submitted.
 */
function advagg_toggle_cookie() {
  "use strict";
  // Fallback to submitting the form for Unicode domains like ".рф"
  if (advagg_is_unicode(document.location.hostname)) {
    return true;
  }

  var cookie_name = 'AdvAggDisabled';

  // See if the cookie exists.
  var cookie_pos = document.cookie.indexOf(cookie_name + '=' + Drupal.settings.advagg.key);

  // If the cookie does exist then remove it.
  if (cookie_pos !== -1) {
    document.cookie = cookie_name + '=;'
      + 'expires=Thu, 01 Jan 1970 00:00:00 GMT;'
      + ' path=' + Drupal.settings.basePath + ';'
      + ' domain=.' + document.location.hostname + ';';
    alert(Drupal.t('AdvAgg Bypass Cookie Removed'));
  }
  // If the cookie does not exist then set it.
  else {
    // Cookie will last for 12 hours.
    var expire_time = new Date();
    expire_time.setTime(expire_time.getTime()+(1000*60*60*12));
    document.cookie = cookie_name + '=' + Drupal.settings.advagg.key + ';'
      + ' expires=' + expire_time.toGMTString() + ';'
      + ' path=' + Drupal.settings.basePath + ';'
      + ' domain=.' + document.location.hostname + ';';
    alert(Drupal.t('AdvAgg Bypass Cookie Set'));
  }

  // Must return false, if returning true then form gets submitted.
  return false;
}

