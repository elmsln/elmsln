(function ($) {
  $(document).ready(function(){
    // display left controller if told to do so
    if (Drupal.settings.thumbnav.left) {
      Drupal.thumbnav.leftrightControllerShow();
    }
    // display right controller if told to do so
    if (Drupal.settings.thumbnav.right) {
      Drupal.thumbnav.leftrightControllerShow();
    }
  });
})(jQuery);