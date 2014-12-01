(function ($, Drupal) {

	Drupal.behaviors.foundation_access = {
		attach: function(context, settings) {
			// Get your Yeti started.
			
			////////////
			// sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
			////////////
			
			////////////
			// Add debounce function:
			// http://davidwalsh.name/javascript-debounce-function
			////////////

			////////////
			// Look at waypoints
			// http://imakewebthings.com/jquery-waypoints/
			////////////




			////////////
			// Global Active Outline Accordion Menu
			// block--cis-service-connection--active-outline.tpl.php
			// 
			// To Do:
			// 1. Make separate menus for static and sticky
			////////////	
			
			
			// $('.accordion').hide(); //hide accordion items on page load
			// $('.accordion-btn').click(function() {//toggle the clicked dl item
			// 	var $this = $(this);
			// 	//$('.accordion-btn').addClass('active');
			// 	$('.accordion').not($this.next()).hide(); // close all items except for current clicked item
			// 	//$('.accordion-btn').not($this.next()).removeClass('active');
			// 	$this.next().toggle(); // open or close cliked item
			// 	setActiveOutline(); // Rerun the setActiveOutline function to recalculate the height
			// });

			// ////////////
			// // Action Menu Links
			// // page.tpl.php
			// //////////// 

			// // Move accessibility link to action-links menu
			// $( ".accessibility-content-toggle a" ).appendTo( ".action-links-bar ul" ).wrap("<li></li>");
			// $( ".accessibility-content-toggle").hide();

			// ////////////
			// // Scroll to top of page
			// // page.tpl.php
			// ////////////
			
			// $('#banner-image-sticky').click(function() {//toggle the clicked dl item
			// 	$('html, body').animate({scrollTop: "0px"}, 800); // close all items except for current clicked item
			// });
						
			// // Window Height Variable
			// var windowHeight = $(window).height();
			// // var windowTop = $(window).scrollTop();
			// var topOffsetlmsless = $('#lmsless-bar').offset().top; // Top location LMSLess Bar (top-most nav bar)
			// var heightlmsless = $('#lmsless-bar').outerHeight(true); // Height of LMSLess Bar (top-most nav bar)
			// var bottomOffsetlmsless = heightlmsless + topOffsetlmsless + 10; // Bottom location LMSLess Bar (top-most nav bar)
			// // Banner Image Variables
			// var topOffsetBanner = $('#banner-image').offset().top; // returns number
			// var heightBanner = $('#banner-image').outerHeight(true);
			// var bottomOffsetBanner = heightBanner + topOffsetBanner - heightlmsless + 10; // returns number
			// // Topbar Nav Variables
			// var topOffsetTopbarnav = $('#topbarnav').offset().top; // returns number
			// var heightTopbarnav = $('#topbarnav').outerHeight(true); // returns number
			// var bottomOffsetTopbarnav = heightTopbarnav + topOffsetTopbarnav; // returns number
			// // Sticky Elements Height Variables
			// var heightTopbarNavSticky = $('#topbarnav-sticky').outerHeight(); // height of sticky topbar
			// var heightBannerImageSticky = $('#banner-image-sticky').outerHeight(); // height of sticky topbar
			// var heightlmslessSticky = $('#lmsless-bar-sticky').outerHeight(); // height of sticky LMSLess Bar
			// var topOffsetTopbarNavSticky = $('#topbarnav-sticky').offset().top;
			// var bottomTopbarNavSticky = topOffsetTopbarNavSticky + heightTopbarNavSticky;
			// // Active Outline Variables
			// var topOffsetOutlineNav = $('#activeoutline').offset().top;
			// var heightOutlineNav = $('#activeoutline').outerHeight(true);
			// var bottomOffsetOutlineNav = heightOutlineNav + topOffsetOutlineNav; // TODO - figure out why I need 50px more
			// // Height of space above visible area in window
			// // Active Outline Height Variable
			// var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight();
			// // Total Height Sticky Elements Height Variables
			// var topOffsetOutlineNavSticky = $('#activeoutline-sticky').offset().top;
			// var heightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(true);
			// var bottomOffsetOutlineNavSticky = heightOutlineNavSticky + topOffsetOutlineNavSticky;


			// // TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// // This variable is reporting the wrong height. Fix.
			// var totalHeightStickies = insideHeightOutlineNavSticky + heightTopbarNavSticky + heightBannerImageSticky;



			// // var scrollDiffBottom = bottomOffsetOutlineNavSticky + windowHeight;
			// // // Figure out how to get this value
			// // var scrollDiffTop = "distance between top of outline nav and bottom of Topbarnav" + bottomOffsetTopbarnav;

			// // function activeOutlineDiffScroll() {
			// // 	$('#activeoutline-sticky').css({marginTop: - scrollDiffTop}); // Subtract margin
			// // }

			// // /TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// function showStickyOutline() {
			// 	var windowTop = $(window).scrollTop();
			// 	$('#activeoutline-sticky').css({display:'block', marginTop: windowTop - bottomOffsetTopbarnav }); // Set sticky active outline to visible and relocate within view // Set sticky active outline to visible
			// 	console.log("show");
			// }

			// function compactStickyOutline() {
			// 	$('#activeoutline-sticky').removeClass( "compact-mode" ).addClass( "compact-mode" );
			// 	console.log("compactorize!");
			// }

			// function unCompactStickyOutline() {
			// 	$('#activeoutline-sticky').removeClass( "compact-mode" );
			// 	console.log("un compactorize!");
			// }

			// function setLmsless() {
			// 	var windowTop = $(window).scrollTop();
			// 	console.log("setLmsless function reporting for duty!");
			// 	if (bottomOffsetlmsless < windowTop) { // Go into sticky mode
			// 		$('#lmsless-bar-sticky').addClass( "locator" );
					
			// 	}
			//     else { // Do not go into sticky mode
			// 		$('#lmsless-bar-sticky').removeClass( "locator" );
			//     }
			// }

			// function setBanner() {
			// 	var windowTop = $(window).scrollTop();
			// 	console.log("setBanner function reporting for duty!");
			// 	if (bottomOffsetBanner < windowTop) { // Go into sticky mode
			// 		$('#banner-image-sticky').addClass( "locator" );
			// 	}
			//     else { // Do not go into sticky mode
			// 		$('#banner-image-sticky').removeClass( "locator" );
			//     }
			// }

			// function setTopbarnav() {
			// 	var windowTop = $(window).scrollTop();
			// 	console.log("setTopbarnav function reporting for duty!");
			// 	if (bottomOffsetTopbarnav < windowTop) { // Go into sticky mode
			// 		$('#topbarnav-sticky').addClass( "locator" );
			// 	}
			//     else { // Do not go into sticky mode
			// 		$('#topbarnav-sticky').removeClass( "locator" );
			//     }
			// }

			// function setActiveOutline() {
			// 	var windowTop = $(window).scrollTop();
			// 	var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(); // Re-evaluate this variable when function runs
			// 	var scrollOutlineNavStickyFarTop = topOffsetOutlineNavSticky;
			// 	var scrollOutlineNavStickyFarBottom = bottomOffsetOutlineNavSticky;
			// 	var scrollThreshold = 0;
			// 	console.log("setActiveOutline function reporting for duty!");
			// 	console.log("insideHeightOutlineNavSticky:");
			// 	console.log(insideHeightOutlineNavSticky);
				// If the top of the Active Outline is off screen to the top AND the height of the window is GREATER than the height of the stickies
				// if (topOffsetOutlineNav < windowTop && windowHeight > totalHeightStickies) { // Go into sticky mode
				// 	console.log("normal sticky");
				// 	$('#activeoutline-sticky').css({display: 'block', marginTop: windowTop - bottomOffsetTopbarnav });
				// }

// TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ////
				// sidenav_static_dynamic function
				// ////
				// If the windowHeight - totalStickiesHeight is greater than the sidenav expanded height then don't fire the move function
				// 		If this is true and you scroll significantly past the top/bottom of the navigation, wait 2 seconds and fire the move function
				// 		If any sidenav buttons are clicked, re-evaluate the height of side nav and run this
				
				// if (windowHeight - totalHeightStickies < ) {

				// }
				// 
				// Set Static or dynamic state of sidebar navigation
				//	top of nav [ less than ] window position AND browser size [ greater or equal than ] height of nav + 94 pixels
//   				if (windowHeight >= insideHeightOutlineNavSticky && topOffsetOutlineNav < windowTop) { // Go into sticky mode Add evaluation for top/bottom sidenav distance
// 					var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(); // Re-evaluate this variable when function runs
// 					var topOffsetOutlineNavSticky = $('#activeoutline-sticky').offset().top;
// 					var heightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(true);
// 					var bottomOffsetOutlineNavSticky = heightOutlineNavSticky + topOffsetOutlineNavSticky;
// 					console.log("normal sticky");
// 					console.log("1");
// 					$('#activeoutline-sticky').css({display: 'block', marginTop: windowTop - topOffsetTopbarnav });
// 				}

// 				// top of nav [ less than ] window position AND browser size [ greater or equal than ] height of nav + 94 pixels AND scrolled dist down page [is grater than the browser height minus desired threshold]
// 				// else if (windowHeight < insideHeightOutlineNavSticky + 94 && topOffsetOutlineNav < windowTop  && scrollOutlineNavStickyFarTop < windowHeight - scrollThreshold) { // Go into sticky mode if scrolled too far down page
// 				// 	console.log("normal sticky");
// 				// 	console.log("2");
// 				// 	$('#activeoutline-sticky').css({display: 'block', marginTop: windowTop - topOffsetTopbarnav });
// 				// }

// 				// top of nav [ less than ] window position AND browser size [ greater or equal than ] height of nav + 94 pixels AND scrolled dist up page [is grater than the browser height minus desired threshold]
// 				// else if (windowHeight < insideHeightOutlineNavSticky + 94 && topOffsetOutlineNav < windowTop && scrollOutlineNavStickyFarBottom > windowHeight + insideHeightOutlineNavSticky + 94 + scrollThreshold) { // Go into sticky mode if scrolled too far up page
// 				// 	// var topOffsetOutlineNavSticky = $('#activeoutline-sticky').offset().top;
// 				// 	// var heightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(true);
// 				// 	// var bottomOffsetOutlineNavSticky = heightOutlineNavSticky + topOffsetOutlineNavSticky;
// 				// 	console.log("normal sticky");
// 				// 	console.log("3");
// 				// 	$('#activeoutline-sticky').css({display: 'block', marginTop: windowTop - bottomOffsetTopbarnav });
// 				// }
// 				else if (windowHeight < insideHeightOutlineNavSticky) { 
// 					console.log("This is a SMALL WINDOW!");

// 					if (windowTop - insideHeightOutlineNavSticky - scrollThreshold > bottomOffsetOutlineNav) {
// 						var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(); // Re-evaluate this variable when function runs
// 						var topOffsetOutlineNavSticky = $('#activeoutline-sticky').offset().top;
// 						var heightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(true);
// 						var bottomOffsetOutlineNavSticky = heightOutlineNavSticky + topOffsetOutlineNavSticky;
// 						console.log("4");
// 						console.log("topOffsetOutlineNav");
// 						console.log(topOffsetOutlineNav);
// 						console.log("Is Less Than:");
// 						console.log("windowTop - scrollThreshold");
// 						console.log(windowTop - scrollThreshold);
// 						console.log("bottomOffsetOutlineNav");
// 						console.log(bottomOffsetOutlineNav);
// 						$('#activeoutline-sticky').css({display: 'block', marginTop: windowTop - bottomOffsetTopbarnav });
// 					}
// 					else if (windowTop + windowHeight + insideHeightOutlineNavSticky + scrollThreshold < topOffsetOutlineNav) { // Nav is beloew view, move top nav into place
// 						var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(); // Re-evaluate this variable when function runs
// 						var topOffsetOutlineNavSticky = $('#activeoutline-sticky').offset().top;
// 						var heightOutlineNavSticky = $('#activeoutline-sticky').outerHeight(true);
// 						var bottomOffsetOutlineNavSticky = heightOutlineNavSticky + topOffsetOutlineNavSticky;
// 						console.log("5");
// 						console.log(bottomOffsetOutlineNavSticky);
// 						console.log("Is Greater Than:");
// 						console.log(windowTop + windowHeight + scrollThreshold);
// 						console.log(topOffsetOutlineNav);
// 						$('#activeoutline-sticky').css({display: 'block', marginTop: windowTop - bottomOffsetTopbarnav });
						
// 					}
// 					else {
// 						// Don't do anything
// 					}

// 				}
				
// // /TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 				// If the top of the Active Outline is off screen to the top AND the height of the window is LESS than the height of the stickies
// 				// else if (topOffsetOutlineNav - 100 < windowTop && windowHeight < totalHeightStickies) { // Go into sticky mode
// 				// 	console.log("follow down sticky");
// 				// 	$('#activeoutline-sticky').css({marginTop: windowTop + bottomOffsetTopbarnav });
// 				// 	// Add top Margin so the top of the active outline is in view
// 				// 	// It should be allowed off screen by 30% before it moves itself into place
// 				// }
// 				// If the bottom of the Active Outline is off screen to the top AND the height of the window is LESS than the height of the stickies
// 				// else if (bottomOffsetOutlineNav + 100 > windowTop + windowHeight && windowHeight < totalHeightStickies) { // Go into sticky mode
// 				// 	console.log("follow up sticky");
// 				// 	$('#activeoutline-sticky').css({marginTop: windowTop + totalHeightStickies });
// 				// 	// Reduce the top margin so the bottom of active outline is in view
// 				// 	// It should be allowed off screen by 30% before it moves itself into place
					
// 				// }


// 				// if the window is smaller than the active outline, then do not adjust margin
// 				// 
// 			//     else { // Do not go into sticky mode
// 			// 		$('#activeoutline-sticky').css({display:'none', marginTop: 0});
// 			//     }
// 			}

// 			function resizeContent() {
// 				/////////
// 				/// To Do:
// 				/// 1. Instead of hiding upon resize, disable dynamic top-margin so users can scroll the menu
// 				/// 2. Transfer keyboard focus to equivelant button when changing to sticky menu for accessibility
// 				////////
				
// 				// Reset these variables each time you resize the browser
// 				var windowTop = $(window).scrollTop();
// 				var windowHeight = $(window).height();
// 				var insideHeightOutlineNavSticky = $('#activeoutline-sticky').outerHeight();
// 				var heightBannerImageSticky = $('#banner-image-sticky').outerHeight();
// 				var heightTopbarNavSticky = $('#topbarnav-sticky').outerHeight(); // height of sticky topbar
// 				var totalHeightStickies = insideHeightOutlineNavSticky + heightTopbarNavSticky + heightBannerImageSticky;

// 				console.log("windowHeight");
// 				console.log(windowHeight);
// 				console.log("Window Top");
// 				console.log(windowTop);
// 				console.log("totalHeightStickies");
// 				console.log(totalHeightStickies);
// 				console.log("insideHeightOutlineNavSticky");
// 				console.log(insideHeightOutlineNavSticky);
// 				console.log("heightOutlineNavSticky");
// 				console.log(insideHeightOutlineNavSticky);
				
				

// 				// if the height of the window is smaller than the total height of all stickies AND we are not scrolled within view of the original navigation
// 				if (windowHeight < totalHeightStickies && bottomOffsetOutlineNav < windowTop) {
// 					compactStickyOutline();
// 				}
// 				// if the height of the window is larger than the total height of all stickies AND we are scrolled within view of the original navigation
// 				else if (windowHeight > totalHeightStickies && bottomOffsetOutlineNav > windowTop) {
// 					compactStickyOutline();
// 				}
// 				// if the height of the window is smaller than the total height of all stickies AND we are not scrolled within view of the original navigation
// 				// else if (windowHeight < totalHeightStickies && bottomOffsetOutlineNav < windowTop) {
// 				// compactStickyOutline();
// 				// }
// 				// if the height of the window is larger than the total height of all stickies AND we are not scrolled within view of the original navigation
// 				else if (windowHeight > totalHeightStickies && bottomOffsetOutlineNav < windowTop) {
// 					unCompactStickyOutline();
					
// // TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 					// Merge into setActiveOutline function
					
// 					// If you scroll too far up past the top, adjust the sticky nav's topmmargin accordingly
// 					// if (bottomOffsetOutlineNavSticky -  insideHeightOutlineNavSticky > windowHeight + 10) {
// 					//	console.log("scrolled past top");
// 					// }
// 					// // If you scroll too far past the buttom, adjust the margin accordingly
// 					// else if (bottomOffsetOutlineNavSticky < windowHeight + 10) {
// 					//	console.log("scrolled past bottom");
// 					// }

// // /TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 				}
// 			    else { // Otherwise, compactorize!
// 					compactStickyOutline();
// 			    }
// 			}
			// When you resize the browser, do these things
			// $(window).resize(function() {
			// 	resizeContent();
			// });
			// // When you scroll the browser, do these things
			// $(window).scroll(function(){
			// 	setLmsless();
			// 	setBanner();
			// 	setTopbarnav();
			// 	setActiveOutline();
			// 	resizeContent();
			// });
			// When you click on a sideNav button, do these things
			
			// Let's kick things off right
			// resizeContent();
			// setLmsless();
			// setBanner();
			// setTopbarnav();
			// setActiveOutline();
		}
	};
})(jQuery, Drupal);