/**
 * @file
 * equalheights module javascript settings.
 */
(function($) {
  Drupal.behaviors.equalHeightsModule = {
    attach: function (context, settings) {
      if (Drupal.settings.equalHeightsModule) {
        var eqClass = Drupal.settings.equalHeightsModule.classes;
      }
      if (eqClass) {
        equalHeightsTrigger();
        $(window).bind('resize', function () {
          equalHeightsTrigger();
        });
      }
      function equalHeightsTrigger() {
        $.each(eqClass, function(eqClass, setting) {
          var target = $(setting.selector);
          var minHeight = setting.minheight;
          var maxHeight = setting.maxheight;
          var overflow = setting.overflow;
          target.css('height', '');
          target.css('overflow', '');

          // Disable equalheights not matching the mediaquery
          var mediaQuery = setting.mediaquery;
          var matchMedia = window.matchMedia;
          if (mediaQuery) {
            if (matchMedia && !matchMedia(mediaQuery).matches) {
                return;
              } else {
                equalHeightsLoad(target, minHeight, maxHeight, overflow);
              }
            } else {
              equalHeightsLoad(target,minHeight, maxHeight, overflow);
          }
        });
      }
      function equalHeightsLoad(target, minHeight, maxHeight, overflow) {
          // disable imagesloaded for IE<=8
          var imagesLoadedIE8 = Drupal.settings.equalHeightsModule.imagesloaded_ie8;
          if (imagesLoadedIE8 && window.attachEvent && !window.addEventListener) {
              target.equalHeights(minHeight, maxHeight).css('overflow', overflow);
          } else {
          // imagesloaded library checks if all images are loaded before callback
           target.imagesLoaded({
           callback: function($images, $proper, $broken) {
             this.equalHeights(minHeight, maxHeight).css('overflow', overflow)
           }
          });
          }
      }

    }
  }
})(jQuery);
