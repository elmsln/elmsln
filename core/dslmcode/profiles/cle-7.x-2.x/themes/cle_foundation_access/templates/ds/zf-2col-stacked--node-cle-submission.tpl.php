<?php
/**
 * @file
 * Template for Zurb Foundation Two column stacked Display Suite layout.
 */
  // make middle column fluid based on material being loaded
  if (empty($left)) {
    $right_classes = str_replace('-6', '-12', $right_classes);
  }
  if (empty($right)) {
    $left_classes = str_replace('-6', '-12', $left_classes);
  }
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-2col-stacked <?php print $classes;?>">

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

  <?php if (!empty($left) || !empty($right)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
    <?php if (!empty($left)): ?>
      <<?php print $left_wrapper ?> class="group-left<?php print $left_classes; ?>">
      <?php print $left; ?>
      </<?php print $left_wrapper ?>>
    <?php endif; ?>
    <?php if (!empty($right)): ?>
      <<?php print $right_wrapper ?> class="group-right<?php print $right_classes; ?>">
      <?php print $right; ?>
      </<?php print $right_wrapper ?>>
    <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($footer)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $footer_wrapper ?> class="group-footer<?php print $footer_classes; ?>">
      <?php print $footer; ?>
      </<?php print $footer_wrapper ?>>
    </div>
  <?php endif; ?>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
