<?php

/**
 * @file
 * Devel generate support for video_embed_field module.
 */

// The Youtube’s API url.
define('YT_API_URL', 'http://gdata.youtube.com/feeds/api/videos?q=');

/**
 * Devel generate plugin definition.
 */
function video_embed_field_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_video_embed_field_devel_generate', $object, $field, $instance, $bundle);
  }
  else {
    return _video_embed_field_devel_generate($object, $field, $instance, $bundle);
  }
}

/**
 * Generates a random video_embed_field item.
 *
 * @param object $object
 *   The devel_generate object.
 * @param array $field
 *   The field definition.
 * @param array $instance
 *   The field instance definition.
 * @param array $bundle
 *   The bundle definition.
 *
 * @return array
 *   The video_embed_field item.
 */
function _video_embed_field_devel_generate($object, $field, $instance, $bundle) {
  $video = video_embed_field_retrieve_video();
  $object_field = array();
  $object_field['video_url'] = $video['video_url'];
  if ($instance['settings']['description_field']) {
    $object_field['description'] = $video['description'];
  }
  return $object_field;
}

/**
 * Retrieves a random youtube video info from the bunch.
 *
 * @return array
 *   The video definition.
 */
function video_embed_field_retrieve_video() {
  $videos = video_embed_field_generate_videos();
  return $videos[array_rand($videos)];
}

/**
 * Generates a pseudo random bunch of youtube videos.
 *
 * @return array
 *   A bunch of youtube videos.
 */
function video_embed_field_generate_videos() {
  $videos = &drupal_static(__FUNCTION__);
  if (!isset($videos)) {
    $videos = array();

    // Create random video seed.
    $video_id = user_password(2);

    // Using cURL php extension to make the request to youtube API.
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, YT_API_URL . $video_id);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    // $feed holds a rss feed xml returned by youtube API.
    $feed = curl_exec($ch);
    curl_close($ch);

    // Using SimpleXML to parse youtube’s feed.
    $xml = simplexml_load_string($feed);
    foreach ($xml->entry as $entry) {
      $videos[] = array(
        'video_url' => $entry->children('media', TRUE)->group->player->attributes()->url,
        'description' => $entry->title,
      );
    }
    if (empty($videos)) {
      video_embed_field_generate_videos();
    }
  }
  return $videos;
}
