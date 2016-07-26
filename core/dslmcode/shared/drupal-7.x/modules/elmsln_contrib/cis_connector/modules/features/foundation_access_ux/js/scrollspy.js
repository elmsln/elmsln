(function ($) {
  $(document).ready(function(){
    // target data property and convert to scrollspy class addition
    $('h2[data-scrollspy="scrollspy"],h3[data-scrollspy="scrollspy"],h4[data-scrollspy="scrollspy"]').addClass('scrollspy');
    // activate class
    $('.scrollspy').scrollSpy();
  });
})(jQuery);
