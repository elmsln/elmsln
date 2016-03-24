(function ($) {
  $(document).ready(function(){
    $('#a11y_opendyslexic_checkbox').click(function(){
      Drupal.a11y.opendyslexic(this.checked);
    });
    // test for cookie being set
    if ($.cookie('a11y_opendyslexic') == 'true') {
      $('#a11y_opendyslexic_checkbox').click();
    }
  });
  // opendyslexic functionality
  Drupal.a11y.opendyslexic = function(opendyslexic){
    if (opendyslexic == true) {
      $("body").addClass('a11y-opendyslexic');
      $("body").append($("<link id='a11y_opendyslexic_styles' rel='stylesheet' href='" + Drupal.settings.a11y.path + "plugins/opendyslexic/opendyslexic.css' type='text/css' media='screen' />"));
    }
    else {
      $("#a11y_opendyslexic_styles").remove();
      $("body").removeClass('a11y-opendyslexic');
    }
    $.cookie('a11y_opendyslexic', opendyslexic, { path: '/', domain: Drupal.settings.a11y.domain });
  };
})(jQuery);