<figure id="node-<?php print $node->nid; ?>" class="mediasvg <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_accessible_fallback'])) :?>
    <div class="element-invisible">
      <?php print t('The following media is highly interactive in nature and may not be immediately accessible to you. If you would like a more accessible version of this media please access the next link.');?>
    </div>
    <?php print l(t('Enable more accessible form of this media.'), 'entity_iframe/node/' . $nid . '/accessible_fallback');?>
  <?php endif; ?>
  <?php if (isset($content['field_figurelabel_ref'])): ?>
    <?php print render($content['field_figurelabel_ref'][0]); ?>
  <?php endif; ?>
  <div class="mediasvg__img" aria-hidden="<?php print $svg_aria_hidden; ?>">
    <?php print render($content['field_svg'][0]); ?>
  </div>
  <div class="mediasvg__alttext"><?php print render($svg_alttext); ?></div>
</figure>