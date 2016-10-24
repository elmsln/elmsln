(function ($) {
  $(document).ready(function(){
    var animatedgif = new freezeframe('.animatedgif').freeze();
    $('.start').click(function(e) {
      e.preventDefault();
      animatedgif.trigger();
    });

    $('.stop').click(function(e) {
      e.preventDefault();
      animatedgif.release();
    });
  });
})(jQuery);
