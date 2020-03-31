<?php
  /**
   * For Media Poster, we will add put the poster within the video wrapper to accomidate intrinsic ratio.
   */
  $video = '';
  if (isset($node->field_video['und'][0]['uri'])) {
    $video = ' source="'. file_create_url($node->field_video['und'][0]['uri']) .'"';
  }
  $track = '';
  if (isset($node->field_caption['und'][0]['uri'])) {
    $track = ' track="' . file_create_url(str_replace('.xml', '.vtt', $node->field_caption['und'][0]['uri'])) . '"';
  }
  $poster = '';
  if (isset($node->field_poster['und'][0]['uri'])) {
    $poster = ' thumbnail-src="' . file_create_url($node->field_poster['und'][0]['uri']) . '"';
  }
?>
<figure id="node-<?php print $node->nid; ?>" class="mediavideo <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>
  <div>
    <?php if ($video_url): ?>
      <video-player
      crossorigin="anonymous"
      id="node-<?php print $node->nid; ?>"
      <?php print $poster;?>
      <?php print $video; ?>
      <?php print $track;?>
      source="<?php print _elmsln_api_video_url($video_url); ?>"
      class="iframe"
      accent-color="red"
      sticky-corner="none"
      <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>>
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
