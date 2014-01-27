(function($) {

	var is_shadowbox_form;
	var current_location;

	current_location = document.location.href;
	is_shadowbox_form = current_location.indexOf('shadowbox', current_location.length - 'shadowbox'.length) !== -1;

	if ( ! is_shadowbox_form && parent.Shadowbox.isOpen() ) {
		parent.window.location.href = current_location;
	}

}(jQuery));
