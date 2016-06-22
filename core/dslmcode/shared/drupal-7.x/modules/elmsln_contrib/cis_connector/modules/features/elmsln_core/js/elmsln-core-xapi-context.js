(function ($) {
  // attempt to spit xapi context into all iframes
  $(document).ready(function(){
    $('iframe.entity_iframe').each(function(){
      var data = {
        "subject" : "elmsln.xapiContext",
        "course": Drupal.settings.elmslnCore.course,
        "section": Drupal.settings.elmslnCore.section,
        "url": Drupal.settings.elmslnCore.url,
        "title": Drupal.settings.elmslnCore.title,
        "role": Drupal.settings.elmslnCore.role
      };
      var obj = this;
      // send the message to the other domain using postMessage call
      // @todo ensure this is within our network before sending it data
      $(obj).load(function() {
        obj.contentWindow.postMessage(data, $(obj).attr('src'));
      });
    });
  });
})(jQuery);