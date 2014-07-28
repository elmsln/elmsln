(function ($, Drupal) {

	Drupal.behaviors.foundation_access = {
		attach: function(context, settings) {
			// Get your Yeti started.
			
			// Active Outline Accordion Menu
			// block--cis-service-connection--active-outline.tpl.php
			$('.accordion').hide(); //hide accordion items on page load
			$('.accordion-btn').click(function() {//toggle the clicked dl item
				var $this = $(this);
				//$('.accordion-btn').addClass('active');
				$('.accordion').not($this.next()).hide(); // close all items except for current clicked item
				//$('.accordion-btn').not($this.next()).removeClass('active');
				$this.next().toggle(); // open or close cliked item
			});





			// Move accessibility link to action-links menu
			$( ".accessibility-content-toggle a" ).appendTo( ".action-links-bar ul" ).wrap("<li></li>");
			$( ".accessibility-content-toggle").hide();

			$(window).scroll(function(){ // scroll event  

				// find width and position of .main and apply to .sticky-content-nav
				// var mainWidth = $('.main').outerWidth(true);

				// sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
				
				var windowTop = $(window).scrollTop(); // returns number
				
				// Lmsless Bar
				var topOffsetlmsless = $('#lmsless-bar').offset().top; // returns number
				var heightlmsless = $('#lmsless-bar').outerHeight(true); // NOT USED DIRECTLY
				var bottomOffsetlmsless = heightlmsless + topOffsetlmsless; // returns number NOT USED DIRECTLY

				if (topOffsetlmsless < windowTop) { // Go into sticky mode
					$('#lmsless-bar-sticky').css({display:'block'});
				}
			    else { // Do not go into sticky mode
					$('#lmsless-bar-sticky').css({display:'none'});
			    }

				// Banner Image
				var topOffsetBanner = $('#banner-image').offset().top; // returns number
				var heightBanner = $('#banner-image').outerHeight(true);
				var bottomOffsetBanner = heightBanner + topOffsetBanner - heightlmsless - 20; // returns number

				if (bottomOffsetBanner < windowTop) { // Go into sticky mode
					$('#banner-image-sticky').css({display:'block'});
				}
			    else { // Do not go into sticky mode
					$('#banner-image-sticky').css({display:'none'});
			    }

				// Topbar Nav
				var topOffsetTopbarnav = $('#topbarnav').offset().top; // returns number
				var heightTopbarnav = $('#topbarnav').outerHeight(true); // returns number NOT USED DIRECTLY
				var bottomOffsetTopbarnav = heightTopbarnav + topOffsetTopbarnav; // returns number NOT USED DIRECTLY

				if (bottomOffsetTopbarnav < windowTop) { // Go into sticky mode
					$('#topbarnav-sticky').css({top: '96px'});
				}
			    else { // Do not go into sticky mode
					$('#topbarnav-sticky').css({top: '-80px'});
			    }

				// Active Outline
			// 	var topOffset = $('.book-outline.main-a').offset().top; // returns number
			// 	var bottomOffset = $('.book-outline.main-a').outerHeight(true) + topOffset; // returns number
			//     
			//  
			//     if (bottomOffset < windowTop) { // Go into sticky mode
			// 		$('.book-outline.sticky-book-outline').css({ position: 'fixed', top: 0, display:'block'});
			// 		$('.book-outline.main-a');
			// 	}
			//     else { // Do not go into sticky mode
			//       	$('.book-outline.sticky-book-outline').css({ position: 'static', display:'none'});
			// 		$('.book-outline.main-a');
			//     }
			
			});
		}
	};
})(jQuery, Drupal);