<figure id="node-<?php print $node->nid; ?>" class="mediasvg <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_accessible_fallback'])) :?>
    <div class="element-invisible">
      <?php print t('The following media is highly interactive in nature and may not be immediately accessible to you. If you would like a more accessible version of this media please access the next link.');?>
    </div>
    <?php print l(t('Enable more accessible form of this media.'), 'entity_iframe/node/' . $nid . '/accessible_fallback', array('attributes' => array('icon' => 'accessibility'))); ?>
  <?php endif; ?>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>
  <div class="mediasvg__img" aria-hidden="<?php print $svg_aria_hidden; ?>">
  <?php if ($svg_lightbox_url): ?>
      <a data-imagelightbox href="<?php print $svg_lightbox_url; ?>">
        <?php print render($content['field_svg'][0]); ?>
      </a>
  <?php else: ?>
    <?php print render($content['field_svg'][0]); ?>
  <?php endif; ?>
  </div>
  <div class="mediasvg__alttext"><?php print render($svg_alttext); ?></div>
</figure>