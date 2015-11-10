<figure id="node-<?php print $node->nid; ?>" class="mediasvg <?php print $classes; ?>"<?php print $attributes; ?>>
  <img class="mediasvg__img" aria-hidden="<?php print $svg_aria_hidden; ?>" src="<?php print $svg_url; ?>">
  <div class="mediasvg__alttext"><?php print render($svg_alttext); ?></div>
</figure>