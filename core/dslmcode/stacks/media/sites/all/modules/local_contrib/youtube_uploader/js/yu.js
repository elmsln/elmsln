/**
* @file
* Javascript to process the video to YouTube.
*/

(function($) {
  Drupal.behaviors.youtube_uploader = {

    attach : function(context, settings) {
      var STATUS_POLLING_INTERVAL_MILLIS = 60 * 1000; // One minute.


      /**
       * YouTube video uploader class
       *
       * @constructor
       */
      var UploadVideo = function() {
        this.videoId = '';
        this.uploadStartTime = 0;
      };

      UploadVideo.prototype.ready = function(accessToken, object) {
        this.accessToken = accessToken;
        $('a.upload-toyoutube').bind("click", this.handleUploadClicked.bind(this));
      };

      /**
       * Uploads a video file to YouTube.
       *
       * @method uploadFile
       * @param {object} file File object corresponding to the video to upload.
       * @param {string} token requested to upload.
       */
      UploadVideo.prototype.uploadFile = function(file, token) {
        var metadata = {
          snippet: {
            title: this.title,
            description: this.description,
            tags: this.tags,
            categoryId: this.categoryId
          },
          status: {
            privacyStatus: this.privacy
          }
        };
        var uploader = new MediaUploader({
          baseUrl: 'https://www.googleapis.com/upload/youtube/v3/videos',
          file: file,
          token: token,
          metadata: metadata,
          params: {
            part: Object.keys(metadata).join(',')
          },
          onError: function(data) {
            var message = data;
            // Assuming the error is raised by the YouTube API, data will be
            // a JSON string with error.message set. That may not be the
            // only time onError will be raised, though.
            try {
              var errorResponse = JSON.parse(data);
              message = errorResponse.error.message;
            } finally {
              alert(message);
            }
          }.bind(this),
          onProgress: function(data) {
            var currentTime = Date.now();
            var bytesUploaded = data.loaded;
            var totalBytes = data.total;
            // The times are in millis, so we need to divide by 1000 to get seconds.
            var bytesPerSecond = bytesUploaded / ((currentTime - this.uploadStartTime) / 1000);
            var estimatedSecondsRemaining = Math.round((totalBytes - bytesUploaded) / bytesPerSecond);
            var percentageComplete = Math.ceil((bytesUploaded * 100) / totalBytes);

            $('#upload-progress').attr({
              value: bytesUploaded,
              max: totalBytes
            });

            $('#percent-transferred').text(percentageComplete);
            $('#seconds-left').text(estimatedSecondsRemaining);

            $('.during-upload').show();
          }.bind(this),
          onComplete: function(data) {
            var uploadResponse = JSON.parse(data);
            // Add the id to the hidden fid field.
            $('input.youtube_hidden_id:last').val(uploadResponse.id);
            // Remove form input value. 
            $('.field-type-youtube-upload .form-type-file input').val('');
            // Then trigger the real upload button so Drupal will rebuild everything fine.
            $('.field-type-youtube-upload .upload-video').trigger("mousedown");

          }.bind(this)
        });
        // This won't correspond to the *exact* start of the upload, but it should be close enough.
        this.uploadStartTime = Date.now();
        uploader.upload();
      };
      
      // Create a fake button to send the video to youtube.
      if ($('.upload-toyoutube').length < 1) {
        $('.field-type-youtube-upload .form-type-file')
            .after('<a href="javascript:;" class="button upload-toyoutube">' + Drupal.t('Upload') + '</a>')
            .end().find('.upload-toyoutube').bind("click", sendToYoutube);
      }

      // Refresh the thumb from youtube.
      $('.refresh_thumb a').each(refreshYoutubeInfo);
      
      // Get video title from node title
      if(Drupal.settings.youtube_uploader.autotitle == 1) {
        var $vid_title = $('.field-type-youtube-upload input.video_title');
        $('#edit-title').keyup(function () {
          $vid_title.val( $(this).val() );
        });
      }

      function refreshYoutubeInfo() {
        // Test if binding is already done... do not know why it binds a
        // second event when the field is rebuilt ?? otherwise it
        // triggers 2 times the func.
        if (!$(this).data('events'))  {
          $(this).click(refreshYoutubeInfoClick);
        }
      }

      function refreshYoutubeInfoClick() {
        $(this).displayThrobber();
        var video_id = $(this).parents('.file-widget').find('input.youtube_hidden_id').val();
        var _this = $(this);
        // Coy the new thumb.
        $.getJSON(Drupal.settings.basePath + "youtube_uploader/refreshthumb/" + video_id, function(json) {
              _this.removeThrobber();
              if (json.error) {
                _this.parents('.video-form-preview').showErrorMessage(json.error);
              }
              else {
                // Replace the text by an image, ready to be populated.
                _this.parents('.video-form-preview').find(' .thumb span').replaceWith('<img src="" />');
                // Force refresh of thumb image.
                d = new Date();
                _this.parents('.video-form-preview').find('img').attr('src', json.src + '?' + d.getTime());
                // Add thumb_fid.
                _this.parents('.form-video-upload').find('input.thumb_fid').val(json.fid);
                // And new title.
                _this.parents('.form-video-upload').find('input.video_title').val(json.title);
                _this.parents('ul.title_options').find('li.title').text(json.title);
              }
            });
        return false;
      }

      function sendToYoutube() {
     // Remove error messages if any.
        $(this).parent('.form-managed-file').removeErrorMessage();
        $(this).unbind("click", sendToYoutube);

        // Check if title and file is set.
        var video_title = $(this).parents('.field-type-youtube-upload').find('input[type="text"]').val();
        if (video_title == '' || $(this).parents('.field-type-youtube-upload').find('input[type="file"]').val() == '') {
          $(this).parent('.form-managed-file').showErrorMessage('please provide a title AND a video file');
          $(this).bind("click", sendToYoutube);
          return false;
        }
        
        var field_ref = $(this).parents('.field-type-youtube-upload').find('input[name$="[youtube_uploader_field_ref]"]').val();
        
        var uploadVideo = new UploadVideo();
        
        var _this = $(this);
        $.getJSON(Drupal.settings.basePath + "youtube_uploader/get_upload_data/" + Drupal.encodePath(field_ref), function(json) {
 
          if (json.error) {
            _this.parent('.form-managed-file').showErrorMessage(json.error);
          } else {
            uploadVideo.description = json.up_settings.youtube_uploader_description;
            uploadVideo.tags = json.up_settings.youtube_uploader_tags.split(',');
            uploadVideo.categoryId = json.up_settings.youtube_uploader_category;
            uploadVideo.title = video_title;
            uploadVideo.privacy = json.up_settings.youtube_uploader_publishing_options;
            uploadVideo.uploadFile($('input.youtube-uploader-file').get(0).files[0], json.up_token.token);
          }

        });
      
        return false;

      }
      
   // Display error message.
      $.fn.showErrorMessage = function(message) {
        if ($(this).siblings('.messages').length < 1) {
          $(this).siblings('.messages').remove();
        }
        $(this).before('<div class="messages error" style="display:none">' + message + '</div>').siblings('.messages').slideDown();
      };
      $.fn.removeErrorMessage = function(message) {
        $(this).siblings('.messages').remove();
      };

      // Display throbber.
      $.fn.displayThrobber = function() {
        $(this).after('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div><span>&nbsp;</span></div>');
      };

      $.fn.waitingMessage = function(message) {
        $(this).find('.ajax-progress span').text(message);
      };

      // Remove throbber.
      $.fn.removeThrobber = function() {
        $(this).siblings('div.ajax-progress').remove();
      };

    }
  };

})(jQuery);
