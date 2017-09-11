(function ($) {
  $(document).ready(function(){
    // initial setup after ready
    Drupal.settings.elmslnCore.inContext = 'destination=elmsln/redirect/' + Drupal.settings.distro + '/' + Drupal.settings.elmslnCore.path + '&elmsln_course=' + Drupal.settings.elmslnCore.course + '&addHash=end';
    $('.elmsln-add-menu-items lrnsys-button').each(function() {
      if (typeof $(this).attr('href') !== typeof undefined && $(this).attr('href').indexOf('elmsln/redirect/') != -1) {
        var url = $(this).attr('href').split('?');
        $(this).attr('show-href', url[0] + '?' + Drupal.settings.elmslnCore.inContext);
      }
    });
  });
})(jQuery);


