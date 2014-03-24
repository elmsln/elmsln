(function($) {
/**
 * @file
 * JS enabling one filter fieldset to controll filter formats for all textareas in alternatives.
 */
Drupal.behaviors.quizFormBehavior = {
  attach: function(context) {
    $('.quiz-filter:first :radio').click(function(){
    var myValue = $(this).val();
      $('.quiz-filter:not(:first) :radio[value='+myValue+']').click();
      $('.quiz-filter:not(:first) :radio[value='+myValue+']').change();
    });
    var defaultValue = $('.quiz-filter:first :radio[checked=1]').val();
    $('.quiz-filter:not(:first):not(.quizFormBehavior-processed) :radio[value='+defaultValue+']').click().change().addClass('quizFormBehavior-processed');
    $('.quiz-filter:not(:first)').hide().addClass('quizStayHidden');
    var oldToggle = Drupal.toggleFieldset;
    Drupal.toggleFieldset = function(context) {
      oldToggle(context);
      $('.quizStayHidden').hide();
    };
  }
};

})(jQuery);
