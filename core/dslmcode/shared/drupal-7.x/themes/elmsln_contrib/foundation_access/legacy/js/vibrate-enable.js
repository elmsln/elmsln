(function ($) {
  $(document).ready(function(){
    $('[data-activates],a[href="#"]').vibrate(50);
    $('a[href!="#"]').vibrate(30);
  });
})(jQuery);
