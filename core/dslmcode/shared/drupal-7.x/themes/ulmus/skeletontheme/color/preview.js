
(function ($) {
  Drupal.color = {
    logoChanged: false,
    callback: function(context, settings, form, farb, height, width) {
		
		// Text preview.
		$('#preview', form).css('color', $('#palette input[name="palette[text]"]', form).val());
		$('#preview a', form).css('color', $('#palette input[name="palette[link]"]', form).val());
		$('#preview a:hover', form).css('color', $('#palette input[name="palette[linkhover]"]', form).val());
		$('#preview h1', form).css('color', $('#palette input[name="palette[headings]"]', form).val());
		$('#preview #site-name a', form).css('color', $('#palette input[name="palette[sitename]"]', form).val());
		$('#preview #site-name a:hover', form).css('color', $('#palette input[name="palette[sitenamehover]"]', form).val());
		$('#preview #site-slogan', form).css('color', $('#palette input[name="palette[slogan]"]', form).val());
		$('#wrapper', form).css('border-color', $('#palette input[name="palette[bodyborder]"]', form).val());
		$('#wrapper-inside', form).css('border-color', $('#palette input[name="palette[wrapborder]"]', form).val());
		$('#preview-footer', form).css('border-color', $('#palette input[name="palette[footerborder]"]', form).val());
		$('#preview-footer', form).css('background-color', $('#palette input[name="palette[footerbackground]"]', form).val());
		
    }
  };
})(jQuery);