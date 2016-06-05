/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  Drupal.voicecommander.clearCache = function(phrase) {
    window.location.href = Drupal.settings.basePath + 'admin/config/user-interface/voice-commander/cc_all?destination=' + window.location.pathname.replace(Drupal.settings.basePath, '') + '&token=' + Drupal.settings.secureToken;
  };
})(jQuery);
