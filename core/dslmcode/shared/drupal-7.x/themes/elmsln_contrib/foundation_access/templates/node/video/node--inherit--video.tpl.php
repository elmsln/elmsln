<?php
  $poster = '';
  if (isset($node->field_poster['und'][0]['uri'])) {
    $poster = file_create_url($node->field_poster['und'][0]['uri']);
  }
  $video = '';
  if (isset($node->field_video['und'][0]['uri'])) {
    $video = file_create_url($node->field_video['und'][0]['uri']);
  }
  $tracks = array();
  if (isset($node->field_caption['und'][0]['uri'])) {
    $tracks[] = array(
      'src' => file_create_url($node->field_caption['und'][0]['uri']),
      'label' => 'English',
      'srclang' => 'en',
      'kind' => 'subtitles',
    );
  }
?>
<video-player
 id="node-<?php print $node->nid; ?>"
 thumbnail-src="<?php print $poster; ?>"
 source="<?php print $video; ?>"
 class="iframe <?php print $classes; ?>"
 accent-color="red"
 sticky-corner="none"
 tracks='<?php print json_encode($tracks); ?>'
 <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>>
</video-player>