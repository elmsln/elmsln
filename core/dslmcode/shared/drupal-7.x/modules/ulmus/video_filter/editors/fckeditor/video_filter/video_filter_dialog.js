var dialog  = window.parent;
var oEditor = dialog.InnerDialogLoaded();
var FCK     = oEditor.FCK;

dialog.SetAutoSize(true);

// Activate the "OK" button.
dialog.SetOkButton(true);

(function ($) {
  $(document).ready(function() {
    $('#edit-cancel, #edit-insert').hide();
    $('*', document).keydown(function(ev) {
      if (ev.keyCode == 13) {
        // Prevent browsers from firing the click event on the first submit
        // button when enter is used to select.
        return false;
      }
    });
  });
})(jQuery);

// The "OK" button was hit.
function Ok() {
  var sInnerHtml;
  (function ($) {
    var file_url = $('#edit-file-url').val();

    if(file_url == "") {
      dialog.Cancel();
    }

    var str = '[video:' + file_url;
    if ($('#edit-width').val() !== '') {
      str += ' width:' + $('#edit-width').val();
    }
    if ($('#edit-height').val() !== '') {
      str += ' height:' + $('#edit-height').val();
    }
    if ($('#edit-align').val() !== 'none') {
      str += ' align:' + $('#edit-align').val();
    }
    if ($('#edit-autoplay').is(':checked')) {
      str += ' autoplay:' + $('#edit-autoplay').val();
    }
    str += ']';

    oEditor.FCKUndo.SaveUndoStep();

    var text = oEditor.FCK.InsertHtml(str);
   })(jQuery);
   return true;
}
