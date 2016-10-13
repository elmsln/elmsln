module.exports = function() {
  (function ($) {
	  'use strict';

	  $(".mediavideo__open, .mediavideo__close").click(function(e) {
	  	e.preventDefault();
	    var videoContainer = $(this).parents('.mediavideo');

	    // Add the is-open tag to the base element.
	    videoContainer.toggleClass('mediavideo--is-open');

			videoContainer.find('*[data-mediavideo-src]').each(function() {
				var video = $(this);
				if (videoContainer.hasClass('mediavideo--is-open')) {
					// Give the animation enough time to complete.
					setTimeout(function() {
						startIframeVideo(video);
					}, 500);
				}
				else {
	    		stopIframeVideo(video);
	    	}
	    });
	  });

	  function startIframeVideo(video) {
			// Start the iframe videos.
			var videoIframeSrc = video.data('mediavideo-src');
			// If it's a youtube or vimeo video then add an autoplay attr on the end
			// of the url.
			if (videoIframeSrc.indexOf('youtube') >= 0 || videoIframeSrc.indexOf('vimeo') >= 0) {
				// Find out if we need to fstart the query parameter or add
				// on to an existing one.
		  	if (videoIframeSrc.indexOf('?') >= 0) {
		  		videoIframeSrc += '&autoplay=1';
		  	}
		  	else {
		  		videoIframeSrc += '?autoplay=1';
		  	}
			}
			// Add it to the source attribute to load the video.
			video.attr('src', videoIframeSrc);
	  }

	  function stopIframeVideo(video) {
	  	video.attr('src', '');
	  }
  })(jQuery);
};
