(function ($) {
  $(document).ready(function(){
    // display left controller if told to do so
    if (typeof Drupal.settings.thumbnav.left != 'undefined' && Drupal.settings.thumbnav.left) {
      Drupal.thumbnav.leftControllerShow();
    }
    // display right controller if told to do so
    if (typeof Drupal.settings.thumbnav.right != 'undefined' && Drupal.settings.thumbnav.right) {
      Drupal.thumbnav.rightControllerShow();
    }
  });
})(jQuery);
