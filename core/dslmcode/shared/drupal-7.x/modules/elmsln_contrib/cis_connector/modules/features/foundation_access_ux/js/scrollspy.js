(function ($) {
  $(document).ready(function(){
    // target data property and convert to scrollspy class addition
    $('h2[data-scrollspy="scrollspy"],h3[data-scrollspy="scrollspy"],h4[data-scrollspy="scrollspy"]').addClass('scrollspy');
    // activate class
    $('.scrollspy').scrollSpy();
    $('.scrollspy-toc').pushpin({offset: 50, top: $('#scrollspy-nav').offset().top });
    $('.scrollspy-link').click(function(){
      $($(this).attr('href')).css('background-color', '#FF8866').animate({
        backgroundColor: 'transparent',
        },
        1000, function() {
      });
    });
  });
})(jQuery);
