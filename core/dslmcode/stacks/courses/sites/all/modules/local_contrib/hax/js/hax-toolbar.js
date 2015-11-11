(function ($) {

$(document).ready(function() {
  // create toolbar buttons for appending items to the interface
  $('.hax-toolbar-tool').click(function(){
    var tool = $(this).attr('data-hax-tool');
    // easiest use-case, insert the markup we have
    if (Drupal.settings.hax[tool]['action'] == 'insert') {
      $('.hax-body').prepend(Drupal.settings.hax[tool]['markup']);
      // ensure we can move this thing around
      // @todo
      //Drupal.hax.activate();
    }
  });
});

})(jQuery);