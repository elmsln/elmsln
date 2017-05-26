<?php

/**
 * @file
 * This file contains all codecs provided by Video Filter.
 */

/**
 * Implements hook_codec_info().
 */
function video_filter_codec_info() {
  $codecs = array();

  $codecs['archive'] = array(
    'name' => t('Archive.org'),
    'sample_url' => 'http://www.archive.org/details/DrupalconBoston2008-TheStateOfDrupal',
    'callback' => 'video_filter_archive',
    'html5_callback' => 'video_filter_archive',
    'regexp' => '/archive\.org\/details\/([\w-_\.]+)/i',
    'ratio' => 4 / 3,
  );

  $codecs['bliptv'] = array(
    'name' => t('Blip.tv'),
    'sample_url' => 'http://blip.tv/file/123456',
    'callback' => 'video_filter_bliptv',
    'regexp' => array(
      '@blip\.tv/rss/flash/([^"\&\?/]+)@i',
      '@blip\.tv/file/view/([^"\&\?/]+)@i',
      '@blip\.tv/file/([^"\&\?/]+)@i',
      '@blip\.tv/play/([^"\&\?/]+)@i',
    ),
    'ratio' => 16 / 9,
    'control_bar_height' => 30,
  );

  $codecs['candidcareer'] = array(
    'name' => t('Candid Career'),
    'sample_url' => 'https://www.candidcareer.com/embed.php?vkey=ed5fdd900a274930252f&shared=CandidCareer&uid=30',
    'callback' => 'video_filter_candidcareer',
    'regexp' => '/candidcareer\.com\/embed\.php\?vkey=([a-zA-Z0-9\-_&;]+)shared=([a-zA-Z0-9\-_&;]+)uid=([a-zA-Z0-9\-_&;]+)/',
    'ratio' => 16 / 9,
    'control_bar_height' => 20,
  );

  $codecs['capped'] = array(
    'name' => t('Capped'),
    'sample_url' => 'http://capped.tv/playeralt.php?vid=some-title',
    'callback' => 'video_filter_capped',
    'regexp' => '/capped\.tv\/([a-zA-Z0-9\-_]+)/',
    'ratio' => 425 / 355,
  );

  $codecs['collegehumor'] = array(
    'name' => t('College Humor'),
    'sample_url' => 'http://www.collegehumor.com/video:1234567890',
    'callback' => 'video_filter_collegehumor',
    'regexp' => '/collegehumor\.com\/video\:([0-9]+)/',
    'ratio' => 16 / 9,
    'control_bar_height' => 0,
  );

  $codecs['coub'] = array(
    'name' => t('Coub'),
    'sample_url' => 'http://coub.com/view/b7ghv',
    'callback' => 'video_filter_coub',
    'html5_callback' => 'video_filter_coub',
    'regexp' => '/coub\.com\/view\/([a-z0-9]+)/i',
    'ratio' => 4 / 3,
  );

  $codecs['dailymotion'] = array(
    'name' => t('DailyMotion'),
    'sample_url' => 'http://www.dailymotion.com/video/some_video_title',
    'callback' => 'video_filter_dailymotion',
    'html5_callback' => 'video_filter_dailymotion_html5',
    'regexp' => '/dailymotion\.com\/video\/([a-z0-9\-_]+)/i',
    'ratio' => 4 / 3,
    'control_bar_height' => 20,
  );

  $codecs['democracynow_fullshow'] = array(
    'name' => t('DemocracyNow Fullshow'),
    'sample_url' => 'http://www.democracynow.org/shows/2015/3/20',
    'callback' => 'video_filter_democracynow_fullshow',
    'regexp' => '/democracynow\.org\/shows\/([0-9]+)\/([0-9]+)\/([0-9]+)/',
    'ratio' => 16 / 9,
    'control_bar_height' => 0,
  );

  $codecs['democracynow_story'] = array(
    'name' => t('DemocracyNow Story'),
    'sample_url' => 'http://www.democracynow.org/2015/3/23/yemen_in_crisis_us_closes_key',
    'callback' => 'video_filter_democracynow_story',
    'regexp' => '/democracynow\.org\/([0-9]+)\/([0-9]+)\/([0-9]+)\/([a-zA-Z0-9\-_]+)/',
    'ratio' => 16 / 9,
    'control_bar_height' => 0,
  );

  $codecs['flickr_slideshows'] = array(
    'name' => t('Flickr Slideshows'),
    'sample_url' => 'http://www.flickr.com/photos/username/sets/1234567890/show/',
    'callback' => 'video_filter_flickr_slideshows',
    'regexp' => '/flickr\.com\/photos\/([a-zA-Z0-9@_\-]+)\/sets\/([0-9]+)\/?[show]?\/?/i',
    'ratio' => 4 / 3,
    'control_bar_height' => 0,
  );

  $codecs['flickr_video'] = array(
    'name' => t('Flickr Video'),
    'sample_url' => 'http://www.flickr.com/photos/hansnilsson/1234567890/',
    'callback' => 'video_filter_flickr_video',
    'regexp' => '/flickr\.com\/photos\/([a-zA-Z0-9@_\-]+)\/([0-9]+)/',
    'ratio' => 4 / 3,
    'control_bar_height' => 0,
  );

  $codecs['foxnews'] = array(
    'name' => t('Fox News'),
    'sample_url' => 'http://video.foxnews.com/v/123456/the-title/',
    'callback' => 'video_filter_foxnews',
    'html5_callback' => 'video_filter_foxnews',
    'regexp' => '/video\.foxnews\.com\/v\/([0-9]+)\/([a-zA-Z0-9\-]+)/i',
    'ratio' => 466 / 263,
    'control_bar_height' => 0,
  );

  $codecs['gametrailers'] = array(
    'name' => t('Game Trailers'),
    'sample_url' => 'http://www.gametrailers.com/video/some-title/12345',
    'callback' => 'video_filter_gametrailers',
    'regexp' => array(
      '/gametrailers\.com\/player\/([0-9]+)/',
      '/gametrailers\.com\/video\/([a-z0-9\-_]+)\/([0-9]+)/',
    ),
    'ratio' => 16 / 9,
  );

  $codecs['gamevideos'] = array(
    'name' => t('Game Videos'),
    'sample_url' => 'http://gamevideos.1up.com/video/id/12345',
    'callback' => 'video_filter_gamevideos',
    'regexp' => '/gamevideos\.1up\.com\/video\/id\/([0-9]+)/',
    'ratio' => 500 / 319,
  );

  $codecs['giphy'] = array(
    'name' => t('Giphy'),
    'sample_url' => 'http://giphy.com/gifs/disney-kids-peter-pan-[gif-id]',
    'callback' => 'video_filter_giphy',
    'html5_callback' => 'video_filter_giphy',
    'regexp' => '/giphy\.com\/gifs\/(([a-zA-Z0-9\-]+)\-|)([a-zA-Z0-9]+)/i',
    'ratio' => 16 / 9,
  );

  $codecs['godtube'] = array(
    'name' => t('GodTube'),
    'sample_url' => 'http://www.godtube.com/watch/?v=123abc',
    'callback' => 'video_filter_godtube',
    'regexp' => '/godtube\.com\/watch\/\?v=([a-z0-9\-_]+)/i',
    'ratio' => 400 / 283,
    'control_bar_height' => 40,
  );

  $codecs['google'] = array(
    'name' => t('Google Video'),
    'sample_url' => 'http://video.google.com/videoplay?docid=-uN1qUeId',
    'callback' => 'video_filter_google',
    'regexp' => '/video\.google\.[a-z]+\.?[a-z]+?\/videoplay\?docid=(\-?[0-9]+)/',
    'ratio' => 400 / 326,
  );

  $codecs['instagram'] = array(
    'name' => t('Instagram'),
    'callback' => 'video_filter_instagram',
    'sample_url' => 'http://instagram.com/p/uN1qUeId',
    'regexp' => array(
      '/instagram\.com\/p\/([a-z0-9\-_]+)/i',
      '/instagr.am\/p\/([a-z0-9\-_]+)/i',
    ),
    'ratio' => 612 / 710,
  );

  $codecs['metacafe'] = array(
    'name' => t('Meta Cafe'),
    'sample_url' => 'http://www.metacafe.com/watch/1234567890/some_title/',
    'callback' => 'video_filter_metacafe',
    'regexp' => '/metacafe\.com\/watch\/([a-z0-9\-_]+)\/([a-z0-9\-_]+)/i',
    'ratio' => 400 / 313,
    'control_bar_height' => 32,
  );

  $codecs['mailru'] = array(
    'name' => t('Mail.Ru'),
    'sample_url' => 'https://my.mail.ru/v/semenikhin_denis/video/_groupvideo/[video-id].html',
    'callback' => 'video_filter_mailru',
    'html5_callback' => 'video_filter_mailru',
    'regexp' => '/my\.mail\.ru\/v\/(.*)\/([0-9]+)\.html/i',
    'ratio' => 16 / 9,
    'control_bar_height' => 0,
  );

  $codecs['myspace'] = array(
    'name' => t('MySpace'),
    'sample_url' => 'http://myspace.com/video/vid/1234567890',
    'callback' => 'video_filter_myspace',
    'regexp' => array(
      '/vids\.myspace\.com\/.*VideoID=([0-9]+)/i',
      '/myspace\.com\/video\/([a-z])+\/([0-9]+)/i',
      '/myspace\.com\/video\/([a-z0-9\-_]+)\/([a-z0-9\-_]+)\/([a-z0-9]+)/i',
      '/myspace\.com\/([a-z0-9\-_]+)\/videos\/([a-z0-9\-_]+)\/([a-z0-9]+)/i',
    ),
    'ratio' => 620 / 400,
    'control_bar_height' => 40,
  );

  $codecs['myvideo'] = array(
    'name' => t('MyVideo'),
    'sample_url' => 'http://www.myvideo.de/filme/story-title-1234567890',
    'html5_callback' => 'video_filter_myvideo',
    'callback' => 'video_filter_myvideo',
    'regexp' => array(
      '/myvideo\.de\/(.+)\-([0-9]+)/i',
    ),
    'ratio' => 400 / 283,
  );

  $codecs['picasa_slideshows'] = array(
    'name' => t('Picasa Slideshows'),
    'sample_url' => 'http://picasaweb.google.com/data/feed/base/user/USER_NAME/albumid/5568104935784209834?alt=rss&amp;kind=photo&amp;hl=en_US',
    'callback' => 'video_filter_picasa_slideshows',
    'instructions' => t('You must use the URL of the RSS feed for the Picasa album:') .
      '<ol>' .
      '<li>' . t('View the album in Picasa (you should see thumbnails, not a slideshow).') . '</li>' .
      '<li>' . t('Find the "RSS" link and click it.') . '</li>' .
      '<li>' . t('Copy the resulting URL from the browser address bar.  Example:') . '<br />' .
      '<code>[video: http://picasaweb.google.com/data/feed/base/user/USER_NAME/albumid/5568104935784209834?alt=rss&amp;kind=photo&amp;hl=en_US]</code>' .
      '</li>' .
      '</ol>',
    'regexp' => '/picasaweb\.google\.com\/data\/feed\/base\/user\/([a-zA-Z0-9@_\-\.]+)\/albumid\/([a-z0-9]+)/i',
    'ratio' => 800 / 600,
  );

  $codecs['rutube'] = array(
    'name' => t('Rutube'),
    'sample_url' => 'http://rutube.ru/video/c80617086143e80ee08f760a2e9cbf43/?pl_type=source&pl_id=8188',
    'html5_callback' => 'video_filter_rutube',
    'callback' => 'video_filter_rutube',
    'regexp' => array(
      '/rutube\.ru\/(.*)/i',
    ),
    'ratio' => 16 / 9,
  );

  $codecs['slideshare'] = array(
    'name' => t('Slideshare'),
    'sample_url' => 'http://slideshare.net/1759622',
    'callback' => 'video_filter_slideshare',
    'instructions' => t('You need to construct your own URL, using the "Wordpress Embed" code from Slideshare, extract the "id", and form the URL like this: slideshare.net/1759622'),
    'regexp' => array(
      '/slideshare\.net\/\?id=([a-z0-9]+)/',
      '/slideshare\.net\/([a-z0-9]+)/',
    ),
    'ratio' => 425 / 355,
  );

  $codecs['streamhoster'] = array(
    'name' => t('Streamhoster'),
    'sample_url' => 'http://web26.streamhoster.com/username/filename.flv',
    'callback' => 'video_filter_streamhoster',
    'regexp' => '/([a-z0-9]+)\:\/\/([a-z0-9\-_]+)\.streamhoster\.com\/([a-z0-9\-_]+)\/([a-z0-9\-_\.]+)/i',
    'ratio' => 480 / 360,
  );

  $codecs['teachertube'] = array(
    'name' => t('Teachertube'),
    'sample_url' => 'http://www.teachertube.com/viewVideo.php?video_id=VIDEOID',
    'callback' => 'video_filter_teachertube',
    'regexp' => '/teachertube\.com\/viewVideo.php\?video_id\=([0-9]+)/i',
    'ratio' => 16 / 9,
  );

  $codecs['ted'] = array(
    'name' => t('TED'),
    'sample_url' => 'https://www.ted.com/talks/[story-title]',
    'instructions' => t('Click in Embed and copy the "Link to this talk" link and paste here.'),
    'callback' => 'video_filter_ted',
    'html5_callback' => 'video_filter_ted',
    'regexp' => '/ted\.com\/talks\/lang\/([a-zA-Z]+)\/([a-zA-Z0-9\-_]+)(\.html)?/',
    'ratio' => 4 / 3,
  );

  $codecs['twitch'] = array(
    'name' => t('Twitch'),
    'sample_url' => 'http://www.twitch.tv/uN1qUe-I_d',
    'callback' => 'video_filter_twitch',
    'regexp' => '/twitch\.tv\/([a-z0-9\-_]+)/i',
    'ratio' => 16 / 9,
  );

  $codecs['ustream'] = array(
    'name' => t('Ustream'),
    'sample_url' => 'http://www.ustream.tv/recorded/111212121212',
    'html5_callback' => 'video_filter_ustream',
    'callback' => 'video_filter_ustream',
    'regexp' => '/ustream\.tv\/recorded\/([0-9]+)/i',
    'ratio' => 16 / 9,
  );

  $codecs['vbox'] = array(
    'name' => t('Vbox7'),
    'sample_url' => 'http://vbox7.com/play:b4a7291f3d',
    'callback' => 'video_filter_vbox',
    'regexp' => '/vbox7\.com\/play\:([a-z0-9]+)/i',
    'ratio' => 400 / 345,
  );

  $codecs['vimeo'] = array(
    'name' => t('Vimeo'),
    'sample_url' => 'http://www.vimeo.com/123456',
    'callback' => 'video_filter_vimeo',
    'html5_callback' => 'video_filter_vimeo_html5',
    'regexp' => '/vimeo\.com\/([0-9]+)/',
    'ratio' => 16 / 9,
    'control_bar_height' => 0,
  );

  $codecs['vine'] = array(
    'name' => t('Vine'),
    'sample_url' => 'https://www.vine.co/v/uN1qUeId',
    'callback' => 'video_filter_vine',
    'regexp' => '/vine\.co\/v\/([0-9a-z]+)/i',
    'ratio' => 4 / 3,
  );

  $codecs['whatchado'] = array(
    'name' => t('whatchado'),
    'sample_url' => 'https://www.whatchado.com/de/some-title',
    'callback' => 'video_filter_whatchado_whatchado',
    'regexp' => array(
      '/whatchado\.com\/[a-z]{2}\/([\w-_]+)/i',
    ),
    'ratio' => 960 / 540,
  );

  $codecs['wistia'] = array(
    'name' => t('Wistia'),
    'sample_url' => 'http://wistia.com/medias/9pj9n6ftlk',
    'callback' => 'video_filter_wistia_html5',
    'html5_callback' => 'video_filter_wistia_html5',
    'regexp' => '@https?://(.+\.)?(wistia\.(com|net)|wi\.st)/((m|medias|projects)|embed/(iframe|playlists))/([a-zA-Z0-9]+)@',
  );

  $codecs['youku'] = array(
    'name' => t('YouKu'),
    'sample_url' => 'http://v.youku.com/v_show/id_XNjgzNDM4MzIw.html',
    'callback' => 'video_filter_youku_html5',
    'html5_callback' => 'video_filter_youku_html5',
    'regexp' => array(
      '/youku\.com\/v_show\/id_([a-z0-9\-_=]+)\.html/i',
      '/youku\.com\/player\.php\/sid\/([a-z0-9\-_=]+)/i',
    ),
    'ratio' => 16 / 9,
    'control_bar_height' => 50,
  );

  $codecs['youtube'] = array(
    'name' => t('YouTube'),
    'sample_url' => 'http://www.youtube.com/watch?v=uN1qUeId',
    'callback' => 'video_filter_youtube',
    'html5_callback' => 'video_filter_youtube_html5',
    'regexp' => array(
      '/youtube\.com\/watch\?.*?v=([a-z0-9\-_]+)/i',
      '/youtu.be\/([a-z0-9\-_]+)/i',
      '/youtube\.com\/v\/([a-z0-9\-_]+)/i',
      '/youtube\.com\/embed\/([a-z0-9\-_]+)/i',
    ),
    'ratio' => 16 / 9,
    'control_bar_height' => 0,
  );

  $codecs['youtube_playlist'] = array(
    'name' => t('YouTube (Playlist)'),
    'sample_url' => 'http://www.youtube.com/playlist?list=uN1qUeId',
    'callback' => 'video_filter_youtube_playlist_html5',
    'regexp' => array(
      '/youtube\.com\/playlist\?list=([a-z0-9\-_]+)/i',
    ),
    'ratio' => 16 / 9,
    'control_bar_height' => 0,
  );

  return $codecs;
}

/**
 * Callback for Archive.org codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_archive($video) {
  $video['source'] = '//www.archive.org/embed/' . $video['codec']['matches'][1];

  return video_filter_iframe($video);
}

/**
 * Callback for Blip.tv codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_bliptv($video) {
  $id = $video['codec']['matches'][1];

  // Since video ID in URL is different than in embed code, use API to lookup
  // the embed code video ID. Adapted from emfield.module.
  $result = drupal_http_request('http://blip.tv/file/' . $id . '?skin=api');

  if ($result->code == 200) {
    $parser = drupal_xml_parser_create($result->data);
    $vals = array();
    $index = array();
    xml_parse_into_struct($parser, $result->data, $vals, $index);
    xml_parser_free($parser);

    $response = array();
    // @todo: What's $arghash supposed to be? It's undefined.
    $response['_emfield_arghash'] = $arghash;
    $level = array();
    $start_level = 1;
    foreach ($vals as $xml_elem) {
      if ($xml_elem['type'] == 'open') {
        if (array_key_exists('attributes', $xml_elem)) {
          list($level[$xml_elem['level']], $extra) = array_values($xml_elem['attributes']);
        }
        else {
          $level[$xml_elem['level']] = $xml_elem['tag'];
        }
      }
      if ($xml_elem['type'] == 'complete') {
        $php_stmt = '$response';
        while ($start_level < $xml_elem['level']) {
          $php_stmt .= '[$level[' . $start_level . ']]';
          $start_level++;
        }
        $php_stmt .= '[$xml_elem[\'tag\']][] = $xml_elem[\'value\'];' . $php_stmt . '[$xml_elem[\'tag\']][] = $xml_elem[\'attributes\'];';
        eval($php_stmt);
        $start_level--;
      }
    }
    $id = $response['EMBEDLOOKUP'][0];
    // Protect from XSS.
    if (preg_match("/[^A-Za-z0-9]/", $id, $matches)) {
      watchdog('Video Filter', 'A faulty Blip.tv ID has been detected.');
      $id = 0;
    }
  }

  $video['source'] = '//blip.tv/play/' . $id;
  $params = array(
    'allowscriptaccess' => 'always',
  );

  return video_filter_flash($video, $params);
}

/**
 * Callback for Candid Career codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_candidcareer($video) {
  // Their urls contain & symbols which Drupal is encoding, so decode those.
  $decoded = decode_entities($video['codec']['matches'][0]);
  $video['source'] = '//' . $decoded;
  $video['attributes']['marginwidth'] = 0;
  $video['attributes']['marginheight'] = 0;
  return video_filter_iframe($video);
}

/**
 * Callback for Capped codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_capped($video) {
  $video['source'] = '//capped.micksam7.com/playeralt.swf?vid=' . $video['codec']['matches'][1];

  return video_filter_flash($video);
}

/**
 * Callback for College Humor codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_collegehumor($video) {
  $video['source'] = '//www.collegehumor.com/moogaloop/moogaloop.swf?clip_id=' . $video['codec']['matches'][1] . '&amp;fullscreen=1';

  return video_filter_flash($video);
}

/**
 * HTML5 callback for Coub codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_coub($video) {
  $attributes = array(
    'autostart' => !empty($video['autoplay']) ? 'autoplay=true' : 'autoplay=false',
    'originalSize' => !empty($video['originalSize']) ? 'originalSize=true' : 'originalSize=false',
    'startWithHD' => !empty($video['startWithHD']) ? 'startWithHD=true' : 'startWithHD=false',
    'muted' => !empty($video['muted']) ? 'muted=true' : 'muted=false',
  );
  $video['source'] = '//coub.com/embed/' . $video['codec']['matches'][1] . '?' . implode('&', $attributes);

  return video_filter_iframe($video);
}

/**
 * Callback for DailyMotion codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_dailymotion($video) {
  $attributes = array(
    'autoplay' => $video['autoplay'] ? 'autoplay=1' : 'autoplay=0',
  );
  $video['source'] = '//www.dailymotion.com/swf/' . $video['codec']['matches'][1] . '?' . implode('&amp;', $attributes);

  return video_filter_flash($video);
}

/**
 * HTML5 callback for DailyMotion codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_dailymotion_html5($video) {
  $attributes = array(
    'autoplay' => $video['autoplay'] ? 'autoplay=1' : 'autoplay=0',
  );
  $video['source'] = '//www.dailymotion.com/embed/video/' . $video['codec']['matches'][1] . '?' . implode('&amp;', $attributes);

  return video_filter_iframe($video);
}

/**
 * Callback for Flickr Slideshows codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_flickr_slideshows($video) {
  $slideshow_player_url = 'http://www.flickr.com/apps/slideshow/show.swf?v=67348';
  $video['source'] = $slideshow_player_url . ($video['autoplay'] ? '&amp;autoplay=1' : '');

  $user_name = $video['codec']['matches'][1];
  $set_id = $video['codec']['matches'][2];

  $params['flashvars'] = "&amp;offsite=true&amp;lang=en-us&amp;page_show_url=%2Fphotos%2F$user_name%2Fsets%2F$set_id%2Fshow%2F&amp;page_show_back_url=%2Fphotos%2F$user_name%2Fsets%2F$set_id%2F&amp;set_id=$set_id&amp;jump_to=";

  return video_filter_flash($video, $params);
}

/**
 * Callback for DemocracyNow Fullshow codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_democracynow_fullshow($video) {
  $video['source'] = 'http://www.democracynow.org/embed/show/' . $video['codec']['matches'][0];
  // The above is pulling in the url part of the regex, so we need to do a
  // search and replace to remove it.
  $toomuch = array("http://www.democracynow.org/embed/show/democracynow.org/shows/");
  $justright = array("http://www.democracynow.org/embed/show/");
  $replaced = str_replace($toomuch, $justright, $video);
  $video = $replaced;

  return video_filter_iframe($video);
}

/**
 * Callback for DemocracyNow story codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_democracynow_story($video) {
  $video['source'] = 'http://www.democracynow.org/embed/story/' . $video['codec']['matches'][0];
  // The above is pulling in the url part of the regex, so we need to do a
  // search and replace to remove it.
  $toomuch = array("http://www.democracynow.org/embed/story/democracynow.org/");
  $justright = array("http://www.democracynow.org/embed/story/");
  $replaced = str_replace($toomuch, $justright, $video);
  $video = $replaced;

  return video_filter_iframe($video);
}

/**
 * Callback for Ted.com codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_ted($video) {
  $video['source'] = '//embed.ted.com/talks/' . $video['codec']['matches'][3] . '.html';
  return video_filter_iframe($video);
}

/**
 * Callback for Flickr Video codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_flickr_video($video) {
  $video['source'] = '//www.flickr.com/apps/video/stewart.swf?v=1.161';

  $params['flashvars'] = '&amp;photo_id=' . $video['codec']['matches'][2] . '&amp;flickr_show_info_box=true';

  return video_filter_flash($video, $params);
}

/**
 * Callback for Fox News codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_foxnews($video) {
  $video_id = $video['codec']['matches'][1];
  $html = '<script type="text/javascript" src="http://video.foxnews.com/v/embed.js?id=' . $video_id . '&w=' . $video['width'] . '&h=' . $video['height'] . '"></script>';
  return $html;
}

/**
 * Callback for Game Trailers codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_gametrailers($video) {
  if (is_numeric($video['codec']['matches'][1])) {
    $match = $video['codec']['matches'][1];
  }
  elseif (is_numeric($video['codec']['matches'][2])) {
    $match = $video['codec']['matches'][2];
  }
  $video['source'] = '//media.mtvnservices.com/embed/mgid:moses:video:gametrailers.com:' . $match;

  return video_filter_iframe($video);
}

/**
 * Callback for Game Videos codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_gamevideos($video) {
  $video['source'] = '//gamevideos.1up.com/swf/gamevideos12.swf?embedded=1&amp;fullscreen=1&amp;autoplay=0&amp;src=http://gamevideos.1up.com/do/videoListXML%3Fid%3D' . $video['codec']['matches'][1];

  return video_filter_flash($video);
}

/**
 * Callback for Giphy codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_giphy($video) {
  $video['source'] = '//giphy.com/embed/' . $video['codec']['matches'][3];

  return video_filter_iframe($video);
}

/**
 * Callback for GodTube codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_godtube($video) {
  $video['source'] = '//www.godtube.com/embed/watch/' . $video['codec']['matches'][1];

  return video_filter_iframe($video);
}

/**
 * Callback for Google Video codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_google($video) {
  $video['source'] = '//video.google.com/googleplayer.swf?docId=' . $video['codec']['matches'][1];

  return video_filter_flash($video);
}

/**
 * Callback for Instagram codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_instagram($video) {
  $html = &drupal_static(__FUNCTION__);
  $id = $video['codec']['matches'][1];
  if ($cache = cache_get('video_filter_instagram:' . $id)) {
    $html = $cache->data;
  }
  else {
    $endpoint = 'https://api.instagram.com/oembed';
    $options = array(
      'url' => 'http://instagr.am/p/' . $id,
    );
    $data = video_filter_oembed_request($endpoint, $options);
    if (!empty($data['html'])) {
      $html = $data['html'];
    } 
    cache_set('video_filter_instagram:' . $id, $html, 'cache');
  }
  return $html;
}

/**
 * Callback for Mail.Ru codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_mailru($video) {
  $attributes = array(
    'autoplay' => !empty($video['autoplay']) ? 'autoplay=' . (int) $video['autoplay'] : '',
  );
  $video['source'] = 'https://videoapi.my.mail.ru/videos/embed/v/' . $video['codec']['matches'][1] . '/' . $video['codec']['matches'][2] . '.html?' . implode('&', $attributes);
  return video_filter_iframe($video);
}

/**
 * Callback for Meta Cafe codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_metacafe($video) {
  $video['source'] = '//metacafe.com/fplayer/' . $video['codec']['matches'][1] . '/' . $video['codec']['matches'][2] . '.swf';

  return video_filter_flash($video);
}

/**
 * Callback for MySpace codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_myspace($video) {
  // The last match is the ID we need.
  $last = count($video['codec']['matches']);
  $video['source'] = '//mediaservices.myspace.com/services/media/embed.aspx/m=' . $video['codec']['matches'][$last - 1];

  return video_filter_flash($video, $params);
}

/**
 * Callback for MyVideo codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_myvideo($video) {
  $video['source'] = 'http://www.myvideo.de/embedded/public/' . $video['codec']['matches'][2];
  return video_filter_iframe($video);
}

/**
 * Callback for Picasa Slideshows codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_picasa_slideshows($video) {
  $video['source'] = '//picasaweb.google.com/s/c/bin/slideshow.swf';

  $user_name = $video['codec']['matches'][1];
  $set_id = $video['codec']['matches'][2];

  $params['flashvars'] = "host=picasaweb.google.com&amp;&amp;feat=flashalbum&amp;RGB=0x000000&amp;feed=http%3A%2F%2Fpicasaweb.google.com%2Fdata%2Ffeed%2Fapi%2Fuser%2F" . $user_name . "%2Falbumid%2F" . $set_id . "%3Falt%3Drss%26kind%3Dphoto%26" . ($video['autoplay'] ? '' : '&amp;noautoplay=1');

  return video_filter_flash($video, $params);
}

/**
 * Callback for Rutube codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_rutube($video) {
  $attributes = array(
    'skinColor' => (isset($video['skinColor']) && !empty($video['standardColor'])) ? 'skinColor=' . (string) $video['skinColor'] : '',
    'sTitle' => (isset($video['sTitle']) && $video['sTitle'] == 1) ? 'sTitle=true' : 'sTitle=false',
    'sAuthor' => (isset($video['sAuthor']) && $video['sAuthor'] == 1) ? 'sAuthor=true' : 'sAuthor=false',
    'bmstart' => (isset($video['bmstart']) && $video['bmstart'] > 1) ? 'bmstart=' . (int) $video['bmstart'] : 'bmstart=false',
  );
  $endpoint = 'http://rutube.ru/api/oembed';
  $options = array(
    'url' => $video['source'],
    'format' => 'json',
  );
  $data = video_filter_oembed_request($endpoint, $options);
  if (!empty($data['html'])) {
    if (preg_match('/src="([^"]+)"/', $data['html'], $match)) {
      $video['source'] = $match[1] . '?' . implode('&', $attributes);
      return video_filter_iframe($video);
    }
  }
}

/**
 * Callback for Slideshare codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_slideshare($video) {
  $video['source'] = '//www.slideshare.net/slideshow/embed_code/' . $video['codec']['matches'][1];

  return video_filter_iframe($video);
}

/**
 * Callback for Streamhoster codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_streamhoster($video) {
  $video['source'] = '//public.streamhoster.com/Resources/Flash/JWFLVMediaPlayer/mediaplayer.swf';

  $params = array('allowscriptaccess' => 'always');
  $protocol = $video['codec']['matches'][1];

  if ($protocol == 'rtmp') {
    $params['flashvars'] = 'file=' . urlencode('/' . $video['codec']['matches'][4]);
    $params['flashvars'] .= '&amp;streamer=' . urlencode('rtmp://' . $video['codec']['matches'][2] . '.streamhoster.com/' . $video['codec']['matches'][3]);
    $params['flashvars'] .= '&amp;type=rtmp';
  }
  elseif ($protocol == 'http') {
    $params['flashvars'] = 'file=' . urlencode('http://' . $video['codec']['matches'][2] . '.streamhoster.com/' . $video['codec']['matches'][3] . '/' . $video['codec']['matches'][4]);
    $params['flashvars'] .= '&amp;type=video';
  }

  $params['flashvars'] .= '&amp;width=' . $video['width'];
  $params['flashvars'] .= '&amp;height=' . $video['height'];
  $params['flashvars'] .= !empty($video['autoplay']) ? '&amp;autostart=true' : '&amp;autostart=false';

  return video_filter_flash($video, $params);
}

/**
 * Callback for Twitch codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_twitch($video) {
  $video['source'] = '//player.twitch.tv/?channel=' . $video['codec']['matches'][1] ;
  return video_filter_iframe($video);
}

/**
 * Callback for Teachertube codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_teachertube($video) {
  $video['source'] = '//www.teachertube.com/embed/player.swf';

  $params['flashvars'] = 'file=http://www.teachertube.com/embedFLV.php?pg=video_' . $video['codec']['matches'][1] . '&amp;menu=false&amp;frontcolor=ffffff&amp;lightcolor=FF0000&amp;logo=http://www.teachertube.com/www3/images/greylogo.swf&amp;skin=http://www.teachertube.com/embed/overlay.swf&amp;volume=80&amp;controlbar=over&amp;displayclick=link&amp;viral.link=http://www.teachertube.com/viewVideo.php?video_id=' . $video['codec']['matches'][1] . '&amp;stretching=exactfit&amp;plugins=viral-2&amp;viral.callout=none&amp;viral.onpause=false';

  return video_filter_flash($video, $params);
}

/**
 * Callback for Ustream codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_ustream($video) {
  $attributes = array(
    'html5ui' => 'html5ui',
    'autoplay' => isset($video['autoplay']) ? 'autoplay=' . (int) $video['autoplay'] : 'autoplay=0',
  );
  $video['source'] = 'http://www.ustream.tv/embed/recorded/' . $video['codec']['matches'][1] . '?' . implode('&', $attributes);
  return video_filter_iframe($video);
}

/**
 * Callback for VBox7 codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_vbox($video) {
  $video['source'] = '//vbox7.com/emb/external.php?vid=' . $video['codec']['matches'][1];

  return video_filter_flash($video);
}

/**
 * Callback for Vimeo codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_vimeo($video) {
  $attributes = array(
    'autopause' => isset($video['autopause']) ? 'autopause=' . (int) $video['autopause'] : 'autopause=1',
    'autoplay' => isset($video['autoplay']) ? 'autoplay=' . (int) $video['autoplay'] : 'autoplay=0',
    'badge' => isset($video['badge']) ? 'badge=' . (int) $video['badge'] : 'badge=1',
    'byline' => isset($video['byline']) ? 'byline=' . (int) $video['byline'] : 'byline=1',
    'loop' => isset($video['loop']) ? 'loop=' . (int) $video['loop'] : 'loop=0',
    'portrait' => isset($video['portrait']) ? 'portrait=' . (int) $video['portrait'] : 'portrait=1',
    'title' => isset($video['title']) ? 'autopause=' . (int) $video['title'] : 'autopause=1',
    'fullscreen' => isset($video['fullscreen']) ? 'fullscreen=' . (int) $video['fullscreen'] : 'fullscreen=1',
  );
  if (!empty($video['color'])) {
    $attributes['color'] = (string) $video['color'];
  }
  $video['source'] = '//www.vimeo.com/moogaloop.swf?clip_id=' . $video['codec']['matches'][1] . '&amp;server=www.vimeo.com&amp;' . implode('&amp;', $attributes);

  return video_filter_flash($video);
}

/**
 * HTML5 callback for Vimeo codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_vimeo_html5($video) {
  $attributes = array(
    'autopause' => isset($video['autopause']) ? 'autopause=' . (int) $video['autopause'] : 'autopause=1',
    'autoplay' => isset($video['autoplay']) ? 'autoplay=' . (int) $video['autoplay'] : 'autoplay=0',
    'badge' => isset($video['badge']) ? 'badge=' . (int) $video['badge'] : 'badge=1',
    'byline' => isset($video['byline']) ? 'byline=' . (int) $video['byline'] : 'byline=1',
    'loop' => isset($video['loop']) ? 'loop=' . (int) $video['loop'] : 'loop=0',
    'portrait' => isset($video['portrait']) ? 'portrait=' . (int) $video['portrait'] : 'portrait=1',
    'title' => isset($video['title']) ? 'autopause=' . (int) $video['title'] : 'autopause=1',
    'fullscreen' => isset($video['fullscreen']) ? 'fullscreen=' . (int) $video['fullscreen'] : 'fullscreen=1',
  );
  if (!empty($video['color'])) {
    $attributes['color'] = (string) $video['color'];
  }
  $video['source'] = '//player.vimeo.com/video/' . $video['codec']['matches'][1] . '?' . implode('&', $attributes);

  return video_filter_iframe($video);
}

/**
 * Callback for Whatchadoo codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_whatchado($video) {
  $video['source'] = '//www.whatchado.com/embed/player/' . $video['codec']['matches'][1];

  return video_filter_iframe($video);
}

/**
 * HTML5 callback for YouKu codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_youku_html5($video) {
  $attributes = array();
  $video['source'] = 'http://player.youku.com/embed/' . $video['codec']['matches'][1] . '?' . implode('&amp;', $attributes);

  return video_filter_iframe($video);
}

/**
 * Callback for YouTube codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_youtube($video) {
  $attributes = array(
    'modestbranding' => !empty($video['modestbranding']) ? 'modestbranding=1' : 'modestbranding=0',
    'rel' => !empty($video['related']) ? 'rel=1' : 'rel=0',
    'autoplay' => !empty($video['autoplay']) ? 'autoplay=1' : 'autoplay=0',
    'fs' => 'fs=1',
    'loop' => !empty($video['loop']) ? 'loop=1' : 'loop=0',
    'controls' => !empty($video['controls']) ? 'controls=1' : (!isset($video['controls']) ? 'controls=1' : 'controls=0'),
    'autohide' => !empty($video['autohide']) ? 'autohide=1' : 'autohide=0',
    'showinfo' => !empty($video['showinfo']) ? 'showinfo=1' : 'showinfo=0',
    'theme' => !empty($video['theme']) ? 'theme=' . $video['theme'] : 'theme=dark',
    'color' => !empty($video['color']) ? 'color=' . $video['color'] : 'color=red',
    'enablejsapi' => !empty($video['enablejsapi']) ? 'enablejsapi=' . (int) $video['enablejsapi'] : 'enablejsapi=0',
  );

  if (!empty($video['loop'])) {
    $attributes['playlist'] = 'playlist=' . $video['codec']['matches'][1];
  }

  if (preg_match('/t=((\d+[m|s])?(\d+[s]?)?)/', $video['source'], $matches)) {
    $attributes['start'] = 'start=' . (preg_replace("/[^0-9]/", "", $matches[2]) * 60 + (preg_replace("/[^0-9]/", "", $matches[3])));
  }
  if (!empty($video['start'])) {
    if (preg_match('/((\d+[m|s])?(\d+[s]?)?)/', $video['start'], $matches)) {
      $attributes['start'] = 'start=' . (preg_replace("/[^0-9]/", "", $matches[2]) * 60 + (preg_replace("/[^0-9]/", "", $matches[3])));
    }
  }

  $video['source'] = '//www.youtube.com/embed/' . $video['codec']['matches'][1] . '?' . implode('&amp;', $attributes);

  $params['wmode'] = 'opaque';

  return video_filter_flash($video, $params);
}

/**
 * Callback for Vine codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_vine($video) {
  $video['source'] = '//vine.co/v/' . $video['codec']['matches'][1] . '/embed/simple';

  return video_filter_iframe($video);
}

/**
 * HTML5 callback for YouTube codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_youtube_html5($video) {
  $attributes = array(
    'modestbranding' => !empty($video['modestbranding']) ? 'modestbranding=1' : 'modestbranding=0',
    'html5' => 'html5=1',
    'rel' => $video['related'] ? 'rel=1' : 'rel=0',
    'autoplay' => $video['autoplay'] ? 'autoplay=1' : 'autoplay=0',
    'wmode' => 'wmode=opaque',
    'loop' => !empty($video['loop']) ? 'loop=1' : 'loop=0',
    'controls' => !empty($video['controls']) ? 'controls=1' : (!isset($video['controls']) ? 'controls=1' : 'controls=0'),
    'autohide' => !empty($video['autohide']) ? 'autohide=1' : 'autohide=0',
    'showinfo' => !empty($video['showinfo']) ? 'showinfo=1' : 'showinfo=0',
    'theme' => !empty($video['theme']) ? 'theme=' . $video['theme'] : 'theme=dark',
    'color' => !empty($video['color']) ? 'color=' . $video['color'] : 'color=red',
    'enablejsapi' => !empty($video['enablejsapi']) ? 'enablejsapi=' . (int) $video['enablejsapi'] : 'enablejsapi=0',
  );

  if (!empty($video['loop'])) {
    $attributes['playlist'] = 'playlist=' . $video['codec']['matches'][1];
  }

  if (preg_match('/t=((\d+[m|s])?(\d+[s]?)?)/', $video['source'], $matches)) {
    $attributes['start'] = 'start=' . (preg_replace("/[^0-9]/", "", $matches[2]) * 60 + (preg_replace("/[^0-9]/", "", $matches[3])));
  }
  if (!empty($video['start'])) {
    if (preg_match('/((\d+[m|s])?(\d+[s]?)?)/', $video['start'], $matches)) {
      $attributes['start'] = 'start=' . (preg_replace("/[^0-9]/", "", $matches[2]) * 60 + (preg_replace("/[^0-9]/", "", $matches[3])));
    }
  }

  $video['source'] = '//www.youtube.com/embed/' . $video['codec']['matches'][1] . '?' . implode('&amp;', $attributes);

  return video_filter_iframe($video);
}

/**
 * HTML5 callback for YouTube (Playlist) codec.
 *
 * @see video_filter_codec_info()
 */
function video_filter_youtube_playlist_html5($video) {
  $attributes = array(
    'rel' => $video['related'] ? 'rel=1' : 'rel=0',
    'autoplay' => $video['autoplay'] ? 'autoplay=1' : 'autoplay=0',
    'wmode' => 'wmode=opaque',
  );
  $video['source'] = '//www.youtube.com/embed/videoseries?list=' . $video['codec']['matches'][1] . '&amp;' . implode('&amp;', $attributes);

  return video_filter_iframe($video);
}

/**
 * Callback for Wistia codec.
 *
 * Adapted from the media_wistia module.
 *
 * @see video_filter_codec_info()
 */
function video_filter_wistia_html5($video) {
  $video_code = $video['codec']['matches'][7];
  $matches = $video['codec']['matches'];
  $embed_type = ($matches[4] == 'projects' || $matches[6] == 'playlists') ? 'playlists' : 'iframe';

  // Get embed code via oEmbed.
  $endpoint = 'http://fast.wistia.com/oembed';
  $options = array(
    'url' => "http://fast.wistia.com/embed/{$embed_type}/{$video_code}",
    'width' => $video['width'],
    'height' => $video['height'],
  );
  $data = video_filter_oembed_request($endpoint, $options);
  $html = $data['html'];

  // See if the video source is already an iframe src.
  $pattern = '@https?://fast.wistia.(com|net)/embed/(iframe|playlists)/[a-zA-Z0-9]+\?+.+@';
  $matches = array();
  if (preg_match($pattern, $video['source'], $matches)) {
    // Replace the oEmbed iframe src with that provided in the token, in order
    // to support embed builder URLs.
    $pattern = '@https?://fast.wistia.(com|net)/embed/(iframe|playlists)/[a-zA-Z0-9]+\?[^"]+@';
    $replacement = $matches[0];
    $html = preg_replace($pattern, $replacement, $html);
  }

  return $html;
}
