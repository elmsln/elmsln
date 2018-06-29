(function ($) {
  $(document).ready(function(){
    // go back
    jwerty.key('←,←', function () {
      if ($('.page-previous').attr('href')) {
        $('.page-previous').click();
      }
    });
    // go forward
    jwerty.key('→,→', function () {
      if ($('.page-next').attr('href')) {
        $('.page-next').click();
      }
    });
  });
})(jQuery);