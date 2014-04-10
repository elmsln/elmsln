<?php

/**
 * @file
 * Gpanel snippet for the one column layout
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

; 1 col
regions[one_main] = AT One column

 */
?>

<?php if ($page['one_main']): ?>
  <!-- One column -->
  <div class="at-panel gpanel panel-display one-column clearfix">
    <?php print render($page['one_main']); ?>
  </div>
<?php endif; ?>
