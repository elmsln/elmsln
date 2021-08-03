(function ($) {
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
  });
})(jQuery);