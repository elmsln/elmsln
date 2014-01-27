/**
 * @file video_filter ckeditor dialog helper
 */

var video_filter_dialog = {};
(function ($) {
video_filter_dialog = {
  init : function() {
    //Get CKEDITOR
    CKEDITOR = dialogArguments.opener.CKEDITOR;
    //Get the current instance name
    var name = dialogArguments.editorname;
    //Get the editor instance
    editor = CKEDITOR.instances[name];
  },

  insert : function() {
    // Get the params from the form
    var params = this._getParams();
    //If no file url, just close this window
    if(params.file_url == "") {
      window.close();
    }
    else {
      CKEDITOR.tools.callFunction(editor._.video_filterFnNum, params, editor);
      window.close();
    }
  },

  _getParams : function () {
    var params = {};
    $('fieldset:first-child input, fieldset:first-child select').each(function() {
      if($(this).attr('type') == "checkbox") {
        if($(this).is(':checked')) {
          params[$(this).attr('name')] = $(this).val();
        }
      }
      else {
        if($(this).val() != "" && $(this).val() != "none") {
          params[$(this).attr('name')] = $(this).val();
        }
      }
    });

    return params;
  }
};

$(document).ready(function() {
  var CKEDITOR, editor;

  video_filter_dialog.init();

  $('#edit-insert').click(function() {
    video_filter_dialog.insert();
    return false;
  });

  $('#edit-cancel').click(function() {
    window.close();
    return false;
  });
});

})(jQuery);
