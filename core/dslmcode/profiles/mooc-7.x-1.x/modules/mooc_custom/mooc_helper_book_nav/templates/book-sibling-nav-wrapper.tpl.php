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
   * - $count - number of children in the container so we can name the wrapper
   */
  $output = implode('<span class="book-sibling-spacer">/</span>', $breadcrumbs);
?>
<div class="book-navigation-header small-12 medium-12 large-12 book-sibling-nav-container book-navigation-header-<?php print $count ?>">
  <?php print $output ?>
  <div class="book-sibling-parent-pagination-wrapper">
  <?php if ($prev_url): ?>
    <li class="toolbar-menu-icon book-sibling-parent-pagination book-sibling-parent-pagination-previous">
      <a href="<?php print $prev_url; ?>" class="page-previous" title="<?php print t('Go to previous page'); ?>"><?php print $prev_title; ?></a>
    </li>
  <?php else : ?>
    <span class="page-previous"><?php print $prev_title; ?></span>
  <?php endif; ?>
  <?php if ($next_url): ?>
    <li class="toolbar-menu-icon book-sibling-parent-pagination book-sibling-parent-pagination-next">
      <a href="<?php print $next_url; ?>" class="page-next" title="<?php print t('Go to next page'); ?>"><?php print $next_title; ?></a>
    </li>
  <?php else : ?>
    <span class="page-next"><?php print $next_title; ?></span>
  <?php endif; ?>
  </div>
</div>
