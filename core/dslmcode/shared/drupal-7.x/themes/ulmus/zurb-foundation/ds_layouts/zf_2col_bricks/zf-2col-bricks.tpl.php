<?php
/**
 * @file
 * Template for Zurb Foundation Two column bricks Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="row zf-2col-bricks <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <div class="row">
    <?php if (!empty($top)): ?>
      <<?php print $top_wrapper ?> class="group-top columns<?php print $top_classes; ?>">
      <?php print $top; ?>
      </<?php print $top_wrapper ?>>
    <?php endif; ?>
  </div>

  <div class="row">
    <<?php print $above_left_wrapper ?> class="group-above-left columns<?php print $above_left_classes; ?>">
    <?php print $above_left; ?>
    </<?php print $above_left_wrapper ?>>

    <<?php print $above_right_wrapper ?> class="group-above-right columns<?php print $above_right_classes; ?>">
    <?php print $above_right; ?>
    </<?php print $above_right_wrapper ?>>
  </div>

  <div class="row">
    <?php if (!empty($middle)): ?>
      <<?php print $middle_wrapper ?> class="group-middle columns<?php print $middle_classes; ?>">
      <?php print $middle; ?>
      </<?php print $middle_wrapper ?>>
    <?php endif; ?>
  </div>

  <div class="row">
    <<?php print $below_left_wrapper ?> class="group-below-left columns<?php print $below_left_classes; ?>">
    <?php print $below_left; ?>
    </<?php print $below_left_wrapper ?>>

    <<?php print $below_right_wrapper ?> class="group-below-right columns<?php print $below_right_classes; ?>">
    <?php print $below_right; ?>
    </<?php print $below_right_wrapper ?>>
  </div>

  <div class="row">
    <?php if (!empty($bottom)): ?>
      <<?php print $bottom_wrapper ?> class="group-bottom columns<?php print $bottom_classes; ?>">
      <?php print $bottom; ?>
      </<?php print $bottom_wrapper ?>>
    <?php endif; ?>
  </div>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
