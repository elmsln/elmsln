<?php
/**
 * @file
 * elmsmedia_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsmedia_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function elmsmedia_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function elmsmedia_feature_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['cache'] = 1; /* WAS: 0 */
    $data['textbook_editor']['filters']['cis_filter'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -49,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['ckeditor_link_filter']['weight'] = -46; /* WAS: -44 */
    $data['textbook_editor']['filters']['filter_htmlcorrector']['weight'] = -47; /* WAS: -45 */
    $data['textbook_editor']['filters']['video_filter']['settings']['video_filter_codecs'] = array(
      'archive' => 'Archive.org',
      'bliptv' => 'Blip.tv',
      'candidcareer' => 'Candid Career',
      'capped' => 'Capped',
      'collegehumor' => 'College Humor',
      'coub' => 'Coub',
      'dailymotion' => 'DailyMotion',
      'democracynow_fullshow' => 'DemocracyNow Fullshow',
      'democracynow_story' => 'DemocracyNow Story',
      'flickr_slideshows' => 'Flickr Slideshows',
      'flickr_video' => 'Flickr Video',
      'foxnews' => 'Fox News',
      'gametrailers' => 'Game Trailers',
      'gamevideos' => 'Game Videos',
      'giphy' => 'Giphy',
      'godtube' => 'GodTube',
      'google' => 'Google Video',
      'instagram' => 'Instagram',
      'mailru' => 'Mail.Ru',
      'metacafe' => 'Meta Cafe',
      'myspace' => 'MySpace',
      'myvideo' => 'MyVideo',
      'picasa_slideshows' => 'Picasa Slideshows',
      'rutube' => 'Rutube',
      'slideshare' => 'Slideshare',
      'streamhoster' => 'Streamhoster',
      'teachertube' => 'Teachertube',
      'ted' => 'TED',
      'twitch' => 'Twitch',
      'ustream' => 'Ustream',
      'vbox' => 'Vbox7',
      'vimeo' => 'Vimeo',
      'vine' => 'Vine',
      'whatchado' => 'whatchado',
      'wistia' => 'Wistia',
      'youku' => 'YouKu',
      'youtube' => 'YouTube',
      'youtube_playlist' => 'YouTube (Playlist)',
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['video_filter']['settings']['video_filter_multiple_sources'] = TRUE; /* WAS: '' */
    $data['textbook_editor']['filters']['video_filter']['weight'] = -50; /* WAS: -48 */
  }
}

/**
 * Implements hook_wysiwyg_default_profiles_alter().
 */
function elmsmedia_feature_wysiwyg_default_profiles_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['name'] = 'formattextbook_editor'; /* WAS: '' */
    $data['textbook_editor']['preferences'] = array(
      'add_to_summaries' => 1,
      'default' => 1,
      'show_toggle' => 0,
      'user_choose' => 0,
      'version' => '4.5.6.91e81fe',
    ); /* WAS: '' */
    unset($data['textbook_editor']['settings']['add_to_summaries']);
    unset($data['textbook_editor']['settings']['default']);
    unset($data['textbook_editor']['settings']['show_toggle']);
    unset($data['textbook_editor']['settings']['user_choose']);
  }
}

/**
 * Implements hook_image_default_styles().
 */
function elmsmedia_feature_image_default_styles() {
  $styles = array();

  // Exported image style: image.
  $styles['image'] = array(
    'label' => 'Image',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1200,
          'height' => '',
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: image_card_medium.
  $styles['image_card_medium'] = array(
    'label' => 'Image Card medium',
    'effects' => array(
      3 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 240,
          'height' => 160,
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: image_lightboxed.
  $styles['image_lightboxed'] = array(
    'label' => 'Image Lightboxed',
    'effects' => array(
      6 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1200,
          'height' => '',
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 2,
      ),
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 675,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 3,
      ),
    ),
  );

  // Exported image style: mediavideo_poster.
  $styles['mediavideo_poster'] = array(
    'label' => 'Mediavideo Poster',
    'effects' => array(
      9 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1200,
          'height' => '',
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 1,
      ),
      10 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 675,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
