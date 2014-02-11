/********************************************************************
 * Project: Drupal Media Recorder jQuery Plugin
 * Description: Adds a media recorder to the drupal media module
 * Author: Norman Kerr
 * License: GPL 2.0 (http://www.gnu.org/licenses/gpl-2.0.html)
 *******************************************************************/

(function($, window, document, undefined) {
  
  // ********************************************************************
  // * Global variables.
  // ********************************************************************

  // jQuery plugin variables.
  var defaults = {
    'timeLimit': 300000
  };

  // Normalize features.
  navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
  window.AudioContext = window.AudioContext || window.webkitAudioContext || window.mozAudioContext;
  window.URL = window.URL || window.webkitURL;

  // Feature detection.
  var browser = $.browser;
  var getUserMediaCheck = typeof(navigator.getUserMedia) === 'function';
  var webAudioCheck = typeof(window.AudioContext) === 'function';
  var flashVersion = swfobject.getFlashPlayerVersion();
  var canvas = document.createElement('canvas');
  var canvasCheck = !!(canvas.getContext && canvas.getContext('2d'));

  // ********************************************************************
  // * jQuery Plugin Functions.
  // ********************************************************************

  function mediaRecorder(element, options) {
    this.element = element;
    this.options = $.extend({}, defaults, options);
    this.defaults = defaults;

    // Check for existing recorder.
    if (typeof this.element.recorder != 'undefined') {
      return this.element.mediaRecorder;
    }
    // Otherwise attach recorder to DOM node for reference
    else {
      this.element.mediaRecorder = this;
    }

    // Run webRTC recorder.
    if (getUserMediaCheck && webAudioCheck) {
      // Hide specific file related elements.
      $(this.element).parent().children('span.file, span.file-size, input.media-recorder-upload, input.media-recorder-upload-button').hide();
      // Set audio player width to recorder width.
      $(this.element).parent().children('div.file-audio').width(options.width);
      // Load Recorderjs library and initialize recorder.
      $.ajax({
        url: Drupal.settings.basePath + 'sites/all/libraries/Recorderjs/recorder.js',
        async: false,
        dataType: "script",
      });
      this.init();
    }
    // Run flash recorder.
    else if (flashVersion.major >= 10) {
      // Hide all file input related elements.
      $(this.element).parent().children('span.file, span.file-size, input.media-recorder-upload, input.media-recorder-upload-button').hide();
      // Set audio player width to recorder width.
      $(this.element).parent().children('div.file-audio').width(options.width);
      // Load recorder.js library and initialize recorder.
      $.ajax({
        url: Drupal.settings.basePath + 'sites/all/libraries/recorder.js/recorder.js',
        async: false,
        dataType: "script",
      });
      this.flashInit();
    }
    // Display flash warning if not newer version.
    else if (flashVersion.major < 10 && flashVersion.major > 0) {
      $(this.element).prepend($('<div class="messages error"><span class="message-text"><a target="_blank" href="https://get.adobe.com/flashplayer">Flash 10</a> or higher must be installed in order to record.</span></div>'));
    }
    // Show file element.
    else {
      // Hide all media recorder related elements.
      $(this.element).parent().children('.media-recorder-toggle').hide();
      $(this.element).hide();
    }

    return this;
  }

  $.fn.mediaRecorder = function(options) {
    return this.each(function() {
      if (!$.data(this, "plugin_" + mediaRecorder)) {
        $.data(this, "plugin_" + mediaRecorder, new mediaRecorder(this, options));
      }
    });
  };

  // ********************************************************************
  // * Media Recorder Prototype Functions.
  // ********************************************************************

  mediaRecorder.prototype = {

    // ********************************************************************
    // * Initialize Recorder.
    // ********************************************************************
    init: function() {

      // Generate general recorder markup.
      var element = $(this.element);
      var options = this.options;
      element.recorder = $('<div class="media-recorder"></div>').width(options.width).height(options.height);
      element.recorder.controls = $('<div class="controls"></div>');
      element.recorder.canvas = $('<canvas class="media-recorder-analyser"></canvas>');
      element.recorder.status = $('<div class="media-recorder-status">00:00 / ' + millisecondsToTime(options.timeLimit) + '</div>');
      element.recorder.statusInterval = 0;
      element.recorder.meterInterval = 0;
      element.recorder.progressInterval = 0;
      element.recorder.HTML5Recorder = null;
      element.recorder.audioContext = null;

      // Add button handlers.
      element.recorder.controls.record = $('<div class="media-recorder-record record-off" title="Click the mic to record and to stop recording."><span>Record</span></div>')
        .click(function(){
          mediaRecorder.prototype.record(element, options);
        });

      // Set HTML5 variables.
      element.recorder.volume = $('<div class="volume" title="Adjust the mic volume."></div>')
        .slider({
          orientation: "vertical",
          range: "min",
          step: 0.05,
          min: 0,
          max: 1,
          value: 0.8,
          slide: function(event, ui) {
            gainNode.gain.value = ui.value;
          }
        });

      // Add markup.
      element.prepend(element.recorder);
      element.recorder.addClass('HTML5');
      element.recorder.append(element.recorder.controls);
      element.recorder.controls.append(element.recorder.controls.record);
      element.recorder.append(element.recorder.volume);
      element.recorder.append(element.recorder.canvas);
      element.recorder.append(element.recorder.status);

      // Initiate getUserMedia.
      navigator.getUserMedia(
        {audio: true},
        function(stream) {startUserMedia(element, options, stream);},
        function(error) {onError(error);}
      );
    },

    // ********************************************************************
    // * Record Callback.
    // ********************************************************************
    record: function(element, options) {
      element.recorder.HTML5Recorder.record();
      mediaRecorder.prototype.recordStart(element, options);
    },

    // ********************************************************************
    // * Start Recording Callback.
    // ********************************************************************
    recordStart: function(element, options) {
      mediaRecorder.prototype.recordDuring(element, options);
      $(element).find('.media-recorder-analyser').html('');
      $(element).find('.media-recorder-record')
        .removeClass('record-off')
        .addClass('record-on')
        .unbind('click').click(function() {
          mediaRecorder.prototype.stop(element, options);
        });
    },

    // ********************************************************************
    // * During Recording Callback.
    // ********************************************************************
    recordDuring: function(element, options) {
      var currentSeconds = 0;
      element.recorder.statusInterval = window.setInterval(function() {
        // Set time limit and convert to date obj.
        currentSeconds = currentSeconds + 1;
        var currentMilliSeconds = new Date(currentSeconds * 1000);
        // Stop recording if time limit is reached.
        if ((options.timeLimit - currentMilliSeconds) < 0) {
          mediaRecorder.prototype.stop(element, options);
        }
        time = millisecondsToTime(currentMilliSeconds);
        // Refresh time display with current time.
        $(element).find('.media-recorder-status').html(time + ' / 05:00');
      }, 1000);
    },

    // ********************************************************************
    // * Finished Recording Callback.
    // ********************************************************************
    recordFinish: function(element, options) {
      $(element).find('.media-recorder-status').html('00:00 / 05:00');
      $(element).find('.media-recorder-record')
        .removeClass('record-on')
        .addClass('record-off')
        .unbind('click').click(function() {
          mediaRecorder.prototype.record(element, options);
        });
    },

    // ********************************************************************
    // * Stop Recording Callback.
    // ********************************************************************
    stop: function(element, options) {
      clearInterval(element.recorder.statusInterval);
      element.recorder.HTML5Recorder.stop();
      element.recorder.HTML5Recorder.exportWAV(function(blob) {
        $(element).find('.media-recorder-status').html('<div class="progressbar"></div>');
        sendBlob(element, options, blob);
      });
      element.recorder.HTML5Recorder.clear();
      mediaRecorder.prototype.recordFinish(element, options);
    },

    // ********************************************************************
    // * Initialize Flash Recorder.
    // ********************************************************************
    flashInit: function() {

      // Generate general recorder markup.
      var element = $(this.element);
      var options = this.options;
      var wrapperID = $(element).parent().attr('id');

      // Build recorder.
      element.recorder = $('<div class="media-recorder"></div>').width(options.width).height(options.height);
      element.recorder.controls = $('<div class="controls"></div>');
      element.recorder.canvas = $('<div class="media-recorder-analyser"></div>');
      element.recorder.status = $('<div class="media-recorder-status">00:00 / ' + millisecondsToTime(options.timeLimit) + '</div>');
      element.recorder.statusInterval = 0;
      element.recorder.meterInterval = 0;
      element.recorder.progressInterval = 0;

      // Add button handlers.
      element.recorder.controls.record = $('<div class="media-recorder-record record-off" title="Click the mic to record and to stop recording.">Record</div>')
        .click(function(){
          mediaRecorder.prototype.flashRecord(element, options);
        });

      // Add flash recorder markup.
      element.flash = $('<div id="flashRecorder-' + wrapperID + '" class="flashRecorder"></div>');
      element.recorder.micSettings = $('<div class="media-recorder-mic-settings" title="Adjust microphone settings.">Settings</div>')
        .click(function() {
          Recorder.flashInterface().showFlash();
        });

      // Add markup.
      element.append(element.flash);
      element.prepend(element.recorder);
      element.recorder.addClass('flash');
      element.recorder.append(element.recorder.controls);
      element.recorder.controls.append(element.recorder.controls.record);
      element.recorder.append(element.recorder.canvas);
      element.recorder.append(element.recorder.micSettings);
      element.recorder.append(element.recorder.status);

      // Initialize flash recorder.
      Recorder.initialize({
        swfSrc: Drupal.settings.basePath + 'sites/all/libraries/recorder.js/recorder.swf',
        flashContainer: document.getElementById('flashRecorder-' + wrapperID),
      });
    },

    // ********************************************************************
    // * Flash Record Callback.
    // ********************************************************************
    flashRecord: function(element, options) {
      Recorder.record({
        start: mediaRecorder.prototype.flashRecordStart(element, options),
        progress: mediaRecorder.prototype.flashRecordDuring(element, options),
      });
    },

    // ********************************************************************
    // * Flash Start Recording Callback.
    // ********************************************************************
    flashRecordStart: function(element, options) {
      $(element).find('.media-recorder-record').removeClass('record-off').addClass('record-on')
      .unbind('click').click(function() {
        mediaRecorder.prototype.flashStop(element, options);
      });
      $(element).find('.media-recorder-analyser').html('<p style="height: ' + options.height / 2 + 'px; line-height: ' + options.height / 2 + 'px">Recording<span>.</span><span>.</span><span>.</span></p>');
    },

    // ********************************************************************
    // * Flash During Recording Callback.
    // ********************************************************************
    flashRecordDuring: function(element, options) {
      // Update status interval.
      var currentSeconds = 0;
      element.recorder.statusInterval = window.setInterval(function() {
        // Set time limit and convert to date obj.
        currentSeconds = currentSeconds + 1;
        var currentMilliSeconds = new Date(currentSeconds * 1000);
        // Stop recording if time limit is reached.
        if ((options.timeLimit - currentMilliSeconds) < 0) {
          mediaRecorder.prototype.flashStop(element, options);
        }
        time = millisecondsToTime(currentMilliSeconds);
        // Refresh time display with current time.
        $(element).find('.media-recorder-status').html(time + ' / 05:00');
      }, 1000);
    },

    // ********************************************************************
    // * Flash Finished Recording Callback.
    // ********************************************************************
    flashRecordFinish: function(element, options, file) {
      // Clear all progress intervals.
      clearInterval(element.recorder.progressInterval);
      // Set audio and file input values.
      $(element).parent().children('input.media-recorder-fid').val(file.fid);
      $(element).parent().children('input.media-recorder-refresh').trigger('mousedown');
    },

    // ********************************************************************
    // * Flash Stop Recording Callback.
    // ********************************************************************
    flashStop: function(element, options) {
      clearInterval(element.recorder.statusInterval);
      Recorder.stop();
      Recorder.upload({
        url: options.recordingPath + '/' + options.fileName,
        audioParam: 'mediaRecorder',
        success: function(response) {
          var file = JSON.parse(response);
          mediaRecorder.prototype.flashRecordFinish(element, options, file);
        },
      });
      var progressCount = 0;
      var progressIndicator = '';
      element.recorder.progressInterval = setInterval(function() {
        progressCount = progressCount + 1;
        progressIndicator = progressIndicator + '.';
        $(element).find('.media-recorder-status').html('Uploading' + progressIndicator);
        if (progressCount === 3) { progressCount = 0; progressIndicator = ''; }
      }, 500);
    }
  };

  // ********************************************************************
  // * Private Functions.
  // ********************************************************************

  // ********************************************************************
  // * Start getUserMedia Audio Stream.
  // ********************************************************************
  function startUserMedia(element, options, stream) {
    if (webAudioCheck) {

      // Audio analyzer variables.
      var analyserNode = null;
      var analyserContext = null;
      var canvas = $("canvas.media-recorder-analyser");
      var canvasWidth = canvas[0].width;
      var canvasHeight = canvas[0].height;

      // Create an audio context.
      element.recorder.audioContext = new AudioContext();

      // Create a source node.
      mediaStreamSourceNode = element.recorder.audioContext.createMediaStreamSource(stream);

      // Create a default gain node.
      gainNode = element.recorder.audioContext.createGain();
      gainNode.gain.value = 0.8;

      // Send media stream through gain node.
      mediaStreamSourceNode.connect(gainNode);

      // Create analyser node.
      analyserNode = element.recorder.audioContext.createAnalyser();
      analyserNode.fftSize = 2048;

      // Send gain node data to analyser node.
      gainNode.connect(analyserNode);

      // Create a recorder using the gain node.
      element.recorder.HTML5Recorder = new Recorder(gainNode, {workerPath:Drupal.settings.basePath + 'sites/all/libraries/Recorderjs/recorderWorker.js'});

      // Create a muted gain node.
      zeroGainNode = element.recorder.audioContext.createGain();
      zeroGainNode.gain.value = 0.0;

      // Send gain node data through zero gain node.
      gainNode.connect(zeroGainNode);

      // Send zero gain data to audio context destination.
      zeroGainNode.connect(element.recorder.audioContext.destination);

      // Update audio canvas.
      updateAudioCanvas(element, options);
    }

    // ********************************************************************
    // * Update Audio Canvas.
    // ********************************************************************
    function updateAudioCanvas() {
      if (!analyserContext) {
        analyserContext = canvas[0].getContext('2d');
      }
      var spacing = 1;
      var barWidth = 1;
      var numBars = Math.round(canvasWidth / spacing);
      var freqByteData = new Uint8Array(analyserNode.frequencyBinCount);
      analyserNode.getByteFrequencyData(freqByteData);
      analyserContext.clearRect(0, 0, canvasWidth, canvasHeight);
      analyserContext.fillStyle = '#F6D565';
      analyserContext.lineCap = 'round';
      var multiplier = analyserNode.frequencyBinCount / numBars;
      // Draw rectangle for each frequency bin.
      for (var i = 0; i < numBars; ++i) {
        var magnitude = 0;
        var offset = Math.floor(i * multiplier);
        for (var j = 0; j < multiplier; j++) {
          magnitude += freqByteData[offset + j];
        }
        magnitude = magnitude / multiplier;
        var magnitude2 = freqByteData[i * multiplier];
        analyserContext.fillStyle = "hsl( " + Math.round((i * 360) / numBars) + ", 100%, 50%)";
        analyserContext.fillRect(i * spacing, canvasHeight, barWidth, -magnitude);
      }
      rafID = window.requestAnimationFrame(updateAudioCanvas);
    }
  }

  // ********************************************************************
  // * Send Blob for getUserMedia recordings.
  // ********************************************************************
  function sendBlob(element, options, blob) {
    var formData = new FormData();
    var fileObj = {};
    formData.append("mediaRecorder", blob);
    var req = new XMLHttpRequest();
    req.upload.onprogress = updateProgress;
    req.addEventListener("progress", updateProgress, false);
    req.addEventListener("load", transferComplete, false);
    req.addEventListener("error", transferFailed, false);
    req.addEventListener("abort", transferCanceled, false);
    req.open("POST", options.recordingPath + '/' + options.fileName, true);
    req.send(formData);

    function updateProgress(evt) {
      if (evt.lengthComputable) {
        var percentComplete = (evt.loaded / evt.total) * 100;
        $(element).find('.progressbar').progressbar({
          value: percentComplete
        });
      }
      else {
        $(element).find('.progressbar').progressbar({
          value: 100
        });
      }
    }

    function transferComplete(evt) {
      var file = JSON.parse(req.response);
      $(element).parent().children('input.media-recorder-fid').val(file.fid);
      $(element).parent().children('input.media-recorder-refresh').trigger('mousedown');
    }

    function transferFailed(evt) {
      onError("An error occurred while transferring the file.");
    }

    function transferCanceled(evt) {
      onError("The transfer has been canceled by the user.");
    }
  }

  // ********************************************************************
  // * Convert milliseconds to time.
  // ********************************************************************
  function millisecondsToTime(milliSeconds) {
    // Format Current Time
    var milliSecondsDate = new Date(milliSeconds);
    var mm = milliSecondsDate.getMinutes();
    var ss = milliSecondsDate.getSeconds();
    if (mm < 10) {
      mm = "0" + mm;
    }
    if (ss < 10) {
      ss = "0" + ss;
    }
    return mm + ':' + ss;
  }

  // ********************************************************************
  // * Error Handler.
  // ********************************************************************
  function onError(msg) {
    alert(msg);
  }

})(jQuery, window, document);
