(function ($) {
  /**
   * Wysiwyg plugin button implementation for shortcode plugin.
   */
  Drupal.wysiwyg.plugins.shortcode_wysiwyg = {
    /**
     * Return whether the passed node belongs to this plugin.
     *
     * @param node
     *   The currently focused DOM element in the editor content.
     */
    isNode:function (node) {
      return ($(node).is('img.shortcode_wysiwyg-shortcode_wysiwyg'));
    },

    /**
     * Execute the button.
     *
     * @param data
     *   An object containing data about the current selection:
     *   - format: 'html' when the passed data is HTML content, 'text' when the
     *     passed data is plain-text content.
     *   - node: When 'format' is 'html', the focused DOM element in the editor.
     *   - content: The textual representation of the focused/selected editor
     *     content.
     * @param settings
     *   The plugin settings, as provided in the plugin's PHP include file.
     * @param instanceId
     *   The ID of the current editor instance.
     */
    invoke:function (data, settings, instanceId) {
      /*
       if (data.format == 'html') {
       var content = this._getPlaceholder(settings);
       }
       else {
       var content = '<!--shortcode_wysiwyg-->';
       }
       */
      Drupal.wysiwyg.plugins.shortcode_wysiwyg.insert_form(data, settings, instanceId);
    },


    insert_form:function (data, settings, instanceId) {
      var form_id = Drupal.settings.shortcode_wysiwyg.current_form;
      // Location, where to fetch the dialog.
      var aurl = Drupal.settings.basePath + 'index.php?q=shortcode_wysiwyg/' + Drupal.wysiwyg.instances[instanceId].format + '/' + form_id;
      var tmpdiv = $('<div id="shortcode-wysiwyg-form-wrapper" class="element-invisible"></div>');
      var dialogdiv = $('<div id="shortcode-insert-dialog"></div>');
      // We need to load the whole document so that scripts get executed
      tmpdiv.load(aurl, function () {
        var shortcodeForm = $(this).find('#shortcode-wysiwyg-form');
        dialogdiv.html(shortcodeForm);
        var dialogClose = function () {
          try {
            dialogdiv.dialog('destroy').remove();
          }
          catch (e) {
          }
          ;
        };
        var btns = {};
        btns[Drupal.t('Insert shortcode')] = function () {

          var shortcode = dialogdiv.contents().find('#edit-shortcode option:selected').val();
          var editor_id = instanceId;

          var options = [];
          dialogdiv.contents().find('.form-item').not(':hidden').find('input,select')
            .not('#edit-shortcode,[type="hidden"]')
            .each(function () {
              var name = $(this).attr('name'), val = $(this).val();
              if (val.length) {
                options.push(name + '=' + '"' + val + '"');
              }
            });

          shortcode = '[' + shortcode + (options.length ? ' ' + options.join(' ') : '') + ']' + data.content + '[/' + shortcode + ']';

          Drupal.wysiwyg.plugins.shortcode_wysiwyg.insertIntoEditor(shortcode, editor_id);
          dialogClose();
        };

        btns[Drupal.t('Cancel')] = function () {
          dialogClose();
        };

        dialogdiv.dialog({
          modal:true,
          autoOpen:false,
          closeOnEscape:true,
          resizable:false,
          draggable:false,
          autoresize:true,
          namespace:'jquery_ui_dialog_default_ns',
          dialogClass:'jquery_ui_dialog-dialog',
          title:Drupal.t('Insert shortcode'),
          buttons:btns,
          width:700,
          close:dialogClose
        });
        dialogdiv.dialog("open");
        // TODO: add context there
        Drupal.attachBehaviors();
      });
    },

    insertIntoEditor:function (shortcode, editor_id) {
      Drupal.wysiwyg.instances[editor_id].insert(shortcode);
    },

    /**
     * Prepare all plain-text contents of this plugin with HTML representations.
     *
     * Optional; only required for "inline macro tag-processing" plugins.
     *
     * @param content
     *   The plain-text contents of a textarea.
     * @param settings
     *   The plugin settings, as provided in the plugin's PHP include file.
     * @param instanceId
     *   The ID of the current editor instance.
     */
    attach:function (content, settings, instanceId) {
      content = content.replace(/<!--shortcode_wysiwyg-->/g, this._getPlaceholder(settings));
      return content;
    },

    /**
     * Process all HTML placeholders of this plugin with plain-text contents.
     *
     * Optional; only required for "inline macro tag-processing" plugins.
     *
     * @param content
     *   The HTML content string of the editor.
     * @param settings
     *   The plugin settings, as provided in the plugin's PHP include file.
     * @param instanceId
     *   The ID of the current editor instance.
     */
    detach:function (content, settings, instanceId) {
      var $content = $('<div>' + content + '</div>');
      $.each($('img.shortcode_wysiwyg-shortcode_wysiwyg', $content), function (i, elem) {
        //...
      });
      return $content.html();
    },

    /**
     * Helper function to return a HTML placeholder.
     *
     * The 'drupal-content' CSS class is required for HTML elements in the editor
     * content that shall not trigger any editor's native buttons (such as the
     * image button for this example placeholder markup).
     */
    _getPlaceholder:function (settings) {
      return '<img src="' + settings.path + '/images/spacer.gif" alt="&lt;--shortcode_wysiwyg-&gt;" title="&lt;--shortcode_wysiwyg--&gt;" class="shortcode_wysiwyg-shortcode_wysiwyg drupal-content" />';
    }
  };
})(jQuery);
