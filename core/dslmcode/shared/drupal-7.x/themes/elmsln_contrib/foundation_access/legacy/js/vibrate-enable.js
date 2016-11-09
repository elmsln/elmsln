(function ($) {
  $(document).ready(function(){
    $('[data-activates],a[href^="#"]').vibrate(50);
    $('a:not([href^="#"])').vibrate(30);
  });
})(jQuery);
