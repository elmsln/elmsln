<?php
/**
 * @file
 * mooc_textbook.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_textbook_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.filters|cis_filter"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -46,
  );
  $overrides["filter.textbook_editor.filters|filter_footnotes"] = array(
    'settings' => array(
      'footnotes_collapse' => 0,
    ),
    'status' => 1,
    'weight' => -45,
  );
  $overrides["filter.textbook_editor.filters|filter_tokens"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -44,
  );
  $overrides["filter.textbook_editor.filters|video_filter|settings|video_filter_codecs"] = array(
    'archive' => 0,
    'bliptv' => 0,
    'candidcareer' => 0,
    'capped' => 0,
    'collegehumor' => 0,
    'coub' => 0,
    'dailymotion' => 0,
    'democracynow_fullshow' => 0,
    'democracynow_story' => 0,
    'flickr_slideshows' => 0,
    'flickr_video' => 0,
    'foxnews' => 0,
    'gametrailers' => 0,
    'gamevideos' => 0,
    'giphy' => 0,
    'godtube' => 0,
    'google' => 0,
    'instagram' => 0,
    'mailru' => 0,
    'metacafe' => 0,
    'myspace' => 0,
    'myvideo' => 0,
    'picasa_slideshows' => 0,
    'rutube' => 0,
    'slideshare' => 0,
    'streamhoster' => 0,
    'teachertube' => 0,
    'ted' => 0,
    'twitch' => 0,
    'ustream' => 0,
    'vbox' => 0,
    'vimeo' => 0,
    'vine' => 0,
    'whatchado' => 'whatchado',
    'wistia' => 0,
    'youku' => 0,
    'youtube' => 0,
    'youtube_playlist' => 0,
  );
  $overrides["filter.textbook_editor.filters|video_filter|settings|video_filter_multiple_sources"] = 1;

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.textbook_editor.settings|buttons|drupal"] = array(
    'rendered_entity' => 1,
  );
  $overrides["wysiwyg.textbook_editor.settings|buttons|footnotes"] = array(
    'footnotes' => 1,
  );

 return $overrides;
}
