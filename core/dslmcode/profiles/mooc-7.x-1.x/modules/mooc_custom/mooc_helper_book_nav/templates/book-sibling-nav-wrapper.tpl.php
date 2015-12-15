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
  $output = implode('<span class="book-sibling-spacer icon-chevron-right">/</span>', $breadcrumbs);
?>
<div class="book-navigation-header small-12 medium-12 large-12 book-sibling-nav-container book-navigation-header-<?php print $count ?>">
  <!-- TOC Icon -->
  <a href="#" class="mooc-helper-toc courses-icon"  data-reveal-id="block-mooc-helper-mooc-helper-toc-nav-modal" aria-controls="toc-drop" aria-expanded="false" title="Table of Contents">
    <div class="mooc-helper-toc-icon icon-courses-black etb-modal-icons"></div><span class="book-sibling-parent-text show-for-large-up"><?php print t('Outline'); ?></span>
  </a>
  <span class="book-sibling-spacer icon-chevron-right">/</span>
  <ul class="book-navigation-wrapper show-for-large-up">
    <?php print $output ?>
  </ul>
</div>
