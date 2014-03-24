(function($) {
/**
 * @file
 * JS enabling one filter fieldset to controll filter formats for all textareas in alternatives.
 */
Drupal.behaviors.multichoiceBehavior = {
  attach: function (context, settings) {
    // When the top input filter selector is clicked change the rest of the selectors to the same value
    $('.quiz-filter:first :radio').click(function(){
      var myValue = $(this).val();
      $('.quiz-filter:not(:first) :radio[value='+myValue+']').click();
      $('.quiz-filter:not(:first) :radio[value='+myValue+']').change();
    });

    // Change all format selectors to have the same value as the first
    var defaultValue = $('.quiz-filter:first :radio[checked=1]').val();
    $('.quiz-filter:not(:first):not(.multichoiceBehavior-processed) :radio[value='+defaultValue+']').click().change().addClass('multichoiceBehavior-processed');

    // Hide all format selectors except the first
    $('.quiz-filter:not(:first)').hide().addClass('multichoiceStayHidden');

    // Move the first input selector to the input-all-ph helper tag
    $('.quiz-filter:first').insertAfter('#input-all-ph');

    // Make sure the format selectors stay hidden when a fieldset is unfolded
    var oldToggle = Drupal.toggleFieldset;
    Drupal.toggleFieldset = function(context) {
      oldToggle(context);
      $('.multichoiceStayHidden').hide();
    };
  }
};

})(jQuery);
