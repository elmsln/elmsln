(function ($, Drupal) {

	Drupal.behaviors.foundation_access = {
		attach: function(context, settings) {
			// Get your Yeti started.
			
			////////////
			// sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
			////////////
			
			////////////
			// Global Active Outline Accordion Menu
			// block--cis-service-connection--active-outline.tpl.php
			// 
			// To Do:
			// 1. Make separate menus for static and sticky
			//////////// 
			
			
			$('.accordion').hide(); //hide accordion items on page load
			$('.accordion-btn').click(function() {//toggle the clicked dl item
				var $this = $(this);
				//$('.accordion-btn').addClass('active');
				$('.accordion').not($this.next()).hide(); // close all items except for current clicked item
				//$('.accordion-btn').not($this.next()).removeClass('active');
				$this.next().toggle(); // open or close cliked item
			});

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
			var topOffsetlmsless = $('#lmsless-bar').offset().top; // returns number
			var heightlmsless = $('#lmsless-bar').outerHeight(true); // NOT USED DIRECTLY
			var bottomOffsetlmsless = heightlmsless + topOffsetlmsless + 10; // returns number NOT USED DIRECTLY
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
			// Active Outline Variables
			var topOffsetOutlineNav = $('#activeoutline').offset().top;
			var heightOutlineNav = $('#activeoutline').outerHeight(true);
			var bottomOffsetOutlineNav = heightOutlineNav + topOffsetOutlineNav; // TODO - figure out why I need 50px more
			// Height of space above visible area in window
			// Active Outline Height Variable
			var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight();
			// Total Height Sticky Elements Height Variables
			
			var topOffsetOutlineNavSticky = $('#activeoutline-sticky').offset().top;
			var heightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(true);
			var bottomOffsetOutlineNavSticky = heightOutlineNavSticky + topOffsetOutlineNavSticky;


			// TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// This variable is reporting the wrong height. Fix.
			var totalHeightStickies = insideHeightOutlineNavSticky + heightTopbarNavSticky + heightBannerImageSticky;



			var scrollDiffBottom = bottomOffsetOutlineNavSticky + windowHeight;
			// Figure out how to get this value
			var scrollDiffTop = "distance between top of outline nav and bottom of Topbarnav" + bottomOffsetTopbarnav;

			function activeOutlineDiffScroll() {
				$('#activeoutline-sticky').css({marginTop: - scrollDiffTop}); // Subtract margin
			}

			// /TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			function showStickyOutline() {
				var windowTop = $(window).scrollTop();
				$('#activeoutline-sticky').css({display:'block', marginTop: windowTop - bottomOffsetTopbarnav }); // Set sticky active outline to visible and relocate within view // Set sticky active outline to visible
				console.log("show");
			}

			function compactStickyOutline() {
				$('#activeoutline-sticky').removeClass( "compact-mode" ).addClass( "compact-mode" );
				console.log("compactorize!");
			}

			function unCompactStickyOutline() {
				$('#activeoutline-sticky').removeClass( "compact-mode" );
				console.log("un compactorize!");
			}

			function setLmsless() {
				var windowTop = $(window).scrollTop();
				console.log("setLmsless function reporting for duty!");
				if (bottomOffsetlmsless < windowTop) { // Go into sticky mode
					$('#lmsless-bar-sticky').addClass( "locator" );
					
				}
			    else { // Do not go into sticky mode
					$('#lmsless-bar-sticky').removeClass( "locator" );
			    }
			}

			function setBanner() {
				var windowTop = $(window).scrollTop();
				console.log("setBanner function reporting for duty!");
				if (bottomOffsetBanner < windowTop) { // Go into sticky mode
					$('#banner-image-sticky').addClass( "locator" );
				}
			    else { // Do not go into sticky mode
					$('#banner-image-sticky').removeClass( "locator" );
			    }
			}

			function setTopbarnav() {
				var windowTop = $(window).scrollTop();
				console.log("setTopbarnav function reporting for duty!");
				if (bottomOffsetTopbarnav < windowTop) { // Go into sticky mode
					$('#topbarnav-sticky').addClass( "locator" );
				}
			    else { // Do not go into sticky mode
					$('#topbarnav-sticky').removeClass( "locator" );
			    }
			}

			function setActiveOutline() {
				var windowTop = $(window).scrollTop();
				console.log("setActiveOutline function reporting for duty!");
				// If the top of the Active Outline is off screen to the top AND the height of the window is GREATER than the height of the stickies
				if (topOffsetOutlineNav < windowTop && windowHeight > totalHeightStickies) { // Go into sticky mode
					console.log("normal sticky");
					$('#activeoutline-sticky').css({display: 'block', marginTop: windowTop - bottomOffsetTopbarnav });
				}

// TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				// If the top of the Active Outline is off screen to the top AND the height of the window is LESS than the height of the stickies
				else if (topOffsetOutlineNav - 100 < windowTop && windowHeight < totalHeightStickies) { // Go into sticky mode
					console.log("follow down sticky");
					$('#activeoutline-sticky').css({marginTop: windowTop + bottomOffsetTopbarnav });
					// Add top Margin so the top of the active outline is in view
					// It should be allowed off screen by 30% before it moves itself into place
				}
				// If the bottom of the Active Outline is off screen to the top AND the height of the window is LESS than the height of the stickies
				else if (bottomOffsetOutlineNav + 100 > windowTop + windowHeight && windowHeight < totalHeightStickies) { // Go into sticky mode
					console.log("follow up sticky");
					$('#activeoutline-sticky').css({marginTop: windowTop + totalHeightStickies });
					// Reduce the top margin so the bottom of active outline is in view
					// It should be allowed off screen by 30% before it moves itself into place
					
				}

// /TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// if the window is smaller than the active outline, then do not adjust margin
				// 
			    else { // Do not go into sticky mode
					$('#activeoutline-sticky').css({display:'none', marginTop: 0});
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
				var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight();
				var heightBannerImageSticky = $('#banner-image-sticky').outerHeight();
				var heightTopbarNavSticky = $('#topbarnav-sticky').outerHeight(); // height of sticky topbar
				var totalHeightStickies = insideHeightOutlineNavSticky + heightTopbarNavSticky + heightBannerImageSticky;

				console.log("windowHeight");
				console.log(windowHeight);
				console.log("Window Top");
				console.log(windowTop);
				console.log("totalHeightStickies");
				console.log(totalHeightStickies);
				console.log("insideHeightOutlineNavSticky");
				console.log(insideHeightOutlineNavSticky);
				console.log("heightOutlineNavSticky");
				console.log(insideHeightOutlineNavSticky);
				
				

				// if the height of the window is smaller than the total height of all stickies AND we are not scrolled within view of the original navigation
				if (windowHeight < totalHeightStickies && bottomOffsetOutlineNav < windowTop) {
					compactStickyOutline();
				}
				// if the height of the window is larger than the total height of all stickies AND we are scrolled within view of the original navigation
				else if (windowHeight > totalHeightStickies && bottomOffsetOutlineNav > windowTop) {
					compactStickyOutline();
				}
				// if the height of the window is smaller than the total height of all stickies AND we are not scrolled within view of the original navigation
				// else if (windowHeight < totalHeightStickies && bottomOffsetOutlineNav < windowTop) {
				// compactStickyOutline();
				// }
				// if the height of the window is larger than the total height of all stickies AND we are not scrolled within view of the original navigation
				else if (windowHeight > totalHeightStickies && bottomOffsetOutlineNav < windowTop) {
					unCompactStickyOutline();
					
// TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					// Merge into setActiveOutline function
					
					// If you scroll too far up past the top, adjust the sticky nav's topmmargin accordingly
					// if (bottomOffsetOutlineNavSticky -  insideHeightOutlineNavSticky > windowHeight + 10) {
					//	console.log("scrolled past top");
					// }
					// // If you scroll too far past the buttom, adjust the margin accordingly
					// else if (bottomOffsetOutlineNavSticky < windowHeight + 10) {
					//	console.log("scrolled past bottom");
					// }

// /TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				}
			    else { // Otherwise, compactorize!
					compactStickyOutline();
			    }
			}
			// When you resize the browser, do these things
			$(window).resize(function() {
				resizeContent();
			});
			// When you scroll the browser, do these things
			$(window).scroll(function(){
				setLmsless();
				setBanner();
				setTopbarnav();
				setActiveOutline();
				resizeContent();
			});

			// Let's kick things off right
			resizeContent();
			setLmsless();
			setBanner();
			setTopbarnav();
			setActiveOutline();
		}
	};
})(jQuery, Drupal);