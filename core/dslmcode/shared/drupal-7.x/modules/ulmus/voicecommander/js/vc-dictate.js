/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  Drupal.voicecommander.dictate = function(wildcard) {
    // place holder because the resultMatch has the real data we care about
  };
  // @todo this is not a long term solution, we need to match userSaid
  // to something and then react to it. This might make more sense
  // with a mode that allows for just talking (no buttons) as well as
  // the ability to use it over https so we see how fluid it is as well as
  // the form module which will provide support for navigating forms with
  // your voice, to which filling them out makes more sense at that time.
  annyang.addCallback('resultMatch', function(userSaid, commandText, phrases) {
    $(":focus").val(userSaid);
  });
})(jQuery);
