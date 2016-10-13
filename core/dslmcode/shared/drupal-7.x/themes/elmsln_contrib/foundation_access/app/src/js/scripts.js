(function ($) {
  'use strict';

  // MenuToggle
  if (typeof Drupal != 'undefined') {
    Drupal.behaviors.repaintSlickbanner = {
      attach: function (context, settings) {

      }
    };
  }
  else {
    $(document).ready(function() {

    });
  }

})(jQuery);
