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
<div class="book-navigation-header col s12 m12 l12 book-sibling-nav-container book-navigation-header-<?php print $count ?>">
  <!-- TOC Icon -->
  <a href="#block-mooc-helper-mooc-helper-toc-nav-modal" class="mooc-helper-toc crourses-icon elmsln-outline-button elmsln-modal-trigger" aria-controls="toc-drop" aria-expanded="false" title="Table of Contents" data-jwerty-key="o" data-voicecommand="open outline">
    <div class="mooc-helper-toc-icon icon-courses-black etb-modal-icons"></div><span class="book-sibling-parent-text"><?php print t('Outline'); ?></span>
  </a>
  <span class="book-sibling-spacer icon-chevron-right hide-on-med-and-down">/</span>
  <ul class="book-navigation-wrapper hide-on-med-and-down">
    <?php print $output ?>
  </ul>
</div>
