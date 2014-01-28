(function ($) {
$(document).ready(function(){
	// on click display / hide the book title box
	$('#edit-book-title-override-override').click(function(){
		// show if its checked for the override
	  if ($(this).attr('checked') == true) {
			$('.form-item-book-title-override-title').css('display', 'block');
			$('#edit-book-title-override-title').focus();
		}
		else {
			$('.form-item-book-title-override-title').css('display', 'none');
		}
	});
	// account for default being checked already on page load
	if ($('#edit-book-title-override-override').attr('checked') == true) {
		$('.form-item-book-title-override-title').css('display', 'block');
	}
});
})(jQuery);