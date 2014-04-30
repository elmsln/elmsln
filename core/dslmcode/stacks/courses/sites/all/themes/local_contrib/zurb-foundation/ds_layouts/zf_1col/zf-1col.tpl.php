<?php
/**
 * @file
 * Template for Zurb Foundation One column Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-1col <?php print $classes;?>">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <<?php print $ds_content_wrapper ?> class="group-content<?php print $ds_content_classes; ?>">
    <?php print $ds_content; ?>
  </<?php print $ds_content_wrapper ?>>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
