<?php
/**
 * @file
 * Template for Zurb Foundation Three row Display Suite layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="zf-3row <?php print $classes;?>">

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

  <?php if (!empty($ds_content)): ?>
    <div class="<?php print $zf_wrapper_classes; ?>">
      <<?php print $ds_content_wrapper ?> class="group-content<?php print $ds_content_classes; ?>">
        <?php print $ds_content; ?>
      </<?php print $ds_content_wrapper ?>>
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
