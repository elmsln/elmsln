<figure id="node-<?php print $node->nid; ?>" class="mediasvg <?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="mediasvg__img" aria-hidden="<?php print $svg_aria_hidden; ?>">
  	<?php print render($svg); ?>
  </div>
  <div class="mediasvg__alttext"><?php print render($svg_alttext); ?></div>
</figure>