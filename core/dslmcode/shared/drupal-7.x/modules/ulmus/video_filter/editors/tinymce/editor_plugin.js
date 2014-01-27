(function ($) {
  tinymce.create('tinymce.plugins.video_filter', {
    init : function(ed, url) {
      // Register commands
      ed.addCommand('mceVideoFilter', function() {
        ed.windowManager.open({
          file : Drupal.settings.video_filter.url.wysiwyg_tinymce,
          width : 580,
          height : 480,
          inline : true,
          scrollbars : 1,
          popup_css : false
        }, {
          plugin_url : url
        });
      });

      // Register buttons
      ed.addButton('video_filter', {
        title : 'Video filter',
        cmd : 'mceVideoFilter',
        image : url + '/images/video_filter.png'
      });
    },

    getInfo : function() {
      return {
        longname : 'Video Filter',
        author : 'Video Filter',
        authorurl : 'http://drupal.org/project/video_filter',
        infourl : 'http://drupal.org/project/video_filter',
        version : tinymce.majorVersion + "." + tinymce.minorVersion
      };
    }
  });
  // Register plugin
  tinymce.PluginManager.add('video_filter', tinymce.plugins.video_filter);
})(jQuery);
