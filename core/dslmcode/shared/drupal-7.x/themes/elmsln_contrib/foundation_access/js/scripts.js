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
	 
	    if (bottomOffset < windowTop) { // If the bottom of the menu element is off screen
	      $('.book-outline.sticky-book-outline').css({ position: 'fixed', top: 0});
		  $('.book-outline.main-a');
	    }
	    else { // If the bottom of the menu element is still on the screen
	      $('.book-outline.sticky-book-outline').css({ position: 'static'});
		  $('.book-outline.main-a');
	    }
	 
	  });

    }
  };

})(jQuery, Drupal);
