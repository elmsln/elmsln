<?php

/**
 * @file
 * Displays a list of color swatches.
 *
 * Available variables:
 * - $swatches: An array of color swatches.
 *
 * @see template_preprocess_styleguide_swatch()
 *
 * @ingroup themeable
 */
?>
<div class="styleguide-palette">
<?php if ($empty): ?>
<div class="styleguide-palette-empty">
  <?php print $empty; ?>
</div>
<?php endif; ?>
<?php foreach ($swatches as $swatch): ?>
<div class="styleguide-palette-swatch">
  <?php print $swatch; ?>
</div>
<?php endforeach; ?>
</div>
