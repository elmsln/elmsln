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
    <div id="off-canvas-admin-menu" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
      <ul class="button-group">
      	<li><?php print l(t('Edit course outline'), 'admin/content/book/' . $active_outline); ?></li>
      	<li><?php print l(t('Print course outline'), 'book/export/html/' . $active_outline); ?></li>
      	<li><?php print l(t('Save As new outline'), 'admin/content/book/copy/' . $active_outline); ?></li>
      	<hr>
      	<li><a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">Course Settings</a></li>
      </ul>
    </div>
    <nav class="top-bar" data-topbar role="navigation">
      <section class="right top-bar-section">
        <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="off-canvas-admin-menu" aria-controls="offcanvas-admin-menu" aria-expanded="false">
          <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
        </a>
     </section>
    </nav>
  <a role="button" class="left-off-canvas-toggle close"><div class="icon-close-black outline-nav-icon" data-grunticon-embed></div></a>
  <div class="content-outline-navigation in-place-scroll">
  <?php if ($content): ?>
    <?php print $content; ?>
  <?php endif; ?>
	</div>
</aside>
