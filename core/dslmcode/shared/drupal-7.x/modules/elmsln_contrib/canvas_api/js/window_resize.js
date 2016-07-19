(function ($) {
  document.addEventListener("DOMContentLoaded", function(event) {
    var data = {
      "subject" : "lti.frameResize",
      "height": ($('body').height()+10)
    };
    // post up to the parent frame
    window.parent.postMessage(data, '*');
  });
})(jQuery);