<?php

/**
 * @file
 * Gpanel snippet for the two column 33/66 layout
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

; 2 col 33-66
regions[two_33_66_top]    = AT Two column 33/66 - top
regions[two_33_66_first]  = AT Two column 33/66 - left
regions[two_33_66_second] = AT Two column 33/66 - right
regions[two_33_66_bottom] = AT Two column 33/66 - bottom

 */
?>

<?php if (
  $page['two_33_66_top'] ||
  $page['two_33_66_first'] ||
  $page['two_33_66_second'] ||
  $page['two_33_66_bottom']
  ): ?>
  <!-- Two column 33-66 Gpanel -->
  <div class="at-panel gpanel panel-display two-33-66 clearfix">
    <?php print render($page['two_33_66_top']); ?>
    <?php print render($page['two_33_66_first']); ?>
    <?php print render($page['two_33_66_second']); ?>
    <?php print render($page['two_33_66_bottom']); ?>
  </div>
<?php endif; ?>
