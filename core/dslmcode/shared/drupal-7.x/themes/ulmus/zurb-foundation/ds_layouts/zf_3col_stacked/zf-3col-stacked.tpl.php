<?php
/**
 * @file
 * Template for Zurb Foundation Three column stacked Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="row zf-3col-stacked <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <div class="row">
    <?php if (!empty($header)): ?>
      <<?php print $header_wrapper ?> class="group-header columns<?php print $header_classes; ?>">
      <?php print $header; ?>
      </<?php print $header_wrapper ?>>
    <?php endif; ?>
  </div>

  <div class="row">
    <<?php print $left_wrapper ?> class="group-left columns<?php print $left_classes; ?>">
    <?php print $left; ?>
    </<?php print $left_wrapper ?>>

    <<?php print $middle_wrapper ?> class="group-middle columns<?php print $middle_classes; ?>">
    <?php print $middle; ?>
    </<?php print $middle_wrapper ?>>

    <<?php print $right_wrapper ?> class="group-right columns<?php print $right_classes; ?>">
    <?php print $right; ?>
    </<?php print $right_wrapper ?>>
  </div>

  <div class="row">
    <?php if (!empty($footer)): ?>
      <<?php print $footer_wrapper ?> class="group-footer columns<?php print $footer_classes; ?>">
      <?php print $footer; ?>
      </<?php print $footer_wrapper ?>>
    <?php endif; ?>
  </div>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
