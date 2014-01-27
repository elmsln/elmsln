(function($) {
  CKEDITOR.plugins.add('token_insert_ckeditor', {
    init: function(editor, pluginPath) {
      var tokens = [];

      // Ajax call to get the tokens.
      $.getJSON(Drupal.settings.basePath + 'token_insert_ckeditor/insert', function(data) {
        tokens = data;
      });

      // Register a dialog box with CKEditor.
      CKEDITOR.dialog.add('token_insert_ckeditor_dialog', function(editor) {
        return {
          title: Drupal.t('Insert token'),
          minWidth: 250,
          minHeight: 50,
          contents: [
            {
              id: 'info',
              label: Drupal.t('Insert a token'),
              title: Drupal.t('Insert a token'),
              elements: [
                {
                  id: 'token_insert_ckeditor',
                  type: 'select',
                  items: tokens,
                  label: Drupal.t('Select a variable to insert:')
                }
              ]
            }
          ],
          onOk: function() {
            var editor = this.getParentEditor();
            var content = this.getValueOf('info', 'token_insert_ckeditor');
            if (content.length > 0) {
              editor.insertText('[' + content + ']');
            }
          }
        };
      });

      // Register a command with CKeditor to launch the dialog box.
      editor.addCommand('TokenInsert', new CKEDITOR.dialogCommand('token_insert_ckeditor_dialog'));

      // Add a button to the CKeditor that executes a CKeditor command.
      editor.ui.addButton('TokenInsert', {
        label: Drupal.t('Insert a token'),
        command: 'TokenInsert',
        icon: this.path + 'images/insert.png'
      });
    }
  });
})(jQuery);
