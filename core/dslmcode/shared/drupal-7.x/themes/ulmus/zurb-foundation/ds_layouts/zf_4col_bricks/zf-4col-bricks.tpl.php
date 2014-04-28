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

  <div class="row">
    <?php if (!empty($top)): ?>
      <<?php print $top_wrapper ?> class="group-top<?php print $top_classes; ?>">
      <?php print $top; ?>
      </<?php print $top_wrapper ?>>
    <?php endif; ?>
  </div>

  <div class="row">
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

  <div class="row">
    <?php if (!empty($middle)): ?>
      <<?php print $middle_wrapper ?> class="group-middle<?php print $middle_classes; ?>">
      <?php print $middle; ?>
      </<?php print $middle_wrapper ?>>
    <?php endif; ?>
  </div>

  <div class="row">
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

  <div class="row">
    <?php if (!empty($bottom)): ?>
      <<?php print $bottom_wrapper ?> class="group-bottom<?php print $bottom_classes; ?>">
      <?php print $bottom; ?>
      </<?php print $bottom_wrapper ?>>
    <?php endif; ?>
  </div>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
