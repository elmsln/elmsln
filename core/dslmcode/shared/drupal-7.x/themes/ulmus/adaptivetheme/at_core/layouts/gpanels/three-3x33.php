<?php

/**
 * @file
 * Gpanel snippet for the three column 3x33 layout
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

; 3 col 3x33
regions[three_33_top]    = AT Three column 3x33 - top
regions[three_33_first]  = AT Three column 3x33 - left
regions[three_33_second] = AT Three column 3x33 - center
regions[three_33_third]  = AT Three column 3x33 - right
regions[three_33_bottom] = AT Three column 3x33 - bottom

 */
?>

<?php if (
  $page['three_33_top'] ||
  $page['three_33_first'] ||
  $page['three_33_second'] ||
  $page['three_33_third'] ||
  $page['three_33_bottom']
  ): ?>
  <!-- Three column 3x33 Gpanel -->
  <div class="at-panel gpanel panel-display three-3x33 clearfix">
    <?php print render($page['three_33_top']); ?>
    <?php print render($page['three_33_first']); ?>
    <?php print render($page['three_33_second']); ?>
    <?php print render($page['three_33_third']); ?>
    <?php print render($page['three_33_bottom']); ?>
  </div>
<?php endif; ?>
