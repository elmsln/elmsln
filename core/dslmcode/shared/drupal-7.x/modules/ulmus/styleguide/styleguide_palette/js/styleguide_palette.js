(function ($, Drupal) {

"use strict";

Drupal.behaviors.styleguidePalette = {
  attach: function() {
    var farb = $.farbtastic('#styleguide-palette-colorpicker');
    $('.colorpicker-input').each(function() {
      farb.linkTo(this);
      $(this).click(function () {
        farb.linkTo(this);
      });
    });
  }
};

})(jQuery, Drupal);
