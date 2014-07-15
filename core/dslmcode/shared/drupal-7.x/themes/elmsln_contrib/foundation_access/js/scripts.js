(function ($, Drupal) {

	Drupal.behaviors.foundation_access = {
		attach: function(context, settings) {
			// Get your Yeti started.
			
			// Active Outline Accordion Menu
			// block--cis-service-connection--active-outline.tpl.php
			$('.accordion').children().hide();
			$('.accordion-btn').click(function () {
				//toggle the dl
				var $this = $(this);
				$('.accordion').children().hide();
				$this.next().children().toggle();
			});

			// Move accessibility link to action-links menu
			$( ".accessibility-content-toggle a" ).appendTo( ".action-links-bar ul" ).wrap("<li></li>");
			$( ".accessibility-content-toggle").hide();

			$(window).scroll(function(){ // scroll event  
			//sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
		      	var topOffset = $('.book-outline.main-a').offset().top; // returns number
				var bottomOffset = $('.book-outline.main-a').outerHeight(true) + topOffset;
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
			// Accordion Menu
			// Make a variable the hidden panels state
			
			// When
			// $(‘.accordion-btn’).click(function() {
			// 	var allPanels = $(‘.accordion’).hide();
			// 	allPanels.slideUp();
			// 	$(this).next().slideDown();
			// 	return false;
			// });
		}
	};
})(jQuery, Drupal);
