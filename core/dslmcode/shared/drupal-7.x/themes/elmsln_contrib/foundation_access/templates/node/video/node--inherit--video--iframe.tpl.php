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
 id="node-<?php print $nid;?>"
 <?php print $poster; ?>
 class="entity_iframe entity_iframe_node entity_iframe_tool_elmsmedia elmsmedia_video <?php print $classes; ?>"
 accent-color="red"
 sticky-corner="none"
 crossorigin="anonymous"
 <?php print $video; ?>
 <?php print $track;?>
 <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>>

</video-player>