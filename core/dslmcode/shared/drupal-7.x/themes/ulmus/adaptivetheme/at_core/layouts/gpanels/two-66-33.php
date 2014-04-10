<?php

/**
 * @file
 * Gpanel snippet for the two column 66/33 layout
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

; 2 col 66-33
regions[two_66_33_top]    = AT Two column 66/33 - top
regions[two_66_33_first]  = AT Two column 66/33 - left
regions[two_66_33_second] = AT Two column 66/33 - right
regions[two_66_33_bottom] = AT Two column 66/33 - bottom

 */
?>

<?php if (
  $page['two_66_33_top'] ||
  $page['two_66_33_first'] ||
  $page['two_66_33_second'] ||
  $page['two_66_33_bottom']
  ): ?>
  <!-- Two column 66-33 Gpanel -->
  <div class="at-panel gpanel panel-display two-66-33 clearfix">
    <?php print render($page['two_66_33_top']); ?>
    <?php print render($page['two_66_33_first']); ?>
    <?php print render($page['two_66_33_second']); ?>
    <?php print render($page['two_66_33_bottom']); ?>
  </div>
<?php endif; ?>
