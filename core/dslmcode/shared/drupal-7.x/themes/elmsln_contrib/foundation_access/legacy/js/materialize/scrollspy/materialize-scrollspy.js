(function ($) {
  $(document).ready(function(){
    // target data property and convert to scrollspy class addition
    $('h2[data-scrollspy="scrollspy"],h3[data-scrollspy="scrollspy"],h4[data-scrollspy="scrollspy"]').addClass('scrollspy');
    // activate class
    $('.scrollspy').scrollSpy();
    $('.scrollspy-toc').pushpin({offset: 50, top: $('#scrollspy-nav').offset().top });
    $('.scrollspy-link').click(function(){
      $($(this).attr('href')).addClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light'], 250, function() {
        $(this).removeClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light'], 250, function(){});
      });
    });
  });
})(jQuery);
