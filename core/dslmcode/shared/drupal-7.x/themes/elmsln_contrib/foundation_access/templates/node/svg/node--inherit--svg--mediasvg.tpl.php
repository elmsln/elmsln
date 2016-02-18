<figure id="node-<?php print $node->nid; ?>" class="mediasvg <?php print $classes; ?>"<?php print $attributes; ?>>
	<?php if (isset($content['field_figurelabel_ref'])): ?>
	  <?php print render($content['field_figurelabel_ref']); ?>
	<?php endif; ?>
  <div class="mediasvg__img" aria-hidden="<?php print $svg_aria_hidden; ?>">
  	<?php print render($content['field_svg'][0]); ?>
  </div>
  <div class="mediasvg__alttext"><?php print render($svg_alttext); ?></div>
</figure>