(function ($) {
  Drupal.behaviors.quizJumper = {
    attach: function(context, settings) {
      $("#quiz-jumper-form:not(.quizJumper-processed)", context).show().addClass("quizJumper-processed").change(function(){
        $("#quiz-jumper-form #edit-submit").trigger("click");
      });
      $("#quiz-jumper-form-no-js:not(.quizJumper-processed)").hide().addClass("quizJumper-processed");
    }
  };
})(jQuery);
