(function ($) {
  $(document).ready(function(){
    $('#a11y_voicecommander_checkbox').click(function(){
      Drupal.a11y.voicecommander(this.checked);
    });
    // test for cookie being set
    if ($.cookie('a11y_voicecommander') == 'true') {
      Drupal.settings.voiceCommander.continuous = true;
    }
    // default checkbox on if we should
    if (typeof Drupal.settings.voiceCommander !== 'undefined' && Drupal.settings.voiceCommander.continuous == true) {
      $('#a11y_voicecommander_checkbox').checked = true
      $('#a11y_voicecommander_checkbox').attr('checked', 'checked');
    }
  });
  // voicecommander functionality
  Drupal.a11y.voicecommander = function(voicecommander){
    $.cookie('a11y_voicecommander', voicecommander, { path: '/', domain: Drupal.settings.a11y.domain });
    // set the cookie then reload
    location.reload();
  };
})(jQuery);