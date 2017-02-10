(function ($) {
  $(document).ready(function(){
    // attempt to spit xapi context into all iframes
    $('iframe.entity_iframe').load(function(e){
      var data = {
        "subject" : "elmsln.xapiContext",
        "course": Drupal.settings.elmslnCore.course,
        "section": Drupal.settings.elmslnCore.section,
        "url": Drupal.settings.elmslnCore.url,
        "title": Drupal.settings.elmslnCore.title,
        "role": Drupal.settings.elmslnCore.role,
        "session": Drupal.settings.elmslnCore.xapisession,
        "beacon": Drupal.settings.elmslnCore.xapibeacon
      };
      // check for hypothesis data attribute
      if ($(this).attr('data-xapi-hypothesis')) {
        data["hypothesis"] = $(this).attr('data-xapi-hypothesis');
      }
      // check for core competency data attribute
      if ($(this).attr('data-course-competency')) {
        data["competency"] = $(this).attr('data-course-competency');
      }
      var obj = this;
      // check frame
      var frame = $(obj).attr('src').split('://');
      frame = frame[1].split('/');
      frame = frame[0].split('.');
      var local = window.location.origin.split('://');
      local = local[1].split('.');
      // validate that the subdomain is the same in each
      if (frame.pop() == local.pop() && frame.pop() == local.pop()) {
        obj.contentWindow.postMessage(data, $(obj).attr('src'));
      }
    });
  });
})(jQuery);