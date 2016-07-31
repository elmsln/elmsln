(function($, Drupal, undefined){
  /**
   * When set to enable ableplayer for all audio/video files add it to the page.
   */
  Drupal.behaviors.ableplayer = {
    attach: function(context, settings) {
      if (settings.ableplayer !== undefined) {
        // @todo Remove anonymous function.
        $.each(settings.ableplayer, function(selector, options) {
          var opts;
          $(selector, context).once('ableplayer', function() {
            if (options.controls) {
              $(this).ableplayer(options.opts);
            }
            else {
              $(this).ableplayer();
            }
          });
        });
      }
      // The global option is seperate from the other selectors as it should be
      // run after any other selectors.
      if (settings.ableplayerAll !== undefined) {
        $('video,audio', context).once('ableplayer', function() {
          $(this).ableplayer();
        });
      }
    }
  };
})(jQuery, Drupal);