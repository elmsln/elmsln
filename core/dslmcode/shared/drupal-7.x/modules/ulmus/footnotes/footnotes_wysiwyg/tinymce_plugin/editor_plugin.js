(function() { 
	// Load plugin specific language pack
//	tinymce.PluginManager.requireLangPack('footnotes');

  tinymce.create('tinymce.plugins.FootnotesPlugin', {
    /**
     * Initialize the plugin, executed after the plugin has been created.
     *
     * This call is done before the editor instance has finished it's
     * initialization so use the onInit event of the editor instance to
     * intercept that event.
     *
     * @param ed
     *   The tinymce.Editor instance the plugin is initialized in.
     * @param url
     *   The absolute URL of the plugin location.
     */
    init : function(ed, url) {
      
      // Register the Footnotes execCommand.
      ed.addCommand('Footnotes', function() {
        ed.windowManager.open({
          file : url + '/footnote.htm',
          width : 400,
          height : 300,
          inline : 1
        });
      });

      // Register Footnotes button.
      // The first argument should match the <key> used in 
      // @plugins[<plugin name>]["buttons"][<key>] in hook_wysiwyg_plugin()
      ed.addButton('footnotes', { 
        title : Drupal.t('Add footnote'),
        cmd : 'Footnotes', // This should match the string in ed.addCommand above
        image : url + '/img/note_add.png'
      });
    },

    /**
     * Return information about the plugin as a name/value array.
     */
    getInfo : function() {
      return {
        longname : 'TinyMCE Footnotes',
        author : 'Greg Lavallee',
        authorurl : 'http://www.citidc.com',
        infourl : 'http://drupal.org/project/footnotes',
        version : "0.1"
      };
    }
  });

  // Register plugin.
  tinymce.PluginManager.add('footnotes', tinymce.plugins.FootnotesPlugin);
})();
