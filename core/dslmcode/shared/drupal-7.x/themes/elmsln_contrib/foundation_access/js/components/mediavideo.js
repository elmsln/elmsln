module.exports = function() {
  (function ($) {
	  'use strict';

	  $(".mediavideo__open").click(function() {
	    var videoContainer = $(this).parents('.mediavideo');
	    // Add the is-open tag to the base element.
	    videoContainer.toggleClass('mediavideo--is-open');
	    // Start the iframe videos.
	    videoContainer.find('*[data-mediavideo-src]').each(function() {
	    	var videoIframeSrc = $(this).data('mediavideo-src');

	    	// If it's a youtube or vimeo video then add an autoplay attr on the end
	    	// of the url.
	    	if (videoIframeSrc.indexOf('youtube') >= 0 || videoIframeSrc.indexOf('vimeo') >= 0) {
	    		// Find out if we need to start the query parameter or add
	    		// on to an existing one.
		    	if (videoIframeSrc.indexOf('?') >= 0) {
		    		videoIframeSrc += '&autoplay=1';
		    	}
		    	else {
		    		videoIframeSrc += '?autoplay=1';
		    	}
	    	}
	    	// Add it to the source attribute to load the video.
	    	$(this).attr('src', videoIframeSrc);
	    });
	  });
  })(jQuery);
};
