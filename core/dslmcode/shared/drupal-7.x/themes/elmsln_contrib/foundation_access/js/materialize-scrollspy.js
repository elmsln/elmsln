(function ($) {
  Drupal.behaviors.scrollSpy = {
    attach: function(context, settings) {
      if (typeof $('#scrollspy-nav').offset() !== typeof undefined) {
        // target data property and convert to scrollspy class addition
        $('h2[data-scrollspy="scrollspy"],h3[data-scrollspy="scrollspy"],h4[data-scrollspy="scrollspy"]').addClass('scrollspy');
        // activate class
        $('.scrollspy').scrollSpy();
        $('.scrollspy-toc').pushpin({offset: 48, top: $('#scrollspy-nav').offset().top });
      }
    }
  };
})(jQuery);
