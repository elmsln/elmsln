<?php
/**
 * @file
 * Adativetheme implementation to display a block.
 *
 * The block template in Adaptivetheme is a little different to most other themes.
 * Instead of hard coding its markup Adaptivetheme generates most of it in
 * adaptivetheme_process_block(), conditionally printing outer and inner wrappers.
 *
 * This allows the core theme to have just one template instead of five.
 *
 * You can override this in your sub-theme with a normal block suggestion and use
 * a standard block template if you prefer, or use your own themeName_process_block()
 * function to control the markup. For example a typical navigation tempate might look
 * like this:
 *
 * @code
 * <nav id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
 *   <div class="block-inner clearfix">
 *     <?php print render($title_prefix); ?>
 *     <?php if ($block->subject): ?>
 *       <h2<?php print $title_attributes; ?>><?php print $block->subject; ?></h2>
 *     <?php endif; ?>
 *     <?php print render($title_suffix); ?>
 *     <div<?php print $content_attributes; ?>>
 *       <?php print $content ?>
 *     </div>
 *   </div>
 * </nav>
 * @endcode
 *
 * Adativetheme supplied variables:
 * - $outer_prefix: Holds a conditional element such as nav, section or div and
 *                  includes the block id, classes and attributes.
 * - $outer_suffix: Closing element.
 * - $inner_prefix: Inner div with .block-inner and .clearfix classes.
 * - $inner_suffix: Closing div.
 * - $title: Holds the block->subject.
 * - $content_processed: Pre-wrapped in div and attributes, but for some
 *   blocks these are stripped away, e.g. menu bar and main content.
 * - $is_mobile: Mixed, requires the Mobile Detect or Browscap module to return
 *   TRUE for mobile.  Note that tablets are also considered mobile devices.  
 *   Returns NULL if the feature could not be detected.
 * - $is_tablet: Mixed, requires the Mobile Detect to return TRUE for tablets.
 *   Returns NULL if the feature could not be detected.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 * @see adaptivetheme_preprocess_block()
 * @see adaptivetheme_process_block()
 */
?>
<?php print $outer_prefix . $inner_prefix; ?>
  <?php print render($title_prefix); ?>

  <?php if ($title): ?>
    <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
  <?php endif; ?>

  <?php print $content_processed; ?>

  <?php print render($title_suffix); ?>
<?php print $inner_suffix . $outer_suffix; ?>
