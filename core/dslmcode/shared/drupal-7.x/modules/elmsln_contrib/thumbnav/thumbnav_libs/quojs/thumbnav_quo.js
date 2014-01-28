(function ($) {
  $(document).ready(function(){
    // if page is touched, make sure class is removed
    $$('#page').touch(function(){
      Drupal.thumbnav.hideController();
    });
    if (Drupal.settings.thumbnav.left) {
      // on swipe from off screen, display controller
      $$('#thumbnav_left').swiping(function(){
        Drupal.thumbnav.leftSideSwipe();
      });
    }
    // account for the right side zone
    if (Drupal.settings.thumbnav.right) {
      // on swipe from off screen, display controller
      $$('#thumbnav_right').swiping(function(){
        Drupal.thumbnav.rightSideSwipe();
      });
    }
  });
})(jQuery);