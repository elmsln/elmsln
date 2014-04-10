<?php

/**
 * @file
 * Gpanel snippet for the two column brick layout
 *
 * Gpanels are drop in multi-column snippets for displaying blocks.
 * Most Gpanels are stacked, meaning they have top and bottom regions
 * by default, however you do not need to use them. You should always
 * use all the horizonal regions or you might experience layout issues.
 *
 * How to use:
 * 1. Copy and paste the code snippet into your page.tpl.php file.
 * 2. Copy and paste the region definitions to your themes .info file.
 * 3. Clear the cache (in Performance settings) to refresh the theme registry.

Region Deinitions:

; 2 col 2x50
regions[two_brick_top]         = AT Two column brick - top
regions[two_brick_left_above]  = AT Two column brick - left above
regions[two_brick_right_above] = AT Two column brick - right above
regions[two_brick_middle]      = AT Two column brick - middle
regions[two_brick_left_below]  = AT Two column brick - left below
regions[two_brick_right_below] = AT Two column brick - right below
regions[two_brick_bottom]      = AT Two column brick - bottom

 */
?>

<?php if (
  $page['two_brick_top'] ||
  $page['two_brick_left_above'] ||
  $page['two_brick_right_above'] ||
  $page['two_brick_middle'] ||
  $page['two_brick_left_below'] ||
  $page['two_brick_right_below'] ||
  $page['two_brick_bottom']
  ): ?>
  <!-- Two column brick Gpanel -->
  <div class="at-panel gpanel panel-display two-brick clearfix">
    <?php print render($page['two_brick_top']); ?>
    <div class="panel-row row-1 clearfix">
      <?php print render($page['two_brick_left_above']); ?>
      <?php print render($page['two_brick_right_above']); ?>
    </div>
    <?php print render($page['two_brick_middle']); ?>
    <div class="panel-row row-2 clearfix">
      <?php print render($page['two_brick_left_below']); ?>
      <?php print render($page['two_brick_right_below']); ?>
    </div>
    <?php print render($page['two_brick_bottom']); ?>
  </div>
<?php endif; ?>
