/**
 * @file
 *
 * Javascript to add placeholder events.
 */

(function ($) {
  Drupal.behaviors.placeholder = {
    attach: function () {
      $("input[placeholder], textarea[placeholder]").placeholder();
    }
  };

})(jQuery);
