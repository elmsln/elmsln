(function ($) {
  $(document).ready(function(){
    $('#a11y_animation_checkbox').click(function(){
      Drupal.a11y.animation(this.checked);
    });
    // test for cookie being set
    if ($.cookie('a11y_animation') == 'true') {
      $('#a11y_animation_checkbox').attr('checked', true);
      Drupal.a11y.animation(true);
    }
  });
  // animation functionality
  Drupal.a11y.animation = function(animation){
    if (animation == true) {
      $.fx.off = true;
      $("body").addClass('a11y-animation');
      $("body").append($("<link id='a11y_animation_styles' rel='stylesheet' href='" + Drupal.settings.a11y.path + "plugins/animation/animation.css' type='text/css' media='screen' />"));
    }
    else {
      $.fx.off = false;
      $("body").removeClass('a11y-animation');
      $("#a11y_animation_styles").remove();
    }
    $.cookie('a11y_animation', animation, { path: '/', domain: Drupal.settings.a11y.domain });
  };
})(jQuery);