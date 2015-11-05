/**
 * @file
 * Handles statement creation for YouTube player interaction.
 */

(function ($) {

  var YoutubeTracker = function(id) {
    var globals = this;

    this.id = id;
    this.title = "- Private -";
    this.url = "https://youtube.com/"+this.id;
    this.time = null;

    this.init = function() {
      globals.player = new YT.Player(id, {
        events: {
          'onReady': function(event) {

            var video_data = event.target.getVideoData();

            // Get some data.
            globals.duration = event.target.getDuration();
            globals.title = video_data.title;
            globals.url = video_data.video_id;

            // Start checking video progress.
            globals.tracker = new VideoTracker(globals.duration*1000, {
              getCurrentTime: function(onDone) {
                onDone(globals.player.getCurrentTime()*1000);
              },
              events: {
                all: function() {
                  globals.trackEvent.apply(globals, arguments);
                }
              },
            });

          },
        }
      });
    };

    this.trackEvent = function (event, start, end) {
      var event2verb = {
        onPlay: "play",
        onPaused: 'paused',
        onSkipped: "skipped",
        onComlete: "complete",
        onWatched: "watched",
      };

      var verb = event2verb[event];

      var data = {
        module: 'youtube',
        verb: verb,
        id: globals.url,
        title: globals.title,
        duration: globals.duration,
        referrer: Drupal.settings.tincanapi.currentPage
      };

      if(start !== null) {
        data["start_time"] = start;
      }

      if(end !== null) {
        data["end_time"] = end;
      }

      Drupal.tincanapi.track(data);

      // Create Watched event
      if(verb == "play") {
        globals.time = start;
      }

      if(verb == "paused" && globals.time !== null) {
        globals.trackEvent("onWatched", globals.time, end);
        globals.time = null;
      }
    };

    this.init();
  };

  // Add Youtube API
  var tag = document.createElement('script');
  tag.src = "//www.youtube.com/iframe_api";
  var firstScriptTag = document.getElementsByTagName('script')[0];
  firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

  window.onYouTubeIframeAPIReady = function() {
    $(document).ready(function () {
      $('.media-youtube-video').not('.tincan-processed').each(function () {
        Drupal.tincanapi.youtube.processVideo($(this));
      });
    });
  };

  Drupal.behaviors.tincanapiYouTube = {
    attach: function (context) {
      // The YouTube API isn't ready when the page is loaded.
      if (typeof YT !== 'undefined') {
        $('.media-youtube-video', context).not('.tincan-processed').each(function () {
          Drupal.tincanapi.youtube.processVideo($(this));
        });
      }
    }
  };

  Drupal.tincanapi.youtube = {
    processVideo: function(video) {
      if(typeof YT.Player === "undefined") {
        return;
      }

      var iframe = video.find('iframe');
      var id;

      if (iframe.attr('id')) {
        id = iframe.attr('id');
      }
      else {
        id = Drupal.tincanapi.youtube.getRandomId();
        iframe.attr('id', id);
      }

      new YoutubeTracker(id);

      video.addClass('tincan-processed');
    },

    getRandomId: function() {
      var id = '';

      var min = 97;
      var max = 122;

      for (var i = 0; i < 10; i++) {
        var random = Math.floor(Math.random() * (max - min + 1)) + min;
        id += String.fromCharCode(random);
      }

      return 'youtube-' + id;
    },
  };



})(jQuery);
