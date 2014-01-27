(function ($) {

// Check that shadowbox library is available
if (typeof Shadowbox === 'undefined') return;

Drupal.behaviors.shadowbox = {
  attach: function(context, settings) {
    Shadowbox.init(Drupal.settings.shadowbox);
    try {
      if ($('iframe#sb-player', top.document).length == 0) {
        if (settings.shadowbox.auto_enable_all_images == 1) {
          $("a[href$='.jpg'], a[href$='.png'], a[href$='.gif'], a[href$='.jpeg'], a[href$='.bmp'], a[href$='.JPG'], a[href$='.PNG'], a[href$='.GIF'], a[href$='.JPEG'], a[href$='.BMP']").each(function() {
            if ($(this).attr('rel') == '') {
              if (settings.shadowbox.auto_gallery == 1) {
                $(this).attr('rel', 'shadowbox[gallery]');
              }
              else {
                $(this).attr('rel', 'shadowbox');
              }
            }
          });
        }
      }
    }
    catch(err) {
      // ignore if this failed
    }
    Shadowbox.clearCache();
    Shadowbox.setup();
  }
};

})(jQuery);

