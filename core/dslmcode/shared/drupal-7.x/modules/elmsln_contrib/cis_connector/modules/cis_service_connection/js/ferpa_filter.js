/**
 * @file
 * Allow for ferpa filter actions to be applied to content
 */
(function ($) {
  Drupal.behaviors.ferpa_filter = {
    attach: function(context) {
      $('#block-cis-service-connection-ferpa-filter-nav-modal input[type=checkbox]').click(function(){
        if (this.checked) {
          // look for anything that's marked ferpa and change the class to enforce our privacy blur
          $('.ferpa-protect').addClass('ferpa-privacy-blur');
        }
        else {
          $('.ferpa-protect').removeClass('ferpa-privacy-blur');
        }
      });
    }
  };
})(jQuery);