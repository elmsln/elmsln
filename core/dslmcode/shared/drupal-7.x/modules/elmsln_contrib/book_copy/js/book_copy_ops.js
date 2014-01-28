/**
 * @file
 * Book copy, outline designer integration
 *
 * Provides the JS integration of book copy with outline designer callbacks.
 */

(function ($) {
  // define function for book_copy
  Drupal.outline_designer_ops.book_copy = function() {
    // set the title default to the title that was selected
    $("#od_book_copy_title").val($('#edit-table-book-admin-'+ Drupal.settings.outline_designer.activeNid +'-title-span').html());
    $(".od_submit_button").val('Copy content');
    Drupal.outline_designer.render_popup(true);
    $("#od_book_copy_title").focus();
  };
  // submit handler
  Drupal.outline_designer_ops.book_copy_submit = function() {
    var dup_title = $.param($("#od_book_copy_title"));
    dup_title = dup_title.replace(/%2F/g,"@2@F@"); //weird escape for ajax with /
    dup_title = dup_title.replace(/%23/g,"@2@3@"); //weird escape for ajax with #
    dup_title = dup_title.replace(/%2B/g,"@2@B@"); //weird escape for ajax with +
    dup_title = dup_title.replace(/%26/g,"@2@6@"); // Fix ampersand issue &
    dup_title = dup_title.substr(1);
    Drupal.outline_designer.ajax_call(Drupal.settings.outline_designer.type, 'book_copy', Drupal.settings.outline_designer.activeNid, dup_title);
  };
  // reset handler
  Drupal.outline_designer_ops.book_copy_reset = function() {
    $('#od_book_copy_title').val('');
  };
})(jQuery);