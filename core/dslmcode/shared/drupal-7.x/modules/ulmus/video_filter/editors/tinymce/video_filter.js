var video_filter_dialog = {};

(function ($) {
video_filter_dialog = {
  insert : function() {
    var ed = tinyMCEPopup.editor, e;

    tinyMCEPopup.restoreSelection();

    tinyMCEPopup.execCommand("mceBeginUndoLevel");

    var file_url = $('#edit-file-url').val();

    // @Todo: validate width and hight is INTs?

    if (file_url == "") {
      // File url is empty, we have nothing to insert, close the window
      ed.execCommand('mceRepaint');
      tinyMCEPopup.execCommand("mceEndUndoLevel");
      tinyMCEPopup.close();
    }
    else {
      var str = '[video:' + file_url;
      // If field is present (ie. not unset by the admin theme) and if value is not empty: insert value.
      if (typeof $('#edit-width').val() != 'undefined' && $('#edit-width').val() !== '') {
        str += ' width:' + $('#edit-width').val();
      }
      if (typeof $('#edit-height').val() != 'undefined' && $('#edit-height').val() !== '') {
        str += ' height:' + $('#edit-height').val();
      }
      if (typeof $('#edit-align').val() != 'undefined' && $('#edit-align').val() !== 'none') {
        str += ' align:' + $('#edit-align').val();
      }
      if ($('#edit-autoplay').is(':checked')) {
        str += ' autoplay:' + $('#edit-autoplay').val();
      }
      str += ']';

      ed.execCommand('mceInsertContent', false, str);
    }

    tinyMCEPopup.execCommand("mceEndUndoLevel");
    tinyMCEPopup.close();
  }
};

Drupal.behaviors.video_filter_tinymce =  {
  attach: function(context, settings) {
    $('#edit-insert').click(function() {
      video_filter_dialog.insert();
    });

    $('#edit-cancel').click(function() {
      tinyMCEPopup.close();
    });
  }
}

})(jQuery);
