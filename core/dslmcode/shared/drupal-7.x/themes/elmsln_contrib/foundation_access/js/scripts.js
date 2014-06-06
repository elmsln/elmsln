(function ($, Drupal) {

  Drupal.behaviors.foundation_access = {
    attach: function(context, settings) {
      // Get your Yeti started.
      $( ".accessibility-content-toggle a" ).appendTo( ".action-links-bar ul" ).wrap("<li></li>");
      $( ".accessibility-content-toggle").hide();

      //sticky stuff from http://andrewhenderson.me/tutorial/jquery-sticky-sidebar/
      var stickyTop = $('.sticky-nav').offset().top; // returns number

      $(window).scroll(function(){ // scroll event  
 
	    var windowTop = $(window).scrollTop(); // returns number
	 
	    if (stickyTop < windowTop) {
	      $('.sticky-nav').css({ position: 'fixed', top: 0 });
		  $('.book-outline.main-a').hide;
	    }
	    else {
	      $('.sticky-nav').css('position','static');
	    }
	 
	  });

    }
  };

})(jQuery, Drupal);
