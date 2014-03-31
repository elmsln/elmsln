/**
 * @file
 * Allow for auto selection of cis shortcode content area on focus.
 */
(function ($) {
  Drupal.behaviors.cis_shortcodes = {
    attach: function(context) {
      $('textarea.cis_shortcodes_embed').focus(function() { $(this).select() });
      $('textarea.cis_shortcodes_embed').mouseup(function(e){
        e.preventDefault();
      });
    }
  };
})(jQuery);