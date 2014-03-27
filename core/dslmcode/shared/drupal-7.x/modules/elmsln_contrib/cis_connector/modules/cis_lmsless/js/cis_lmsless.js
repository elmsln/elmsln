/**
 * @file
 * CIS LMS-less helper for top bar
 */
(function ($) {
  Drupal.behaviors.lmslessbar = {
    attach: function(context, settings) {
      // On option change, switch location
      $('select.cis-lmsless-bar-services').change(function(){
        window.location = $(this).val();
      });
    }
  };
})(jQuery);
