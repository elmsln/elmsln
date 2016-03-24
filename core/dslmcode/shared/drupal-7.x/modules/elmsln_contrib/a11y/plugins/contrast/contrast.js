(function ($) {
  $(document).ready(function(){
    $('#a11y_contrast_checkbox').click(function(){
      Drupal.a11y.contrast(this.checked);
    });
    $('#a11y_invert_checkbox').click(function(){
      Drupal.a11y.invert(this.checked);
    });
    // test for cookie being set
    if ($.cookie('a11y_contrast') == 'true') {
      $('#a11y_contrast_checkbox').click();
    }
    // test for cookie being set
    if ($.cookie('a11y_invert') == 'true') {
      $('#a11y_invert_checkbox').click();
    }
  });
  // contrast functionality
  Drupal.a11y.contrast = function(contrast){
    if (contrast == true) {
      $("body").addClass('a11y-contrast');
      $("body").append($("<link id='a11y_contrast_styles' rel='stylesheet' href='" + Drupal.settings.a11y.path + "plugins/contrast/contrast.css' type='text/css' media='screen' />"));
    }
    else {
      $("body").removeClass('a11y-contrast');
      $("#a11y_contrast_styles").remove();
    }
    $.cookie('a11y_contrast', contrast, { path: '/', domain: Drupal.settings.a11y.domain });
  };
  // invert functionality
  Drupal.a11y.invert = function(invert){
    if (invert == true) {
      $("body").addClass('a11y-invert');
      $("body").append($("<link id='a11y_invert_styles' rel='stylesheet' href='" + Drupal.settings.a11y.path + "plugins/contrast/invert.css' type='text/css' media='screen' />"));
    }
    else {
      $("body").removeClass('a11y-invert');
      $("#a11y_invert_styles").remove();
    }
    $.cookie('a11y_invert', invert, { path: '/', domain: Drupal.settings.a11y.domain });
  };
})(jQuery);