(function ($) {
  $(document).ready(function(){
    Drupal.settings.startTime = new Date().getTime();
  });
  // Send off viewed statement on unload event
  $(window).on('beforeunload', function(e) {
    Drupal.settings.tincanapi.elmslnCore.duration = Drupal.calcViewTime();
    var data = {
      module: 'elmsln_core',
      verb: 'viewed',
      id: Drupal.settings.tincanapi.elmslnCore.url,
      title: Drupal.settings.tincanapi.elmslnCore.title
    };
    Drupal.tincanapi.track(data);
  });
  // calculate the time on the page
  Drupal.calcViewTime = function() {
    var end = new Date().getTime();
    var totalTime = Math.round((end - Drupal.settings.startTime) / 1000);
    return totalTime;
  };
})(jQuery);