<?php

/**
 * @file
 * Theme functions for Able Player.
 */

/**
 * Implements hook_preprocess_THEME().
 */
function ableplayer_preprocess_ableplayer(&$variables) {
  $variables['options']['transcript_title'] = check_plain(filter_xss($variables['options']['transcript_title']));
  $variables['fallback_path'] = url(libraries_get_path('jwplayer') . '/', array('absolute' => TRUE));
  $variables['test_fallback'] = variable_get('ableplayer_test_fallback', 0);
  $variables['translation_path'] = url(libraries_get_path('ableplayer') . '/translations/', array('absolute' => TRUE));
  $variables['id'] = drupal_html_id($variables['id']);
}

/**
 * Theme function for Able Player.
 */
function theme_ableplayer($variables) {
  if (strpos($variables['mimetype'], ABLEPLAYER_BUNDLE_VIDEO) > -1) {
    $open_tag = '<video ';
    $close_tag = '</video>';
  }
  elseif (strpos($variables['mimetype'], ABLEPLAYER_BUNDLE_AUDIO) > -1) {
    $open_tag = '<audio ';
    $close_tag = '</audio>';
  }
  else {
    return '';
  }

  $output = $open_tag;
  $output .= 'id="ableplayer-' . $variables['id'] . '" ';
  $output .= 'width="' . $variables['options']['width'] . '" ';
  $output .= 'height="' . $variables['options']['height'] . '" ';

  if ($variables['options']['autoplay']) {
    $output .= 'autoplay ';
  }

  if ($variables['options']['show_now_playing']) {
    $output .= 'data-show-now-playing ';
  }

  if ($variables['options']['use_transcript_button']) {
    $output .= 'data-use-transcript-button="false" ';
  }

  if ($variables['options']['lyrics_mode']) {
    $output .= 'data-lyrics-mode ';
  }

  $output .= 'data-volume="' . $variables['options']['volume'] . '" ';

  if ($variables['options']['preload']) {
    $output .= 'preload="' . $variables['options']['preload'] . '" ';
  }

  if ($variables['options']['start_time']) {
    $output .= 'data-start-time="' . $variables['options']['start_time'] . '" ';
  }

  if ($variables['options']['seek_interval']) {
    $output .= 'data-seek-interval="' . $variables['options']['seek_interval'] . '" ';
  }

  if ($variables['options']['transcript_title']) {
    $output .= 'data-transcript-title="' . $variables['options']['transcript_title'] . '" ';
  }

  if ($variables['options']['lang']) {
    $output .= 'data-lang="' . $variables['options']['lang'] . '" ';
  }

  if ($variables['options']['force_lang']) {
    $output .= 'data-force-lang ';
  }

  if (isset($variables['youtube_id'])) {
    $output .= 'data-youtube-id="' . $variables['youtube_id'] . '" ';
  }

  if ($variables['test_fallback']) {
    $output .= 'data-test-fallback ';
  }

  $output .= 'data-fallback-path="' . $variables['fallback_path'] . '" ';
  $output .= 'data-translation-path="' . $variables['translation_path'] . '" ';
  $output .= 'data-debug ';
  $output .= 'data-able-player>';
  $output .= "\n";

  if (empty($variables['youtube_id'])) {
    $output .= '<source type="' . $variables['mimetype'] . '" src="' . $variables['uri'] . '" />';
    $output .= "\n";

    foreach ($variables['tracks']['transcripts'] as $transcript) {
      $output .= '<track kind="captions" src="' . $transcript['uri'];
      $output .= '" srclang="' . $transcript['code'];
      $output .= '" label="' . $transcript['label'] . '" />';
      $output .= "\n";
    }

    foreach ($variables['tracks']['descriptions'] as $description) {
      $output .= '<track kind="descriptions" src="' . $description['uri'];
      $output .= '" srclang="' . $description['code'];
      $output .= '" label="' . $description['label'] . '" />';
      $output .= "\n";
    }

    foreach ($variables['tracks']['chapters'] as $chapter) {
      $output .= '<track kind="chapters" src="' . $chapter['uri'];
      $output .= '" srclang="' . $chapter['code'];
      $output .= '" label="' . $chapter['label'] . '" />';
      $output .= "\n";
    }
  }

  $output .= $close_tag;
  $output .= "\n";

  return $output;
}
