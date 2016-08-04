// set event listener for our post back message from parents
// of this content item being framed to display elsewhere
(function ($) {
  Drupal.elmslnMessage = function(e) {
    // only read in data if this is a trusted domain via browser policy
    if (e.isTrusted && e.data.subject == 'elmsln.xapiContext') {
      var data = e.data;
      Drupal.settings.h5pTincanBridge.course = data.course;
      Drupal.settings.h5pTincanBridge.section = data.section;
      Drupal.settings.h5pTincanBridge.title = data.title;
      Drupal.settings.h5pTincanBridge.url = data.url;
      Drupal.settings.h5pTincanBridge.role = data.role;
      Drupal.settings.h5pTincanBridge.hypothesis = data.hypothesis;
    }
  };
  window.addEventListener("message", Drupal.elmslnMessage, false);

})(jQuery);