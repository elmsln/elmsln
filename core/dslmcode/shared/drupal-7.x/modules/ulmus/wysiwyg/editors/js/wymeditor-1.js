(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.wymeditor = function (context, params, settings) {
  // Prepend basePath to wymPath.
  settings.wymPath = settings.basePath + settings.wymPath;
  settings.postInit = function (instance) {
    var $doc = $(instance._doc);
    // Inject stylesheet for backwards compatibility.
    if (settings.stylesheet) {
      $doc.find('head').append('<link rel="stylesheet" type="text/css" media="screen" href="' + settings.stylesheet + '">');
    }
    // Update activeId on focus.
    $doc.find('body').focus(function () {
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
  instance.update();
  if (trigger != 'serialize') {
    instance.vanish();
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
    return this.getInstance().html();
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
