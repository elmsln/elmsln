// JavaScript Document
// set event listener for our post back message from parents
// of this content item being framed to display elsewhere
(function ($) {
  // iframe resize function that finds who triggered it
  Drupal.entityIframeResize = function(e) {
    // look at the message that came over and assemble our 4 parts of the message
    // only read in data if this is a trusted domain via browser policy or subdomain
    if (e.data.subject == 'entityIframe.resize') {
      var allowed = false;
      if (e.isTrusted) {
        allowed = true;
      }
      else {
        // check frame
        var frame = e.origin.split('.');
        var local = window.location.origin.split('.')
        // validate that the subdomain is the same in each
        if (frame.pop() == local.pop() && frame.pop() == local.pop()) {
          allowed = true;
        }
      }
      // resize if we are allowed
      if (allowed) {
        // Find out who sent the message
        var iframes = document.getElementsByTagName('iframe');
        for (var i = 0; i < iframes.length; i++) {
          if (iframes[i].contentWindow === e.source) {
            $(iframes[i]).attr('height', e.data.height);
            $(document).trigger('frame-resize');
            break;
          }
        }
      }
    }
  };
  // listen for receiving the message and then resizing to that height
  window.addEventListener("message", Drupal.entityIframeResize, false);
})(jQuery)
