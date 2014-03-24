(function ($) {
  Drupal.behaviors.quizQuestionBrowserBehavior = {
    attach: function(context, settings) {
      //  $('div.checkbox div.form-item').hide();
      var $cell = $('div.mark-doubtful');
      var $checkbox = $(':checkbox', $cell);
      var $switch = $('.toggle', $cell);
      if ($checkbox.is(':checked')) {
	$switch.toggleClass('off');
      }
      $switch.click(function() {
	$checkbox.click();
      });
      $checkbox.click(function() {
	$switch.toggleClass('off');
      });
    }
  };
})(jQuery);
