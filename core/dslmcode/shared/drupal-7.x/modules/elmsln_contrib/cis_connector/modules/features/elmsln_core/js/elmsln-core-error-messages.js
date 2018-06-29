(function ($) {
  $(document).ready(function(){
    setInterval(function(){ $('.error-page-hal9000').addClass('on'); }, 1000);
    setInterval(function(){ $('.error-page-hal9000').removeClass('on'); }, 2000);
  });
})(jQuery);