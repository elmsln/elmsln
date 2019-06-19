<?php
/**
 * For Media Poster, we will add put the poster within the video wrapper to accomidate intrinsic ratio.
 */
  $track = '';
  if (isset($node->field_caption['und'][0]['uri'])) {
    $track = '<track
  src="' . file_create_url($node->field_caption['und'][0]['uri']) . '"
  kind="subtitles"
  label="English"
  slot="track">';
  }
?>
<video-player
 id="node-<?php print $node->nid; ?>"
 source="<?php print $content['field_external_media']['#items'][0]['video_url']; ?>"
 class="iframe <?php print $classes; ?>"
 accent-color="red"
 sticky-corner="none"
 <?php print $attributes; ?>>
<?php print $track;?>
</video-player>
