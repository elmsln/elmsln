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
  $strongarm->name = 'view_mode_enable_by_default';
  $strongarm->value = 0;
  $export['view_mode_enable_by_default'] = $strongarm;

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
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
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
  $strongarm->name = 'view_mode_tab_settings__audio__figurelabel_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__figurelabel_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__full_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__full_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__h5p_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__h5p_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__h5p__card_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__h5p__card_audio'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__left__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__left__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__lightboxed__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__lightboxed__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__lightboxed__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__lightboxed__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__boxed__right__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__boxed__right__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__left__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__left__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__left__lightboxed__large_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__left__lightboxed__large_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__left__lightboxed__medium_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__left__lightboxed__medium_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__left__lightboxed__small_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__left__lightboxed__small_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__lightboxed__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__lightboxed__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__lightboxed__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__lightboxed__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__right__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__right__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__right__lightboxed__large_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__right__lightboxed__large_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__right__lightboxed__medium_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__right__lightboxed__medium_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__card__right__lightboxed__small_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__card__right__lightboxed__small_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__circle_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__circle_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__circle__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__circle__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__left__circle_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__left__circle_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__left__circle__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__left__circle__lightboxed_audio'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__audio__image__lightboxed__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__lightboxed__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__lightboxed__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__lightboxed__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__parallax_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__parallax_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__parallax__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__parallax__lightboxed_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__right__circle_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__right__circle_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__image__right__circle__lightboxed_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__image__right__circle__lightboxed_audio'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__medium_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__medium_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__medium__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__medium__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__medium__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__medium__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__medium__stretch_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__medium__stretch_audio'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__small_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__small_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__small__left_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__small__left_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__small__right_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__small__right_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__small__stretch_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__small__stretch_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__stretch_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__stretch_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__stretch__medium_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__stretch__medium_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__mediasvg__stretch__small_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__mediasvg__stretch__small_audio'] = $strongarm;

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
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
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
  $strongarm->name = 'view_mode_tab_settings__document__figurelabel_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__figurelabel_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__full_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__full_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__h5p_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__h5p_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__h5p__card_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__h5p__card_document'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__left__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__left__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__lightboxed__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__lightboxed__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__lightboxed__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__lightboxed__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__boxed__right__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__boxed__right__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__left__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__left__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__left__lightboxed__large_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__left__lightboxed__large_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__left__lightboxed__medium_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__left__lightboxed__medium_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__left__lightboxed__small_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__left__lightboxed__small_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__lightboxed__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__lightboxed__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__lightboxed__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__lightboxed__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__right__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__right__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__right__lightboxed__large_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__right__lightboxed__large_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__right__lightboxed__medium_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__right__lightboxed__medium_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__card__right__lightboxed__small_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__card__right__lightboxed__small_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__circle_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__circle_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__circle__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__circle__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__left__circle_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__left__circle_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__left__circle__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__left__circle__lightboxed_document'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__document__image__lightboxed__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__lightboxed__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__lightboxed__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__lightboxed__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__parallax_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__parallax_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__parallax__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__parallax__lightboxed_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__right__circle_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__right__circle_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__image__right__circle__lightboxed_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__image__right__circle__lightboxed_document'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__medium_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__medium_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__medium__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__medium__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__medium__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__medium__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__medium__stretch_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__medium__stretch_document'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__small_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__small_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__small__left_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__small__left_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__small__right_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__small__right_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__small__stretch_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__small__stretch_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__stretch_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__stretch_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__stretch__medium_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__stretch__medium_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__mediasvg__stretch__small_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__mediasvg__stretch__small_document'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'image' => 1,
    'image__left' => 1,
    'image__left__lightboxed' => 1,
    'image__left__circle' => 1,
    'image__left__circle__lightboxed' => 1,
    'image__right' => 1,
    'image__right__lightboxed' => 1,
    'image__right__circle' => 1,
    'image__right__circle__lightboxed' => 1,
    'image__circle' => 1,
    'image__circle__lightboxed' => 1,
    'image__lightboxed' => 1,
    'image__card' => 1,
    'image__card__left__lightboxed' => 1,
    'image__card__left__lightboxed__small' => 1,
    'image__card__left__lightboxed__medium' => 1,
    'image__card__left__lightboxed__large' => 1,
    'image__card__right__lightboxed' => 1,
    'image__card__right__lightboxed__small' => 1,
    'image__card__right__lightboxed__medium' => 1,
    'image__card__right__lightboxed__large' => 1,
    'image__boxed' => 1,
    'image__boxed__left' => 1,
    'image__boxed__left__lightboxed' => 1,
    'image__boxed__right' => 1,
    'image__boxed__right__lightboxed' => 1,
    'image__parallax' => 1,
    'image__parallax__lightboxed' => 1,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__diff_standard_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__diff_standard_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__figurelabel_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__figurelabel_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__full_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__full_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__h5p_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__h5p_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__h5p__card_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__h5p__card_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__iframe_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__iframe_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__left_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__left__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__left__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed__left_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed__right_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__right_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__right__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__right__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__left_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed__large_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed__large_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed__medium_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed__small_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__left__lightboxed__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__lightboxed__left_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__lightboxed__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__lightboxed__right_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__lightboxed__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__right_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed__large_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed__large_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed__medium_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed__small_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__card__right__lightboxed__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__circle_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__circle_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed__large_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed__large_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed__medium_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed__small_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__circle__lightboxed__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__left_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__left__circle_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__left__circle_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__left__circle__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__left__circle__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__left__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__left__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__lightboxed__left_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__lightboxed__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__lightboxed__right_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__lightboxed__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__parallax_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__parallax_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__parallax__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__parallax__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__right_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__right__circle_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__right__circle_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__right__circle__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__right__circle__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__right__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__right__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__left_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__left__medium_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__left__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__left__small_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__left__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__medium_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__medium__left_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__medium__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__medium__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__medium__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__medium__stretch_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__medium__stretch_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__right__medium_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__right__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__right__small_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__right__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__small_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__small__left_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__small__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__small__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__small__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__small__stretch_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__small__stretch_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__stretch_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__stretch_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__stretch__medium_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__stretch__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__stretch__small_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__stretch__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__left_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__poster_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__poster_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__poster__left_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__poster__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__poster__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__poster__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail__left_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__revision_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__revision_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__rss_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__rss_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__teaser_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__teaser_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__token_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__token_elmsmedia_image'] = $strongarm;

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
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 1,
    'mediavideo__thumbnail' => 1,
    'mediavideo__thumbnail__right' => 1,
    'mediavideo__poster' => 1,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
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
  $strongarm->name = 'view_mode_tab_settings__external_video__figurelabel_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__figurelabel_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__full_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__full_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__h5p_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__h5p_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__h5p__card_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__h5p__card_external_video'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__left__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__left__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__lightboxed__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__lightboxed__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__lightboxed__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__lightboxed__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__boxed__right__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__boxed__right__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__left__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__left__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__left__lightboxed__large_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__left__lightboxed__large_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__left__lightboxed__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__left__lightboxed__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__left__lightboxed__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__left__lightboxed__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__lightboxed__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__lightboxed__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__lightboxed__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__lightboxed__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__right__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__right__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__right__lightboxed__large_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__right__lightboxed__large_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__right__lightboxed__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__right__lightboxed__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__card__right__lightboxed__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__card__right__lightboxed__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__circle_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__circle_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__circle__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__circle__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__left__circle_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__left__circle_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__left__circle__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__left__circle__lightboxed_external_video'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__external_video__image__lightboxed__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__lightboxed__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__lightboxed__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__lightboxed__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__parallax_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__parallax_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__parallax__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__parallax__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__right__circle_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__right__circle_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__right__circle__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__right__circle__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__image__right__lightboxed_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__image__right__lightboxed_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__left__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__left__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__left__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__left__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__medium__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__medium__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__medium__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__medium__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__medium__stretch_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__medium__stretch_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__right__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__right__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__right__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__right__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__small__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__small__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__small__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__small__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__small__stretch_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__small__stretch_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__stretch_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__stretch_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__stretch__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__stretch__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__stretch__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__stretch__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__left_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__poster_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__poster_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__poster__left_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__poster__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__poster__right_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__poster__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__right_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__thumbnail_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__thumbnail_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__thumbnail__left_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__thumbnail__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__thumbnail__right_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__thumbnail__right_external_video'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__figurelabel';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'image' => 0,
    'image__left' => 0,
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 1,
    'h5p' => 0,
    'h5p__card' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__diff_standard_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__diff_standard_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__figurelabel_figurelabel';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__figurelabel__figurelabel_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__full_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__full_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__h5p_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__h5p_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__h5p__card_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__h5p__card_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__iframe_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__iframe_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__left__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__left__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__lightboxed__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__lightboxed__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__lightboxed__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__lightboxed__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__right__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__right__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__left__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__left__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__left__lightboxed__large_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__left__lightboxed__large_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__left__lightboxed__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__left__lightboxed__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__left__lightboxed__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__left__lightboxed__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__lightboxed__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__lightboxed__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__lightboxed__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__lightboxed__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__right__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__right__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__right__lightboxed__large_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__right__lightboxed__large_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__right__lightboxed__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__right__lightboxed__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__card__right__lightboxed__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__card__right__lightboxed__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__circle_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__circle_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__circle__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__circle__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__left__circle_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__left__circle_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__left__circle__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__left__circle__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__left__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__left__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__lightboxed__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__lightboxed__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__lightboxed__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__lightboxed__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__parallax_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__parallax_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__parallax__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__parallax__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__right__circle_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__right__circle_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__right__circle__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__right__circle__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__right__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__right__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__left__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__left__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__left__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__left__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__medium__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__medium__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__medium__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__medium__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__medium__stretch_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__medium__stretch_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__right__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__right__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__right__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__right__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__small__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__small__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__small__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__small__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__small__stretch_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__small__stretch_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__stretch_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__stretch_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__stretch__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__stretch__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__stretch__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__stretch__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__poster_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__poster_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__poster__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__poster__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__poster__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__poster__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__thumbnail_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__thumbnail_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__thumbnail__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__thumbnail__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__thumbnail__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__thumbnail__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__revision_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__revision_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__rss_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__rss_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__teaser_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__teaser_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__token_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__token_figurelabel'] = $strongarm;

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
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 1,
    'h5p__card' => 1,
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
  $strongarm->name = 'view_mode_tab_settings__h5p_content__figurelabel_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__figurelabel_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__full_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__full_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__h5p_h5p_content';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__h5p_content__h5p_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__h5p__card_h5p_content';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__h5p_content__h5p__card_h5p_content'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__left__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__left__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__lightboxed__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__lightboxed__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__lightboxed__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__lightboxed__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__boxed__right__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__boxed__right__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__left__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__left__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__left__lightboxed__large_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__left__lightboxed__large_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__left__lightboxed__medium_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__left__lightboxed__medium_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__left__lightboxed__small_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__left__lightboxed__small_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__lightboxed__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__lightboxed__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__lightboxed__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__lightboxed__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__right__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__right__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__right__lightboxed__large_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__right__lightboxed__large_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__right__lightboxed__medium_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__right__lightboxed__medium_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__card__right__lightboxed__small_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__card__right__lightboxed__small_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__circle_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__circle_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__circle__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__circle__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__left__circle_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__left__circle_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__left__circle__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__left__circle__lightboxed_h5p_content'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__lightboxed__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__lightboxed__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__lightboxed__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__lightboxed__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__parallax_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__parallax_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__parallax__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__parallax__lightboxed_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__right__circle_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__right__circle_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__image__right__circle__lightboxed_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__image__right__circle__lightboxed_h5p_content'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__medium_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__medium_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__medium__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__medium__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__medium__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__medium__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__medium__stretch_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__medium__stretch_h5p_content'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__small_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__small_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__small__left_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__small__left_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__small__right_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__small__right_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__small__stretch_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__small__stretch_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__stretch_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__stretch_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__stretch__medium_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__stretch__medium_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__mediasvg__stretch__small_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__mediasvg__stretch__small_h5p_content'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__image_gallery';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'image' => 1,
    'image__left' => 0,
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 1,
    'image__circle__lightboxed' => 1,
    'image__lightboxed' => 1,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__diff_standard_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__diff_standard_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__figurelabel_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__figurelabel_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__full_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__full_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__h5p_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__h5p_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__h5p__card_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__h5p__card_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__iframe_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__iframe_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image_image_gallery';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__image_gallery__image_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__boxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__boxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__boxed__left_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__boxed__left_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__boxed__left__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__boxed__left__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__boxed__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__boxed__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__boxed__right__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__boxed__right__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__left__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__left__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__left__lightboxed__large_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__left__lightboxed__large_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__left__lightboxed__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__left__lightboxed__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__left__lightboxed__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__left__lightboxed__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__right__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__right__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__right__lightboxed__large_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__right__lightboxed__large_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__right__lightboxed__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__right__lightboxed__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__card__right__lightboxed__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__card__right__lightboxed__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__circle_image_gallery';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__image_gallery__image__circle_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__circle__lightboxed_image_gallery';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__image_gallery__image__circle__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__left_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__left_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__left__circle_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__left__circle_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__left__circle__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__left__circle__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__left__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__left__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__lightboxed_image_gallery';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__image_gallery__image__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__parallax_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__parallax_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__parallax__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__parallax__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__right__circle_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__right__circle_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__right__circle__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__right__circle__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__image__right__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__image__right__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__left_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__left_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__left__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__left__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__left__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__left__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__right__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__right__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__right__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__right__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__stretch_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__stretch_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__stretch__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__stretch__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediasvg__stretch__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediasvg__stretch__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediavideo_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediavideo_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediavideo__poster_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediavideo__poster_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediavideo__thumbnail_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediavideo__thumbnail_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__mediavideo__thumbnail__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__mediavideo__thumbnail__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__revision_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__revision_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__rss_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__rss_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__teaser_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__teaser_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__image_gallery__token_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__image_gallery__token_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 1,
    'image' => 0,
    'image__left' => 0,
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 1,
    'mediasvg__stretch' => 1,
    'mediasvg__stretch__medium' => 1,
    'mediasvg__stretch__small' => 1,
    'mediasvg__left' => 1,
    'mediasvg__left__medium' => 1,
    'mediasvg__left__small' => 1,
    'mediasvg__right' => 1,
    'mediasvg__right__medium' => 1,
    'mediasvg__right__small' => 1,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__diff_standard_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__diff_standard_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__figurelabel_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__figurelabel_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__full_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__full_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__h5p_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__h5p_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__h5p__card_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__h5p__card_svg'] = $strongarm;

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
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__left_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__left__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed__left__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__lightboxed__left_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed__lightboxed__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__lightboxed__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed__lightboxed__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__boxed__right__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__boxed__right__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__left_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__left__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__left__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__left__lightboxed__large_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__left__lightboxed__large_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__left__lightboxed__medium_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__left__lightboxed__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__left__lightboxed__small_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__left__lightboxed__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__lightboxed__left_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__lightboxed__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__lightboxed__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__lightboxed__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__right__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__right__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__right__lightboxed__large_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__right__lightboxed__large_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__right__lightboxed__medium_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__right__lightboxed__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__card__right__lightboxed__small_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__card__right__lightboxed__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__circle_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__circle_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__circle__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__circle__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__circle__lightboxed__large_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__circle__lightboxed__large_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__circle__lightboxed__medium_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__circle__lightboxed__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__circle__lightboxed__small_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__circle__lightboxed__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__left_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__left__circle_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__left__circle_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__left__circle__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__left__circle__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__left__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__left__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__lightboxed__left_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__lightboxed__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__lightboxed__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__lightboxed__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__parallax_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__parallax_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__parallax__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__parallax__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__right__circle_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__right__circle_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__right__circle__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__right__circle__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__image__right__lightboxed_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__image__right__lightboxed_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__left_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__left__medium_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__left__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__left__small_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__left__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__medium_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__medium__left_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__medium__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__medium__right_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__medium__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__medium__stretch_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__medium__stretch_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__right_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__right__medium_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__right__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__right__small_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__right__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__small_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__small__left_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__small__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__small__right_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__small__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__small__stretch_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__small__stretch_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__stretch_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__stretch_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__stretch__medium_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__stretch__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__stretch__small_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__stretch__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo__poster_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo__poster_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo__thumbnail_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo__thumbnail_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo__thumbnail__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo__thumbnail__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__revision_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__revision_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__rss_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__rss_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__teaser_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__teaser_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__token_svg';
  $strongarm->value = 0;
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
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
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
  $strongarm->name = 'view_mode_tab_settings__video__figurelabel_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__figurelabel_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__full_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__full_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__h5p_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__h5p_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__h5p__card_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__h5p__card_video'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__left__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__left__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__lightboxed__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__lightboxed__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__lightboxed__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__lightboxed__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__boxed__right__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__boxed__right__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__left__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__left__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__left__lightboxed__large_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__left__lightboxed__large_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__left__lightboxed__medium_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__left__lightboxed__medium_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__left__lightboxed__small_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__left__lightboxed__small_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__lightboxed__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__lightboxed__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__lightboxed__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__lightboxed__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__right__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__right__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__right__lightboxed__large_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__right__lightboxed__large_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__right__lightboxed__medium_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__right__lightboxed__medium_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__card__right__lightboxed__small_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__card__right__lightboxed__small_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__circle_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__circle_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__circle__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__circle__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__left__circle_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__left__circle_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__left__circle__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__left__circle__lightboxed_video'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__video__image__lightboxed__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__lightboxed__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__lightboxed__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__lightboxed__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__parallax_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__parallax_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__parallax__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__parallax__lightboxed_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__right__circle_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__right__circle_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__image__right__circle__lightboxed_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__image__right__circle__lightboxed_video'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__medium_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__medium_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__medium__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__medium__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__medium__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__medium__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__medium__stretch_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__medium__stretch_video'] = $strongarm;

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
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__small_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__small_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__small__left_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__small__left_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__small__right_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__small__right_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__small__stretch_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__small__stretch_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__stretch_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__stretch_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__stretch__medium_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__stretch__medium_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__mediasvg__stretch__small_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__mediasvg__stretch__small_video'] = $strongarm;

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

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____diff_standard_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____diff_standard_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____figurelabel_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____figurelabel_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____full_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____full_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____h5p_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____h5p_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____h5p__card_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____h5p__card_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____iframe_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____iframe_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image_image_gallery';
  $strongarm->value = 1;
  $export['view_mode_tab_settings____image_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed__left_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed__left_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed__left__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed__left__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed__right__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed__right__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__card_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__card_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__card__left_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__card__left_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__card__left__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__card__left__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__card__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__card__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__card__right__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__card__right__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__left_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__left_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__left__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__left__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__parallax_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__parallax_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__parallax__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__parallax__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__right__lightboxed_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__right__lightboxed_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__stretch_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__stretch_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__stretch__medium_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__stretch__medium_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__stretch__small_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__stretch__small_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__poster_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__poster_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__thumbnail_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__thumbnail_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__thumbnail__right_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__thumbnail__right_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____revision_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____revision_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____rss_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____rss_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____teaser_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____teaser_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____token_image_gallery';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____token_image_gallery'] = $strongarm;

  return $export;
}
