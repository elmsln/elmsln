<?php
/**
 * @file
 * Template for Zurb Foundation Four column stacked Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-4col-stacked <?php print $classes;?>">

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

  <?php if (!empty($first) || !empty($second) || !empty($third) || !empty($fourth)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $first_wrapper ?> class="group-first<?php print $first_classes; ?>">
      <?php print $first; ?>
      </<?php print $first_wrapper ?>>

      <<?php print $second_wrapper ?> class="group-second<?php print $second_classes;?>">
      <?php print $second; ?>
      </<?php print $second_wrapper ?>>

      <<?php print $third_wrapper ?> class="group-third<?php print $third_classes; ?>">
      <?php print $third; ?>
      </<?php print $third_wrapper ?>>

      <<?php print $fourth_wrapper ?> class="group-fourth<?php print $fourth_classes; ?>">
      <?php print $fourth; ?>
      </<?php print $fourth_wrapper ?>>
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
