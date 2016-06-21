// set event listener for our post back message from parents
// of this content item being framed to display elsewhere
(function ($) {
  Drupal.elmslnMessage = function(e) {
    // look at the message that came over and assemble our 4 parts of the message
    // @todo only do this from trusted sources which we'll have knowledge of
    var data = e.data;
    Drupal.settings.h5pTincanBridge.course = data.course;
    Drupal.settings.h5pTincanBridge.section = data.section;
    Drupal.settings.h5pTincanBridge.title = data.title;
    Drupal.settings.h5pTincanBridge.url = data.url;
  };
  window.addEventListener("message", Drupal.elmslnMessage, false);

})(jQuery);