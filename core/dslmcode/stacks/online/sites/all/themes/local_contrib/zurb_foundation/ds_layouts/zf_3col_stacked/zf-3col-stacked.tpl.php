<?php
/**
 * @file
 * Template for Zurb Foundation Three column stacked Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-3col-stacked <?php print $classes;?>">

  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if (!empty($header)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $header_wrapper ?> class="group-header<?php print $header_classes; ?>">
      <?php print $header; ?>
      </<?php print $header_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($left) || !empty($middle) || !empty($right)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $left_wrapper ?> class="group-left<?php print $left_classes; ?>">
      <?php print $left; ?>
      </<?php print $left_wrapper ?>>

      <<?php print $middle_wrapper ?> class="group-middle<?php print $middle_classes; ?>">
      <?php print $middle; ?>
      </<?php print $middle_wrapper ?>>

      <<?php print $right_wrapper ?> class="group-right<?php print $right_classes; ?>">
      <?php print $right; ?>
      </<?php print $right_wrapper ?>>
    </div>
  <?php endif; ?>

  <div class="<?php print $zf_wrapper_classes; ?>">
    <?php if (!empty($footer)): ?>
      <<?php print $footer_wrapper ?> class="group-footer<?php print $footer_classes; ?>">
      <?php print $footer; ?>
      </<?php print $footer_wrapper ?>>
    <?php endif; ?>
  </div>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
