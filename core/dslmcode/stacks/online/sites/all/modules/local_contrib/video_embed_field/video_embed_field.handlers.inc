<?php
/**
 *  Provide some handlers for video embed field
 *  Other modules can implement the hook_video_embed_handler_info to provide more handlers
 */


/**
 *  Implementation of hook_video_embed_handler_info
 */
function video_embed_field_video_embed_handler_info() {
  $handlers = array();

  $handlers['youtube'] = array(
    'title' => 'Youtube',
    'function' => 'video_embed_field_handle_youtube',
    'thumbnail_function' => 'video_embed_field_handle_youtube_thumbnail',
    'data_function' => 'video_embed_field_handle_youtube_data',
    'form' => 'video_embed_field_handler_youtube_form',
    'domains' => array(
      'youtube.com',
      'youtu.be'
    ),
    'defaults' => array(
      'width' => '640px',
      'height' => '360px',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'autohide' => 2,
      'showinfo' => 1,
      'modestbranding' => 0,
      'theme' => 'dark',
      'iv_load_policy' => 1,
    ),
  );

  $handlers['vimeo'] = array(
    'title' => 'Vimeo',
    'function' => 'video_embed_field_handle_vimeo',
    'thumbnail_function' => 'video_embed_field_handle_vimeo_thumbnail',
    'data_function' => 'video_embed_field_handle_vimeo_data',
    'form' => 'video_embed_field_handler_vimeo_form',
    'domains' => array(
      'vimeo.com'
    ),
    'defaults' => array(
      'width' => '640px',
      'height' => '360px',
      'color' => '00adef',
      'portrait' => 1,
      'title' => 1,
      'byline' => 1,
      'autoplay' => 0,
      'loop' => 0,
    ),
  );

  return $handlers;
}

/**
 *  Helper function to get the youtube video's id
 *  Returns false if it doesn't parse for wahtever reason
 */
function _video_embed_field_get_youtube_id($url){
  // Find the ID of the video they want to play from the url
  if (stristr($url, 'http://')) {
    $url = substr($url, 7);
  }
  else if (stristr($url, 'https://')) {
    $url = substr($url, 8);
  }

  if(stristr($url, 'playlist')){
    //Playlists need the appended ampersand to take the options properly.
    $url = $url . '&';
    $pos = strripos($url, '?list=');
    if($pos!==FALSE){
      $pos2 = stripos($url, '&');
      $pos2++;
    }
    else{
      return FALSE;
    }
  }
  //Alternate playlist link
  else if(stristr($url, 'view_play_list')){
    $url = $url . '&';
    //All playlist ID's are prepended with PL. view_play_list links allow you to not have that, though.
    if(!stristr($url, '?p=PL')){
      $url = substr_replace($url, 'PL', strpos($url, '?p=') + 3, 0);
    }
    //Replace the links format with the embed format
    $url = str_ireplace('play_list?p=', 'videoseries?list=', $url);
    $pos = strripos($url, 'videoseries?list=');
    if($pos !== FALSE){
      $pos2 = stripos($url, '&');
      $pos2++;
    }
    else{
      return FALSE;
    }
  }
  else{
    $pos = strripos($url, 'v=');
    if ($pos!== FALSE) {
      $pos += 2;
      $pos2 = stripos($url, '&', $pos);
      $pos_hash = stripos($url, '#', $pos);

      $pos2 = _video_embed_get_min($pos2, $pos_hash);
    }
    else {
      $pos = strripos($url, '/');
      if ($pos !== FALSE) {
        $pos++;
        $pos2 = stripos($url, '?', $pos);
        $pos_hash = stripos($url, '#', $pos);

        $pos2 = _video_embed_get_min($pos2, $pos_hash);
      }
    }
  }
  if ($pos === FALSE) {
    return FALSE;
  }
  else {
    if ($pos2 > 0) {
      $id = substr($url, $pos, $pos2 - $pos);
    }
    else {
      $id = substr($url, $pos);
    }
  }
  return $id;
}

/**
 * Handler for Youtube videos.
 */
function video_embed_field_handle_youtube($url, $settings) {
  $output = array();

  //Grab the minutes and seconds, and just convert it down to seconds
  preg_match('/#t=((?P<min>\d+)m)?((?P<sec>\d+)s)?/', $url, $matches);

  //Give it some default data in case there is no #t=...
  $matches += array(
  	"min" => 0,
  	"sec" => 0,
  );
  $time = ($matches["min"] * 60) + $matches["sec"];
  $settings['start'] = $time;

  $id = _video_embed_field_get_youtube_id($url);
  if (!$id) {
    // We can't decode the URL - just return the URL as a link
    $output['#markup'] = l($url, $url);
    return $output;
  }
  // Construct the embed code
  $settings['wmode'] = 'opaque';
  $settings_str = _video_embed_code_get_settings_str($settings);

  $output['#markup'] = '<iframe width="' . $settings['width'] . '" height="' . $settings['height'] . '" src="//www.youtube.com/embed/' . $id . '?' . $settings_str . '" frameborder="0" allowfullscreen></iframe>';

  return $output;
}

/**
 *  Get the thumbnail url for youtube videos
 */
function video_embed_field_handle_youtube_thumbnail($video_url){
  $info = array();

  $id = _video_embed_field_get_youtube_id($video_url);

  //Playlist
  if(stristr($id, '?list=')){
    //Strip out all but the ID, including the PL behind the ID.
    $start = strpos($id, '?list=PL') + 8;
    $length = strpos($id, '&') - $start;
    $id = substr($id, $start, $length);
    $info['id'] = $id;
    //Playlist info is stored in XML. The thumbnail is in there.
    $xml = drupal_http_request('http://gdata.youtube.com/feeds/api/playlists/' . $id);
    if(!isset($xml->error)){
      $xml = new SimpleXMLElement($xml->data);
      $media = $xml->children('http://search.yahoo.com/mrss/');
      if($media->group->thumbnail && $media->group->thumbnail[0]->attributes()){
        $attrs = $media->group->thumbnail[0]->attributes();
        $info['url'] = (string)$attrs['url'];
      }
    }
  }
  //Regular video
  else if($id) {
    $info['id'] = $id;
    $info['url'] = 'http://img.youtube.com/vi/'.$id.'/0.jpg';
  }
  return $info;
}

 /**
 * Get video data for a YouTube video URL
 *
 * @param string $url
 *   A YouTube video URL to get data for
 *
 * @return array|false $data
 *   An array of video data, or FALSE if unable to fetch data
 */
function video_embed_field_handle_youtube_data($url) {
  $data = array();

  // Get YouTube video ID from URL
  $id = _video_embed_field_get_youtube_id($url);

  if ($id) {
    $response = drupal_http_request('http://gdata.youtube.com/feeds/api/videos/' . $id . '?v=2&alt=json');
    if (!isset($response->error)) {
      $data = json_decode($response->data);
      $data = (array) $data->entry;
      return _video_embed_field_clean_up_youtube_data($data);
    }
  }

  return FALSE;
}

/**
 *  Flatten out some unnecessary nesting in the youtube data
 */
function _video_embed_field_clean_up_youtube_data($data) {
  //make things a bit nicer for people trying to use the data
  foreach ($data as $key => $value) {
    if (is_object($value)) {
      $temp = (array)$value;
      if (isset($temp['$t'])) {
        $data[$key] = $temp['$t'];
      } else {
        $data[$key] = _video_embed_field_clean_up_youtube_data($temp);
      }
    } else if (is_array($value)) {
      $data[$key] = _video_embed_field_clean_up_youtube_data($value);
    }

    if($key === 'category') {
      $terms = array();
      foreach ($data[$key] as $value) {
        if(isset($value['scheme']) && $value['scheme'] == 'http://schemas.google.com/g/2005#kind') {
          continue;
        }

        if(isset($value['term'])) {
          $terms[] = $value['term'];
        }
      }
      $data['terms'] = $terms;
    }
  }
  return $data;
}

/**
 * Defines the form elements for the Youtube configuration form.
 */
function video_embed_field_handler_youtube_form($defaults) {
  $form = array();

  $form['width'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Player Width'),
    '#description' => t('The width of the youtube player.'),
    '#default_value' => $defaults['width'],
  );
  $form['height'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Player Height'),
    '#description' => t('The height of the youtube player.'),
    '#default_value' => $defaults['height'],
  );
  $form['theme'] = array(
    '#type' => 'select',
    '#options' => array(
      'dark' => t('Dark'),
      'light' => t('Light'),
    ),
    '#title' => t('Player theme'),
    '#default_value' => $defaults['theme'],
  );
  $form['autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autoplay'),
    '#description' => t('Play the video immediately.'),
    '#default_value' => $defaults['autoplay'],
  );
  $form['hd'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use HD'),
    '#description' => t('Attempt to play the video in HD if available.'),
    '#default_value' => $defaults['hd'],
  );
  $form['rel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show related videos'),
    '#description' => t('Show related videos after the video is finished playing.'),
    '#default_value' => $defaults['rel'],
  );
  $form['showinfo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show info'),
    '#description' => t('Display information like the video title and rating before the video starts playing.'),
    '#default_value' => $defaults['showinfo'],
  );
  $form['modestbranding'] = array(
  	'#type' => 'checkbox',
  	'#title' => t('Hide Youtube logo'),
  	'#description' => t('Hide the Youtube logo button on the player'),
  	'#default_value' => $defaults['modestbranding']
  );
  $form['iv_load_policy'] = array(
    '#type' => 'radios',
    '#options' => array(
      1 => t('Show video annotations.'),
      3 => t('Hide video annotations.'),
    ),
    '#title' => t('Display annotations'),
    '#description' => t('Controls the display of annotations over the video content. Only works when using the flash player.'),
    '#default_value' => $defaults['iv_load_policy'],
  );
  $form['autohide'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('The video progress bar and player controls will be visible throughout the video.'),
      1 => t('Automatically slide the video progress bar and the player controls out of view a couple of seconds after the video starts playing. They will only reappear if the user moves her mouse over the video player or presses a keyboard key.'),
      2 => t('The video progress bar will fade out but the player controls (play button, volume control, etc.) remain visible.'),
    ),
    '#title' => t('Autohide progress bar and the player controls'),
    '#description' => t('Controls the autohide behavior of the youtube player controls.'),
    '#default_value' => $defaults['autohide'],
  );

  return $form;
}

/**
 * Helper function to get the Vimeo video's ID
 *
 * @param string $url
 *   A Vimeo video URL to get the ID of
 *
 * @return integer|false $id
 *   The video ID, or FALSE if unable to get the video ID
 */
function _video_embed_field_get_vimeo_id($url){
  $pos = strripos($url, '/');
  if ($pos != FALSE) {
    $pos += 1;
    return (int) substr($url, $pos);
  }
  return FALSE;
}

/**
 * Handler for Vimeo videos.
 */
function video_embed_field_handle_vimeo($url, $settings) {
  // Get ID of video from URL
  $id = _video_embed_field_get_vimeo_id($url);
  if (!$id) {
    return array(
      '#markup' => l($url, $url),
    );
  }

  // Construct the embed code
  $settings['portrait'] = 0;
  $settings_str = _video_embed_code_get_settings_str($settings);

  return array(
    '#markup' => '<iframe width="' . $settings['width'] . '" height="' . $settings['height'] . '" src="//player.vimeo.com/video/' . $id .
                 '?' . $settings_str . '" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowfullscreen></iframe>',
  );
}

/**
 *  Get the thumbnail url for youtube videos
 */
function video_embed_field_handle_vimeo_thumbnail($url){
    // Get ID of video from URL
  $id = _video_embed_field_get_vimeo_id($url);
  $info = array(
    'id' => $id,
  );
  $response = drupal_http_request('http://vimeo.com/api/v2/video/' . $id . '.php');
  if (!isset($response->error)) {
    $response = unserialize($response->data);
    $video = current($response);

    $image_url = $video['thumbnail_large'];
    $info['url'] = $image_url;
  }
  return $info;
}

/**
 * Get video data for a Vimeo video URL
 *
 * @param string $url
 *   A Vimeo video URL to get data for
 *
 * @return array|false $data
 *   An array of video data, or FALSE if unable to fetch data
 */
function video_embed_field_handle_vimeo_data($url) {
  // Get ID of video from URL
  $id = _video_embed_field_get_vimeo_id($url);
  if ($id) {
    $response = drupal_http_request('http://vimeo.com/api/v2/video/' . $id . '.php');
    if (!isset($response->error)) {
      $response = unserialize($response->data);
      return (array) current($response);
    }
  }
  return FALSE;
}

/**
 * Defines the form elements for the Vimeo configuration form.
 */
function video_embed_field_handler_vimeo_form($defaults) {
  $form = array();

  $form['width'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Player Width'),
    '#description' => t('The width of the vimeo player.'),
    '#default_value' => $defaults['width'],
  );
  $form['height'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Player Height'),
    '#description' => t('The height of the vimeo player.'),
    '#default_value' => $defaults['height'],
  );
  $form['color'] = array(
    '#type' => 'select',
    '#options' => array(
      '00adef' => t('Blue'),
      'ff9933' => t('Orange'),
      'c9ff23' => t('Lime'),
      'ff0179' => t('Fuschia'),
      'ffffff' => t('White')
    ),
    '#title' => t('Player Color'),
    '#description' => t('The color to use on the vimeo player.'),
    '#default_value' => $defaults['color'],
  );
  $form['portrait'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overlay Author Thumbnail'),
    '#description' => t('Overlay the author\'s thumbnail before the video is played.'),
    '#default_value' => $defaults['portrait'],
  );
  $form['title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overlay Video\'s Title'),
    '#description' => t('Overlay the video\'s title before the video is played.'),
    '#default_value' => $defaults['title'],
  );
  $form['byline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overlay Video\'s Byline'),
    '#description' => t('Overlay the video\'s description before the video is played.'),
    '#default_value' => $defaults['byline'],
  );
  $form['overridable'] = array (
    '#prefix' => '<p class="note"><strong>'.t('Note').': </strong><em>',
    '#markup' => t('Color, portrait, title and byline can be restricted by Vimeo Plus videos.
      Such videos will ignore these settings.'),
    '#suffix' => '</em></p>',
  );
  $form['autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autoplay'),
    '#description' => t('Play the video immediately.'),
    '#default_value' => $defaults['autoplay'],
  );
  $form['loop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Loop'),
    '#description' => t('Loop the video\'s playback'),
    '#default_value' => $defaults['loop'],
  );
  return $form;
}

/**
 *  Calculate the min index for use in finding the id of a youtube video
 */
function _video_embed_get_min($pos1, $pos2) {
  if(!$pos1) {
    return $pos2;
  } else if(!$pos2) {
    return $pos1;
  } else {
    return min($pos1, $pos2);
  }
}
