/**
 * This file should be used instead of foundation_access/js/tweaks.js
 * if you are not using the grunt task runner.
 */

(function ($) {
  Drupal.behaviors.foundationAccessClickField = {
    attach: function(context) {
      $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').focus(function() { $(this).select() });
      $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').mouseup(function(e){
        e.preventDefault();
      });
    }
  };
  Drupal.behaviors.accessibilityCheckHide = {
    attach: function(context, settings) {
      if ($(".cis_accessibility_check a").length == 0) {
        $(".accessibility-content-toggle a").appendTo( ".cis_accessibility_check" );
      }
      $(".accessibility-content-toggle").hide();
    }
  };
})(jQuery);
