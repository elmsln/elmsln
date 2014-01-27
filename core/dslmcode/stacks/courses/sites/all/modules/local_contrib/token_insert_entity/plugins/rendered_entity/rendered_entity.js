// $Id
(function ($) {
  /**
   * Wysiwyg plugin button implementation for Rendered Entity plugin.
   */
  Drupal.wysiwyg.plugins.rendered_entity = {
    /**
     * Return whether the passed node belongs to this plugin.
     *
     * @param node
     *   The currently focused DOM element in the editor content.
     */
    isNode: function(node) {
      return ($(node).is('img.rendered-entity'));
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
      this.insert_form(data, settings, instanceId);
     },

    /**
     * Renders the form to insert a token.
     */
    insert_form: function (data, settings, instanceId) {
      // Location, where to fetch the dialog.
      var aurl = Drupal.settings.basePath + 'index.php?q=token_insert_entity/insert';
      dialogdiv = jQuery('<div id="token-insert-entity-dialog"></div>');
      // Load the Insert Token form.
      $.getJSON(aurl, function(data) {
        dialogdiv.html(data.markup);
        dialogdiv.view_modes = data.view_modes;
        var dialogClose = function () {
          try {
            dialogdiv.dialog('destroy').remove();
          } catch (e) {};
        };
        btns = {};
        // Implement the Insert button.
        btns[Drupal.t('Insert token')] = function () {
          var entity = dialogdiv.contents().find('#edit-entity').val();
          var viewMode = $('#view-modes', dialogdiv).val();
          // Check that a content and view mode have been selected.
          if ((!entity) || (!viewMode)) {
            $('#edit-entity', dialogdiv).focus();
            return;
          }
          token = '[embed:' + viewMode + ':' + entity + ']';

          var editor_id = instanceId;
          Drupal.wysiwyg.plugins.rendered_entity.insertIntoEditor(token, editor_id);
          jQuery(this).dialog("close");
        };

        // Implement the Cancel button.
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

        // Prevent form submission.
        Drupal.attachBehaviors($('#token-insert-entity-form'));
        $('form', dialogdiv).submit(function() {
          // Prevent form submission.
          return false;
        });

        // Show available view modes for the selected content.
        // Note: this needs core patch http://drupal.org/node/365241#comment-6314864
        $('#edit-entity', dialogdiv).bind('autocompleteSelect', function(event) {
          // Remove extra fields in case the user changed his mind and chosed another entity.
          $('.extra-fields', dialogdiv).remove();
          // Render a select with the view modes of the selected entity.
          var entity = $('#edit-entity', dialogdiv).val();
          entity = entity.split(':');
          var view_modes = dialogdiv.view_modes[entity[0]];
          $('form', dialogdiv).append('<div class="form-item form-type-select form-item-view-modes extra-fields" role="application"><label for="edit-view-modes">View modes</label><select id="view-modes" name="view_modes" class="form-select"></select></div>');
          $('#view-modes').append($('<option>', { value : 'link' }).text('Link to content'));
          $.each(view_modes, function(key, value) {
            $('#view-modes').append($('<option>', { value : 'render:' + key }).text('Embedded view: ' + value));
          });
        });
      });
    },

    /**
     * Inserts a token into the editor
     */
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
      content = content.replace(/<!--rendered-entity-->/g, this._getPlaceholder(settings));
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
      return '<img src="' + settings.path + '/images/spacer.gif" alt="&lt;--rendered-entity-&gt;" title="&lt;--rendered-entity--&gt;" class="rendered-entity drupal-content" />';
    }
  };
}(jQuery));
