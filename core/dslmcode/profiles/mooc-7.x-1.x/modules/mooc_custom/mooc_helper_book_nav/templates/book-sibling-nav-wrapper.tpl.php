<?php
  /**
   * Print book items that are on the same level so we can keep context
   * of pacing through a lesson of instruction.
   *
   * Variables
   * - $breadcrumbs - an array of breadcrumbed book navigational items
   *   in the order in which they appear trickeling down from the
   *   highest level of navigation to the active page.
   * - $next_url: URL to the next node.
   * - $next_title: Title of the next node.
   * - $prev_url: URL to the previous node.
   * - $prev_title: Title of the previous node.
   */
  $output = implode('>', $breadcrumbs);
?>
<div class="small-12 medium-12 large-10 columns book-sibling-nav-container">
  <?php print $output ?>
  <?php if ($prev_url): ?>
    <a href="<?php print $prev_url; ?>" class="page-previous" title="<?php print t('Go to previous page'); ?>"><?php print $prev_title; ?></a>
  <?php else : ?>
    <span class="page-previous"><?php print t('<'); ?></span>
  <?php endif; ?>
  <?php if ($next_url): ?>
    <a href="<?php print $next_url; ?>" class="page-next" title="<?php print t('Go to next page'); ?>"><?php print $next_title; ?></a>
  <?php else : ?>
    <span class="page-next"><?php print t('>'); ?></span>
  <?php endif; ?>
</div>
