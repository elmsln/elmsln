module.exports = function() {
  (function ($) {
    'use strict';

  	$("body")
  	    .append("<div class='imagelightbox__overlay'>")
  	    .append("<a href='javascript:;' class='imagelightbox__close'>Close</a>");

    function startLightboxOverlay() {
      $("body").addClass("lightbox--is-open");
    }

    function endLightboxOverlay() {
      $("body").removeClass("lightbox--is-open");
    }

    $("*[data-imagelightbox]").imageLightbox({
      selector: 'class="imagelightbox"',
      allowedTypes: "all",
      preloadNext: false,
      onStart: startLightboxOverlay,
      enableKeyboard: false,
      quitOnImgClick: true,
      onEnd: endLightboxOverlay
    });
  })(jQuery);
};
