(function ($, Drupal) {

	Drupal.behaviors.foundation_access = {
		attach: function(context, settings) {
			// Get your Yeti started.
			$( ".accessibility-content-toggle a" ).appendTo( ".action-links-bar ul" ).wrap("<li></li>");
			$( ".accessibility-content-toggle").hide();

			$(window).scroll(function(){ // scroll event  
		//sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
      var topOffset = $('.book-outline.main-a').offset().top; // returns number
			var bottomOffset = $('.book-outline.main-a').outerHeight(true) + topOffset;
	    var windowTop = $(window).scrollTop(); // returns number
	 
	    if (bottomOffset < windowTop) { // Go into sticky mode
				$('.book-outline.sticky-book-outline').css({ position: 'fixed', top: 0, display:'block'});
				$('.book-outline.main-a').css({display:'none'});
			}
	    else { // Do not go into sticky mode
	      $('.book-outline.sticky-book-outline').css({ position: 'static', display:'none'});
				$('.book-outline.main-a').css({display:'block'});
	    }
	  });
		}
	};
})(jQuery, Drupal);
