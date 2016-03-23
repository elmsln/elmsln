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
    if(scale == 1 && Drupal.settings.a11y.factor != 2) {
      Drupal.settings.a11y.factor = Drupal.settings.a11y.factor + 0.25;
    }
    else if(scale == -1 && Drupal.settings.a11y.factor != 1) {
      Drupal.settings.a11y.factor = Drupal.settings.a11y.factor - 0.25;
    }
    else if(scale == 0) {
      Drupal.settings.a11y.factor = 1;
    }
    // account for initial page load, stupid IE thing
    if (Drupal.settings.a11y.factor == null && scale == -2) {
      Drupal.settings.a11y.factor = 1;
    }
    if (Drupal.settings.a11y.factor == 1) {
      $("body").css({'zoom': '', '-moz-transform': '', '-moz-transform-origin': ''});
      $.cookie('a11y_factor', Drupal.settings.a11y.factor);
    }
    else {
      $("body").css({'zoom': Drupal.settings.a11y.factor, '-moz-transform': Drupal.settings.a11y.factor, '-moz-transform-origin': Drupal.settings.a11y.factor});
      $.cookie('a11y_factor', Drupal.settings.a11y.factor);
    }
  };
})(jQuery);