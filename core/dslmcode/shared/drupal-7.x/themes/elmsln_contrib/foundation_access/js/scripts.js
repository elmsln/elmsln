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
	 
	    if (bottomOffset < windowTop) {
	      $('.book-outline.sticky-book-outline').css({ position: 'fixed', top: 0 });
		  $('.book-outline.main-a').show;
	    }
	    else {
	      $('.book-outline.sticky-book-outline').css('position','static');
		  $('.book-outline.main-a').hide;
	    }
	 
	  });

    }
  };

})(jQuery, Drupal);
