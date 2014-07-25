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
				//var mainWidth = $('.main').outerWidth(true);


				//sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
				var topOffset = $('.book-outline.main-a').offset().top; // returns number
				var bottomOffset = $('.book-outline.main-a').outerHeight(true) + topOffset; // returns number
			    var windowTop = $(window).scrollTop(); // returns number
			 
			    if (bottomOffset < windowTop) { // Go into sticky mode
						$('.book-outline.sticky-book-outline').css({ position: 'fixed', top: 0, display:'block'});
						$('.book-outline.main-a');
					}
			    else { // Do not go into sticky mode
			      $('.book-outline.sticky-book-outline').css({ position: 'static', display:'none'});
						$('.book-outline.main-a');
			    }
			
			});
		}
	};
})(jQuery, Drupal);