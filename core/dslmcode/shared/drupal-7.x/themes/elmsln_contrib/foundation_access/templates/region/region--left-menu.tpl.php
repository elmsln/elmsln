<?php
/**
 * @file
 * Default theme implementation to display a region.
 *
 * Available variables:
 * - $content: The content for this region, typically blocks.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - region: The current template type, i.e., "theming hook".
 *   - region-[name]: The name of the region with underscores replaced with
 *     dashes. For example, the page_top region would have a region-page-top class.
 * - $region: The name of the region variable as defined in the theme's .info file.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 *
 * @see template_preprocess()
 * @see template_preprocess_region()
 * @see template_process()
 */
?>
<aside class="left-off-canvas-menu">
  <!-- Menu Item Dropdowns -->
  <?php if (isset($button_group)): ?>
    <?php print $button_group; ?>
  <?php endif; ?>
  <a role="button" class="left-off-canvas-toggle close"><div class="icon-close-black outline-nav-icon" data-grunticon-embed></div></a>
  <div class="content-outline-navigation in-place-scroll">
  <?php if ($content): ?>
    <?php print $content; ?>
  <?php endif; ?>
  </div>
</aside>
