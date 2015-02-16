<?php
/**
 * @file
 * Template for Zurb Foundation Four column bricks Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-4col-bricks <?php print $classes;?>">

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

  <?php if (!empty($above_first) || !empty($above_second) || !empty($above_third) || !empty($above_fourth)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $above_first_wrapper ?> class="group-above-first<?php print $above_first_classes; ?>">
      <?php print $above_first; ?>
      </<?php print $above_first_wrapper ?>>

      <<?php print $above_second_wrapper ?> class="group-above-second<?php print $above_second_classes; ?>">
      <?php print $above_second; ?>
      </<?php print $above_second_wrapper ?>>

      <<?php print $above_third_wrapper ?> class="group-above-third<?php print $above_third_classes; ?>">
      <?php print $above_third; ?>
      </<?php print $above_third_wrapper ?>>

      <<?php print $above_fourth_wrapper ?> class="group-above-fourth<?php print $above_fourth_classes; ?>">
      <?php print $above_fourth; ?>
      </<?php print $above_fourth_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($middle)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $middle_wrapper ?> class="group-middle<?php print $middle_classes; ?>">
      <?php print $middle; ?>
      </<?php print $middle_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($below_first) || !empty($below_second) || !empty($below_third) || !empty($below_fourth)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $below_first_wrapper ?> class="group-below-first<?php print $below_first_classes; ?>">
      <?php print $below_first; ?>
      </<?php print $below_first_wrapper ?>>

      <<?php print $below_second_wrapper ?> class="group-below-second<?php print $below_second_classes; ?>">
      <?php print $below_second; ?>
      </<?php print $below_second_wrapper ?>>

      <<?php print $below_third_wrapper ?> class="group-below-third<?php print $below_third_classes; ?>">
      <?php print $below_third; ?>
      </<?php print $below_third_wrapper ?>>

      <<?php print $below_fourth_wrapper ?> class="group-below-fourth<?php print $below_fourth_classes; ?>">
      <?php print $below_fourth; ?>
      </<?php print $below_fourth_wrapper ?>>
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
