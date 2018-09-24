<?php
/**
 * @file
 * elmsmedia_feature.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function elmsmedia_feature_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.cache"] = 1;
  $overrides["filter.textbook_editor.filters|cis_filter"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -49,
  );
  $overrides["filter.textbook_editor.filters|ckeditor_link_filter|weight"] = -46;
  $overrides["filter.textbook_editor.filters|filter_htmlcorrector|weight"] = -47;
  $overrides["filter.textbook_editor.filters|video_filter|settings|video_filter_codecs"] = array(
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
  );
  $overrides["filter.textbook_editor.filters|video_filter|settings|video_filter_multiple_sources"] = TRUE;
  $overrides["filter.textbook_editor.filters|video_filter|weight"] = -50;

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.textbook_editor.name"] = 'formattextbook_editor';
  $overrides["wysiwyg.textbook_editor.preferences"] = array(
    'add_to_summaries' => 1,
    'default' => 1,
    'show_toggle' => 0,
    'user_choose' => 0,
    'version' => '4.5.6.91e81fe',
  );
  $overrides["wysiwyg.textbook_editor.settings|add_to_summaries"]["DELETED"] = TRUE;
  $overrides["wysiwyg.textbook_editor.settings|default"]["DELETED"] = TRUE;
  $overrides["wysiwyg.textbook_editor.settings|show_toggle"]["DELETED"] = TRUE;
  $overrides["wysiwyg.textbook_editor.settings|user_choose"]["DELETED"] = TRUE;

 return $overrides;
}
