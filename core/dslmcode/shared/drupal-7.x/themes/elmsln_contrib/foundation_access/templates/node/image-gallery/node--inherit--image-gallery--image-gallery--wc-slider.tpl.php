<div class="elmsln-image-gallery-wrapper">
  <div>
<?php
foreach ($images as $key => $image) {
  if ($key == 0) {
    $image1 = file_create_url($image['#item']['uri']);
  }
  elseif ($key < 2) {
    $image2 = file_create_url($image['#item']['uri']);
  }
}
?>
    <image-compare-slider title="<?php print $title;?>" top-src="<?php print $image1; ?>" bottom-src="<?php print $image2; ?>"></image-compare-slider>
  </div>
</div>