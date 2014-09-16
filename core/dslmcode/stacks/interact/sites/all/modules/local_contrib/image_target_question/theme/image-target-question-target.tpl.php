<?php

/**
 * @file
 * This displays the drag targets that the user can drag onto the image
 * to indicate their answer
 *
 * Variables available are
 *   $top (INT) - Top left co-ordinate
 *   $left (INT) - Left co-ordinate
 *   $height (INT) - Height of the target image
 *   $width (INT) - Width of the target image
 *   $identifier (STRING) - Identifier to match the target with the relevant
 *     description
 */
?>
<div style="background: url('<?php print $imgurl; ?>') no-repeat scroll 0 0 transparent; z-index: 200; position: absolute; top: <?php print $top; ?>px; left: <?php print $left; ?>px; width: <?php print $width;?>px; height: <?php print $height;?>px;">
  <span class="imagetarget-target-identifier"><?php print $identifier; ?></span>
</div>
