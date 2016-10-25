(function ($) {
  $(document).ready(function(){
    if ($('.animatedgif').length > 0) {
      var animatedgif = new freezeframe('.animatedgif').freeze();
      $('.start').click(function(e) {
        e.preventDefault();
        animatedgif.trigger();
      });
      $('.stop').click(function(e) {
        e.preventDefault();
        animatedgif.release();
      });
      setTimeout(function() {
        // support our circle classes
        $('.animatedgif.circle').parent().addClass('circle').children('canvas').addClass('circle');
      }, 250);
    }
  });
})(jQuery);
