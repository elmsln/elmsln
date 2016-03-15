(function ($) {
  // define function for book_title_override operation
  Drupal.outline_designer_ops.book_title_override = function() {
    $(".od_submit_button").val('Submit');
    $("#od_book_title_override_title").parent().css('display', 'none');
    // click handler for override
    $('#od_book_title_override_override').click(function(){
      // show if its checked for the override
      if ($(this).is(':checked')) {
        $("#od_book_title_override_title").parent().css('display', 'block');
        $('#od_book_title_override_title').focus();
      }
      else {
        $("#od_book_title_override_title").parent().css('display', 'none');
      }
    });
    // function call
    Drupal.outline_designer.render_popup(true);
  };
  // submit handler
  Drupal.outline_designer_ops.book_title_override_submit = function() {
    var override = $('#od_book_title_override_override:checked').length;
    var title = $('#od_book_title_override_title').val();
    // update database
    Drupal.outline_designer.ajax_call('book', 'book_title_override', Drupal.settings.outline_designer.activeNid, override, title, null);
  };
  // reset handler
  Drupal.outline_designer_ops.book_title_override_reset = function() {
	// check for .prop function. Must use .attr for jQuery < 1.6. Use .prop for jQuery >=1.6
	if (typeof $.fn.prop !== 'function') {
		$("#od_book_title_override_override").attr("checked", false);
	} else {
		$("#od_book_title_override_override").prop("checked", false);
	}
    $("#od_book_title_override_title").val('');
  };
})(jQuery);