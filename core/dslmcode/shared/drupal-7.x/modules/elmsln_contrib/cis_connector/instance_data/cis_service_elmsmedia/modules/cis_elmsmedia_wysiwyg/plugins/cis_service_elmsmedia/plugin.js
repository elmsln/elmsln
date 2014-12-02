/**
 * @file
 * Plugin for inserting images with cis_service_elmsmedia.
 */

(function($) {
  Drupal.visualSelectFile || (Drupal.visualSelectFile = {});

  CKEDITOR.plugins.add('cis_service_elmsmedia', {
    "requires": ['fakeobjects'],
    "init": function(editor) {

      var
        $textarea = $('#' + editor.name),
        field = $textarea.data('elmsmedia-field');
      editor.elmsmedia_field = field;

      // Add Button.
      editor.ui.addButton('cis_service_elmsmedia', {
        "label": 'cis_service_elmsmedia',
        "command": 'cis_service_elmsmedia',
        "icon": this.path + 'cis_service_elmsmedia.png'
      });

      // Add Command.
      editor.addCommand('cis_service_elmsmedia', {
        exec: function(editor) {
          var path = Drupal.settings.basePath + 'admin/cis_service_elmsmedia';
          path += '?ckeditor&iframe&elmsmedia_field=' + editor.elmsmedia_field + '#modal';

          Drupal.visualSelectFile.editor = editor;

          // Method 3 - in an iframe.
          Drupal.visualSelectFile.openModal(path, {
            "type": 'ckeditor',
            "field": editor.elmsmedia_field,
          });
        }
      });

    }
  });

})(jQuery);
