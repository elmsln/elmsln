
/**
 *  @file
 *  Create the 'YouTube' tab for the WYSIWYG plugins.
 */

// (function ($) {
//   namespace('Drupal.media.browser.plugin');
//
//   Drupal.media.browser.plugin.media_youtube = function(mediaBrowser, options) {
//     return {
//       init: function() {
//         tabset = mediaBrowser.getTabset();
//         tabset.tabs('add', '#media_youtube', 'YouTube');
//         mediaBrowser.listen('tabs.show', function (e, id) {
//           if (id == 'media_youtube') {
//             // We only need to set this once.
//             // We probably could set it upon load.
//             if (mediaBrowser.getActivePanel().html() == '') {
//               mediaBrowser.getActivePanel().html(options.media_youtube);
//             }
//           }
//         });
//       }
//     }
//   };
//
//   // For now, I guess self registration makes sense.
//   // Really though, we should be doing it via drupal_add_js and some settings
//   // from the drupal variable.
//   //@todo: needs a review.
//   Drupal.media.browser.register('media_youtube', Drupal.media.browser.plugin.media_youtube, {});
// })(jQuery);

(function ($) {
  namespace('media.browser.plugin');

  Drupal.media.browser.plugin.youtube_library = function(mediaBrowser, options) {

    return {
      mediaFiles: [],
      init: function() {
        tabset = mediaBrowser.getTabset();
        tabset.tabs('add', '#youtube_library', 'YouTube');
        var that = this;
        mediaBrowser.listen('tabs.show', function (e, id) {
          if (id == 'youtube_library') {
            // This is kinda rough, I'm not sure who should delegate what here.
            mediaBrowser.getActivePanel().addClass('throbber');
            mediaBrowser.getActivePanel().html('');
            //mediaBrowser.getActivePanel().addClass('throbber');

            // Assumes we have to refresh everytime.
            // Remove any existing content
            mediaBrowser.getActivePanel().append('<ul></ul>');
            that.browser = $('ul', mediaBrowser.getActivePanel());
            that.browser.addClass('clearfix');
            that.getMedia();
          }
        });
      },

      getStreams: function () {
        return ['youtube://'];
      },

      getConditions: function () {
        return {};
        //return this.settings.conditions;
      },

      getMedia: function() {
        var that = this;
        var callback = mediaBrowser.getCallbackUrl('getMedia');
        var params = {
          conditions: JSON.stringify(this.getConditions()),
          streams: JSON.stringify(this.getStreams())
        };
        jQuery.get(
          callback,
          params,
          function(data, status) {
            that.mediaFiles = data.media;
            that.emptyMessage = data.empty;
            that.pager = data.pager;
            that.render();
          },
          'json'
        );
      },

      render: function() {
        var that = this;
        mediaBrowser.getActivePanel().removeClass('throbber');
        if (this.mediaFiles.length < 1) {
          jQuery('<div id="media-empty-message" class="media-empty-message"></div>').appendTo(this.browser)
            .html(this.emptyMessage);
          return;
        }

        for (var m in this.mediaFiles) {
          mediaFile = this.mediaFiles[m];

          var listItem = jQuery('<li></li>').appendTo(this.browser)
            .attr('id', 'media-file-' + mediaFile.fid)
            .addClass('media-file');

          var imgLink = jQuery('<a href="#"></a>').appendTo(listItem)
            .html(mediaFile.preview)
            .bind('click', mediaFile, function(e) {
              // Notify the main browser
              //this.selectedMedia = mediaFile;
              $('div.media-thumbnail img').removeClass('selected');
              $('div.media-thumbnail img', $(this)).addClass('selected');
              mediaBrowser.notify('mediaSelected', {mediaFiles: [e.data]});
              //that.settings.onSelect(mediaFile);
              return false;
            });
        }
        jQuery('<div id="media-pager" class="media-pager"></div>').appendTo(this.browser)
          .html(this.pager);
      }
  };
};

  Drupal.media.browser.register('youtube_library', Drupal.media.browser.plugin.youtube_library);
})(jQuery);
