<?php

/**
 * @file
 * Gpanel snippet for the five column layout
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

; 5 col
regions[five_first]  = AT Five column 5x20 - 1
regions[five_second] = AT Five column 5x20 - 2
regions[five_third]  = AT Five column 5x20 - 3
regions[five_fourth] = AT Five column 5x20 - 4
regions[five_fifth]  = AT Five column 5x20 - 5

 */
?>

<?php if (
  $page['five_first'] ||
  $page['five_second'] ||
  $page['five_third'] ||
  $page['five_fourth'] ||
  $page['five_fifth']
  ): ?>
  <!-- Five column Gpanel -->
  <div class="at-panel gpanel panel-display five-5x20 clearfix">
    <div class="panel-row row-1 clearfix">
      <?php print render($page['five_first']); ?>
      <?php print render($page['five_second']); ?>
    </div>
    <div class="panel-row row-2 clearfix">
      <?php print render($page['five_third']); ?>
      <?php print render($page['five_fourth']); ?>
      <?php print render($page['five_fifth']); ?>
    </div>
  </div>
<?php endif; ?>
