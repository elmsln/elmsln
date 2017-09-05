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
var clipboardjs = require('./components/clipboardjs.js');
(function ($) {
  if (typeof Drupal != 'undefined') {
    Drupal.behaviors.init = {
      attach: function (context, settings) {
        imageLightbox();
        mediavideo();
        clipboardjs();
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
  Drupal.settings.progressScroll ={scroll:0, total:0, scrollPercent:0, windowDividedByDocumentPercent:($(window).height() / $(document).height()) * 100,};
  // sticky stuff
  Drupal.behaviors.stickyStuff = {
    attach: function (context, settings) {
      $('.r-header').pushpin({offset: 4, top: $('.main-section').offset().top });
      $('.page-scroll.progress').pushpin({offset: 0, top: $('.main-section').offset().top });
    }
  };
  // Page Scrolling Progress Bar
  Drupal.progressScroll = {
    attach: function (context, settings) {
      // Only show the progressScoll if the height of the browser viewport / height of the html document is less than or equal to 50%.
      // (The page is at least 2x the height of the monitor.)
      if (Drupal.settings.progressScroll.windowDividedByDocumentPercent <= 50) {
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
        $(".page-scroll.progress .meter", context).css({"width": Drupal.settings.progressScroll.scrollPercent+"%"});
      }
    }
  };
  /**
   * behavior to make sure select lists are applied every time we do an ajax reload.
   */
  Drupal.behaviors.materializeCSS = {
    attach: function (context, settings) {
      // select lists but not the chosen ones
      $('select').not('.chosen').not('.cke_dialog_body select').not('.form-select.initialized').material_select();
    }
  };

  Drupal.settings.activeSideNav = null;

  // calculate the color difference between items
  // based on https://www.sitepoint.com/javascript-generate-lighter-darker-color/
  Drupal.ColorLuminance = function(hex, lum) {
    // validate hex string
    hex = String(hex).replace(/[^0-9a-f]/gi, '');
    if (hex.length < 6) {
      hex = hex[0]+hex[0]+hex[1]+hex[1]+hex[2]+hex[2];
    }
    lum = lum || 0;

    // convert to decimal and change luminosity
    var rgb = "#", c, i;
    for (i = 0; i < 3; i++) {
      c = parseInt(hex.substr(i*2,2), 16);
      c = Math.round(Math.min(Math.max(0, c + (c * lum)), 255)).toString(16);
      rgb += ("00"+c).substr(c.length);
    }

    return rgb;
  };
  // add support for accessibility of materialized components
  $(document).bind('keydown', function(event) {
    if (event.keyCode == 27) {
      $('.elmsln-dropdown-button.active').dropdown('close');
      // try closing all lightboxes
      var lightboxes = $('.lightbox--is-open .imagelightbox__close').trigger('click');
      if (lightboxes.length == 0) {
        var modals = $('.close-reveal-modal:visible').trigger('click');
      }
    }
  });
  // nice UI element to let us select users
  $('#edit-elmsln-view-user').click(function(event) {
    // prevent empty submission though this won't block incorrect submissions which would be page not found
    if ($('#edit-masquerade-user-field').val() != '' && $('#edit-masquerade-user-field').val() != 'Anonymous') {
      // force browser to this location, though we aren't garenteed this is a real place
      // but should be most of the time unless someone mistypes
      window.location = Drupal.settings.basePath + 'users/' + $('#edit-masquerade-user-field').val();
    }
  });
  // attach events to the window resizing / scrolling
  $(document).ready(function(){
    $(window).scroll(function () {
      Drupal.progressScroll.attach();
    });
    // ensure height of the body is cool w/ this floating column if it exists
    $('.views-exposed-form').each(function(){
      $('section.main-section').css('min-height', $('.views-exposed-form').outerHeight()+128);
    });
    $('.highlighted-block-area').each(function(){
      $('section.main-section').css('min-height', $('.highlighted-block-area').outerHeight()+48);
    });
    // hide accessibility button
    if ($('.cis_accessibility_check a').length == 0) {
      $('.accessibility-content-toggle a').appendTo('.cis_accessibility_check');
    }
    $('.accessibility-content-toggle').hide();
    // color luminance
    $('.list-colorluminance[data-colorluminance]').each(function(){
      var color=$(this).attr('data-colorluminance');
      var count = $(this).children('li').length;
      $(this).children('li').each(function(index, el) {
        var floor = (index/count);
        if (floor > .7) {
          floor = .7;
        }
        var luminance = Drupal.ColorLuminance(color, floor);
        $("<style type='text/css'> li.luminance-" + luminance.replace('#', '') + ":before { border-color:" + luminance + " !important; background:" + luminance + " !important;}</style>").appendTo("head");
        $(this).addClass('luminance-' + luminance.replace('#', ''));
      });
    });
    // load the next page if there is one and we see it on our screen
    $('[data-prefetch-scrollfire="true"]:visible').each(function(){
      var options = [
        {selector: '[href="' + $(this).attr('href') + '"]', offset: 0, callback: function(el) {
          $('head').append('<link rel="prefetch" href="' + $(el).attr('href')  + '?no-track">');
        }}
      ];
      Materialize.scrollFire(options);
    });
    // allow for prefetch on hover to prime the request
    $('[data-prefetch-hover="true"]').one('mouseenter', function(){
      var href = $(this).attr('href');
      if ($(this).attr('href').indexOf('?') == -1) {
        href += '?no-track';
      }
      else {
        href += '&no-track';
      }
      $('head').append('<link rel="prefetch" href="' + href + '"">');
    });
    // shortcode embed focus idea
    $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').focus(function() { $(this).select() });
    $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').mouseup(function(e){
      e.preventDefault();
    });
    // enable parallax
    $('.parallax').parallax();
    // normal carousel
    $('.carousel').not('.carousel-slider').carousel();
    // full size slider carousel
    $('.carousel-slider').carousel({full_width: true});
    // collapsible sets
    $('.collapsible').collapsible({
      accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
    });
    // dropdown items
    $('.elmsln-dropdown-button').dropdown({
      inDuration: 150,
      outDuration: 50,
      constrain_width: false,
      hover: false,
      gutter: 0,
      belowOrigin: true,
      alignment: 'left'
    });
    // modal items
    $('.elmsln-modal-trigger').bind('click', function() {
      // hide all currently visible modals
      $('.close-reveal-modal:visible').trigger('click');
    });
    $('.elmsln-modal').modal({
      dismissible: true, // Modal can be dismissed by clicking outside of the modal
      opacity: .5, // Opacity of modal background
      in_duration: 150, // Transition in duration
      out_duration: 50, // Transition out duration
      starting_top: '8rem', // Starting top style attribute
      ending_top: '8rem', // Ending top style attribute
      ready: function(modal, trigger) {
        $('.close-reveal-modal:visible').parents().focus();
      }, // Callback for Modal open
    });
    $(".resizable").resizable({
      maxHeight: 306,
      maxWidth: 630,
      minHeight: 10,
      minWidth: 10,
      handles: "e, s, se",
    });
    $('.elmsln-basic-gallery a').click(function(){
      // trigger the currently related featured image / text
      var img = $(this).children('img');
      var trigger = $(this).attr('data-elmsln-triggers');
      $('#' + trigger).attr('href', $(this).attr('data-elmsln-lightbox'));
      $('#' + trigger).children('.elmsln-featured-image-title').html($(img).attr('title'));
      $('#' + trigger).children('img').attr('src', $(img).attr('src')).attr('alt', $(img).attr('alt')).attr('title', $(img).attr('title'));
    });
    // close x's for modals
    $('.close-reveal-modal').click(function(){
      $('#' + $(this).parents().parents().attr('id')).modal('close');
      $('[href=#' + $(this).parents().attr('id') + '] paper-button').focus();
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
},{"./components/clipboardjs.js":2,"./components/imageLightbox.js":3,"./components/mediavideo.js":4}],2:[function(require,module,exports){
module.exports = function() {
  (function ($) {
    'use strict';
      // Replicate label if id exists with guid to match
      if (typeof Drupal.clipboard !== typeof undefined) {
        Drupal.clipboard.on('success', function (e) {
          var alertStyle = $(e.trigger).data('clipboardAlert');
          var alertText = $(e.trigger).data('clipboardAlertText');
          var target = $(e.trigger).data('clipboardTarget');

          // Display as Materialize toast.
          if (alertStyle === 'toast') {
            Materialize.toast(alertText, 2000);
          }
        });
      }
  })(jQuery);
};
},{}],3:[function(require,module,exports){
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
},{}],4:[function(require,module,exports){
module.exports = function() {
  (function ($) {
	  'use strict';
	  $(".mediavideo__open, .mediavideo__close").click(function(e) {
	  	e.preventDefault();
	    var videoContainer = $(this).parents('.mediavideo');
      var videoPoster = $(this).parents('.mediavideo-button-container');
      videoPoster.toggleClass('mediavideo-button-display');
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

// Sticky Plugin v1.0.0 for jQuery
// =============
// Author: Anthony Garand
// Improvements by German M. Bravo (Kronuz) and Ruud Kamphuis (ruudk)
// Improvements by Leonardo C. Daronco (daronco)
// Created: 2/14/2011
// Date: 2/12/2012
// Website: http://labs.anthonygarand.com/sticky
// Description: Makes an element on the page stick on the screen as you scroll
//       It will only set the 'top' and 'position' of your element, you
//       might need to adjust the width in some cases.

(function($) {
  var defaults = {
      topSpacing: 0,
      bottomSpacing: 0,
      className: 'is-sticky',
      wrapperClassName: 'sticky-wrapper',
      center: false,
      getWidthFrom: '',
      responsiveWidth: false
    },
    $window = $(window),
    $document = $(document),
    sticked = [],
    windowHeight = $window.height(),
    scroller = function() {
      var scrollTop = $window.scrollTop(),
        documentHeight = $document.height(),
        dwh = documentHeight - windowHeight,
        extra = (scrollTop > dwh) ? dwh - scrollTop : 0;

      for (var i = 0; i < sticked.length; i++) {
        var s = sticked[i],
          elementTop = s.stickyWrapper.offset().top,
          etse = elementTop - s.topSpacing - extra;

        if (scrollTop <= etse) {
          if (s.currentTop !== null) {
            s.stickyElement
              .css('width', '')
              .css('position', '')
              .css('top', '');
            s.stickyElement.trigger('sticky-end', [s]).parent().removeClass(s.className);
            s.currentTop = null;
          }
        }
        else {
          var newTop = documentHeight - s.stickyElement.outerHeight()
            - s.topSpacing - s.bottomSpacing - scrollTop - extra;
          if (newTop < 0) {
            newTop = newTop + s.topSpacing;
          } else {
            newTop = s.topSpacing;
          }
          if (s.currentTop != newTop) {
            s.stickyElement
              .css('width', s.stickyElement.width())
              .css('position', 'fixed')
              .css('top', newTop);

            if (typeof s.getWidthFrom !== 'undefined') {
              s.stickyElement.css('width', $(s.getWidthFrom).width());
            }

            s.stickyElement.trigger('sticky-start', [s]).parent().addClass(s.className);
            s.currentTop = newTop;
          }
        }
      }
    },
    resizer = function() {
      windowHeight = $window.height();

      for (var i = 0; i < sticked.length; i++) {
        var s = sticked[i];
        if (typeof s.getWidthFrom !== 'undefined' && s.responsiveWidth === true) {
          s.stickyElement.css('width', $(s.getWidthFrom).width());
        }
      }
    },
    methods = {
      init: function(options) {
        var o = $.extend({}, defaults, options);
        return this.each(function() {
          var stickyElement = $(this);

          var stickyId = stickyElement.attr('id');
          var wrapperId = stickyId ? stickyId + '-' + defaults.wrapperClassName : defaults.wrapperClassName 
          var wrapper = $('<div></div>')
            .attr('id', stickyId + '-sticky-wrapper')
            .addClass(o.wrapperClassName);
          stickyElement.wrapAll(wrapper);

          if (o.center) {
            stickyElement.parent().css({width:stickyElement.outerWidth(),marginLeft:"auto",marginRight:"auto"});
          }

          if (stickyElement.css("float") == "right") {
            stickyElement.css({"float":"none"}).parent().css({"float":"right"});
          }

          var stickyWrapper = stickyElement.parent();
          stickyWrapper.css('height', stickyElement.outerHeight());
          sticked.push({
            topSpacing: o.topSpacing,
            bottomSpacing: o.bottomSpacing,
            stickyElement: stickyElement,
            currentTop: null,
            stickyWrapper: stickyWrapper,
            className: o.className,
            getWidthFrom: o.getWidthFrom,
            responsiveWidth: o.responsiveWidth
          });
        });
      },
      update: scroller,
      unstick: function(options) {
        return this.each(function() {
          var unstickyElement = $(this);

          var removeIdx = -1;
          for (var i = 0; i < sticked.length; i++)
          {
            if (sticked[i].stickyElement.get(0) == unstickyElement.get(0))
            {
                removeIdx = i;
            }
          }
          if(removeIdx != -1)
          {
            sticked.splice(removeIdx,1);
            unstickyElement.unwrap();
            unstickyElement.removeAttr('style');
          }
        });
      }
    };

  // should be more efficient than using $window.scroll(scroller) and $window.resize(resizer):
  if (window.addEventListener) {
    window.addEventListener('scroll', scroller, false);
    window.addEventListener('resize', resizer, false);
  } else if (window.attachEvent) {
    window.attachEvent('onscroll', scroller);
    window.attachEvent('onresize', resizer);
  }

  $.fn.sticky = function(method) {
    if (methods[method]) {
      return methods[method].apply(this, Array.prototype.slice.call(arguments, 1));
    } else if (typeof method === 'object' || !method ) {
      return methods.init.apply( this, arguments );
    } else {
      $.error('Method ' + method + ' does not exist on jQuery.sticky');
    }
  };

  $.fn.unstick = function(method) {
    if (methods[method]) {
      return methods[method].apply(this, Array.prototype.slice.call(arguments, 1));
    } else if (typeof method === 'object' || !method ) {
      return methods.unstick.apply( this, arguments );
    } else {
      $.error('Method ' + method + ' does not exist on jQuery.sticky');
    }

  };
  $(function() {
    setTimeout(scroller, 0);
  });
})(jQuery);

/*
  By Osvaldas Valutis, www.osvaldas.info
  Available for use under the MIT License
*/

;( function( $, window, document, undefined )
{
  'use strict';

  var cssTransitionSupport = function()
    {
      var s = document.body || document.documentElement, s = s.style;
      if( s.WebkitTransition == '' ) return '-webkit-';
      if( s.MozTransition == '' ) return '-moz-';
      if( s.OTransition == '' ) return '-o-';
      if( s.transition == '' ) return '';
      return false;
    },

    isCssTransitionSupport = cssTransitionSupport() === false ? false : true,

    cssTransitionTranslateX = function( element, positionX, speed )
    {
      var options = {}, prefix = cssTransitionSupport();
      options[ prefix + 'transform' ]  = 'translateX(' + positionX + ')';
      options[ prefix + 'transition' ] = prefix + 'transform ' + speed + 's linear';
      element.css( options );
    },

    hasTouch  = ( 'ontouchstart' in window ),
    hasPointers = window.navigator.pointerEnabled || window.navigator.msPointerEnabled,
    wasTouched  = function( event )
    {
      if( hasTouch )
        return true;

      if( !hasPointers || typeof event === 'undefined' || typeof event.pointerType === 'undefined' )
        return false;

      if( typeof event.MSPOINTER_TYPE_MOUSE !== 'undefined' )
      {
        if( event.MSPOINTER_TYPE_MOUSE != event.pointerType )
          return true;
      }
      else
        if( event.pointerType != 'mouse' )
          return true;

      return false;
    };

  $.fn.imageLightbox = function( options )
  {
    var options    = $.extend(
             {
              selector:   'id="imagelightbox"',
              allowedTypes: 'png|jpg|jpeg|gif',
              animationSpeed: 250,
              preloadNext:  true,
              enableKeyboard: true,
              quitOnEnd:    false,
              quitOnImgClick: false,
              quitOnDocClick: true,
              onStart:    false,
              onEnd:      false,
              onLoadStart:  false,
              onLoadEnd:    false
             },
             options ),

      targets   = $([]),
      target    = $(),
      image   = $(),
      imageWidth  = 0,
      imageHeight = 0,
      swipeDiff = 0,
      inProgress  = false,

      isTargetValid = function( element )
      {
        if (options.allowedTypes == 'all') {
          return true;
        } else {
          return $( element ).prop( 'tagName' ).toLowerCase() == 'a' && ( new RegExp( '\.(' + options.allowedTypes + ')$', 'i' ) ).test( $( element ).attr( 'href' ) );
        }
      },

      setImage = function()
      {
        if( !image.length ) return false;

        var screenWidth  = $( window ).width() * 0.8,
          screenHeight = $( window ).height() * 0.9,
          tmpImage   = new Image();

        tmpImage.src  = image.attr( 'src' );
        tmpImage.onload = function()
        {
          imageWidth   = tmpImage.width;
          imageHeight  = tmpImage.height;

          if( imageWidth > screenWidth || imageHeight > screenHeight )
          {
            var ratio  = imageWidth / imageHeight > screenWidth / screenHeight ? imageWidth / screenWidth : imageHeight / screenHeight;
            imageWidth  /= ratio;
            imageHeight /= ratio;
          }

          image.css(
          {
            'width':  imageWidth + 'px',
            'height': imageHeight + 'px',
            'top':    ( $( window ).height() - imageHeight ) / 2 + 'px',
            'left':   ( $( window ).width() - imageWidth ) / 2 + 'px'
          });
        };
      },

      loadImage = function( direction )
      {
        if( inProgress ) return false;

        direction = typeof direction === 'undefined' ? false : direction == 'left' ? 1 : -1;

        if( image.length )
        {
          if( direction !== false && ( targets.length < 2 || ( options.quitOnEnd === true && ( ( direction === -1 && targets.index( target ) == 0 ) || ( direction === 1 && targets.index( target ) == targets.length - 1 ) ) ) ) )
          {
            quitLightbox();
            return false;
          }
          var params = { 'opacity': 0 };
          if( isCssTransitionSupport ) cssTransitionTranslateX( image, ( 100 * direction ) - swipeDiff + 'px', options.animationSpeed / 1000 );
          else params.left = parseInt( image.css( 'left' ) ) + 100 * direction + 'px';
          image.animate( params, options.animationSpeed, function(){ removeImage(); });
          swipeDiff = 0;
        }

        inProgress = true;
        if( options.onLoadStart !== false ) options.onLoadStart();

        setTimeout( function()
        {
          image = $( '<img ' + options.selector + ' />' )
          .attr( 'src', target.attr( 'href' ) )
          .load( function()
          {
            image.appendTo( 'body' );
            setImage();

            var params = { 'opacity': 1 };

            image.css( 'opacity', 0 );
            if( isCssTransitionSupport )
            {
              cssTransitionTranslateX( image, -100 * direction + 'px', 0 );
              setTimeout( function(){ cssTransitionTranslateX( image, 0 + 'px', options.animationSpeed / 1000 ) }, 50 );
            }
            else
            {
              var imagePosLeft = parseInt( image.css( 'left' ) );
              params.left = imagePosLeft + 'px';
              image.css( 'left', imagePosLeft - 100 * direction + 'px' );
            }

            image.animate( params, options.animationSpeed, function()
            {
              inProgress = false;
              if( options.onLoadEnd !== false ) options.onLoadEnd();
            });
            if( options.preloadNext )
            {
              var nextTarget = targets.eq( targets.index( target ) + 1 );
              if( !nextTarget.length ) nextTarget = targets.eq( 0 );
              $( '<img />' ).attr( 'src', nextTarget.attr( 'href' ) ).load();
            }
          })
          .error( function()
          {
            if( options.onLoadEnd !== false ) options.onLoadEnd();
          })

          var swipeStart   = 0,
            swipeEnd   = 0,
            imagePosLeft = 0;

          image.on( hasPointers ? 'pointerup MSPointerUp' : 'click', function( e )
          {
            e.preventDefault();
            if( options.quitOnImgClick )
            {
              quitLightbox();
              return false;
            }
            if( wasTouched( e.originalEvent ) ) return true;
              var posX = ( e.pageX || e.originalEvent.pageX ) - e.target.offsetLeft;
            target = targets.eq( targets.index( target ) - ( imageWidth / 2 > posX ? 1 : -1 ) );
            if( !target.length ) target = targets.eq( imageWidth / 2 > posX ? targets.length : 0 );
            loadImage( imageWidth / 2 > posX ? 'left' : 'right' );
          })
          .on( 'touchstart pointerdown MSPointerDown', function( e )
          {
            if( !wasTouched( e.originalEvent ) || options.quitOnImgClick ) return true;
            if( isCssTransitionSupport ) imagePosLeft = parseInt( image.css( 'left' ) );
            swipeStart = e.originalEvent.pageX || e.originalEvent.touches[ 0 ].pageX;
          })
          .on( 'touchmove pointermove MSPointerMove', function( e )
          {
            if( !wasTouched( e.originalEvent ) || options.quitOnImgClick ) return true;
            e.preventDefault();
            swipeEnd = e.originalEvent.pageX || e.originalEvent.touches[ 0 ].pageX;
            swipeDiff = swipeStart - swipeEnd;
            if( isCssTransitionSupport ) cssTransitionTranslateX( image, -swipeDiff + 'px', 0 );
            else image.css( 'left', imagePosLeft - swipeDiff + 'px' );
          })
          .on( 'touchend touchcancel pointerup MSPointerUp', function( e )
          {
            if( !wasTouched( e.originalEvent ) || options.quitOnImgClick ) return true;
            if( Math.abs( swipeDiff ) > 50 )
            {
              target = targets.eq( targets.index( target ) - ( swipeDiff < 0 ? 1 : -1 ) );
              if( !target.length ) target = targets.eq( swipeDiff < 0 ? targets.length : 0 );
              loadImage( swipeDiff > 0 ? 'right' : 'left' );
            }
            else
            {
              if( isCssTransitionSupport ) cssTransitionTranslateX( image, 0 + 'px', options.animationSpeed / 1000 );
              else image.animate({ 'left': imagePosLeft + 'px' }, options.animationSpeed / 2 );
            }
          });

        }, options.animationSpeed + 100 );
      },

      removeImage = function()
      {
        if( !image.length ) return false;
        image.remove();
        image = $();
      },

      quitLightbox = function()
      {
        if( !image.length ) return false;
        image.animate({ 'opacity': 0 }, options.animationSpeed, function()
        {
          removeImage();
          inProgress = false;
          if( options.onEnd !== false ) options.onEnd();
        });
      };

    $( window ).on( 'resize', setImage );

    if( options.quitOnDocClick )
    {
      $( document ).on( hasTouch ? 'touchend' : 'click', function( e )
      {
        if( image.length && !$( e.target ).is( image ) ) quitLightbox();
      })
    }

    if( options.enableKeyboard )
    {
      $( document ).on( 'keyup', function( e )
      {
        if( !image.length ) return true;
        e.preventDefault();
        if( e.keyCode == 27 ) quitLightbox();
        if( e.keyCode == 37 || e.keyCode == 39 )
        {
          target = targets.eq( targets.index( target ) - ( e.keyCode == 37 ? 1 : -1 ) );
          if( !target.length ) target = targets.eq( e.keyCode == 37 ? targets.length : 0 );
          loadImage( e.keyCode == 37 ? 'left' : 'right' );
        }
      });
    }

    $( document ).on( 'click', this.selector, function( e )
    {
      if( !isTargetValid( this ) ) return true;
      e.preventDefault();
      if( inProgress ) return false;
      inProgress = false;
      if( options.onStart !== false ) options.onStart();
      target = $( this );
      loadImage();
    });

    this.each( function()
    {
      if( !isTargetValid( this ) ) return true;
      targets = targets.add( $( this ) );
    });

    this.switchImageLightbox = function( index )
    {
      var tmpTarget = targets.eq( index );
      if( tmpTarget.length )
      {
        var currentIndex = targets.index( target );
        target = tmpTarget;
        loadImage( index < currentIndex ? 'left' : 'right' );
      }
      return this;
    };

    this.quitImageLightbox = function()
    {
      quitLightbox();
      return this;
    };

    return this;
  };
})( jQuery, window, document );
