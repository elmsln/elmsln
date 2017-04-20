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

      if(typeof window.showModalDialog !== 'undefined') {
        editor.addCommand('video_filter', {
          exec : function () {
            var path = (Drupal.settings.video_filter.url.wysiwyg_ckeditor) ? Drupal.settings.video_filter.url.wysiwyg_ckeditor : Drupal.settings.video_filter.url.ckeditor
            var media = window.showModalDialog(path, { 'opener' : window, 'editorname' : editor.name }, "dialogWidth:580px; dialogHeight:480px; center:yes; resizable:yes; help:no;");
          }
        });

        // Register an extra function, this will be used in the popup.
        editor._.video_filterFnNum = CKEDITOR.tools.addFunction(insert, editor);
      }
      else {
        editor.addCommand('video_filter', new CKEDITOR.dialogCommand('video_filterDialog'));
      }
    }
  });

  CKEDITOR.dialog.add('video_filterDialog', function( editor ) {
    var instructions_path = Drupal.settings.video_filter.instructions_url;

    return {
      title : 'Add Video',
      minWidth : 600,
      minHeight : 180,
      contents : [{
        id : 'general',
        label : 'Settings',
        elements : [
          {
            type : 'text',
            id : 'file_url',
            label : 'URL',
            validate : CKEDITOR.dialog.validate.notEmpty( 'The link must have a URL.' ),
            required : true,
            commit : function( data )
            {
              data.file_url = this.getValue();
            }
          },
          {
            type : 'text',
            id : 'width',
            label : 'Width',
            commit : function( data )
            {
              data.width = this.getValue();
            }
          },
          {
            type : 'text',
            id : 'height',
            label : 'Height',
            commit : function( data )
            {
              data.height = this.getValue();
            }
          },
          {
            type : 'select',
            id : 'align',
            label : 'Align',
            'default': 'none',
            items: [
              ['None', ''],
              ['Left', 'left'],
              ['Right', 'right'],
              ['Center', 'center']
            ],
            commit : function( data )
            {
              data.align = this.getValue();
            }
          },
          {
            type : 'checkbox',
            id : 'autoplay',
            label : 'Autoplay',
            'default': '',
            commit : function( data )
            {
              data.autoplay = this.getValue() ? 1 : 0;
            }
          },
          {
              type: 'html',
              html: '<iframe src="' + instructions_path + '" style="width:100%; height: 200px;"></iframe>',
          },
        ]
      }],
      onOk : function()
      {
        var dialog = this,
          data = {},
          link = editor.document.createElement( 'p' );
        this.commitContent( data );
        var str = '[video:' + data.file_url;
        if (data.width) {
          str += ' width:' + data.width;
        }
        if (data.height) {
          str += ' height:' + data.height;
        }
        if (data.align) {
          str += ' align:' + data.align;
        }
        if (data.autoplay) {
          str += ' autoplay:' + data.autoplay;
        }
        str += ']';
        link.setHtml( str );
        editor.insertElement( link );
      }
    };
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
    else {
      str += ' autoplay:' + '0';
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
