/**
 * @file
 * Trigger hidden input field when visible one selected.
 */
(function ($) {
  $(document).ready(function(){
    $('#edit-field-instructional-outline--2').change(function(){
      $('input[name="field_instructional_outline[und][0][value]"]').val($(this).val());
    });
    $('#edit-field-instructional-outline--2').change();
  });
})(jQuery);