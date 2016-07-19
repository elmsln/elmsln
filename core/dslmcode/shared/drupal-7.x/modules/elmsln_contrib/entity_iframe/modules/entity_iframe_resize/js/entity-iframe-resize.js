// JavaScript Document
// set event listener for our post back message from parents
// of this content item being framed to display elsewhere
(function ($) {
  // iframe resize function that finds who triggered it
  Drupal.entityIframeResize = function(e) {
    // look at the message that came over and assemble our 4 parts of the message
    // only read in data if this is a trusted domain via browser policy
    if (e.isTrusted && e.data.subject == 'entityIframe.resize') {
      // Find out who sent the message
      var iframes = document.getElementsByTagName('iframe');
      for (var i = 0; i < iframes.length; i++) {
        if (iframes[i].contentWindow === event.source) {
          $(iframes[i]).attr('height', e.data.height);
          break;
        }
      }
    }
  };
  // listen for receiving the message and then resizing to that height
  window.addEventListener("message", Drupal.entityIframeResize, false);
  // wire up the mutator observer so we can detect a change in the frame to post
  $(document).ready(function(){
    // account for prefixed mutators in older browsers
    var MutationObserver = window.MutationObserver || window.WebKitMutationObserver || window.MozMutationObserver;
    // if we observe this happening do something
    var iframeObserver = new MutationObserver(function(mutations, observer) {
      // fired when a mutation occurs of any kind this ensures that even if the content dynamically
      // resizes that we're noticing the change in real time and passing forward the new dimensions to set
      var data = {
        "subject" : "entityIframe.resize",
        "height": ($('body').height()+10)
      };
      // post up to the parent frame
      window.parent.postMessage(data, '*');
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
