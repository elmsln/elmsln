/**
 * @file
 * assignment bulk operations.
 */
(function ($) {
  Drupal.behaviors.assignmentBulk = {
    attach: function(context, settings) {
      // resize to something reasonable
      $('input.select-or-other-other', context).attr('size', '6');
      // replacement handlers for the select or other glitch in multiple displayed
      $('select.select-or-other-select').change(function(){
        // capture ID
        var id = '#' + $(this).attr('id').replace('-select', '-other');
        // apply class correctly based on state change
        if ($(this).val() == 'select_or_other') {
          $(id).addClass('display');
        }
        else {
          $(id).removeClass('display');
        }
      });
    }
  };
})(jQuery);