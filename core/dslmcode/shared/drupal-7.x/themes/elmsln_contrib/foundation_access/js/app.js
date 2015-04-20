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

  Drupal.behaviors.foundation_access = {
    attach: function(context, settings) {
      $(".accessibility-content-toggle a").appendTo( ".cis_accessibility_check" );
      $(".accessibility-content-toggle").hide();
    }
  };
  Drupal.settings.progressScroll ={scroll:0, total:0, scrollPercent:0};
  // sticky stuff
  Drupal.behaviors.stickyStuff = {
    attach: function (context, settings) {
      $('.page-scroll.progress', context).sticky({topSpacing:0});
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
      Drupal.settings.progressScroll.scroll = $(window).scrollTop() - $("#etb-tool-nav", context)[0].offsetTop;
      Drupal.settings.progressScroll.total = $("#etb-tool-nav .inner-wrap", context)[0].offsetHeight - $(window).height();
      Drupal.settings.progressScroll.scrollPercent = (Drupal.settings.progressScroll.scroll / Drupal.settings.progressScroll.total)*100;
      // set percentage of the meter to the scroll down the screen
      $(".page-scroll.progress .meter", context).css({"width": Drupal.settings.progressScroll.scrollPercent+"%"});
      if (Drupal.settings.progressScroll.scrollPercent < 25 ) {
        $(".page-scroll.progress .meter").css({backgroundColor:"#4b4b4b"});
      }
      if (Drupal.settings.progressScroll.scrollPercent > 25 && Drupal.settings.progressScroll.scrollPercent < 50) {
        $(".page-scroll.progress .meter").css({backgroundColor:"#3b3b3b"});
      }
      if (Drupal.settings.progressScroll.scrollPercent > 50 && Drupal.settings.progressScroll.scrollPercent < 75) {
        $(".page-scroll.progress .meter").css({backgroundColor:'#2b2b2b'});
      }
      if (Drupal.settings.progressScroll.scrollPercent > 75) {
        $(".page-scroll.progress .meter").css({backgroundColor:'#1b1b1b'});
      }
      if (Drupal.settings.progressScroll.scrollPercent > 100) {
        $(".page-scroll.progress .meter").css({backgroundColor:'#000000'});
      }
    }
  };

  // Function for making the offcanvas menu height stretch down to the footer

  Drupal.offcanvasHeight = {
    attach: function (context, settings) {

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
  };

  Drupal.offcanvasSubmenuHeight = {
    attach: function (context, settings) {

      ////// This corrects the vertical height of the offcanvas sub-navigation panels
      $("ul.off-canvas-list .left-submenu", context).css({"min-height": "0"}); // Clear the min-height
      var remBase = parseInt($("body").css('font-size')); // Detect base px size for REM calculation
      var offCanvasMenuHeight = $(".content-outline-navigation", context)[0].offsetHeight;
      var remOffCanvasMenuOffset = offCanvasMenuHeight / remBase; // Divdes by remBase to get size in REMs
      $("ul.off-canvas-list .left-submenu", context).css({"min-height": remOffCanvasMenuOffset+"rem"}); // Add the min-height to the wrapper
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

  $(window).resize(function() {
  		Drupal.offcanvasHeight.attach();
      Drupal.offcanvasSubmenuHeight.attach();
	});
  $(window).scroll(function () {
      Drupal.progressScroll.attach();
  });

})(jQuery);
