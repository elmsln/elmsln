(function (window) {

  // Known issues:
  // - When CPU is to busy, the getDuration of youtube/vimeo can lag or just don't send data. Because the library can't track the data, it will issue a skip event (instead of a watched event)
  // - When the video starts, the initial play event will not have startpoint 0, but startpoint 0.4s or something. Because it can take an interval before we notice the start.
  // - Same with play after pauze. There will mostly be a gap between the pauze time and the play time. Just because it takes time for the interval to notice the change. Everything is done within 400-800ms.
  // - Private vimeo videos will not have a title.

  window.VideoTracker = function (totalDuration, options) {

    var globals = this;

    // Settings
    this.intervalTime = 300;
    this.variance = 0.25; // How much the movie time and clock time may differ, before the knowledge can be used as pauze/skip information.
    this.sampleLimit = 5; // Because the getCurrentTime API from Youtube can shift under time, we take three samples (of setInterval), to check if the video clock time doesn't catch up, just because it was under load.

    // Internal data
    this.hooks = {};

    this.options = options;
    this.totalDuration = totalDuration;
    this.oldTime = 0;
    this.oldPerf = 0;
    this.samples = 0;

    this.state = "paused";

    this.init = function() {
      globals.interval = setInterval(function() {
        globals.options.getCurrentTime(function(time) {
          globals.checkup(time);
        });
      }, globals.intervalTime);
    };

    this.callEvent = function (name) {
      if (globals.options.events["all"] !== undefined) {
        globals.options.events["all"].apply(undefined, arguments);
      }

      if (globals.options.events[name] !== undefined) {
        globals.options.events[name].apply(undefined, Array.prototype.slice.call(arguments, 1));
      }
    };

    this.checkup = function (time) {
      // Calculate difference of video time.
      //var time = Math.round(globals.player.getCurrentTime() * 1000);
      var diff = time - globals.oldTime;

      // Calculate difference of clock time.
      var perf = window.performance.now();
      var perfDiff = (perf - globals.oldPerf);

      // Check if the clock time and video time are reasonable going the same rate (with a partical variance)
      var inSync = !(diff < perfDiff*(1.0-globals.variance) || diff > perfDiff*(1.0+globals.variance));


      // If clock time and video time aren't going in sync, just check the next sample.
      // Maybe the getCurrentTime from Youtube is just slow and shifted over time.
      // So take some samples together and check if the video time catch up.
      if(!inSync && globals.samples+1 < globals.sampleLimit) {
        globals.samples++;
        return;
      }

      // Normalize the diff
      if(inSync) {
        // Difference is going with the time.
        diff = perfDiff;
        //time = globals.oldTime;
      }
      else if(diff < perfDiff && diff > -perfDiff*(1.0-globals.variance)) {
        // The video is going way to slow, so is stopped (minus a variance).
        diff = 0;
      }
      else {
        // Difference is like it should.
      }

      // Check state and possibly adapt state.
      if(globals.state == "complete") {
        if(diff === 0) {
          // still complete
        }
        else {
          globals.callEvent('onPaused', null, globals.oldTime/1000);
          globals.state = "paused";
        }
      }
      else if(globals.state == "paused") {
        if(diff === 0) {
          // paused
        }
        else if(diff == perfDiff) {
          globals.callEvent('onPlay', globals.oldTime/1000);
          globals.state = "play";
        }
        else {
          globals.callEvent('onSkipped', globals.oldTime/1000, time/1000);
          globals.callEvent('onPaused', null, time/1000);
        }
      }
      else if(globals.state == "play") {
        if(diff === 0) {
          if(time >= globals.totalDuration-1000) {
            globals.callEvent('onPaused', null, time/1000);
            globals.callEvent('onComplete', null, time/1000);
            globals.state = "complete";
          }
          else {
            globals.callEvent('onPaused', null, time/1000);
            globals.state = "paused";
          }
        }
        else if(diff == perfDiff) {
          // stil playing
        }
        else {
          globals.callEvent('onPaused', null, globals.oldTime/1000);
          globals.callEvent('onSkipped', globals.oldTime/1000, time/100);
          globals.callEvent('onPaused', null, time/1000);
          globals.callEvent('onPlay', time/1000);
        }
      }

      globals.oldTime = time;
      globals.oldPerf = perf;
      globals.samples = 0;
    };

    this.init();

    return this;
  };

  window.performance = window.performance || {};
  performance.now = (function() {
    return performance.now       ||
          performance.mozNow    ||
          performance.msNow     ||
          performance.oNow      ||
          performance.webkitNow ||
          Date.now
    })();

})(window);
