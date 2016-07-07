(function ($) {
  Drupal.behaviors.quizAnswerConfirm = {
    attach : function(context, settings) {
      $('form.quiz-answer-confirm #edit-submit').once(function() {
        var $form = $(this);
        $form.submit(function(){
          // Return false to avoid submitting if user aborts
          return confirm($form.data('confirm-message'));
        });
      });
    }
  };
})(jQuery);
