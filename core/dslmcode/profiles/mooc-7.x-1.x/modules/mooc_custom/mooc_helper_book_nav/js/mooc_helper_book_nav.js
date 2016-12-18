(function ($) {
  $(document).ready(function(){
    // go back
    jwerty.key('←,←', function () {
      if ($('.page-previous').attr('href')) {
        window.location = $('.page-previous').attr('href');
      }
    });
    // go forward
    jwerty.key('→,→', function () {
      if ($('.page-next').attr('href')) {
        window.location = $('.page-next').attr('href');
      }
    });

    // ensure left highlighted column isn't flowing over the footer height
    $('.highlighted-block-area').each(function(){
      $('article.node').css('min-height', $('.highlighted-block-area').outerHeight());
    });
  });
})(jQuery);