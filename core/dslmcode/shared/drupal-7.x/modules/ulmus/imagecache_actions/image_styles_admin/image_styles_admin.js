(function($) {
"use strict";

Drupal.behaviors.imageStylesAdmin = {
  attach: function(context) {
    $('#image-styles').find('th.expand-all').once('expand-all', function() {
      $(this).click(function() {
        $('#image-styles').find('td.description .inner.expand').addClass('expanded');
      });
    });
    $('#image-styles').find('td.description').once('description', function() {
      $('.inner.expand', $(this)).click(function() {
        $(this).toggleClass('expanded');
      });
    });
  }
};

})(jQuery);
