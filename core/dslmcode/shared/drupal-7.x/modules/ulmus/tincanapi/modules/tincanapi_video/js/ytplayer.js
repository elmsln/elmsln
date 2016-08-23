(function (window) {

  window.YTPlayer = function (id, options) {

    var globals = this;

    this.id = id;
    this.video_id = null;
    this.options = options;
    this.player = null;
    this.hooks = {};

    this.intervalTime = 400;
    this.diff = 0;
    this.totalDuration = 0;
    this.oldTime = 0;

    this.state = "paused";

    this.setupPlayer = function () {
      globals.player = new YT.Player(id, globals.hookEvents(options));
    };

    this.callHook = function (name) {
      if (globals.hooks[name] !== undefined) {
        globals.hooks[name].apply(undefined, Array.prototype.slice.call(arguments, 1));
      }
    };

    this.hookEvents = function (options) {
      var events = options.events;

      globals.hooks.onReady = events.onReady;
      events.onReady = function (ev) {

        globals.video_id = ev.target.getVideoData().video_id;
        globals.interval = setInterval(globals.checkup, globals.intervalTime);
        globals.totalDuration = Math.floor(globals.player.getDuration());
        globals.callHook('onReady', ev);

      };

      return options;
    };

    this.callEvent = function (name) {
      if (globals.options.events[name] !== undefined) {
        globals.options.events[name].apply(undefined, Array.prototype.slice.call(arguments, 1));
      }
    };

    this.checkup = function () {
      var time = Math.round(globals.player.getCurrentTime() * 100) / 100,
        diff = time - globals.diff;

      if(globals.state == "complete") {
        if(diff == 0) {
          // still complete
        }
        else {
          globals.callEvent('onPaused', globals.video_id, time);
          globals.state = "paused";
        }
      }
      else if(globals.state == "paused") {
        if(diff == 0) {
          // paused
        }
        else if(diff && Math.floor(diff) == 0) {
          globals.callEvent('onPlay', globals.video_id, time);
          globals.state = "play";
        } 
        else {
          globals.callEvent('onSkipped', globals.video_id, globals.oldTime, time);
          globals.callEvent('onPaused', globals.video_id, time);
        }
      }
      else if(globals.state == "play") {
        if(diff == 0) {
          if(time == globals.totalDuration) {
            globals.callEvent('onPaused', globals.video_id, time);
            globals.callEvent('onComplete', globals.video_id, time);
            globals.state = "complete";
          }
          else {
            globals.callEvent('onPaused', globals.video_id, time);
            globals.state = "paused";
          }
        }
        else if(diff && Math.floor(diff) == 0) {
          // stil playing
        }
        else {
          globals.callEvent('onPaused', globals.video_id, globals.oldTime);
          globals.callEvent('onSkipped', globals.video_id, globals.oldTime, time);
          globals.callEvent('onPaused', globals.video_id, time);
          globals.callEvent('onPlay', globals.video_id, time);
        }
      }

      globals.diff = time;
      globals.oldTime = time;
    };

    this.setupPlayer();

    return globals.player;

  };

})(window);