<div class="elmsln-image-gallery-wrapper">
  <div class="row">
  <?php foreach ($images as $key => $image) : ?>
    <div class="col s6 m4 l3 elmsln-gallery-image">
    <?php if (isset($image_lightbox_url)): ?>
      <div class="image__img">
        <a data-imagelightbox href="<?php print $image_lightbox_url[$key]; ?>">
          <?php print render($image); ?>
        </a>
      </div>
    <?php else: ?>
      <div class="image__img">
        <?php print render($image); ?>
      </div>
    <?php endif; ?>
    </div>
  <?php endforeach; ?>
  </div>
</div>