<?php

/**
 * @file
 * Template for the FlexSlider row container
 *
 * @author Mathew Winstone (minorOffense) <mwinstone@coldfrontlabs.ca>
 */
?>
<div class="flex-nav-container">
  <div class="flexslider">
    <ul id="flexslider_views_slideshow_<?php print $variables['vss_id']; ?>" class="<?php print $classes; ?>">
      <?php print $rendered_rows; ?>
    </ul>
  </div>
</div>