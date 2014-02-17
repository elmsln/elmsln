<?php
/**
 * @file
 * cle_submission.default_video_embed_styles.inc
 */

/**
 * Implements hook_default_video_embed_styles().
 */
function cle_submission_default_video_embed_styles() {
  $export = array();

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'cle_default';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '711',
      'height' => '400',
      'theme' => 'light',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 1,
      'modestbranding' => 0,
      'iv_load_policy' => '3',
      'autohide' => '2',
    ),
    'vimeo' => array(
      'width' => '711',
      'height' => '400',
      'color' => 'ff9933',
      'portrait' => 0,
      'title' => 1,
      'byline' => 1,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-vimeo',
  );
  $export['cle_default'] = $video_embed_style;

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'cle_overview';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '266',
      'height' => '150',
      'theme' => 'light',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 1,
      'modestbranding' => 0,
      'iv_load_policy' => '3',
      'autohide' => '2',
    ),
    'vimeo' => array(
      'width' => '266',
      'height' => '150',
      'color' => 'ff9933',
      'portrait' => 0,
      'title' => 1,
      'byline' => 1,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-vimeo',
  );
  $export['cle_overview'] = $video_embed_style;

  return $export;
}
