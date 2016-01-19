(function ($) {
  document.addEventListener("DOMContentLoaded", function(event) {
    var wrapper = document.body;
    // Get the height of the content. We add 50px to account for admin menu.
    var wrapper_height = wrapper.offsetHeight + 50;
    // Resize the window via canvas API so we don't have 2 scroll bars.
    parent.postMessage('{"subject":"lti.frameResize", "height":' + wrapper_height + '}', '*');
  });
})(jQuery);