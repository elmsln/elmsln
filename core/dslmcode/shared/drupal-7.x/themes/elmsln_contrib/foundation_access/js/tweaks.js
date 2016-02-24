/**
 * This file should be used instead of foundation_access/js/tweaks.js
 * if you are not using the grunt task runner.
 */

(function ($) {
(function ($) {
  Drupal.behaviors.foundation_access = {
    attach: function(context) {
      $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').focus(function() { $(this).select() });
      $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').mouseup(function(e){
        e.preventDefault();
      });
    }
  };
})(jQuery);
})(jQuery);