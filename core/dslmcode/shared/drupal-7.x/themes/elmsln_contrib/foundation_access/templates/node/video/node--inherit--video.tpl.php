<?php
  $poster = '';
  if (isset($node->field_poster['und'][0]['uri'])) {
    $poster = ' thumbnail-src="' . file_create_url($node->field_poster['und'][0]['uri']) . '"';
  }
  $video = '';
  if (isset($node->field_video['und'][0]['uri'])) {
    $video = ' source="'. file_create_url($node->field_video['und'][0]['uri']) .'"';
  }
  $track = '';
  if (isset($node->field_caption['und'][0]['uri'])) {
    $track = ' track="' . file_create_url(str_replace('.xml', '.vtt', $node->field_caption['und'][0]['uri'])) . '"';
  }
  // @TODO HACK UNTIL VIDEO PLAYER CAN DO THESE THINGS
  /*$url = $node->field_video['und'][0]['uri'];
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
 <?php print $poster; ?>
 class="iframe <?php print $classes; ?>"
 <?php print $track;?>
 <?php print $video; ?>
 accent-color="red"
 sticky-corner="none"
 crossorigin="anonymous"
 <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>>
</video-player>
<?php //} ?>