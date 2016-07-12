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
      $('.r-header', context).sticky({topSpacing:4, width: '100%'}).css({backgroundColor: '#FFFFFF',width: '100%'});
      $('.page-scroll.progress', context).sticky({topSpacing:0}).css('background-color','#EEEEEE');
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
      $(".page-scroll.progress .meter", context).css({backgroundColor:"#222222", "width": Drupal.settings.progressScroll.scrollPercent+"%"});
    }
  };

  // Function for making the offcanvas menu height stretch down to the footer

  Drupal.offcanvasHeight = {
    attach: function (context, settings) {
      // ensure we have everything first
      if ($("footer", context).length > 0 && $("#etb-tool-nav", context).length > 0) {
        ////// This corrects the vertical height of the offcanvas wrapper to fill the open space on the page
        $(".off-canvas-wrap .inner-wrap", context).css({"min-height": "0"}); // Clear the min-height
        var footerOffset = $("footer", context)[0].offsetTop; // Detect top offset of footer
        var offcanvasOffset = $("#etb-tool-nav", context)[0].offsetTop; // Detect top offset of offcanvas nav
        var contentnavOffset = footerOffset - offcanvasOffset; // Figure out how tall the offcanvas menu should be
        var remBase = parseInt($("body").css('font-size')); // Detect base px size for REM calculation

        // var remSize = parseInt(remBase); // Remove px from remBase
        var remOffCanvasOffset = contentnavOffset / remBase; // Divdes by remBase to get size in REMs
        $(".off-canvas-wrap .inner-wrap", context).css({"min-height": remOffCanvasOffset+"rem"}); // Add the min-height to the wrapper
      }
    }
  };

  Drupal.offcanvasSubmenuHeight = {
    attach: function (context, settings) {
      ////// This corrects the vertical height of the offcanvas sub-navigation panels
      if ($("#left-off-canvas-wrapper").length > 0) {
        $("ul.off-canvas-list .left-submenu", context).css({"min-height": "0"}); // Clear the min-height
        var remBase = parseInt($("body").css('font-size')); // Detect base px size for REM calculation
        var offCanvasMenuHeight = $("#left-off-canvas-wrapper")[0].offsetHeight;
        var remOffCanvasMenuOffset = offCanvasMenuHeight / remBase; // Divdes by remBase to get size in REMs
        $("ul.off-canvas-list .left-submenu", context).css({"min-height": remOffCanvasMenuOffset+"rem"}); // Add the min-height to the wrapper
      }
    }
  };

  Drupal.behaviors.offcanvasSubmenuClick = {
    attach:function(context, settings) {

      $("li.has-submenu a:not(li.back a)", context).click(function() {
        // Capture scroll position of container
        Drupal.settings.leftOffCanvasScrollHeight = $(".left-off-canvas-menu", context)[0].scrollTop;
        Drupal.settings.leftOffCanvasScrollWindow = parseInt($("body").scrollTop());

        // Run height fix
        Drupal.offcanvasSubmenuHeight.attach();

        // Scroll to top
        $('body').animate({scrollTop:$("#etb-tool-nav", context)[0].offsetTop},0);
        $(".left-off-canvas-menu").animate({scrollTop:0},0); // Scroll to top of menu
      });

      $("li.back a", context).click(function() {
        //Scroll to x position of the container before submenu was clicked
        $(".left-off-canvas-menu").animate({scrollTop:Drupal.settings.leftOffCanvasScrollHeight},0); // Scroll to top of menu
        $('body').animate({scrollTop:Drupal.settings.leftOffCanvasScrollWindow},0);
      });

    }
  };
  // attach events to the window resizing / scrolling
  $(document).ready(function(){
    $(window).on('resize', function() {
      Drupal.offcanvasHeight.attach();
      Drupal.offcanvasSubmenuHeight.attach();
    });
    $(window).scroll(function () {
        Drupal.progressScroll.attach();
    });
    // forcibly call these to fire the first time
    Drupal.offcanvasHeight.attach();
    Drupal.offcanvasSubmenuHeight.attach();
    /* Implement customer javascript here */
    $(".disable-scroll").on("show", function () {
      $("body").addClass("scroll-disabled");
    }).on("hidden", function () {
      $("body").removeClass("scroll-disabled")
    });

    $('*[data-reveal-id]').click(function () {
      var revealID = $(this).attr("data-reveal-id");
      var wrapper = $("#" + revealID);
      // If the wrapper element is open then give it focus
      if (wrapper.hasClass('open')) {
        wrapper.focus();
      }
    });

    $(window).foundation();
  });

})(jQuery);
