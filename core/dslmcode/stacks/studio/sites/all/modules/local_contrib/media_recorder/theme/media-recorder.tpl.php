<?php

/**
 * @file
 * Video media recorder template.
 *
 * @see template_preprocess()
 * @see template_process()
 */

?>

<div class="media-recorder-wrapper">
  <div class="media-recorder">
    <div class="media-recorder-constraints">
      <button class="media-recorder-enable-audio" title="Click to enable audio recorder.">Audio</button>
      <button class="media-recorder-enable-video" title="Click to enable video recorder.">Video</button>
    </div>
    <div class="media-recorder-preview"></div>
    <div class="media-recorder-status"></div>
    <div class="media-recorder-controls">
      <button class="media-recorder-record" title="Click to start recording.">Record</button>
      <button class="media-recorder-stop" title="Click to stop recording.">Stop</button>
    </div>
  </div>
</div>
