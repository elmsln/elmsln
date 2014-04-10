<?php
/**
 * @file
 * Adativetheme implementation to present the source of the feed.
 *
 * The contents are rendered above feed listings when browsing source feeds.
 * For example, "example.com/aggregator/sources/1".
 *
 * Adaptivetheme variables:
 * - $is_mobile: Mixed, requires the Mobile Detect or Browscap module to return
 *   TRUE for mobile.  Note that tablets are also considered mobile devices.
 *   Returns NULL if the feature could not be detected.
 * - $is_tablet: Mixed, requires the Mobile Detect to return TRUE for tablets.
 *   Returns NULL if the feature could not be detected.
 *
 * Available variables:
 * - $source_icon: Feed icon linked to the source. Rendered through
 *   theme_feed_icon().
 * - $source_image: Image set by the feed source.
 * - $source_description: Description set by the feed source.
 * - $source_url: URL to the feed source.
 * - $last_checked: How long ago the feed was checked locally.
 *
 * @see template_preprocess()
 * @see template_preprocess_aggregator_feed_source()
 *
 * @ingroup themeable
 */
?>
<aside class="feed-source">

  <?php if ($source_description): ?>
    <header class="feed-description"><?php print $source_icon; ?><?php print $source_description; ?></header>
  <?php endif; ?>

  <?php print $source_image; ?>

  <dl class="feed-details">
    <dt class="feed-url"><?php print t('URL:'); ?></dt>
    <dd class="clearfix"><?php print $source_url; ?></dd>
    <dt class="feed-updated"><?php print t('Updated:'); ?></dt>
    <dd class="clearfix"><?php print $last_checked; ?></dd>
  </dl>

</aside>
