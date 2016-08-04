// set event listener for our post back message from parents
// of this content item being framed to display elsewhere
(function ($) {
  Drupal.elmslnMessage = function(e) {
    if (e.data.subject == 'elmsln.xapiContext') {
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
      // mix in this xAPI data if we are allowed
      if (allowed) {
        var data = e.data;
        Drupal.settings.h5pTincanBridge.course = data.course;
        Drupal.settings.h5pTincanBridge.section = data.section;
        Drupal.settings.h5pTincanBridge.title = data.title;
        Drupal.settings.h5pTincanBridge.url = data.url;
        Drupal.settings.h5pTincanBridge.role = data.role;
        Drupal.settings.h5pTincanBridge.hypothesis = data.hypothesis;
      }
    }
  };
  window.addEventListener("message", Drupal.elmslnMessage, false);
})(jQuery);