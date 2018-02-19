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
  $output = implode('<li class="book-sibling-spacer">/</li>', $breadcrumbs);
?>
<ul class="book-navigation-wrapper hide-on-small-only">
  <li class="book-sibling-spacer">/</li>
  <?php print $output ?>
</ul>