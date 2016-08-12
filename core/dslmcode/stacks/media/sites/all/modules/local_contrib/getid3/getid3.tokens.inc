<?php
/**
 * @file
 * Builds placeholder replacement tokens for files.
 */

/**
 * Implements hook_token_info().
 */
function getid3_token_info() {
  $file = array(
    'width' => array(
      'name' => t("Width"),
      'description' => t("Width of a video or image file in pixels."),
    ),
    'height' => array(
      'name' => t("Height"),
      'description' => t("Height of a video or image file in pixels."),
    ),
    'duration' => array(
      'name' => t("Duration"),
      'description' => t("The duration of audio or video files, in seconds."),
    ),
    'audio-format' => array(
      'name' => t("Audio format"),
      'description' => t("The audio format."),
    ),
    'audio-sample-rate' => array(
      'name' => t("Audio sample rate"),
      'description' => t("The sample rate of the audio. TODO: ??? format?"),
    ),
    'audio-channel-mode' => array(
      'name' => t("Audio channel mode"),
      'description' => t("The number of channels in the audio, by name: stereo or mono."),
    ),
    'audio-bitrate' => array(
      'name' => t("Audio bitrate"),
      'description' => t("The audio bitrate."),
    ),
    'audio-bitrate-mode' => array(
      'name' => t("Audio bitrate mode"),
      'description' => t("The audio bitrate mode: cbr, vbr, abr."),
    ),
  );

  // TODO: ID3 tags

  return array(
    'tokens' => array('file' => $file),
  );
}

/**
 * Implements hook_tokens().
 */
function getid3_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $language_code = isset($options['language']) ? $options['language']->language : NULL;
  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'file' && !empty($data['file'])) {
    $file = $data['file'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'width':
          $replacements[$original] = (int) $file->metadata['width'];
          break;

        case 'height':
          $replacements[$original] = (int) $file->metadata['height'];
          break;

        case 'duration':
          $replacements[$original] = theme('getid3_duration', array('duration' => $file->metadata['duration']));
          break;

        case 'audio-format';
          $replacements[$original] = $sanitize ? check_plain($file->metadata['audio_format']) : $file->metadata['audio_format'];
          break;

        case 'audio-sample-rate':
          $replacements[$original] = theme('getid3_sample_rate', array('sample_rate' => $file->metadata['audio_sample_rate']));
          break;

        case 'audio-channel-mode':
          $replacements[$original] = $sanitize ? check_plain($file->metadata['audio_channel_mode']) : $file->metadata['audio_channel_mode'];
          break;

        case 'audio-bitrate':
          $replacements[$original] = theme('getid3_bitrate', array('bitrate' => $file->metadata['audio_bitrate']));
          break;

        case 'audio-bitrate-mode':
          $replacements[$original] = $sanitize ? check_plain($file->metadata['audio_bitrate_mode']) : $file->metadata['audio_bitrate_mode'];
          break;
      }
    }
  }

  // TODO: ID3 tags

  return $replacements;
}
