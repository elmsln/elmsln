(function ($) {
  $(document).ready(function(){
    jwerty.key('↓,↓', function () {
      var height = $(window).height();
      $('html, body').animate({
          scrollTop: $(window).scrollTop()+(height*0.75)
      }, 1000);
    });
    jwerty.key('↑,↑', function () {
      var height = $(window).height();
      $('html, body').animate({
        scrollTop: $(window).scrollTop()-(height*0.75)
      }, 1000);
    });
    // network
    jwerty.key('n', function () {
      $('.apps-icon').click();
    });
    // user
    jwerty.key('u', function () {
      $('.etb-nav_item_service_btn.etb-icon.user-icon').click();
    });
  });
})(jQuery);