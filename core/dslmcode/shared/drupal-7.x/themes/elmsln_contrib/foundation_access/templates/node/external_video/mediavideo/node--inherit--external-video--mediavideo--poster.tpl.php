<?php
/**
 * For Media Poster, we will add put the poster within the video wrapper to accomidate intrinsic ratio.
 */
?>
<media-video>
<figure id="node-<?php print $node->nid; ?>" class="mediavideo <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>

  <?php if ($thumbnail): ?>
    <a href="#close-dialog" class="mediavideo__close icon-close-black" title="Click to stop and close video."></a>
  <?php endif; ?>

  <div class="mediavideo__video-wrapper">
    <?php if ($video_url && $poster): ?>
      <iframe src="<?php print _elmsln_api_video_url($video_url); ?>" data-mediavideo-src="<?php print _elmsln_api_video_url($video_url); ?>" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen <?php if (isset($competency)): ?>data-course-competency="<?php print $competency;?>"<?php endif;?>></iframe>
    <?php else: ?>
      <?php print render($content); ?>
    <?php endif; ?>

    <?php if ($poster): ?>
    <aside class="mediavideo__poster mediavideo-button-container mediavideo-button-display">
      <a tabindex="-1" href="#play-video" class="mediavideo__open" title="<?php print t('Press to start video');?>">
        <paper-button class="mediavideo-button center">
        <img src="<?php print $poster; ?>" class="poster--image" />
          <iron-icon icon="av:play-circle-outline" class="mediavideo-icon"></iron-icon>
        </paper-button>
      </a>
    </aside>
    <?php endif; ?>
  </div>
  <?php if (isset($duration)): ?>
    <div class="mediavideo__duration">
      <?php print $duration; ?>
    </div>
  <?php endif; ?>
</figure>
</media-video>
