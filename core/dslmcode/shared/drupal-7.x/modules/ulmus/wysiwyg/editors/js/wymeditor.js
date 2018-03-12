(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.wymeditor = function (context, params, settings) {
  // Prepend basePath to wymPath.
  settings.wymPath = settings.basePath + settings.wymPath;
  // Update activeId on focus.
  settings.postInit = function (instance) {
    $(instance._doc).find('body').focus(function () {
      Drupal.wysiwyg.activeId = params.field;
    });
  };
  // Attach editor.
  $('#' + params.field).wymeditor(settings);
};

/**
 * Detach a single editor instance.
 */
Drupal.wysiwyg.editor.detach.wymeditor = function (context, params, trigger) {
  var $field = $('#' + params.field, context);
  var index = $field.data(WYMeditor.WYM_INDEX);
  if (typeof index == 'undefined' || !WYMeditor.INSTANCES[index]) {
    return;
  }
  var instance = WYMeditor.INSTANCES[index];
  var i;
  instance.update();
  if (trigger != 'serialize') {
    $(instance._box).remove();
    $(instance._element).show();
    $field.removeData(WYMeditor.WYM_INDEX);
    WYMeditor.INSTANCES.splice(index, 1);
    // Reindex the editors to maintain internal state..
    for (i = 0; i < WYMeditor.INSTANCES.length; i++) {
      WYMeditor.INSTANCES[i]._index = i;
    }
    $field.show();
  }
};

Drupal.wysiwyg.editor.instance.wymeditor = {
  insert: function (content) {
    this.getInstance().insert(content);
  },

  setContent: function (content) {
    this.getInstance().html(content);
  },

  getContent: function () {
    return this.getInstance().xhtml();
  },

  getInstance: function () {
    var $field = $('#' + this.field);
    var index = $field.data(WYMeditor.WYM_INDEX);
    if (typeof index != 'undefined') {
      return WYMeditor.INSTANCES[index];
    }
    return null;
  }
};

})(jQuery);
