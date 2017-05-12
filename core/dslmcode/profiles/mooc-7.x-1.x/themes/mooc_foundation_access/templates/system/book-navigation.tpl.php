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
        <a tabindex="-1" href="<?php print $prev_url; ?>" class="book-sibling-parent-pagination book-sibling-parent-pagination-previous page-previous black-text white" title="<?php print t('Go to previous page'); ?>" data-voicecommand="previous" data-jwerty-key="←">
          <paper-button raised>
            <i class="material-icons left">navigate_before</i><?php print t('previous page'); ?>
          </paper-button>
        </a>
      <?php endif; ?>
      </div>
      <div class="col s6">
      <?php if (!$prev_url && $next_url): ?>
        <a tabindex="-1" href="<?php print $next_url; ?>" data-prefetch-scrollfire="true" class="page-next book-sibling-parent-pagination book-sibling-parent-pagination-next black-text white" title="<?php print t('Go to next page'); ?>" data-voicecommand="next" data-jwerty-key="→">
        <paper-button raised>
           <?php print t('Start reading'); ?>
            <i class="material-icons right">arrow_forward</i>
          </paper-button>
        </a>
      <?php endif; ?>
      <?php if ($prev_url && $next_url): ?>
        <a tabindex="-1" href="<?php print $next_url; ?>" data-prefetch-scrollfire="true" class="page-next book-sibling-parent-pagination book-sibling-parent-pagination-next black-text white" title="<?php print t('Go to next page'); ?>" data-voicecommand="next" data-jwerty-key="→">
        <paper-button raised>
           <?php print t('next page'); ?>
            <i class="material-icons right">navigate_next</i>
          </paper-button>
        </a>
      <?php endif; ?>
      </div>
    <?php endif; ?>
  </div>
<?php endif; ?>
