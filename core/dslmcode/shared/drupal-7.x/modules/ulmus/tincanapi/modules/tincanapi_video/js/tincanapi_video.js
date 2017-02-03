/**
 * @file
 * Handles statement creation for Vimeo / YouTube player interaction.
 */

(function ($) {
  // tee up for tracking
  $(document).ready(function () {
    // Add Youtube API if we detect anything that it would work against in the first place
    if ($(Drupal.settings.tincanapi.selector_youtube).length > 0) {
      var tag = document.createElement('script');
      tag.id = 'tincanapi-google-api';
      tag.src = "//www.youtube.com/iframe_api";
      var firstScriptTag = document.getElementsByTagName('script')[0];
      firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);
      window.onYouTubeIframeAPIReady = function() {
        // YouTube player support; pass ready event to jQuery so we can catch in player.
        $(document).ready(function () {
          $(Drupal.settings.tincanapi.selector_youtube).not('.tincan-processed').each(function () {
            Drupal.tincanapi.youtube.processVideo($(this));
          });
          // check for ableplayer compatibility
          if (typeof window.AblePlayer !== 'undefined') {
            AblePlayer.youtubeIframeAPIReady = true;
            $('body').trigger('youtubeIframeAPIReady', []);
          }
        });
      };
    }
    // try and skim any html5 object on the page
    $('video').not('.tincan-processed').each(function () {
      Drupal.tincanapi.html5Video.processVideo($(this));
    });
  });
      // vimeo tracking
  var HTML5VideoTracker = function(element) {
    var globals = this;
    this.element = element;
    this.title = Drupal.settings.tincanapi.title;
    this.url = Drupal.settings.tincanapi.currentPage;
    this.time = null;
    this.HTML5Video = element;
    this.init = function() {
      globals.element.on('playing', function(event) {
        globals.trackEvent('play', globals.element.context.currentTime, globals.time);
      }).on('pause', function(event) {
        globals.trackEvent('paused', globals.element.context.currentTime, globals.time);
      }).on('seeking', function(event) {
        globals.trackEvent('skipped', globals.time, globals.element.context.currentTime);
      }).on('ended', function(event){
        globals.trackEvent('complete', globals.element.context.currentTime, globals.time);
      });
    };

    this.trackEvent = function (verb, start, end) {
      var data = {
        module: 'video',
        verb: verb,
        id: globals.url,
        title: globals.title,
        duration: globals.element.context.duration,
        referrer: Drupal.settings.tincanapi.currentPage
      };

      if (start !== null) {
        data["start_time"] = start;
      }

      if (end !== null) {
        data["end_time"] = end;
      }
      // don't send paused event
      if (verb != "paused") {
        Drupal.tincanapi.track(data);
      }
      if (verb == "paused" && globals.time !== null) {
        globals.trackEvent("watched", globals.time, start);
      }
      globals.time = start;
    };

    this.init();
  };
  Drupal.tincanapi.html5Video = {
    processVideo: function(video) {
      var id;
      if ($(video).attr('id')) {
        id = $(video).attr('id');
      }
      else {
        id = Drupal.tincanapi.html5Video.getRandomId();
        video.attr('id', id);
        $(video).attr('id', id);
      }
      // HTML5 tracker
      new HTML5VideoTracker(video);
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

      return 'html5video-' + id;
    },
  };
  // youtube tracking
  var YoutubeTracker = function(id) {
    var globals = this;
    this.id = id;
    this.title = "- Private -";
    // temporary url placeholder
    this.url = "https://youtube.com/watch?v=" + this.id;
    this.time = null;
    this.init = function() {
      globals.youtubePlayer = new YT.Player(id, {
        events: {
          'onReady': function(event) {
            var video_data = event.target.getVideoData();
            // Get some data.
            globals.duration = event.target.getDuration();
            globals.title = video_data.title;
            globals.url = "https://youtube.com/watch?v=" + video_data.video_id;
            // Start checking video progress.
            globals.tracker = new VideoTracker(globals.duration*1000, {
              getCurrentTime: function(onDone) {
                onDone(globals.youtubePlayer.getCurrentTime()*1000);
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
        onComplete: "complete",
        onWatched: "watched",
      };

      var verb = event2verb[event];
      var data = {
        module: 'video',
        verb: verb,
        id: globals.url,
        title: globals.title,
        duration: globals.duration,
        referrer: Drupal.settings.tincanapi.currentPage
      };

      if (start !== null) {
        data["start_time"] = start;
      }

      if(end !== null) {
        data["end_time"] = end;
      }
      // we need to see paused events but they are meaningless to actually track
      if (verb != "paused") {
        Drupal.tincanapi.track(data);
      }
      // Create Watched event
      if (verb == "play") {
        globals.time = start;
      }

      if (verb == "paused" && globals.time !== null) {
        globals.trackEvent("onWatched", globals.time, end);
        globals.time = null;
      }
    };

    this.init();
  };
  Drupal.behaviors.tincanapiYouTube = {
    attach: function (context) {
      // The YouTube API isn't ready when the page is loaded.
      if (typeof YT !== 'undefined') {
        $(Drupal.settings.tincanapi.selector_youtube, context).not('.tincan-processed').each(function () {
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

      if ($(iframe.context).attr('id')) {
        id = $(iframe.context).attr('id');
      }
      else {
        id = Drupal.tincanapi.youtube.getRandomId();
        iframe.attr('id', id);
        $(iframe.context).attr('id', id);
      }
      // mediavideo specific src
      if ($(iframe.context).attr('data-mediavideo-src')) {
        var tmp = $(iframe.context).attr('data-mediavideo-src');
        if (tmp.indexOf('?') == -1) {
          var append = '?enablejsapi=1';
        }
        else {
          var append = '&enablejsapi=1';
        }
        $(iframe.context).attr('data-mediavideo-src', '');
        $(iframe.context).attr('data-mediavideo-src', tmp + append);
        new YoutubeTracker(id);
        video.addClass('tincan-processed');
      }
      // add in youtubetracker stuff if we have an src on the iframe
      else if ($(iframe.context).attr('src')) {
        var tmp = $(iframe.context).attr('src');
        if (tmp.indexOf('?') == -1) {
          var append = '?enablejsapi=1';
        }
        else {
          var append = '&enablejsapi=1';
        }
        $(iframe.context).attr('src', '');
        $(iframe.context).attr('src', tmp + append);
        new YoutubeTracker(id);
        video.addClass('tincan-processed');
      }
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

  // vimeo tracking
  var VimeoTracker = function(iframe) {
    var globals = this;
    this.iframe = iframe;
    // get the id from the address itself
    var tmp = iframe.context.src;
    // looks stupid but ensures we get the video ID
    this.id = tmp.split('/').pop().split('?').shift();
    this.vimeoPlayer = new Vimeo.Player(iframe.context);

    this.title = "- Private -";
    this.url = "https://vimeo.com/" + this.id;
    this.time = null;
    this.init = function() {
      globals.vimeoPlayer.getDuration().then(function(duration) {
        globals.duration = duration;
        // Start checking data.
        globals.tracker = new VideoTracker(duration*1000, {
          getCurrentTime: function(onDone) {
            globals.vimeoPlayer.getCurrentTime().then(function(time) {
              onDone(time*1000);
            });
          },
          events: {
            all: function() {
              globals.trackEvent.apply(globals, arguments);
            }
          },
        });
      });

      // Get video information
      $.ajax({
        url: 'https://vimeo.com/api/v2/video/' + globals.id + '.json',
        dataType: 'json',
        success: function(data) {
          globals.title = data[0]["title"];
          globals.url = data[0]["url"];
        },
      });
    };

    this.trackEvent = function (event, start, end) {
      var event2verb = {
        onPlay: "play",
        onPaused: 'paused',
        onSkipped: "skipped",
        onComplete: "complete",
        onWatched: "watched",
      };

      var verb = event2verb[event];

      if(verb == null) {
        return false;
      }

      var data = {
        module: 'video',
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
      // don't track paused
      if (verb != "paused") {
        Drupal.tincanapi.track(data);
      }
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
  Drupal.behaviors.tincanapiVimeo = {
    attach: function (context) {

      $(Drupal.settings.tincanapi.selector_vimeo, context).not('.tincan-processed').each(function () {
        var iframe = $(this).find('iframe');
        var tmp = iframe.context.src;
        // looks stupid but ensures we get the video ID
        var id = tmp.split('/').pop().split('?').shift();
        iframe.attr('id', id);

        new VimeoTracker(iframe);

        $(this).addClass('tincan-processed');
        iframe.trigger('ready');
      });
    }
  };
})(jQuery);
