/**
 * @file
 * Minor Jquery handling for rubric usability while generating.
 */
(function ($) {
  Drupal.behaviors.rubricGenerate = {
    attach: function(context) {
      // category jquery select trigger
      $('#edit-categories').change(function(){
        $('#edit-cat-container .form-type-textfield').css('display', 'none');
        for (var i=0; i < $(this).val(); i++) {
          $('.form-item-cat-title-' + i).css('display', 'block');
        }
      });
      $('#edit-categories').change();
      // criteria jquery select trigger
      $('#edit-criteria').change(function(){
        $('#edit-crit-container .form-type-textfield').css('display', 'none');
        for (var i=0; i < $(this).val(); i++) {
          $('.form-item-crit-title-' + i).css('display', 'block');
        }
      });
      $('#edit-criteria').change();
    }
  };
})(jQuery);
