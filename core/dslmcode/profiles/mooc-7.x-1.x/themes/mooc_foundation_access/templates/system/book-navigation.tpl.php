<?php

/**
 * @file
 * Default theme implementation to navigate books.
 *
 * Presented under nodes that are a part of book outlines.
 *
 * Available variables:
 * - $prev_url: URL to the previous node.
 * - $prev_title: Title of the previous node.
 * - $parent_url: URL to the parent node.
 * - $parent_title: Title of the parent node. Not printed by default. Provided
 *   as an option.
 * - $next_url: URL to the next node.
 * - $next_title: Title of the next node.
 * - $has_links: Flags TRUE whenever the previous, parent or next data has a
 *   value.
 * - $book_id: The book ID of the current outline being viewed. Same as the node
 *   ID containing the entire outline. Provided for context.
 * - $book_url: The book/node URL of the current outline being viewed. Provided
 *   as an option. Not used by default.
 * - $book_title: The book/node title of the current outline being viewed.
 *   Provided as an option. Not used by default.
 *
 * @see template_preprocess_book_navigation()
 *
 * @ingroup themeable
 */
?>
<?php if ($has_links): ?>
  <div id="book-navigation-<?php print $book_id; ?>" class="book-navigation-footer small-12 medium-12 large-12 book-sibling-nav-container">
    <?php if ($has_links): ?>
      <?php if ($prev_url): ?>
        <li class="toolbar-menu-icon book-sibling-parent-pagination book-sibling-parent-pagination-previous">
          <a href="<?php print $prev_url; ?>" class="page-previous" title="<?php print t('Go to previous page'); ?>" data-voicecommand="previous" data-jwerty-key="←"><span class="book-sibling-spacer icon-chevron-left"></span><span class="book-pagination-button-text book-prev visible-for-large-up"><?php print t('previous'); ?></span></a>
        </li>
      <?php endif; ?>
      <?php if ($next_url): ?>
        <li class="toolbar-menu-icon book-sibling-parent-pagination book-sibling-parent-pagination-next">
          <a href="<?php print $next_url; ?>" class="page-next" title="<?php print t('Go to next page'); ?>" data-voicecommand="next" data-jwerty-key="→"><span class="book-pagination-button-text book-next visible-for-large-up"><?php print t('next'); ?></span><span class="book-sibling-spacer icon-chevron-right"></span></a>
        </li>
      <?php endif; ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
