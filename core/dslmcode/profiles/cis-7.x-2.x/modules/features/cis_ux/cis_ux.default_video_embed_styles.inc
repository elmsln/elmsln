<?php
/**
 * @file
 * cis_ux.default_video_embed_styles.inc
 */

/**
 * Implements hook_default_video_embed_styles().
 */
function cis_ux_default_video_embed_styles() {
  $export = array();

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'cis_course_video';
  $video_embed_style->title = '';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '640px',
      'height' => '360px',
      'theme' => 'dark',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 0,
      'modestbranding' => 1,
      'iv_load_policy' => '3',
      'autohide' => '1',
    ),
    'vimeo' => array(
      'width' => '640px',
      'height' => '360px',
      'color' => '00adef',
      'portrait' => 0,
      'title' => 0,
      'byline' => 0,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-youtube',
  );
  $export['cis_course_video'] = $video_embed_style;

  return $export;
}
