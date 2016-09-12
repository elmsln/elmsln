<figure id="node-<?php print $node->nid; ?>" class="image <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>
  <div class="card <?php print $card_size;?>">
    <div class="card-image waves-effect waves-block waves-light">
      <?php if ($image_lightbox_url): ?>
      <a data-imagelightbox href="<?php print $image_lightbox_url; ?>">
        <?php print render($image); ?>
      </a>
      <?php else:
        print render($image);
      endif; ?>
    </div>
    <div class="card-content">
      <span class="card-title activator grey-text text-darken-4"><?php print $title; ?><?php if (!empty($image_cite)) : ?><i class="material-icons right">more_vert</i></span><?php endif; ?>
      <?php if (!empty($image_caption)) : ?>
      <p><?php print render($image_caption); ?></p>
      <?php endif; ?>
    </div>
    <?php if (!empty($image_cite)) : ?>
    <div class="card-reveal">
      <span class="card-title grey-text text-darken-4"><?php print $title; ?><i class="material-icons right"><?php print t('close');?></i></span>
      <p><?php print render($image_cite); ?></p>
    </div>
    <?php endif; ?>
  </div>
</figure>