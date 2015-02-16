<?php
/**
 * @file
 * Template for Zurb Foundation Three column bricks Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-3col-bricks <?php print $classes;?>">

  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if (!empty($top)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $top_wrapper ?> class="group-top<?php print $top_classes; ?>">
      <?php print $top; ?>
      </<?php print $top_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($above_left) || !empty($above_middle) || !empty($above_right)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $above_left_wrapper ?> class="group-above-left<?php print $above_left_classes; ?>">
      <?php print $above_left; ?>
      </<?php print $above_left_wrapper ?>>

      <<?php print $above_middle_wrapper ?> class="group-above-middle<?php print $above_middle_classes; ?>">
      <?php print $above_middle; ?>
      </<?php print $above_middle_wrapper ?>>

      <<?php print $above_right_wrapper ?> class="group-above-right<?php print $above_right_classes; ?>">
      <?php print $above_right; ?>
      </<?php print $above_right_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($middle)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $middle_wrapper ?> class="group-middle<?php print $middle_classes; ?>">
      <?php print $middle; ?>
      </<?php print $middle_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($below_left) || !empty($below_middle) || !empty($below_right)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $below_left_wrapper ?> class="group-below-left<?php print $below_left_classes; ?>">
      <?php print $below_left; ?>
      </<?php print $below_left_wrapper ?>>

      <<?php print $below_middle_wrapper ?> class="group-below-middle<?php print $below_middle_classes; ?>">
      <?php print $below_middle; ?>
      </<?php print $below_middle_wrapper ?>>

      <<?php print $below_right_wrapper ?> class="group-below-right<?php print $below_right_classes; ?>">
      <?php print $below_right; ?>
      </<?php print $below_right_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($bottom)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $bottom_wrapper ?> class="group-bottom<?php print $bottom_classes; ?>">
      <?php print $bottom; ?>
      </<?php print $bottom_wrapper ?>>
    </div>
  <?php endif; ?>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
