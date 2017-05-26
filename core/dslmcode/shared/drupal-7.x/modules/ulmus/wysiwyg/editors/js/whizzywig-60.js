
var buttonPath = null;

(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.whizzywig = function(context, params, settings) {
  // Previous versions used per-button images found in this location,
  // now it is only used for custom buttons.
  if (settings.buttonPath) {
    window.buttonPath = settings.buttonPath;
  }
  // Assign the toolbar image path used for native buttons, if available.
  if (settings.toolbarImagePath) {
    btn._f = settings.toolbarImagePath;
  }
  // Fall back to text labels for all buttons.
  else {
    window.buttonPath = 'textbuttons';
  }
  // Whizzywig needs to have the width set 'inline'.
  var $field = $('#' + params.field);
  this.originalStyle = $field.attr('style');
  $field.css('width', $field.width() + 'px');

  // Attach editor.
  makeWhizzyWig(params.field, (settings.buttons ? settings.buttons : 'all'));
  // Whizzywig fails to detect and set initial textarea contents.
  $('#whizzy' + params.field).contents().find('body').html(tidyD($field.val()));
};

/**
 * Detach a single editor instance.
 */
Drupal.wysiwyg.editor.detach.whizzywig = function (context, params, trigger) {
  for (var index = 0; index < whizzies.length; index++) {
    if (whizzies[index] !== this.field) {
      continue;
    }
    var $field = $('#' + this.field);

    // Save contents of editor back into textarea.
    $field.val(this.getContent());
    // If the editor is just being serialized (not detached), our work is done.
    if (trigger == 'serialize') {
      return;
    }
    // Move original textarea back to its previous location.
    var $container = $('#CONTAINER' + this.field);
    $field.insertBefore($container);
    // Remove editor instance.
    $container.remove();
    whizzies.splice(index, 1);

    // Restore original textarea styling.
    if ('originalStyle' in this) {
      $field.removeAttr('style').attr('style', this.originalStyle);
    }
    break;
  }
};

/**
 * Instance methods for Whizzywig.
 */
Drupal.wysiwyg.editor.instance.whizzywig = {
  insert: function (content) {
    // Whizzywig executes any string beginning with 'js:'.
    insHTML(content.replace(/^js:/, 'js&colon;'));
  },

  setContent: function (content) {
    // Whizzywig shows the original textarea in source mode.
    if ($field.css('display') == 'block') {
      $('#' + this.field).val(content);
    }
    else {
      var doc = $('#whizzy' + this.field).contents()[0];
      doc.open();
      doc.write(content);
      doc.close();
    }
  },

  getContent: function () {
    var $field = $('#' + this.field);
    // Whizzywig's tidyH() expects a document node. Clone the editing iframe's
    // document so tidyH() won't mess with it if this gets called while editing.
    var clone = $($('#whizzy' + this.field).contents()[0].documentElement).clone()[0].ownerDocument;
    // Whizzywig shows the original textarea in source mode so update the body.
    if ($field.css('display') == 'block') {
     clone.body.innerHTML = $field.val();
    }
    return tidyH(clone);
  },

  isFullscreen: function () {
    // This relies on a global function which uses a global variable...
    var idTa_old = idTa;
    idTa = this.field;
    var fullscreen = isFullscreen();
    idTa = idTa_old;
    return fullscreen;
  }
};
})(jQuery);
