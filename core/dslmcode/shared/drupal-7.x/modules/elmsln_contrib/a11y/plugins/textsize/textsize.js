(function ($) {
  $(document).ready(function(){
    // test for cookie being set
    if ($.cookie('a11y_factor') != null) {
      Drupal.settings.a11y.factor = $.cookie('a11y_factor');
      Drupal.a11y.textsize(-2);
    }
  });
  //textsize functionality
  Drupal.a11y.textsize = function(scale){
    if(scale == 1 && Drupal.settings.a11y.factor < 2) {
      Drupal.settings.a11y.factor = parseFloat(Drupal.settings.a11y.factor) + parseFloat(0.25);
    }
    else if(scale == -1 && Drupal.settings.a11y.factor != 1) {
      Drupal.settings.a11y.factor = parseFloat(Drupal.settings.a11y.factor) - parseFloat(0.25);
    }
    else if(scale == 0) {
      Drupal.settings.a11y.factor = 1;
    }
    else if (Drupal.settings.a11y.factor > 2) {
      Drupal.settings.a11y.factor = 2;
    }
    // account for initial page load
    if (Drupal.settings.a11y.factor == null && scale == -2) {
      Drupal.settings.a11y.factor = 1;
    }
    if (Drupal.settings.a11y.factor == 1) {
      $("body").css({'zoom': '', '-moz-transform': '', '-moz-transform-origin': 'top center 1px;'});
    }
    else {
      $("body").css({'zoom': Drupal.settings.a11y.factor, '-moz-transform': 'scale('+ Drupal.settings.a11y.factor +','+ Drupal.settings.a11y.factor +')', '-moz-transform-origin': 'top center 1px;'});
    }
    $.cookie('a11y_factor', Drupal.settings.a11y.factor, { path: '/', domain: Drupal.settings.a11y.domain });
  };
})(jQuery);