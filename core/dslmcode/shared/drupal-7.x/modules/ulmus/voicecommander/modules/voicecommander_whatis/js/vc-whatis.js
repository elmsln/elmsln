/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  Drupal.voicecommander.whatIs = function(what) {
    // make ajax call for what to say in response
    $.ajax({
      type: "POST",
      url: Drupal.settings.voiceCommander.basePath + 'voicecommander/whatis/' + Drupal.settings.voiceCommander.secureToken + '/' + what,
      success: function(msg){
        // loop through message response if valid
        if (msg.status == '200') {
          msg.response.forEach(function(item) {
            // if we got something... say what it is...
            // oh.... snap.
            if (item != '') {
              Drupal.voicecommander.say(item);
            }
          });
        }
      }
    });
  };
})(jQuery);
