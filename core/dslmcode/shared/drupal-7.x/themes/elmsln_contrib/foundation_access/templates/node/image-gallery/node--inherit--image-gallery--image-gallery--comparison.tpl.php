<div class="elmsln-image-gallery-wrapper rp-wrapper">
  <div class="image-compare">
  <?php foreach ($images as $key => $image) : ?>
    <?php if ($key == 0) : ?>
      <div class="comparison-image-<?php print ($key + 1);?>" style="background-image:url('<?php print file_create_url($image['#item']['uri']);?>')"></div>
    <?php elseif ($key < 2) : ?>
    <div class="resizable ui-widget-content comparison-image-<?php print ($key + 1);?>" style="background-image:url('<?php print file_create_url($image['#item']['uri']);?>')"></div>
    <?php endif; ?>
  <?php endforeach; ?>
  </div>
</div>