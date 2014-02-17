<?php

/**
 * @file
 * Theme template to theme the region highlights which appear on the report
 * page and the question overview page
 * @param $top
 *     INT - Top left corner of the region relative to top left of the image
 * @param $leftpx
 *     INT - Left side of the region relative to top left of the image
 * @param @width
 *     INT - Width of the region in px
 * @param $height
 *     INT - Height of the region in px
 * @param $identifier
 *     STRING - Identifier for that region (a number starting with 1)
 */
?>
<div style="background: none repeat scroll 0% 0% blue; z-index: 100; opacity: 0.5; position: absolute; top: <?php print $top; ?>px; left: <?php print $leftpx; ?>px; width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
  <span class='imagetarget-region-identifier'><?php print $identifier; ?></span>
</div>
