<figure id="node-<?php print $node->nid; ?>" class="image <?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="card">
    <div class="card-image waves-effect waves-block waves-light">
      <?php print render($image); ?>
    </div>
    <div class="card-content">
      <span class="card-title activator grey-text text-darken-4"><?php print $title; ?><i class="material-icons right">more_vert</i></span>
      <p><?php print render($image_caption); ?></p>
    </div>
    <div class="card-reveal">
      <span class="card-title grey-text text-darken-4"><?php print $title; ?><i class="material-icons right"><?php print t('close');?></i></span>
      <p><?php print render($image_cite); ?></p>
    </div>
  </div>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>
</figure>