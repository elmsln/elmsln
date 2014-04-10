<?php

/**
 * @file
 * Gpanel snippet for the three inset right layout
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

; Three Inset Right
regions[three_inset_right_sidebar] = AT Inset right - sidebar
regions[three_inset_right_top]     = AT Inset right - top
regions[three_inset_right_middle]  = AT Inset right - middle
regions[three_inset_right_inset]   = AT Inset right - inset
regions[three_inset_right_bottom]  = AT Inset right - bottom

 */
?>

<?php if (
  $page['three_inset_right_sidebar'] ||
  $page['three_inset_right_top'] ||
  $page['three_inset_right_middle'] ||
  $page['three_inset_right_inset'] ||
  $page['three_inset_right_bottom']
  ): ?>
  <!-- Three inset right Gpanel -->
  <div class="at-panel gpanel panel-display three-inset-right clearfix">
    <?php print render($page['three_inset_right_sidebar']); ?>
    <div class="inset-wrapper clearfix">
      <?php print render($page['three_inset_right_top']); ?>
      <?php print render($page['three_inset_right_middle']); ?>
      <?php print render($page['three_inset_right_inset']); ?>
      <?php print render($page['three_inset_right_bottom']); ?>
    </div>
  </div>
<?php endif; ?>
