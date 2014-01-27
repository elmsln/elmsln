(function ($) {
/**
 * @file
 * Imagefield_crop module js
 *
 * JS for cropping image widget
 */
Drupal.behaviors.imagefield_crop = {
  attach: function (context, settings) {
    // wait till 'fadeIn' effect ends (defined in filefield_widget.inc)
    setTimeout(attachJcrop, 1000, context);
    //attachJcrop(context);

    function attachJcrop(context) {
      if ($('.cropbox', context).length == 0) {
        // no cropbox, probably an image upload (http://drupal.org/node/366296)
        return;
      }
      // add Jcrop exactly once to each cropbox
      $('.cropbox', context).once(function() {
        var self = $(this);

        //alert("found a cropbox" + self.attr('id'));

        // get the id attribute for multiple image support
        var self_id = self.attr('id');
        var id = self_id.substring(0, self_id.indexOf('-cropbox'));
        // get the name attribute for imagefield name
        var widget = self.parent().parent();

          if ($(".edit-image-crop-changed", widget).val() == 1) {
              $('.preview-existing', widget).css({display: 'none'});
              $('.jcrop-preview', widget).css({display: 'block'});
          }

        $(this).Jcrop({
          onChange: function(c) {
            $('.preview-existing', widget).css({display: 'none'});
            var preview = $('.imagefield-crop-preview', widget);
            // skip newly added blank fields
            if (undefined == settings.imagefield_crop[id].preview) {
              return;
            }
            var rx = settings.imagefield_crop[id].preview.width / c.w;
            var ry = settings.imagefield_crop[id].preview.height / c.h;
            $('.jcrop-preview', preview).css({
              width: Math.round(rx * settings.imagefield_crop[id].preview.orig_width) + 'px',
              height: Math.round(ry * settings.imagefield_crop[id].preview.orig_height) + 'px',
              marginLeft: '-' + Math.round(rx * c.x) + 'px',
              marginTop: '-' + Math.round(ry * c.y) + 'px',
              display: 'block'
            });
            // Crop image even if user has left image untouched.
            $(widget).siblings('.preview-existing').css({display: 'none'});
            $(widget).siblings(".edit-image-crop-x").val(c.x);
            $(widget).siblings(".edit-image-crop-y").val(c.y);
            if (c.w) $(widget).siblings(".edit-image-crop-width").val(c.w);
            if (c.h) $(widget).siblings(".edit-image-crop-height").val(c.h);
            $(widget).siblings(".edit-image-crop-changed").val(1);
          },
          onSelect: function(c) {
            $(widget).siblings('.preview-existing').css({display: 'none'});
            $(widget).siblings(".edit-image-crop-x").val(c.x);
            $(widget).siblings(".edit-image-crop-y").val(c.y);
            if (c.w) $(widget).siblings(".edit-image-crop-width").val(c.w);
            if (c.h) $(widget).siblings(".edit-image-crop-height").val(c.h);
            $(widget).siblings(".edit-image-crop-changed").val(1);
          },
          aspectRatio: settings.imagefield_crop[id].box.ratio,
          boxWidth: settings.imagefield_crop[id].box.box_width,
          boxHeight: settings.imagefield_crop[id].box.box_height,
          minSize: [Drupal.settings.imagefield_crop[id].minimum.width, Drupal.settings.imagefield_crop[id].minimum.height], 
          /*
           * Setting the select here calls onChange event, and we lose the original image visibility
          */
          setSelect: [
            parseInt($(widget).siblings(".edit-image-crop-x").val()),
            parseInt($(widget).siblings(".edit-image-crop-y").val()),
            parseInt($(widget).siblings(".edit-image-crop-width").val()) + parseInt($(widget).siblings(".edit-image-crop-x").val()),
            parseInt($(widget).siblings(".edit-image-crop-height").val()) + parseInt($(widget).siblings(".edit-image-crop-y").val())
          ]
        });
      });
    };
  }
};

})(jQuery);
