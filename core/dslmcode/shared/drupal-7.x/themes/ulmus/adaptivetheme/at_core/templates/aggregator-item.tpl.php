<?php
/**
 * @file
 * Adativetheme implementation to format an individual feed item for display
 * on the aggregator page.
 *
 * Adaptivetheme variables:
 * - $is_mobile: Mixed, requires the Mobile Detect or Browscap module to return
 *   TRUE for mobile.  Note that tablets are also considered mobile devices.  
 *   Returns NULL if the feature could not be detected.
 * - $is_tablet: Mixed, requires the Mobile Detect to return TRUE for tablets.
 *   Returns NULL if the feature could not be detected.
 *
 * Available variables:
 * - $feed_url: URL to the originating feed item.
 * - $feed_title: Title of the feed item.
 * - $source_url: Link to the local source section.
 * - $source_title: Title of the remote source.
 * - $source_date: Date the feed was posted on the remote source.
 * - $content: Feed item content.
 * - $categories: Linked categories assigned to the feed.
 *
 * @see template_preprocess()
 * @see template_preprocess_aggregator_item()
 * @see adaptivetheme_preprocess_aggregator_item()
 */
?>
<article class="<?php print $classes; ?>">

  <header>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $feed_url; ?>"><?php print $feed_title; ?></a>
    </h2>
    <p class="feed-item-meta">
      <?php if ($source_url) : ?>
        <a href="<?php print $source_url; ?>" class="feed-item-source"><?php print $source_title; ?></a> -
      <?php endif; ?>
      <time datetime="<?php print $datetime; ?>"><?php print $source_date; ?></time>
    </p>
  </header>

  <?php if ($content) : ?>
    <div<?php print $content_attributes; ?>>
      <?php print $content; ?>
    </div>
  <?php endif; ?>

  <?php if ($categories): ?>
    <footer>
      <p class="feed-item-categories">
        <strong><?php print t('Categories'); ?></strong> - <?php print implode(', ', $categories); ?>
      </p>
    </footer>
  <?php endif; ?>

</article>
