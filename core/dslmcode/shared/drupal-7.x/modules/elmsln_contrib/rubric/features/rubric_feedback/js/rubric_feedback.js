/**
 * @file
 * Minor Jquery handling for rubric usability while viewing.
 */
(function ($) {
  Drupal.behaviors.rubricFeedback = {
    attach: function(context) {
      $('.rubric-level-wrapper').click(function(){
        // allow for deselecting of an item if already clicked
        if ($(this).hasClass('rubric-level-selected')) {
          $(this).removeClass('rubric-level-selected');
        }
        else {
          $(this).parent().parent().parent().parent().parent().find('.rubric-level-wrapper').removeClass('rubric-level-selected');
          $(this).addClass('rubric-level-selected');
        }
        // @todo start storing what items are clicked
      });
    }
  };
})(jQuery);
