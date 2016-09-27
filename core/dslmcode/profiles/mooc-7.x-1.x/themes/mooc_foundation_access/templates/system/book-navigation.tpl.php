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
  <div id="book-navigation-<?php print $book_id; ?>" class="book-navigation-footer row book-sibling-nav-container">
    <?php if ($has_links): ?>
      <div class="col s6">
      <?php if ($prev_url): ?>
          <a href="<?php print $prev_url; ?>" class="book-sibling-parent-pagination book-sibling-parent-pagination-previous page-previous waves-effect cis-lmsless-color btn black-text white elmsln-z-depth-0" title="<?php print t('Go to previous page'); ?>" data-voicecommand="previous" data-jwerty-key="←"><i class="material-icons left">navigate_before</i><?php print t('previous'); ?></a>
      <?php endif; ?>
      </div>
      <div class="col s6">
      <?php if ($next_url): ?>
          <a href="<?php print $next_url; ?>" class="page-next book-sibling-parent-pagination book-sibling-parent-pagination-next waves-effect cis-lmsless-color btn black-text white elmsln-z-depth-0" title="<?php print t('Go to next page'); ?>" data-voicecommand="next" data-jwerty-key="→"><i class="material-icons right">navigate_next</i><?php print t('next'); ?></a>
      <?php endif; ?>
      </div>
    <?php endif; ?>
  </div>
<?php endif; ?>
