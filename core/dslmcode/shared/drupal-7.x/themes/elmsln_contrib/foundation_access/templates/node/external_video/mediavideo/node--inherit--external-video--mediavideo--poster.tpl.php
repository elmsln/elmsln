<?php
/**
 * For Media Poster, we will add put the poster within the video wrapper to accomidate intrinsic ratio.
 */
?>
<figure id="node-<?php print $node->nid; ?>" class="mediavideo <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>

  <?php if ($thumbnail): ?>
    <a href="#" class="mediavideo__close icon-close-black" title="Click to stop and close video."></a>
  <?php endif; ?>

  <div class="mediavideo__video-wrapper">
    <?php if ($video_url && $poster): ?>
      <iframe src="<?php print _foundation_access_video_url($video_url); ?>" data-mediavideo-src="<?php print _foundation_access_video_url($video_url); ?>" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
    <?php else: ?>
      <?php print render($content); ?>
    <?php endif; ?>

    <?php if ($poster): ?>
    <aside class="mediavideo__poster">
      <img src="<?php print $poster; ?>">
      <a class="mediavideo__open icon-play-black" href="#" title="Click to view video."></a>
    </aside>
    <?php endif; ?>
  </div>
</figure>