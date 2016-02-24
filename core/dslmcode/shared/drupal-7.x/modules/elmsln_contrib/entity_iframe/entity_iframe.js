/**
 * Allow for auto selection of iframe content area on focus
 */
(function ($) {
  Drupal.behaviors.entity_iframe = {
    attach: function(context) {
      $('textarea.entity_iframe_embed,input.entity_iframe_embed').focus(function() { $(this).select() });
      $('textarea.entity_iframe_embed,input.entity_iframe_embed').mouseup(function(e){
        e.preventDefault();
      });
    }
  };
})(jQuery);