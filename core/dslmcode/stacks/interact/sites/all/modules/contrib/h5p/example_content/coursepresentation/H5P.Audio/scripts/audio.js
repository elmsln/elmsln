var H5P = H5P || {};

if (H5P.getPath === undefined) {
  /**
   * Find the path to the content files based on the id of the content
   *
   * Also identifies and returns absolute paths
   *
   * @param {String} path Absolute path to a file, or relative path to a file in the content folder
   * @param {Number} contentId Identifier of the content requesting the path
   * @returns {String} The path to use.
   */
  H5P.getPath = function (path, contentId) {
    if (path.substr(0, 7) === 'http://' || path.substr(0, 8) === 'https://') {
      return path;
    }

    return H5PIntegration.getContentPath(contentId) + path;
  };
}

/**
 * Constructor.
 *
 * @param {Object} params Options for this library.
 * @param {Number} id Content identifier
 * @returns {undefined}
 */
H5P.Audio = function (params, id) {
  this.params = params;
  this.contentId = id;
};

/**
 * Wipe out the content of the wrapper and put our HTML in it.
 *
 * @param {jQuery} $wrapper Our poor container.
 */
H5P.Audio.prototype.attach = function ($wrapper) {
  // Check if browser supports audio.
  var audio = document.createElement('audio');
  if (audio.canPlayType === undefined) {
    // Try flash
    this.attachFlash($wrapper);
    return;
  }

  // Add supported source files.
  if (this.params.files !== undefined && this.params.files instanceof Object) {
    for (var i = 0; i < this.params.files.length; i++) {
      var file = this.params.files[i];

      if (audio.canPlayType(file.mime)) {
        var source = document.createElement('source');
        source.src = H5P.getPath(file.path, this.contentId);
        source.type = file.mime;
        audio.appendChild(source);
      }
    }
  }

  if (!audio.children.length) {
    // Try flash
    this.attachFlash($wrapper);
    return;
  }

  if (this.endedCallback !== undefined) {
    audio.addEventListener('ended', this.endedCallback, false);
  }

  audio.className = 'h5p-audio';
  audio.controls = this.params.controls === undefined ? true : this.params.controls;
  audio.autoplay = this.params.autoplay === undefined ? false : this.params.autoplay;
  audio.preload = 'auto';

  if (this.params.fitToWrapper === undefined || this.params.fitToWrapper) {
    audio.style.width = '100%';
    audio.style.height = '100%';
  }

  $wrapper.html(audio);
  this.audio = audio;
};

/**
 * Attaches a flash audio player to the wrapper.
 *
 * @param {jQuery} $wrapper Our dear container.
 */
H5P.Audio.prototype.attachFlash = function ($wrapper) {
  if (this.params.files !== undefined && this.params.files instanceof Object) {
    for (var i = 0; i < this.params.files.length; i++) {
      var file = this.params.files[i];
      if (file.mime === 'audio/mpeg' || file.mime === 'audio/mp3') {
        var audioSource = H5P.getPath(file.path, this.contentId);
        break;
      }
    }
  }

  if (audioSource === undefined) {
    $wrapper.text('No supported audio files found.');
    if (this.endedCallback !== undefined) {
      this.endedCallback();
    }
    return;
  }

  var options = {
    buffering: true,
    clip: {
      url: window.location.protocol + '//' + window.location.host + audioSource,
      autoPlay: this.params.autoplay === undefined ? false : this.params.autoplay,
      scaling: 'fit'
    },
    plugins: {
      controls: null
    }
  };

  if (this.params.controls === undefined || this.params.controls) {
    options.plugins.controls = {
      fullscreen: false,
      autoHide: false
    };
  }

  if (this.endedCallback !== undefined) {
    options.clip.onFinish = this.endedCallback;
    options.clip.onError = this.endedCallback;
  }

  this.flowplayer = flowplayer($wrapper[0], {
    src: "http://releases.flowplayer.org/swf/flowplayer-3.2.16.swf",
    wmode: "opaque"
  }, options);
};

/**
 * Stop the audio. TODO: Rename to pause?
 *
 * @returns {undefined}
 */
H5P.Audio.prototype.stop = function () {
  if (this.flowplayer !== undefined) {
    this.flowplayer.stop().close().unload();
  }
  if (this.audio !== undefined) {
    this.audio.pause();
  }
};

H5P.Audio.prototype.play = function () {
  if (this.flowplayer !== undefined) {
    this.flowplayer.play();
  }
  if (this.audio !== undefined) {
    this.audio.currentTime = 0;
    this.audio.play();
  }
}