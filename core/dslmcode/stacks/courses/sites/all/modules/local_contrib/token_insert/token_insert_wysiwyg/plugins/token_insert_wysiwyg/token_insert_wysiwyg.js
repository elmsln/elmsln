// $Id
(function ($) {
function hideShowFieldset(buttonid, action) {
  var $fieldset = $('#' + buttonid).closest('fieldset');
  $fieldset[action]();
}

/**
 * Wysiwyg plugin button implementation for token_insert plugin.
 */
Drupal.wysiwyg.plugins.token_insert_wysiwyg = {
  /**
   * Return whether the passed node belongs to this plugin.
   *
   * @param node
   *   The currently focused DOM element in the editor content.
   */
  isNode: function(node) {
    return ($(node).is('img.token_insert_wysiwyg-token_insert_wysiwyg'));
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
  invoke: function(data, settings, instanceId) {
    Drupal.wysiwyg.plugins.token_insert_wysiwyg.insert_form(data, settings, instanceId);    
  },
  
  
  insert_form: function (data, settings, instanceId) {
    form_id = Drupal.settings.token_insert_wysiwyg.current_form;

    // Location, where to fetch the dialog.
    var aurl = Drupal.settings.basePath + 'index.php?q=token_insert_wysiwyg/insert/' + form_id;
    dialogdiv = jQuery('<div id="token-insert-dialog"></div>');
    dialogdiv.load(aurl + " #token-insert-wysiwyg-form", function(){
      var dialogClose = function () {
        try {
          dialogdiv.dialog('destroy').remove();
        } catch (e) {};
      };
      btns = {};
      btns[Drupal.t('Insert token')] = function () {

        var token = dialogdiv.contents().find('#edit-insert option:selected').val();
        var editor_id = instanceId;

        token = '[' + token + ']';
        Drupal.wysiwyg.plugins.token_insert_wysiwyg.insertIntoEditor(token, editor_id);
        jQuery(this).dialog("close");

      };

      btns[Drupal.t('Cancel')] = function () {
        jQuery(this).dialog("close");
      };

      dialogdiv.dialog({
        modal: true,
        autoOpen: false,
        closeOnEscape: true,
        resizable: false,
        draggable: false,
        autoresize: true,
        namespace: 'jquery_ui_dialog_default_ns',
        dialogClass: 'jquery_ui_dialog-dialog',
        title: Drupal.t('Insert token'),
        buttons: btns,
        width: 700,
        close: dialogClose
      });
      dialogdiv.dialog("open");
    });
  },
    
  insertIntoEditor: function (token, editor_id) {
    Drupal.wysiwyg.instances[editor_id].insert(token);
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
  attach: function(content, settings, instanceId) {
    content = content.replace(/<!--token_insert_wysiwyg-->/g, this._getPlaceholder(settings));
    // hide the token_insert_text fieldset when wysiwyg is enabled,
    // token_insert_test won't work then, users should use the
    // wysiwyg plugin instead.
    if (typeof Drupal.settings.token_insert !== 'undefined') {
      $.each(Drupal.settings.token_insert.buttons, function(index, fieldid) {
        hideShowFieldset(index, 'hide');
      });
    }
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
  detach: function(content, settings, instanceId) {
    var $content = $('<div>' + content + '</div>');
    // show the token_insert_text fieldset when wysiwyg is disabled
    if (typeof Drupal.settings.token_insert !== 'undefined') {
      $.each(Drupal.settings.token_insert.buttons, function(index, fieldid) {
        hideShowFieldset(index, 'show');
      });
    }
    $.each($('img.token_insert_wysiwyg-token_insert_wysiwyg', $content), function (i, elem) {
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
  _getPlaceholder: function (settings) {
    return '<img src="' + settings.path + '/images/spacer.gif" alt="&lt;--token_insert_wysiwyg-&gt;" title="&lt;--token_insert_wysiwyg--&gt;" class="token_insert_wysiwyg-token_insert_wysiwyg drupal-content" />';
  }
};
})(jQuery);