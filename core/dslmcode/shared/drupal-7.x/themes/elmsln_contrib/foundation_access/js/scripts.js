(function ($, Drupal) {

  Drupal.behaviors.foundation_access = {
    attach: function(context, settings) {
      //Get your Yeti started.

      //////////
      //sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
      //////////

      //////////
      //Add debounce function:
      //http://davidwalsh.name/javascript-debounce-function
      //////////

      //////////
      //Look at waypoints
      //http://imakewebthings.com/jquery-waypoints/
      //////////

      //////////
      //Global Active Outline Accordion Menu
      //block--cis-service-connection--active-outline.tpl.php
      $('#fulloutline .accordion').hide(); //hide accordion items on page load
      $('.accordion-btn').click(function() {//toggle the clicked dl item
        var $this = $(this);
        $('.accordion-btn').addClass('active');
        $('.accordion').not($this.next()).hide(); // close all items except for current clicked item
        $('.accordion-btn').not($this.next()).removeClass('active');
        $this.next().toggle(); // open or close cliked item
      });
      // deep active trail make sure its open if needed
      $('#activeoutline .accordion .content a.active-trail').parent().parent().prev().click();

      ////////////
      // Action Menu Links
      // page.tpl.php
      ////////////

      // Move accessibility link to action-links menu
      $( ".accessibility-content-toggle a" ).appendTo( ".action-links-bar ul" ).wrap("<li></li>");
      $( ".accessibility-content-toggle").hide();

      ////////////
      // Scroll to top of page
      // page.tpl.php
      ////////////

      $('#banner-image-sticky').click(function() {//toggle the clicked dl item
        $('html, body').animate({scrollTop: "0px"}, 800); // close all items except for current clicked item
      });

      // Window Height Variable
      var windowHeight = $(window).height();
      // var windowTop = $(window).scrollTop();
      var topOffsetlmsless = $('#lmsless-bar').offset().top; // Top location LMSLess Bar (top-most nav bar)
      var heightlmsless = $('#lmsless-bar').outerHeight(true); // Height of LMSLess Bar (top-most nav bar)
      var bottomOffsetlmsless = heightlmsless + topOffsetlmsless + 10; // Bottom location LMSLess Bar (top-most nav bar)
      // Banner Image Variables
      var topOffsetBanner = $('#banner-image').offset().top; // returns number
      var heightBanner = $('#banner-image').outerHeight(true);
      var bottomOffsetBanner = heightBanner + topOffsetBanner - heightlmsless + 10; // returns number
      // Topbar Nav Variables
      var topOffsetTopbarnav = $('#topbarnav').offset().top; // returns number
      var heightTopbarnav = $('#topbarnav').outerHeight(true); // returns number
      var bottomOffsetTopbarnav = heightTopbarnav + topOffsetTopbarnav; // returns number
      // Sticky Elements Height Variables
      var heightTopbarNavSticky = $('#topbarnav-sticky').outerHeight(); // height of sticky topbar
      var heightBannerImageSticky = $('#banner-image-sticky').outerHeight(); // height of sticky topbar
      var heightlmslessSticky = $('#lmsless-bar-sticky').outerHeight(); // height of sticky LMSLess Bar
      var topOffsetTopbarNavSticky = $('#topbarnav-sticky').offset().top;
      var bottomTopbarNavSticky = topOffsetTopbarNavSticky + heightTopbarNavSticky;

      // This variable is reporting the wrong height. Fix.
      var totalHeightStickies = heightTopbarNavSticky + heightBannerImageSticky;

      function setLmsless() {
        var windowTop = $(window).scrollTop();
        if (bottomOffsetlmsless < windowTop) { // Go into sticky mode
          $('#lmsless-bar-sticky').addClass( "locator" );
        }
        else {
          $('#lmsless-bar-sticky').removeClass( "locator" );
        }
      }

      function setBanner() {
        var windowTop = $(window).scrollTop();
        if (bottomOffsetBanner < windowTop) { // Go into sticky mode
          $('#banner-image-sticky').addClass( "locator" );
        }
        else { // Do not go into sticky mode
        	$('#banner-image-sticky').removeClass( "locator" );
        }
      }

      function setTopbarnav() {
        var windowTop = $(window).scrollTop();
        if (bottomOffsetTopbarnav < windowTop) { // Go into sticky mode
          $('#topbarnav-sticky').addClass( "locator" );
        }
        else { // Do not go into sticky mode
        $('#topbarnav-sticky').removeClass( "locator" );
          }
      }

      function resizeContent() {
        /////////
        /// To Do:
        /// 1. Instead of hiding upon resize, disable dynamic top-margin so users can scroll the menu
        /// 2. Transfer keyboard focus to equivelant button when changing to sticky menu for accessibility
        ////////

        // Reset these variables each time you resize the browser
        var windowTop = $(window).scrollTop();
        var windowHeight = $(window).height();
        var heightBannerImageSticky = $('#banner-image-sticky').outerHeight();
        var heightTopbarNavSticky = $('#topbarnav-sticky').outerHeight(); // height of sticky topbar
        var totalHeightStickies = heightTopbarNavSticky + heightBannerImageSticky;

      }


      $(window).resize(function() {
        resizeContent();
      });
      // When you scroll the browser, do these things
      $(window).scroll(function(){
        setLmsless();
        setBanner();
        setTopbarnav();
        resizeContent();
      });
      // Let's kick things off right
      resizeContent();
      setLmsless();
      setBanner();
      setTopbarnav();
    }
  };
})(jQuery, Drupal);
