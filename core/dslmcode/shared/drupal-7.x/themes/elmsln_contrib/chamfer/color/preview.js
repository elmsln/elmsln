// $Id: preview.js,v 1.5 2010/12/11 21:37:41 webchick Exp $

(function ($) {
  Drupal.color = {
    logoChanged: false,
    callback: function(context, settings, form, farb, height, width) {
      // Change the logo to be the real one.
      if (!this.logoChanged) {
        $('#preview #preview-logo img').attr('src', Drupal.settings.color.logo);
        this.logoChanged = true;
      }
      // Remove the logo if the setting is toggled off. 
      if (Drupal.settings.color.logo == null) {
        $('div').remove('#preview-logo');
      }

      // CSS3 Gradients.
      // vertical gradient for primary body
      var gradient_start = $('#palette input[name="palette[top]"]', form).val();
      var gradient_end = $('#palette input[name="palette[bottom]"]', form).val();
      $('#preview', form).attr('style', "background: " + gradient_start + "; background: url('../../../../sites/all/themes/chamfer/i/striped-bg.png') repeat top left, -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_start + "), to(" + gradient_end + ")); background: url('../../../../sites/all/themes/chamfer/i/striped-bg.png') repeat top left, -moz-linear-gradient(-90deg, " + gradient_start + ", " + gradient_end + ");");
      
      // horizontal gradient for body "wrapper"      
      //var gradient_left = $('#palette input[name="palette[base]"]', form).val();
      //var gradient_right = $('#palette input[name="palette[secondary]"]', form).val();
      //$('#preview-horizontal-grad', form).attr('style', "background: " + gradient_left + "; background: -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_left + "), to(" + gradient_right + ")); background: -moz-linear-gradient(left, " + gradient_left + ", " + gradient_right + ");");
      
      // Text preview.
      $('#preview #preview-main h2, #preview .preview-content', form).css('color', $('#palette input[name="palette[text]"]', form).val());
      $('#preview #preview-content a', form).css('color', $('#palette input[name="palette[link]"]', form).val());

      // Sidebar block.
      $('#preview #preview-sidebar #preview-block', form).css('background-color', $('#palette input[name="palette[sidebar]"]', form).val());
      $('#preview #preview-sidebar #preview-block', form).css('border-color', $('#palette input[name="palette[sidebarborders]"]', form).val());

      // Footer wrapper background.
      $('#preview #preview-footer-wrapper', form).css('background-color', $('#palette input[name="palette[footer]"]', form).val());

      $('#preview #preview-site-name, #preview #preview-site-slogan', form).css('color', $('#palette input[name="palette[siteslogan]"]', form).val());
      //$('#preview #preview-site-name a', form).css('color', $('#palette input[name="palette[contentbg]"]', form).val());
    }
  };
})(jQuery);
