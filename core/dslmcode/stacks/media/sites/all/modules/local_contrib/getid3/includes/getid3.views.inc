<?php
/**
 * @file
 * Provide views data for getid3.module.
 */

/**
 * Implements hook_views_data()
 */
function getid3_views_data() {
  $data['file_managed']['width'] = array(
    'title' => t('Width'),
    'help' => t('Width of a video or image file in pixels.'),
    'field' => array(
      'handler' => 'getid3_metadata_width',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // height
  $data['file_managed']['height'] = array(
    'title' => t('Height'),
    'help' => t('Height of a video or image file in pixels.'),
    'field' => array(
      'handler' => 'getid3_metadata_height',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // duration
  $data['file_managed']['duration'] = array(
    'title' => t('Duration'),
    'help' => t('The duration of audio or video files, in seconds.'),
    'field' => array(
      'handler' => 'getid3_metadata_duration',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // audio_format
  $data['file_managed']['audio_format'] = array(
    'title' => t('Audio format'),
    'help' => t('The audio format.'),
    'field' => array(
      'handler' => 'getid3_metadata_audio_format',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // audio_sample_rate
  $data['file_managed']['audio_sample_rate'] = array(
    'title' => t('Audio sample rate'),
    'help' => t('The sample rate of the audio.'),
    'field' => array(
      'handler' => 'getid3_metadata_audio_sample_rate',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // audio_channel_mode
  $data['file_managed']['audio_channel_mode'] = array(
    'title' => t('Audio channel mode'),
    'help' => t('The number of channels in the audio, by name: stereo or mono.'),
    'field' => array(
      'handler' => 'getid3_metadata_audio_channel_mode',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // audio_bitrate
  $data['file_managed']['audio_bitrate'] = array(
    'title' => t('Audio bitrate'),
    'help' => t('The audio bitrate.'),
    'field' => array(
      'handler' => 'getid3_metadata_audio_bitrate',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // audio_bitrate_mode
  $data['file_managed']['audio_bitrate_mode'] = array(
    'title' => t('Audio bitrate mode'),
    'help' => t('The audio bitrate mode: cbr, vbr, abr.'),
    'field' => array(
      'handler' => 'getid3_metadata_audio_bitrate_mode',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  return $data;
}
