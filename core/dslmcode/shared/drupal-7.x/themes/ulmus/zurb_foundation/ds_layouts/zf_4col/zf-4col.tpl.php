<?php
/**
 * @file
 * Template for Zurb Foundation Four column Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-4col <?php print $classes;?>">

  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if (!empty($first)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $first_wrapper ?> class="group-first<?php print $first_classes; ?>">
      <?php print $first; ?>
      </<?php print $first_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($second)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $second_wrapper ?> class="group-second<?php print $second_classes;?>">
      <?php print $second; ?>
      </<?php print $second_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($third)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $third_wrapper ?> class="group-third<?php print $third_classes; ?>">
      <?php print $third; ?>
      </<?php print $third_wrapper ?>>
    </div>
  <?php endif; ?>

  <?php if (!empty($fourth)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $fourth_wrapper ?> class="group-fourth<?php print $fourth_classes; ?>">
      <?php print $fourth; ?>
      </<?php print $fourth_wrapper ?>>
    </div>
  <?php endif; ?>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
