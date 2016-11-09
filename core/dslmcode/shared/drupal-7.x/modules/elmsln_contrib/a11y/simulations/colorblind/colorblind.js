(function ($) {
  $(document).ready(function(){
    // colorblind functionality
    Drupal.a11y.simulateColorBlindness = function(colorblind){
      $("body").removeClass('protanopia protanomaly deuteranopia deuteranomaly tritanopia tritanomaly achromatopsia achromatomaly');
      switch (colorblind) {
        case '':
        break;
        default:
          $("body").addClass(colorblind);
        break;
      }
    };
    // on select list change simulate field loss when the state changes
    $('#a11y_sim_colorblind_select').change(function(){
      Drupal.a11y.simulateColorBlindness(this.value);
    });
  });
})(jQuery);
