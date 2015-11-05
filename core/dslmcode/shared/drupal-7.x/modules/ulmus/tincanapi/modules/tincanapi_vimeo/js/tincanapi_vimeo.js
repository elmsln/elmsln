/**
 * @file
 * Handles statement creation for Vimeo player interaction.
 */

// Froogaloop library
var Froogaloop=function(){function e(a){return new e.fn.init(a)}function g(a,c,b){if(!b.contentWindow.postMessage)return!1;a=JSON.stringify({method:a,value:c});b.contentWindow.postMessage(a,h)}function l(a){var c,b;try{c=JSON.parse(a.data),b=c.event||c.method}catch(e){}"ready"!=b||k||(k=!0);if(!/^https?:\/\/player.vimeo.com/.test(a.origin))return!1;"*"===h&&(h=a.origin);a=c.value;var m=c.data,f=""===f?null:c.player_id;c=f?d[f][b]:d[b];b=[];if(!c)return!1;void 0!==a&&b.push(a);m&&b.push(m);f&&b.push(f);
return 0<b.length?c.apply(null,b):c.call()}function n(a,c,b){b?(d[b]||(d[b]={}),d[b][a]=c):d[a]=c}var d={},k=!1,h="*";e.fn=e.prototype={element:null,init:function(a){"string"===typeof a&&(a=document.getElementById(a));this.element=a;return this},api:function(a,c){if(!this.element||!a)return!1;var b=this.element,d=""!==b.id?b.id:null,e=c&&c.constructor&&c.call&&c.apply?null:c,f=c&&c.constructor&&c.call&&c.apply?c:null;f&&n(a,f,d);g(a,e,b);return this},addEvent:function(a,c){if(!this.element)return!1;
var b=this.element,d=""!==b.id?b.id:null;n(a,c,d);"ready"!=a?g("addEventListener",a,b):"ready"==a&&k&&c.call(null,d);return this},removeEvent:function(a){if(!this.element)return!1;var c=this.element,b=""!==c.id?c.id:null;a:{if(b&&d[b]){if(!d[b][a]){b=!1;break a}d[b][a]=null}else{if(!d[a]){b=!1;break a}d[a]=null}b=!0}"ready"!=a&&b&&g("removeEventListener",a,c)}};e.fn.init.prototype=e.fn;window.addEventListener?window.addEventListener("message",l,!1):window.attachEvent("onmessage",l);return window.Froogaloop=
window.$f=e}();


(function ($) {
  var VimeoTracker = function(iframe) {
    var globals = this;

    this.iframe = iframe;
    this.id = iframe.attr('title');
    this.player = $f(iframe[0]);

    this.title = "- Private -";
    this.url = "https://vimeo.com/"+this.id;
    this.time = null;

    this.init = function() {
      globals.player.addEvent('ready', function() {
        globals.player.api('getDuration', function (duration) {
          globals.duration = duration;
          // Start checking data.
          globals.tracker = new VideoTracker(duration*1000, {
            getCurrentTime: function(onDone) {
              globals.player.api('getCurrentTime', function (time, id) {
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
          url: 'http://vimeo.com/api/v2/video/' + globals.id + '.json',
          dataType: 'json',
          success: function(data) {
            globals.title = data[0]["title"];
            globals.url = data[0]["url"];
          },
        });
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
        module: 'vimeo',
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

  Drupal.behaviors.tincanapiVimeo = {
    attach: function (context) {

      $('.media-vimeo-video', context).not('.tincan-processed').each(function () {
        var iframe = $(this).find('iframe');
        var id = iframe.attr('title');

        iframe.attr('id', id);
        iframe.attr('src', iframe.attr('src')+"?api=1&player_id="+id);

        new VimeoTracker(iframe);

        $(this).addClass('tincan-processed');
      });
    }
  };

})(jQuery);
