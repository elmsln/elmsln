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
        Drupal.settings.tincanapi.elmslnCore.course = data.course;
        Drupal.settings.tincanapi.elmslnCore.section = data.section;
        Drupal.settings.tincanapi.elmslnCore.title = data.title;
        Drupal.settings.tincanapi.elmslnCore.url = data.url;
        Drupal.settings.tincanapi.elmslnCore.role = data.role;
        Drupal.settings.tincanapi.elmslnCore.hypothesis = data.hypothesis;
        Drupal.settings.tincanapi.elmslnCore.competency = data.competency;
      }
    }
  };
  window.addEventListener("message", Drupal.elmslnMessage, false);
})(jQuery);