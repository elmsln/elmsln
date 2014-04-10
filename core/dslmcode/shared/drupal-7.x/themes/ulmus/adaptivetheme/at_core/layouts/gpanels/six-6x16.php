<?php

/**
 * @file
 * Gpanel snippet for the six column layout
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

; 6 col
regions[six_first]  = AT Six column 6x16 - 1
regions[six_second] = AT Six column 6x16 - 2
regions[six_third]  = AT Six column 6x16 - 3
regions[six_fourth] = AT Six column 6x16 - 4
regions[six_fifth]  = AT Six column 6x16 - 5
regions[six_sixth]  = AT Six column 6x16 - 6

 */
?>

<?php if (
  $page['six_first'] ||
  $page['six_second'] ||
  $page['six_third'] ||
  $page['six_fourth'] ||
  $page['six_fifth'] ||
  $page['six_sixth']
  ): ?>
  <!-- Six column Gpanel -->
  <div class="at-panel gpanel panel-display six-6x16 clearfix">
    <div class="panel-row row-1 clearfix">
      <?php print render($page['six_first']); ?>
      <?php print render($page['six_second']); ?>
    </div>
    <div class="panel-row row-2 clearfix">
      <?php print render($page['six_third']); ?>
      <?php print render($page['six_fourth']); ?>
    </div>
    <div class="panel-row row-3 clearfix">
      <?php print render($page['six_fifth']); ?>
      <?php print render($page['six_sixth']); ?>
    </div>
  </div>
<?php endif; ?>
