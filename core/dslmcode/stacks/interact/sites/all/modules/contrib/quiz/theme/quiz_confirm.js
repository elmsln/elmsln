(function ($) {
  Drupal.behaviors.confirm = {
    attach : function(context, settings) {
      $('form.confirm').each(function() {
        var $form = $(this);
        $form.submit(function(){
          // Return false to avoid submitting if user aborts
          return confirm($form.data('confirm-message'));
        });
      });
    }
  };
})(jQuery);
