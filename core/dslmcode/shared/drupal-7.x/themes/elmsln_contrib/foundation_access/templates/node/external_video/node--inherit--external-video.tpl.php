<?php
  /**
   * For Media Poster, we will add put the poster within the video wrapper to accomidate intrinsic ratio.
   */
  $track = '';
  if (isset($node->field_caption['und'][0]['uri'])) {
    $track = '<track label="English" kind="subtitles" srclang="en" default src="' . file_create_url(str_replace('.xml', '.vtt', $node->field_caption['und'][0]['uri'])) . '"/>';
  }
  // @TODO HACK UNTIL VIDEO PLAYER CAN DO THESE THINGS
  /*$url = $content['field_external_media']['#items'][0]['video_url'];
  if (strpos($url, 'youtube.com') !== FALSE) {
    if (strpos($url, 'https://www.youtube.com/watch?v=') === 0) {
      print '
      <iframe
      width="640"
      height="420"
      src="https://www.youtube-nocookie.com/embed/' . str_replace('https://www.youtube.com/watch?v=','', $url) . '"
      title="YouTube video player"
      frameborder="0"
      allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
      allowfullscreen></iframe>';
    }
    else {
      print '
      <p><a href="' . $url . '"
        target="_blank"
        rel="noopener noreferrer"
        >Trouble playing video? Click to open in new window</a></p>';
      }
    }
  else {*/
?>
  <video-player
 id="node-<?php print $node->nid; ?>"
 source="<?php print $content['field_external_media']['#items'][0]['video_url']; ?>"
 class="iframe <?php print $classes; ?>"
 accent-color="red"
 sticky-corner="none"
 crossorigin="anonymous"
 <?php print $attributes; ?>>
  <video crossorigin="anonymous"><?php print $track;?></video>
</video-player>
<?php //} ?>