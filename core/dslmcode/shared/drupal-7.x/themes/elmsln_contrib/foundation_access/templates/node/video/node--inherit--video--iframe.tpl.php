<?php
  $poster = '';
  if (isset($node->field_poster['und'][0]['uri'])) {
    $poster = file_create_url($node->field_poster['und'][0]['uri']);
  }
  $video = '';
  if (isset($node->field_video['und'][0]['uri'])) {
    $video = file_create_url($node->field_video['und'][0]['uri']);
  }
  $track = '';
  if (isset($node->field_caption['und'][0]['uri'])) {
    $track = file_create_url($node->field_caption['und'][0]['uri']);
  }
?>
<video-player
 id="node-<?php print $nid;?>"
 thumbnail-src="<?php print $poster; ?>"
 source="<?php print $video; ?>"
 class="entity_iframe entity_iframe_node entity_iframe_tool_elmsmedia elmsmedia_video <?php print $classes; ?>"
 accent-color="red"
 sticky-corner="none"
 track="<?php print $track;?>"
 crossorigin="anonymous"
 <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>>
</video-player>