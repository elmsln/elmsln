(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
/**
 * This file will be compiled into foundation_access/js/dist/app.js
 *
 * To make changes to this file you must runt `grunt`.  
 * If you do not have grunt, please make edits directly 
 * to foundation_access/js/tweaks.js
 */

var imageLightbox = require('./components/imageLightbox.js');
var mediavideo = require('./components/mediavideo.js');

(function ($) {
  // Accessibility To Do:
  //
  // --------- Logic for exceptions ---------
  // Must not have the cursor in an input field!
  // No modifiers can be pressed
  // Must not currently be depressing mouse button
  //
  // --------- Off canvas outline ---------
  //
  // //// Keyboard Focusing ////
  // When a link in the subnav is in focus, ensure off canvas menu is open
  // Otherwise, close the off-canvas nav
  //
  // //// Key Bindings ////
  // currently visible back button: b, left arrow
  // Navigate up and down menu items (not sub items): up and down arrow
  // Close off canvas navigation: esc, x
  // Open submenu when focused on link: right arrow
  // Edit item if option is available: e
  //
  // --------- Modals ---------
  // //// Keyboard Focusing ////
  // When a modal is launched, move focus to the modal window
  // When modal is closed, move focus to previously focused item (modal's button??)
  //
  //
  // //// Key Bindings ////
  // close current modal: x, (esc is already set)
  //
  //  --------- System and Admin Tasks ---------
  // //// Key Bindings ////
  // print page: p
  // edit page: e
  // Bring up list of shortcuts: k

  if (typeof Drupal != 'undefined') {
    Drupal.behaviors.init = {
      attach: function (context, settings) {
        imageLightbox();
        mediavideo();
      }
    };
  }
  else {
    $(document).ready(function() {
      imageLightbox();
      mediavideo();
    });
  }

  Drupal.behaviors.foundation_access = {
    attach: function(context, settings) {
      if ($(".cis_accessibility_check a").length == 0) {
        $(".accessibility-content-toggle a").appendTo( ".cis_accessibility_check" );
      }
      $(".accessibility-content-toggle").hide();
    }
  };
  Drupal.settings.progressScroll ={scroll:0, total:0, scrollPercent:0};
  // sticky stuff
  Drupal.behaviors.stickyStuff = {
    attach: function (context, settings) {
      $('.r-header', context).sticky({topSpacing:4, width: '100%'});
      $('.page-scroll.progress', context).sticky({topSpacing:0}).addClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light']);
    }
  };
  // ability to disable background scrolling on modal open
  Drupal.behaviors.bodyScrollDisable = {
    attach: function (context, settings) {
      $('.disable-scroll', context).on("open.fndtn.reveal", function () {
        $("body").addClass("scroll-disabled");
      }).on("close.fndtn.reveal", function () {
        $("body").removeClass("scroll-disabled")
      });
    }
  };
  // Page Scrolling Progress Bar
  Drupal.progressScroll = {
    attach: function (context, settings) {
      // don't use the top bar in the calculation
      if ($(window).height() > $("#etb-tool-nav .inner-wrap", context)[0].offsetHeight) {
        Drupal.settings.progressScroll.scroll = $(window).scrollTop();
        Drupal.settings.progressScroll.total = $("#etb-tool-nav", context)[0].offsetTop;
      }
      else {
        Drupal.settings.progressScroll.scroll = $(window).scrollTop() - $("#etb-tool-nav", context)[0].offsetTop;
        Drupal.settings.progressScroll.total = $("#etb-tool-nav .inner-wrap", context)[0].offsetHeight - $(window).height();
      }
      Drupal.settings.progressScroll.scrollPercent = (Drupal.settings.progressScroll.scroll / Drupal.settings.progressScroll.total)*100;
      // set percentage of the meter to the scroll down the screen
      $(".page-scroll.progress .meter", context).css({"width": Drupal.settings.progressScroll.scrollPercent+"%"}).addClass(Drupal.settings.cis_lmsless['color']);
    }
  };

  // attach events to the window resizing / scrolling
  $(document).ready(function(){
    $(window).scroll(function () {
        Drupal.progressScroll.attach();
    });
    /* Implement customer javascript here */
    $(".disable-scroll").on("show", function () {
      $("body").addClass("scroll-disabled");
    }).on("hidden", function () {
      $("body").removeClass("scroll-disabled")
    });
    // reveal id
    $('*[data-reveal-id]').click(function () {
      var revealID = $(this).attr("data-reveal-id");
      var wrapper = $("#" + revealID);
      // If the wrapper element is open then give it focus
      if (wrapper.hasClass('open')) {
        wrapper.focus();
      }
    });
  });

})(jQuery);

},{"./components/imageLightbox.js":2,"./components/mediavideo.js":3}],2:[function(require,module,exports){
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

},{}],3:[function(require,module,exports){
module.exports = function() {
  (function ($) {
	  'use strict';

	  $(".mediavideo__open, .mediavideo__close").click(function(e) {
	  	e.preventDefault();
	    var videoContainer = $(this).parents('.mediavideo');

	    // Add the is-open tag to the base element.
	    videoContainer.toggleClass('mediavideo--is-open');

			videoContainer.find('*[data-mediavideo-src]').each(function() {
				var video = $(this);
				if (videoContainer.hasClass('mediavideo--is-open')) {
					// Give the animation enough time to complete.
					setTimeout(function() {
						startIframeVideo(video);
					}, 500);
				}
				else {
	    		stopIframeVideo(video);
	    	}
	    });
	  });

	  function startIframeVideo(video) {
			// Start the iframe videos.
			var videoIframeSrc = video.data('mediavideo-src');
			// If it's a youtube or vimeo video then add an autoplay attr on the end
			// of the url.
			if (videoIframeSrc.indexOf('youtube') >= 0 || videoIframeSrc.indexOf('vimeo') >= 0) {
				// Find out if we need to fstart the query parameter or add
				// on to an existing one.
		  	if (videoIframeSrc.indexOf('?') >= 0) {
		  		videoIframeSrc += '&autoplay=1';
		  	}
		  	else {
		  		videoIframeSrc += '?autoplay=1';
		  	}
			}
			// Add it to the source attribute to load the video.
			video.attr('src', videoIframeSrc);
	  }

	  function stopIframeVideo(video) {
	  	video.attr('src', '');
	  }
  })(jQuery);
};

},{}]},{},[1]);
