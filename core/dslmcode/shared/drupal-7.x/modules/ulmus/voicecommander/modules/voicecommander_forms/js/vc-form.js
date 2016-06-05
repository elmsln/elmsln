/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  Drupal.voicecommander.formNavigation = function(phrase) {
    // see if we should go to the previous page or next
    if (phrase.indexOf('start') !== -1) {
      // start working on the form
    }
    else if (phrase.indexOf('next') !== -1) {
      // enter the next item
    }
    else if (phrase.indexOf('previous') !== -1) {
      // enter the previous item
    }
    else if (phrase.indexOf('submit') !== -1) {
      // submit the active form
    }
  };
})(jQuery);
