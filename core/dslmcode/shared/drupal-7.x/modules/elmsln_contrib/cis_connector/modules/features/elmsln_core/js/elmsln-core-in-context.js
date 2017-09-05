(function ($) {
  $(document).ready(function(){
    $('.elmsln-core-in-context').click(function() {
      Drupal.settings.elmslnCore.inContext = 'destination=elmsln/redirect/' + Drupal.settings.distro + '/' + Drupal.settings.elmslnCore.path + '&elmsln_course=' + Drupal.settings.elmslnCore.course + '&addHash=' + $(this).attr('id');
      $('lrnapp-fab-menu').attr('opened', true);
      $('.elmsln-add-menu-items lrnsys-button').each(function() {
      	if (typeof $(this).attr('href') !== typeof undefined && $(this).attr('href').indexOf('elmsln/redirect/') != -1) {
      	  var url = $(this).attr('href').split('?');
          $(this).attr('href', url[0] + '?' + Drupal.settings.elmslnCore.inContext);
      	}
      });
    });
    // initial setup after ready
    Drupal.settings.elmslnCore.inContext = 'destination=elmsln/redirect/' + Drupal.settings.distro + '/' + Drupal.settings.elmslnCore.path + '&elmsln_course=' + Drupal.settings.elmslnCore.course + '&addHash=end';
    $('.elmsln-add-menu-items lrnsys-button').each(function() {
      if (typeof $(this).attr('href') !== typeof undefined && $(this).attr('href').indexOf('elmsln/redirect/') != -1) {
        var url = $(this).attr('href').split('?');
        $(this).attr('href', url[0] + '?' + Drupal.settings.elmslnCore.inContext);
      }
    });
    // hover state
    $('.elmsln-core-in-context').hover(function(e){
      $(this).addClass('elmsln-core-in-context-hover ' + Drupal.settings.cis_lmsless[Drupal.settings.distro]['color'] + '-border');
    }, function(e) {
      $(this).removeClass('elmsln-core-in-context-hover ' + Drupal.settings.cis_lmsless[Drupal.settings.distro]['color'] + '-border');
    });
  });
})(jQuery);


