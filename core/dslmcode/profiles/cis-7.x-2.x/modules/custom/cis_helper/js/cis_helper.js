/**
 * @file
 * Basic form usability tweaks based on conditional values.
 */
(function ($) {
  $(document).ready(function(){
    $('#edit-new-name').focus().select();
    $('#edit-instructional-outline').change(function(){
      switch ($(this).val()) {
        case 'xml_manifest_import':
          $('#edit-xml-manifest-import-ajax-wrapper').removeClass('hide_form_field');
          $('.form-item-git-book-import').addClass('hide_form_field');
        break;
        case 'git_book_import':
          $('#edit-xml-manifest-import-ajax-wrapper').addClass('hide_form_field');
          $('.form-item-git-book-import').removeClass('hide_form_field');
        break;
        default:
          $('#edit-xml-manifest-import-ajax-wrapper').addClass('hide_form_field');
          $('.form-item-git-book-import').addClass('hide_form_field');
        break;
      }
    });
    $('#edit-course').change(function(){
      // hide options related to a new course if it exists
      if ($(this).val() != 'new') {
        $('#edit-new-course').addClass('hide_form_field');
        $('#edit-services').val('course');
      }
      else {
        $('#edit-new-course').removeClass('hide_form_field');
      }
    });
    $('#edit-course').change();
    $('#edit-instructional-outline').change();
  });
})(jQuery);