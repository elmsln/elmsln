<?php
/**
 * @file
 * elmsmedia_view_mode_tabs.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_view_mode_tabs_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 1,
    'image' => 0,
    'image__left' => 0,
    'image__right' => 0,
    'image__boxed' => 0,
    'image__lightboxed' => 0,
    'image__left__lightboxed' => 0,
    'image__right__lightboxed' => 0,
    'image__boxed__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__poster' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediasvg' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'mediasvg__stretch' => 0,
    'figurelabel' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__diff_standard_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__diff_standard_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__full_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__full_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__iframe_audio';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__audio__iframe_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__left__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__left__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__right__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__right__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__left__medium_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__left__medium_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__left__small_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__left__small_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__right__medium_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__right__medium_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__right__small_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__right__small_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__stretch_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__stretch_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediavideo_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediavideo_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediavideo__poster_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediavideo__poster_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediavideo__thumbnail_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediavideo__thumbnail_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediavideo__thumbnail__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediavideo__thumbnail__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__revision_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__revision_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__rss_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__rss_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__teaser_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__teaser_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__token_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__token_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'image' => 0,
    'image__left' => 0,
    'image__right' => 0,
    'image__boxed' => 0,
    'image__lightboxed' => 0,
    'image__left__lightboxed' => 0,
    'image__right__lightboxed' => 0,
    'image__boxed__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__poster' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediasvg' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'mediasvg__stretch' => 0,
    'figurelabel' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__diff_standard_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__diff_standard_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__full_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__full_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__iframe_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__iframe_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__left__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__left__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__right__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__right__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__left__medium_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__left__medium_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__left__small_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__left__small_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__right__medium_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__right__medium_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__right__small_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__right__small_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__stretch_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__stretch_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediavideo_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediavideo_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediavideo__poster_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediavideo__poster_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediavideo__thumbnail_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediavideo__thumbnail_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediavideo__thumbnail__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediavideo__thumbnail__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__revision_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__revision_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__rss_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__rss_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__teaser_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__teaser_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__token_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__token_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 1,
    'image' => 0,
    'image__left' => 0,
    'image__right' => 0,
    'image__boxed' => 0,
    'image__lightboxed' => 0,
    'image__left__lightboxed' => 0,
    'image__right__lightboxed' => 0,
    'image__boxed__lightboxed' => 0,
    'mediavideo' => 1,
    'mediavideo__poster' => 1,
    'mediavideo__thumbnail' => 1,
    'mediavideo__thumbnail__right' => 1,
    'mediasvg' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'mediasvg__stretch' => 0,
    'figurelabel' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__diff_standard_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__diff_standard_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__full_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__full_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__iframe_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__iframe_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__left__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__left__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__right__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__right__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__revision_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__revision_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__rss_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__rss_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__teaser_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__teaser_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__token_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__token_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 1,
    'image' => 0,
    'image__left' => 0,
    'image__right' => 0,
    'image__boxed' => 0,
    'image__lightboxed' => 0,
    'image__left__lightboxed' => 0,
    'image__right__lightboxed' => 0,
    'image__boxed__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__poster' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediasvg' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'mediasvg__stretch' => 0,
    'figurelabel' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__diff_standard_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__diff_standard_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__full_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__full_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__iframe_h5p_content';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__h5p_content__iframe_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__left__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__left__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__right__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__right__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__left__medium_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__left__medium_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__left__small_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__left__small_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__right__medium_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__right__medium_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__right__small_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__right__small_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__stretch_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__stretch_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediavideo_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediavideo_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediavideo__poster_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediavideo__poster_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediavideo__thumbnail_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediavideo__thumbnail_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediavideo__thumbnail__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediavideo__thumbnail__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__revision_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__revision_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__rss_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__rss_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__teaser_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__teaser_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__token_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__token_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__diff_standard_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__diff_standard_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__full_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__full_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__iframe_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__iframe_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image__boxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__lightboxed_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image__boxed__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__left_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__left__lightboxed_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image__left__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__lightboxed_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__right_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__right__lightboxed_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__image__right__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__revision_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__revision_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__rss_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__rss_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__teaser_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__teaser_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__token_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__token_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 1,
    'image' => 0,
    'image__left' => 0,
    'image__right' => 0,
    'image__boxed' => 0,
    'image__lightboxed' => 0,
    'image__left__lightboxed' => 0,
    'image__right__lightboxed' => 0,
    'image__boxed__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__poster' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediasvg' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'mediasvg__stretch' => 0,
    'figurelabel' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__diff_standard_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__diff_standard_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__full_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__full_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__iframe_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__video__iframe_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__left__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__left__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__right__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__right__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__left__medium_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__left__medium_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__left__small_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__left__small_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__right__medium_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__right__medium_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__right__small_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__right__small_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__stretch_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__stretch_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediavideo_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediavideo_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediavideo__poster_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediavideo__poster_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediavideo__thumbnail_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediavideo__thumbnail_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediavideo__thumbnail__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediavideo__thumbnail__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__revision_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__revision_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__rss_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__rss_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__teaser_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__teaser_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__token_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__token_video'] = $strongarm;

  return $export;
}
