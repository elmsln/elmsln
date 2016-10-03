<div class="elmsln-image-gallery-wrapper elmsln-basic-gallery">
  <div class="row">
      <div class="col s12 center-align">
        <a id="<?php print $featured_image_id;?>" data-imagelightbox class="elmsln-featured-image" href="<?php print $image_lightbox_url[0];?>">
          <?php print render($images[0]); ?>
          <div class="elmsln-featured-image-title"><?php print $images[0]['entity']->title; ?></div>
        </a>
      </div>
  </div>
  <div class="container">
    <div class="row">
      <?php foreach ($images as $key => $image) : ?>
        <div class="col s1 elmsln-gallery-image image__img">
          <a href="#<?php print $image_lightbox_url[$key];?>" class="tooltipped" data-position="bottom" data-delay="50" data-tooltip="<?php print $image['entity']->title;?>" data-elmsln-triggers="<?php print $featured_image_id;?>" data-elmsln-lightbox="<?php print $image_lightbox_url[$key];?>">
            <?php print render($image); ?>
          </a>
        </div>
        <?php endforeach; ?>
    </div>
  </div>
</div>
