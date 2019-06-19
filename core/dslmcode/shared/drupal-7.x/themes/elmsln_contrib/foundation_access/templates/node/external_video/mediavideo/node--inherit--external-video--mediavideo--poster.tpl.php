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
<media-video>
<figure id="node-<?php print $node->nid; ?>" class="mediavideo <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>
  <div>
    <?php if ($video_url): ?>
      <video-player
      id="node-<?php print $node->nid; ?>"
      thumbnail-src="<?php print $poster;?>"
      source="<?php print _elmsln_api_video_url($video_url); ?>"
      class="iframe"
      accent-color="red"
      sticky-corner="none"
      <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>>
      <?php print $track;?>
    </video-player>
    <?php else: ?>
      <?php print render($content); ?>
    <?php endif; ?>
  </div>
  <?php if (isset($duration)): ?>
    <div class="mediavideo__duration">
      <?php print $duration; ?>
    </div>
  <?php endif; ?>
</figure>
</media-video>
