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
?>
<video-player
 id="node-<?php print $node->nid; ?>"
 <?php print $poster; ?>
 class="iframe <?php print $classes; ?>"
 <?php print $video; ?>
 <?php print $track;?>
 accent-color="red"
 sticky-corner="none"
 crossorigin="anonymous"
 <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>>
</video-player>