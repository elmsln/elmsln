(function ($) {
  // attempt to spit xapi context into all iframes
  $(document).ready(function(){
    // click to show / hide devel
    $('.dev-query').click(function() {
      if ($('body').hasClass('devel-show')) {
        $('body').removeClass('devel-show');
      }
      else {
        $('body').addClass('devel-show');
      }
    });
    // make it seem friendly to click
    $('.dev-query').addClass('waves-effect waves-light waves-' + Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['outline']);
  });
})(jQuery);