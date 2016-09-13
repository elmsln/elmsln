<div class="elmsln-image-gallery-wrapper rp-wrapper">
  <div class="image-compare">
  <?php foreach ($images as $key => $image) : ?>
    <div class="resizable ui-widget-content comparison-image-<?php print $key;?>" style="background-image:url('<?php print file_create_url($image['#item']['uri']);?>')"></div>
  <?php endforeach; ?>
  </div>
</div>