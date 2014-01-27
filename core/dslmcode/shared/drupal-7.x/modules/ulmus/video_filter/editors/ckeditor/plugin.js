/**
 * @file Plugin for inserting video tags with video_filter
 */
(function ($) {
  CKEDITOR.plugins.add('video_filter', {

    requires : [],

    init: function(editor) {

      // Add Button
      editor.ui.addButton('video_filter', {
        label: 'Video filter',
        command: 'video_filter',
        icon: this.path + 'video_filter.png'
      });
      // Add Command
      editor.addCommand('video_filter', {
        exec : function () {
          var path = (Drupal.settings.video_filter.url.wysiwyg_ckeditor) ? Drupal.settings.video_filter.url.wysiwyg_ckeditor : Drupal.settings.video_filter.url.ckeditor
          var media = window.showModalDialog(path, { 'opener' : window, 'editorname' : editor.name }, "dialogWidth:580px; dialogHeight:480px; center:yes; resizable:yes; help:no;");
        }
      });

      // Register an extra fucntion, this will be used in the popup.
      editor._.video_filterFnNum = CKEDITOR.tools.addFunction(insert, editor);
    }

  });

  function insert(params, editor) {
    var selection = editor.getSelection(),
      ranges = selection.getRanges(),
      range,
      textNode;

    editor.fire('saveSnapshot');

    var str = '[video:' + params.file_url;
    if (params.width) {
      str += ' width:' + params.width;
    }
    if (params.height) {
      str += ' height:' + params.height;
    }
    if (params.align) {
      str += ' align:' + params.align;
    }
    if (params.autoplay) {
      str += ' autoplay:' + params.autoplay;
    }
    str += ']';

    for (var i = 0, len = ranges.length; i < len; i++) {
      range = ranges[i];
      range.deleteContents();

      textNode = CKEDITOR.dom.element.createFromHtml(str);
      range.insertNode(textNode);
    }

    range.moveToPosition(textNode, CKEDITOR.POSITION_AFTER_END);
    range.select();

    editor.fire('saveSnapshot');
  }

})(jQuery);
