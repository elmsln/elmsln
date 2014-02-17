<?php

/**
 * @file
 * A basic template for entityreference view widget
 *
 * Available variables:
 * - $selected_items: The items that have been added.
 *   $filters: The exposed filters, from the view.
 *   $pager_submit: The pager from the view.
 *   $view: The view contents.
 *   $extra: All other elements that have been added.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>

<div class="entityreference-view-widget">
  <?php if ($selected_items): ?>
    <div class="widget-left">
      <div class="widget-selected-items"><?php print($selected_items); ?></div>
    </div>
    <div class="widget-right">
  <?php else: ?>
    <div class="widget-full">
  <?php endif; ?>
    <div class="inner">
      <?php if ($filters): ?>
        <div class="widget-filters"><?php print($filters); ?></div>
      <?php endif; ?>

      <?php if ($view): ?>
        <div class="widget-view"><?php print($view); ?></div>
      <?php endif; ?>
      <div class="widget-bottom">
        <?php if ($filters || $pager_submit): ?>
          <?php if ($pager_submit): ?>
            <div class="widget-pager-submit"><?php print($pager_submit); ?></div>
          <?php endif; ?>
          <?php if ($extra): ?>
            <div class="widget-extra"><?php print($extra); ?></div>
          <?php endif; ?>
        <?php endif; ?>
      </div>
    </div><!-- /.inner -->
  </div><!-- /.widget-right, /.widget-full -->
</div>
