<?php

/**
 * @file
 *
 * Available variables:
 * - $id: The swatch ID.
 * - $name: The swatch name.
 * - $description: The swatch description.
 * - $hex: The swatch hex value.
 *
 * @ingroup themeable
 */
?>
<div class="styleguide-palette-swatch-color" style="background-color: <?php print $hex; ?>;">&nbsp;</div>
<h3 class="styleguide-palette-swatch-name"><?php print $name; ?></h3>
<div class="styleguide-palette-swatch-hex"><em><?php print $hex; ?></em></div>
<div class="styleguide-palette-swatch-description"><?php print $description; ?></div>
