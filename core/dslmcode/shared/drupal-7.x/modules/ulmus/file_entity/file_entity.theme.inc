<?php

/**
 * @file
 * Theme callbacks for the file entity module.
 */

/**
 * Copy of theme_file_link() for linking to the view file page.
 *
 * @see theme_file_link()
 */
function theme_file_entity_file_link($variables) {
  $file = $variables['file'];
  $uri = entity_uri('file', $file);

  // Human-readable names, for use as text-alternatives to icons.
  $mime_name = array(
    'application/msword' => t('Microsoft Office document icon'),
    'application/vnd.ms-excel' => t('Office spreadsheet icon'),
    'application/vnd.ms-powerpoint' => t('Office presentation icon'),
    'application/pdf' => t('PDF icon'),
    'video/quicktime' => t('Movie icon'),
    'audio/mpeg' => t('Audio icon'),
    'audio/wav' => t('Audio icon'),
    'image/jpeg' => t('Image icon'),
    'image/png' => t('Image icon'),
    'image/gif' => t('Image icon'),
    'application/zip' => t('Package icon'),
    'text/html' => t('HTML icon'),
    'text/plain' => t('Plain text icon'),
    'application/octet-stream' => t('Binary Data'),
  );

  $mimetype = file_get_mimetype($file->uri);

  $icon = theme('file_icon', array(
    'file' => $file,
    'icon_directory' => $variables['icon_directory'],
    'alt' => !empty($mime_name[$mimetype]) ? $mime_name[$mimetype] : t('File'),
  ));

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $uri['options']['attributes']['type'] = $file->filemime . '; length=' . $file->filesize;

  // Use the description as the link text if available.
  if (empty($file->description)) {
    $link_text = $file->filename;
  }
  else {
    $link_text = $file->description;
    $options['attributes']['title'] = check_plain($file->filename);
  }

  $output = '<span class="file">' . $icon . ' ' . l($link_text, $uri['path'], $uri['options']);
  $output .= ' ' . '<span class="file-size">(' . format_size($file->filesize) . ')</span>';
  $output .= '</span>';
  return $output;
}

/**
 * Copy of theme_file_link() for linking to the file download URL.
 *
 * @see theme_file_link()
 */
function theme_file_entity_download_link($variables) {
  $file = $variables['file'];
  $uri = file_entity_download_uri($file);

  // Human-readable names, for use as text-alternatives to icons.
  $mime_name = array(
    'application/msword' => t('Microsoft Office document icon'),
    'application/vnd.ms-excel' => t('Office spreadsheet icon'),
    'application/vnd.ms-powerpoint' => t('Office presentation icon'),
    'application/pdf' => t('PDF icon'),
    'video/quicktime' => t('Movie icon'),
    'audio/mpeg' => t('Audio icon'),
    'audio/wav' => t('Audio icon'),
    'image/jpeg' => t('Image icon'),
    'image/png' => t('Image icon'),
    'image/gif' => t('Image icon'),
    'application/zip' => t('Package icon'),
    'text/html' => t('HTML icon'),
    'text/plain' => t('Plain text icon'),
    'application/octet-stream' => t('Binary Data'),
  );

  $mimetype = file_get_mimetype($file->uri);

  $icon = theme('file_icon', array(
    'file' => $file,
    'icon_directory' => $variables['icon_directory'],
    'alt' => !empty($mime_name[$mimetype]) ? $mime_name[$mimetype] : t('File'),
  ));

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $uri['options']['attributes']['type'] = $file->filemime . '; length=' . $file->filesize;

  // Provide the default link text.
  if (!isset($variables['text'])) {
    $variables['text'] = t('Download [file:name]');
  }

  // Perform unsanitized token replacement if $uri['options']['html'] is empty
  // since then l() will escape the link text.
  $variables['text'] = token_replace($variables['text'], array('file' => $file), array('clear' => TRUE, 'sanitize' => !empty($uri['options']['html'])));

  $output = '<span class="file">' . $icon . ' ' . l($variables['text'], $uri['path'], $uri['options']);
  $output .= ' ' . '<span class="file-size">(' . format_size($file->filesize) . ')</span>';
  $output .= '</span>';

  return $output;
}

/**
 * Returns HTML for displaying an HTML5 <audio> tag.
 *
 * @param array $variables
 *   An associative array containing:
 *   - file: Associative array of file data, which must include "uri".
 *   - controls: Boolean indicating whether or not controls should be displayed.
 *   - autoplay: Boolean indicating whether or not the audio should start
 *     playing automatically.
 *   - loop: Boolean indicating whether or not the audio should loop.
 *
 * @ingroup themeable
 */
function theme_file_entity_file_audio($variables) {
  $files = $variables['files'];
  $output = '';

  $audio_attributes = array();
  if ($variables['controls']) {
    $audio_attributes['controls'] = 'controls';

    if (!empty($variables['controls_list'])) {
      $controls_list = array();
      foreach ($variables['controls_list'] as $key => $value) {
        if (!$value) {
          switch ($key) {
            case 'download':
              $controls_list[] = 'nodownload';
              break;
            case 'remote_playback':
              $controls_list[] = 'noremoteplayback';
              break;
          }
        }
      }
      $audio_attributes['controlsList'] = implode(' ', $controls_list);
    }
  }
  if ($variables['autoplay']) {
    $audio_attributes['autoplay'] = 'autoplay';
  }
  if ($variables['loop']) {
    $audio_attributes['loop'] = 'loop';
  }
  if (!empty($variables['preload'])) {
    $audio_attributes['preload'] = $variables['preload'];
  }

  $output .= '<audio' . drupal_attributes($audio_attributes) . '>';
  foreach ($files as $delta => $file) {
    $source_attributes = array(
      'src' => file_create_url($file['uri']),
      'type' => $file['filemime'],
    );
    $output .= '<source' . drupal_attributes($source_attributes) . ' />';
  }
  $output .= '</audio>';
  return $output;
}

/**
 * Returns HTML for displaying an HTML5 <video> tag.
 *
 * @param array $variables
 *   An associative array containing:
 *   - file: Associative array of file data, which must include "uri".
 *   - controls: Boolean indicating whether or not controls should be displayed.
 *   - autoplay: Boolean indicating whether or not the video should start
 *     playing automatically.
 *   - loop: Boolean indicating whether or not the video should loop.
 *   - muted: Boolean indicating whether or not the sound should be muted.
 *   - width: Width, in pixels, of the video player.
 *   - height: Height, in pixels, of the video player.
 *   - playsinline: Boolean indicating if video should automatically play on
 *     mobile (iOS).
 *
 * @ingroup themeable
 */
function theme_file_entity_file_video($variables) {
  $files = $variables['files'];
  $output = '';

  $video_attributes = array();
  if ($variables['controls']) {
    $video_attributes['controls'] = 'controls';

    if (!empty($variables['controls_list'])) {
      $controls_list = array();
      foreach ($variables['controls_list'] as $key => $value) {
        if (!$value) {
          switch ($key) {
            case 'fullscreen':
              $controls_list[] = 'nofullscreen';
              break;
            case 'download':
              $controls_list[] = 'nodownload';
              break;
            case 'remote_playback':
              $controls_list[] = 'noremoteplayback';
              break;
          }
        }
      }
      $video_attributes['controlsList'] = implode(' ', $controls_list);
    }
  }
  if ($variables['autoplay']) {
    $video_attributes['autoplay'] = 'autoplay';
  }
  if ($variables['loop']) {
    $video_attributes['loop'] = 'loop';
  }
  if ($variables['muted']) {
    $video_attributes['muted'] = 'muted';
  }
  if ($variables['width']) {
    $video_attributes['width'] = $variables['width'];
  }
  if ($variables['height']) {
    $video_attributes['height'] = $variables['height'];
  }
  if (!empty($variables['preload'])) {
    $video_attributes['preload'] = $variables['preload'];
  }
  if ($variables['playsinline']) {
    $video_attributes['playsinline'] = 'playsinline';
  }

  $output .= '<video' . drupal_attributes($video_attributes) . '>';
  foreach ($files as $delta => $file) {
    $source_attributes = array(
      'src' => file_create_url($file['uri']),
      'type' => $file['filemime'],
    );
    $output .= '<source' . drupal_attributes($source_attributes) . ' />';
  }
  $output .= '</video>';
  return $output;
}
