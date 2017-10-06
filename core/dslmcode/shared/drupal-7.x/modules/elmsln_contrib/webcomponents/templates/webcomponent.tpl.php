<?php
/**
 * @file
 * Default theme implementation to display a web component.
 * This is laughable small.
 *
 * Available variables:
 * - $tag: the custom web component "html" tag
 * - $properties: an array of attributes / values to fill in.
 * - $innerHTML: Content that gets placed into the middle of the tag.
 *               This is either set content or a combination of defined slots
 */
// just to be safe since drupal_attributes blows up if node system doesn't populate
if (empty($properties)) {
  $properties = array();
}
?>
<?php print $wrap_tag;?>
  <<?php print $tag;?><?php print drupal_attributes($properties);?>>
    <?php print $innerHTML;?>
  </<?php print $tag; ?>>
<?php print $wrap_tag_close;?>