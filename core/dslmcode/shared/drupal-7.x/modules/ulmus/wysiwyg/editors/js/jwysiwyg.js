(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.jwysiwyg = function(context, params, settings) {
  var $field = this.$field;
  // Attach editor.
  $field.wysiwyg(settings);
  this.startWatching($($field.data('wysiwyg').editorDoc).find('body'));
};

/**
 * Detach a single editor instance.
 */
Drupal.wysiwyg.editor.detach.jwysiwyg = function (context, params, trigger) {
  var $field = $('#' + params.field);
  var editor = $field.data('wysiwyg');
  if (typeof editor != 'undefined') {
    editor.saveContent();
    if (trigger != 'serialize') {
      editor.element.remove();
    }
  }
  $field.removeData('wysiwyg');
  if (trigger != 'serialize') {
    $field.show();
  }
};

Drupal.wysiwyg.editor.instance.jwysiwyg = {
  insert: function (content) {
    $('#' + this.field).wysiwyg('insertHtml', content);
  },

  setContent: function (content) {
    $('#' + this.field).wysiwyg('setContent', content);
  },

  getContent: function () {
    return $('#' + this.field).wysiwyg('getContent');
  }
};

})(jQuery);
