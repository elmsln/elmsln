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
