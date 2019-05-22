/*! modernizr 3.5.0 (Custom Build) | MIT *
 * https://modernizr.com/download/?-arrow-es6array-es6collections-es6math-es6number-es6object-es6string-generators-promises-setclasses !*/
!function(window,document,undefined){function is(e,n){return typeof e===n}function testRunner(){var e,n,r,t,o,i,s;for(var a in tests)if(tests.hasOwnProperty(a)){if(e=[],n=tests[a],n.name&&(e.push(n.name.toLowerCase()),n.options&&n.options.aliases&&n.options.aliases.length))for(r=0;r<n.options.aliases.length;r++)e.push(n.options.aliases[r].toLowerCase());for(t=is(n.fn,"function")?n.fn():n.fn,o=0;o<e.length;o++)i=e[o],s=i.split("."),1===s.length?Modernizr[s[0]]=t:(!Modernizr[s[0]]||Modernizr[s[0]]instanceof Boolean||(Modernizr[s[0]]=new Boolean(Modernizr[s[0]])),Modernizr[s[0]][s[1]]=t),classes.push((t?"":"no-")+s.join("-"))}}function setClasses(e){var n=docElement.className,r=Modernizr._config.classPrefix||"";if(isSVG&&(n=n.baseVal),Modernizr._config.enableJSClass){var t=new RegExp("(^|\\s)"+r+"no-js(\\s|$)");n=n.replace(t,"$1"+r+"js$2")}Modernizr._config.enableClasses&&(n+=" "+r+e.join(" "+r),isSVG?docElement.className.baseVal=n:docElement.className=n)}var classes=[],tests=[],ModernizrProto={_version:"3.5.0",_config:{classPrefix:"",enableClasses:!0,enableJSClass:!0,usePrefixes:!0},_q:[],on:function(e,n){var r=this;setTimeout(function(){n(r[e])},0)},addTest:function(e,n,r){tests.push({name:e,fn:n,options:r})},addAsyncTest:function(e){tests.push({name:null,fn:e})}},Modernizr=function(){};Modernizr.prototype=ModernizrProto,Modernizr=new Modernizr,Modernizr.addTest("es6object",!!(Object.assign&&Object.is&&Object.setPrototypeOf)),Modernizr.addTest("es6array",!!(Array.prototype&&Array.prototype.copyWithin&&Array.prototype.fill&&Array.prototype.find&&Array.prototype.findIndex&&Array.prototype.keys&&Array.prototype.entries&&Array.prototype.values&&Array.from&&Array.of)),Modernizr.addTest("arrow",function(){try{eval("()=>{}")}catch(e){return!1}return!0}),Modernizr.addTest("es6collections",!!(window.Map&&window.Set&&window.WeakMap&&window.WeakSet)),Modernizr.addTest("generators",function(){try{new Function("function* test() {}")()}catch(e){return!1}return!0}),Modernizr.addTest("es6math",!!(Math&&Math.clz32&&Math.cbrt&&Math.imul&&Math.sign&&Math.log10&&Math.log2&&Math.log1p&&Math.expm1&&Math.cosh&&Math.sinh&&Math.tanh&&Math.acosh&&Math.asinh&&Math.atanh&&Math.hypot&&Math.trunc&&Math.fround)),Modernizr.addTest("es6number",!!(Number.isFinite&&Number.isInteger&&Number.isSafeInteger&&Number.isNaN&&Number.parseInt&&Number.parseFloat&&Number.isInteger(Number.MAX_SAFE_INTEGER)&&Number.isInteger(Number.MIN_SAFE_INTEGER)&&Number.isFinite(Number.EPSILON))),Modernizr.addTest("promises",function(){return"Promise"in window&&"resolve"in window.Promise&&"reject"in window.Promise&&"all"in window.Promise&&"race"in window.Promise&&function(){var e;return new window.Promise(function(n){e=n}),"function"==typeof e}()});var docElement=document.documentElement,isSVG="svg"===docElement.nodeName.toLowerCase();Modernizr.addTest("es6string",!!(String.fromCodePoint&&String.raw&&String.prototype.codePointAt&&String.prototype.repeat&&String.prototype.startsWith&&String.prototype.endsWith&&String.prototype.includes)),testRunner(),setClasses(classes),delete ModernizrProto.addTest,delete ModernizrProto.addAsyncTest;for(var i=0;i<Modernizr._q.length;i++)Modernizr._q[i]();window.Modernizr=Modernizr}(window,document);
if (!String.prototype.startsWith) {String.prototype.startsWith = function(searchString, position){position = position || 0;return this.substr(position, searchString.length) === searchString;};}
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
  /**
   * Scrollspy behavior.
   */
  Drupal.behaviors.scrollSpy = {
    attach: function(context, settings) {
      const scrollSpyNav = $('#scrollspy-nav').offset()
      if (typeof scrollSpyNav !== typeof undefined) {
        // target data property and convert to scrollspy class addition
        $('h2[data-scrollspy="scrollspy"],h3[data-scrollspy="scrollspy"],h4[data-scrollspy="scrollspy"]').addClass('scrollspy');
        // activate class
        $('.scrollspy').scrollSpy();
        // the pushpin should start after the user has scrolled past
        // the navigation block. This is mainly to prevent the scrollspy-toc
        // from covering up the navigation items below it.
        const nav = $('#block-mooc-nav-block-mooc-nav-nav')
        const pushpinStart = Math.ceil(scrollSpyNav.top + nav.height())
        $('.scrollspy-toc').pushpin({ offset: 48, top: pushpinStart });
      }
    }
  };
  /**
   * behavior to make sure select lists are applied every time we do an ajax reload.
   */
  Drupal.behaviors.materializeCSS = {
    attach: function (context, settings) {
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
    
    // shortcode embed focus idea
    $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').focus(function() { $(this).select() });
    $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').mouseup(function(e){
      e.preventDefault();
    });
    // normal carousel
    $('.carousel').not('.carousel-slider').carousel();
    // full size slider carousel
    $('.carousel-slider').carousel({full_width: true});
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

  // attach events to the window
  $(document).ready(function(){
    // ensure height of the body is cool w/ this floating column if it exists
    $('.views-exposed-form').each(function(){
      $('section.main-section').css('min-height', $('.views-exposed-form').outerHeight()+128);
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
