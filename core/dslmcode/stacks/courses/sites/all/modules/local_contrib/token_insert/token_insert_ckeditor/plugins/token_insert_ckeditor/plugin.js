/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal:true, jQuery: true, CKEDITOR:true*/
(function($) {
  "use strict";
  CKEDITOR.plugins.add('token_insert_ckeditor', {
    init: function(editor) {
      var id = 'token-insert-' + editor.id + '-dialog-container';
      var dialogcontent = {
        id: 'token_insert_ckeditor',
        type: 'html',
        html: '<div id="' + id + '"></div>'
      };

      // Register a dialog box with CKEditor.
      CKEDITOR.dialog.add('token_insert_ckeditor_dialog', function() {
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
                dialogcontent
              ]
            }
          ],
          buttons: [CKEDITOR.dialog.cancelButton],
          onShow: function () {
            var editor = this.getParentEditor();
            var id = 'token-insert-' + editor.id + '-dialog-container';
            var $content = $(this.getElement('info', 'token_insert_ckeditor').$);
            var ajax_settings = {
              url: Drupal.settings.basePath + 'token_insert_ckeditor/insert/' + id,
              event: 'dialog.token-insert-ckeditor',
              method: 'html'
            };
            new Drupal.ajax(id, $content[0], ajax_settings);
            $content.trigger(ajax_settings.event);
            $content.bind('token-insert-table-loaded', function () {
              $(this).find('.token-insert-table .token-key').once('token-insert-table', function() {
                var $token_link = $(this);
                var newThis = $('<a href="javascript:void(0);" title="' + Drupal.t('Insert this token into your form') + '">' + $token_link.html() + '</a>').click(function() {
                  var $self = $(this);
                  editor.insertText($self.text());
                });
                $token_link.html(newThis);
              });
            });
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

