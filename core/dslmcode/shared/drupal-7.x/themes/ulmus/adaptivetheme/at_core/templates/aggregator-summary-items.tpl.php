<?php
/**
 * @file
 * Adativetheme implementation to present feeds as list items.
 *
 * Each iteration generates a single feed source or category.
 *
 * Adaptivetheme variables:
 * - $is_mobile: Mixed, requires the Mobile Detect or Browscap module to return
 *   TRUE for mobile.  Note that tablets are also considered mobile devices.  
 *   Returns NULL if the feature could not be detected.
 * - $is_tablet: Mixed, requires the Mobile Detect to return TRUE for tablets.
 *   Returns NULL if the feature could not be detected.
 *
 * Available variables:
 * - $title: Title of the feed or category.
 * - $summary_list: Unordered list of linked feed items generated through
 *   theme_item_list().
 * - $source_url: URL to the local source or category.
 *
 * @see template_preprocess()
 * @see template_preprocess_aggregator_summary_items()
 *
 * @ingroup themeable
 */
?>
<section id="feed-<?php print drupal_html_class($title); ?>" class="feed">
  <h2 class="summary-title"><?php print $title; ?></h2>
  <?php print $summary_list; ?>
  <p class="read-more"><a href="<?php print $source_url; ?>"><?php print t('More'); ?></a></p>
</section>
