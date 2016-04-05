/**
 * @file
 * Allow for ferpa filter actions to be applied to content
 */
(function ($) {
  $(document).ready(function(){
    // test for cookie being set
    if ($.cookie('ferpa_filter') == 'true') {
      $('#block-cis-service-connection-ferpa-filter-nav-modal input[type=checkbox]').click();
    }
  });
  Drupal.behaviors.ferpa_filter = {
    attach: function(context) {
      $('#block-cis-service-connection-ferpa-filter-nav-modal input[type=checkbox]').click(function(){
        if (this.checked) {
          // look for anything that's marked ferpa and change the class to enforce our privacy blur
          $('.ferpa-protect,#colorbox,.username').addClass('ferpa-privacy-blur');
        }
        else {
          $('.ferpa-protect,#colorbox,.username').removeClass('ferpa-privacy-blur');
        }
        $.cookie('ferpa_filter', this.checked, { path: '/', domain: Drupal.settings.elmslnCore.domain });
      });
    }
  };
})(jQuery);