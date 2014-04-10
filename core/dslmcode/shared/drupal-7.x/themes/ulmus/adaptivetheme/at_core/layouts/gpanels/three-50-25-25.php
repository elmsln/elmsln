<?php

/**
 * @file
 * Gpanel snippet for the three column 50/25/25 layout
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

; 3 col 50-25-25
regions[three_50_25_25_top]    = AT Three column 50/25/25 - top
regions[three_50_25_25_first]  = AT Three column 50/25/25 - left
regions[three_50_25_25_second] = AT Three column 50/25/25 - center
regions[three_50_25_25_third]  = AT Three column 50/25/25 - right
regions[three_50_25_25_bottom] = AT Three column 50/25/25 - bottom

 */
?>

<?php if (
  $page['three_50_25_25_top'] ||
  $page['three_50_25_25_first'] ||
  $page['three_50_25_25_second'] ||
  $page['three_50_25_25_third'] ||
  $page['three_50_25_25_bottom']
  ): ?>
  <!-- Three column 50-25-25 -->
  <div class="at-panel gpanel panel-display three-50-25-25 clearfix">
    <?php print render($page['three_50_25_25_top']); ?>
    <?php print render($page['three_50_25_25_first']); ?>
    <?php print render($page['three_50_25_25_second']); ?>
    <?php print render($page['three_50_25_25_third']); ?>
    <?php print render($page['three_50_25_25_bottom']); ?>
  </div>
<?php endif; ?>
