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
})(jQuery)
