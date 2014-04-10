<?php

/**
 * @file
 * Gpanel snippet for the three inset left layout
 *
 * Gpanels are drop in multi-umn snippets for displaying blocks.
 * Most Gpanels are stacked, meaning they have top and bottom regions
 * by default, however you do not need to use them. You should always
 * use all the horizonal regions or you might experience layout issues.
 *
 * How to use:
 * 1. Copy and paste the code snippet into your page.tpl.php file.
 * 2. Copy and paste the region definitions to your themes .info file.
 * 3. Clear the cache (in Performance settings) to refresh the theme registry.

Region Deinitions:

; Three Inset Left
regions[three_inset_left_sidebar] = AT Inset left - sidebar
regions[three_inset_left_top]     = AT Inset left - top
regions[three_inset_left_middle]  = AT Inset left - middle
regions[three_inset_left_inset]   = AT Inset left - inset
regions[three_inset_left_bottom]  = AT Inset left - bottom

 */
?>

<?php if (
  $page['three_inset_left_sidebar'] ||
  $page['three_inset_left_top'] ||
  $page['three_inset_left_middle'] ||
  $page['three_inset_left_inset'] ||
  $page['three_inset_left_bottom']
  ): ?>
  <!-- Three inset left Gpanel -->
  <div class="at-panel gpanel panel-display three-inset-left clearfix">
    <?php print render($page['three_inset_left_sidebar']); ?>
    <div class="inset-wrapper clearfix">
      <?php print render($page['three_inset_left_top']); ?>
      <?php print render($page['three_inset_left_middle']); ?>
      <?php print render($page['three_inset_left_inset']); ?>
      <?php print render($page['three_inset_left_bottom']); ?>
    </div>
  </div>
<?php endif; ?>
