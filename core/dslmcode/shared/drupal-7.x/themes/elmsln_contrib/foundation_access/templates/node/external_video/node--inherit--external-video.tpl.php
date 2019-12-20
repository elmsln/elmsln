<?php
/**
 * For Media Poster, we will add put the poster within the video wrapper to accomidate intrinsic ratio.
 */
  $track = '';
  if (isset($node->field_caption['und'][0]['uri'])) {
    $track = file_create_url(str_replace('.xml', '.vtt', $node->field_caption['und'][0]['uri']));
  }
?>
<video-player
 id="node-<?php print $node->nid; ?>"
 source="<?php print $content['field_external_media']['#items'][0]['video_url']; ?>"
 class="iframe <?php print $classes; ?>"
 accent-color="red"
 sticky-corner="none"
 track="<?php print $track;?>"
 crossorigin="anonymous"
 <?php print $attributes; ?>>
</video-player>
