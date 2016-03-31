/**
 * @file
 * Basic form usability tweaks based on conditional values.
 */
(function ($) {
  Drupal.elmslnAPI = Drupal.elmslnAPI || { functions: {} };
  // wrapper for a structured call against the ELMSLN low-bootstrap api in other sites
  Drupal.elmslnAPI.request = function(api, bucket, data, callback) {
    var posting = $.post(
      Drupal.settings.elmsln_api.ajaxPath + '/' + Drupal.settings.elmsln_api.token + '/' + api + '/' + bucket,
      data,
      window[callback],
      'json'
    );
    return posting;
  };
})(jQuery);