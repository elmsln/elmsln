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
<div class="book-navigation-header col s12 m12 l12 book-sibling-nav-container book-navigation-header-<?php print $count ?>">
  <!-- TOC Icon -->
  <a href="#block-mooc-helper-mooc-helper-toc-nav-modal" class="mooc-helper-toc elmsln-outline-button elmsln-modal-trigger black-text" aria-controls="block-mooc-helper-mooc-helper-toc-nav-modal" aria-expanded="false" title="Table of Contents" data-jwerty-key="o" data-voicecommand="open outline">
  <paper-button>
    <i class="material-icons">explore</i><?php print t('Outline'); ?>
  </paper-button>
  </a>
  <ul class="book-navigation-wrapper hide-on-med-and-down">
    <li class="book-sibling-spacer">/</li>
    <?php print $output ?>
  </ul>
</div>
