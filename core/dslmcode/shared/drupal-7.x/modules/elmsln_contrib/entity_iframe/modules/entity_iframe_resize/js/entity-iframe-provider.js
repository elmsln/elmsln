// JavaScript Document
// set event listener for our post back message from parents
// of this content item being framed to display elsewhere
(function ($) {
  // resize to just beyond the height of the body
  function fireResize(rebuild) {
    var data = {
      "subject" : "entityIframe.resize",
      "height": ($('body').height())
    };
    // post up to the parent frame
    window.parent.postMessage(data, '*');
    // test if we should rebuild, this is so we don't get infinite loops
    // when the post does the resize
    if (rebuild) {
      window.onresize = false;
      setTimeout(function() {
        window.onresize = function() {
          // looks weird but this helps ensure we don't resize
          if (resizeTimeout) {
            clearTimeout(resizeTimeout);
          }
          resizeTimeout = setTimeout(function() {
            fireResize(true);
          }, 500);
        };
      }, 1000);
    }
  }
  // send frame message on window.resize event
  // this looks weird but this helps ensure we don't resize every milisecond and instead wait
  // till resizing stops before firing
  var resizeTimeout;
  window.onresize = function() {
    // looks weird but this helps ensure we don't resize
    if (resizeTimeout) {
      clearTimeout(resizeTimeout);
    }
    resizeTimeout = setTimeout(function() {
      fireResize(true);
    }, 1000);
  };
  // account for possible scrollbar creation
  $(window).scroll(function () {
      // looks weird but this helps ensure we don't resize
    if (resizeTimeout) {
      clearTimeout(resizeTimeout);
    }
    resizeTimeout = setTimeout(function() {
      fireResize(true);
    }, 10);
  });
  // wire up the mutator observer so we can detect a change in the frame to post
  $(document).ready(function(){
    setTimeout(function() {
      fireResize(false);
    }, 100);
    // do an immediate post once document is loaded
    // account for prefixed mutators in older browsers
    var MutationObserver = window.MutationObserver || window.WebKitMutationObserver || window.MozMutationObserver;
    // if we observe this happening do something
    var iframeObserver = new MutationObserver(function(mutations, observer) {
      // mutators fire when anything changes. This helps prevent a flood of changes by only bubbling up
      // a resize frame event .5 a second after it occurs
      if (resizeTimeout) {
        clearTimeout(resizeTimeout);
      }
      resizeTimeout = setTimeout(function() {
        fireResize(true);
      }, 500);
    });
    // define what element should be observed by the observer and what types of mutations trigger the callback
    // perform this when we notice any change to the body to ensure that the change didn't affect the frame size
    // in some way
    iframeObserver.observe(document.body, {
      subtree: true,
      attributes: true
    });
  });
})(jQuery)
