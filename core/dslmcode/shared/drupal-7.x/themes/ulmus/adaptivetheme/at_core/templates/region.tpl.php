<?php
/**
 * @file
 * Adativetheme region.tpl.php
 *
 * The region template in Adaptivetheme is a little different to most other themes.
 * Instead of hard coding its markup Adaptivetheme generates it in
 * adaptivetheme_process_region(), conditionally printing outer and inner wrappers.
 *
 * This allows the core theme to have just one region template instead of four.
 *
 * You can override this in your sub-theme with a normal region suggestion and use
 * a standard region template if you prefer, or use your own themeName_process_region()
 * function to control the markup.
 *
 * For example, if you prefer a template based approach you can use something
 * like this:
 *
 * @code
 * <?php if ($content): ?>
 *   <div class="<?php print $classes; ?>">
 *     <div class="region-inner clearfix">
 *       <?php print $content; ?>
 *     </div>
 *   </div>
 * <?php endif; ?>
 * @endcode
 *
 * If you prefer to theme from process functions you can control the markup per
 * region using something similar to this:
 *
 * @code
 * if ($vars['region'] === 'foobar_region') {
 *   $vars['outer_prefix'] = '<div class="' . $vars['classes'] . '">';
 *   $vars['inner_prefix'] = '<div class="region-inner clearfix">';
 *   $vars['inner_suffix'] = '</div>';
 *   $vars['outer_suffix'] = '</div>';
 * }
 * @endcode
 *
 * Sidebar Region Template:
 * - You can use a singlular region--sidebar.tpl.php template
 *   file to theme both sidebars.
 *
 * Adativetheme variables:
 * - $outer_prefix: Outer div with region classes.
 * - $outer_suffix: Closing element.
 * - $inner_prefix: Inner div with .region-inner and .clearfix classes.
 * - $inner_suffix: Closing div.
 * - $is_mobile: Mixed, requires the Mobile Detect or Browscap module to return
 *   TRUE for mobile.  Note that tablets are also considered mobile devices.  
 *   Returns NULL if the feature could not be detected.
 * - $is_tablet: Mixed, requires the Mobile Detect to return TRUE for tablets.
 *   Returns NULL if the feature could not be detected.
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
 * @see adaptivetheme_preprocess_region()
 * @see adaptivetheme_process_region()
 */
if ($content) {
  print $outer_prefix . $inner_prefix . $content . $inner_suffix . $outer_suffix;
}
