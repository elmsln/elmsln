<?php
/**
 * @file
 * Adaptivetheme panel pane template.
 *
 * This template has block type classes to they react to styles applied to blocks,
 * saving the trouble of having to style multiple selectors to target blocks
 * and panel panes. This template also makes use the attributes arrays for the
 * wrapper and content wrapper.
 *
 * Adaptivetheme variables:
 * - $is_mobile: Mixed, requires the Mobile Detect or Browscap module to return
 *   TRUE for mobile.  Note that tablets are also considered mobile devices.  
 *   Returns NULL if the feature could not be detected.
 * - $is_tablet: Mixed, requires the Mobile Detect to return TRUE for tablets.
 *   Returns NULL if the feature could not be detected.
 * - $tag: top level wrapper element, section or div.
 *
 * Variables available:
 * - $pane->type: the content type inside this pane
 * - $pane->subtype: The subtype, if applicable. If a view it will be the
 *   view name; if a node it will be the nid, etc.
 * - $title: The title of the content
 * - $content: The actual content
 * - $links: Any links associated with the content
 * - $more: An optional 'more' link (destination only)
 * - $admin_links: Administrative links associated with the content
 * - $feeds: Any feed icons or associated with the content
 * - $display: The complete panels display object containing all kinds of
 *   data including the contexts and all of the other panes being displayed.
 */
?>
<?php if (isset($pane_prefix)): print $pane_prefix; endif; ?>
<<?php print $tag . $attributes . $id; ?>>
  <div class="block-inner clearfix">
    <?php if ($admin_links): ?>
      <?php print $admin_links; ?>
    <?php endif; ?>

    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>

    <?php if ($feeds): ?>
      <div class="feed">
        <?php print $feeds; ?>
      </div>
    <?php endif; ?>

    <div<?php print $content_attributes; ?>>
      <?php print render($content); ?>
    </div>

    <?php if ($links): ?>
      <nav class="links">
        <?php print $links; ?>
      </nav>
    <?php endif; ?>

    <?php if ($more): ?>
      <div class="more-link">
        <?php print $more; ?>
      </div>
    <?php endif; ?>

  </div>
</<?php print $tag; ?>>
<?php if (isset($pane_suffix)): print $pane_suffix; endif; ?>
