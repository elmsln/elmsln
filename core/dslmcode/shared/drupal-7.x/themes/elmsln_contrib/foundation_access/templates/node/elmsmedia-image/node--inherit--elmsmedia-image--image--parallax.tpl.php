<figure id="node-<?php print $node->nid; ?>" class="image <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>
  <?php if ($image_lightbox_url): ?>
    <a data-imagelightbox href="<?php print $image_lightbox_url; ?>">
      <div class="image__img parallax-container">
        <div class="parallax"><?php print render($image); ?></div>
      </div>
    </a>
  <?php else: ?>
    <div class="image__img parallax-container">
      <div class="parallax"><?php print render($image); ?></div>
    </div>
  <?php endif; ?>

  <?php if ($image_cite): ?>
  <cite class="image__cite"><?php print render($image_cite); ?></cite>
  <?php endif; ?>

  <?php if ($image_caption): ?>
  <figcaption class="image__caption">
    <?php print render($image_caption); ?>
  </figcaption>
  <?php endif; ?>
</figure>