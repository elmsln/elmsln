<?php
/**
 * For Media Poster, we will add put the poster within the video wrapper to accomidate intrinsic ratio.
 */
?>
<video-player
 id="node-<?php print $node->nid; ?>"
 source="<?php print $content['field_external_media']['#items'][0]['video_url']; ?>"
 class="iframe <?php print $classes; ?>"
 accent-color="red"
 sticky-corner="none"
 <?php print $attributes; ?>></video-player>
